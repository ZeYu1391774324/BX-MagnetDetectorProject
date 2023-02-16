#include "displaywork.h"
#include "loadingdialog.h"

DisplayWork::DisplayWork()
{

}


void DisplayWork::restartCommand(){
    currentIndex=0;
}

void DisplayWork::jumpCommand(int num){
    if(num<=frameList.length()&&num>0){
        currentIndex=num-1;
    }
}



void DisplayWork::readFile(QString path){



    frameList.clear();
    filePath=path;
    ifstream file;
    file.open(filePath.toStdString(),ios::in|ios::binary);
    file.seekg(0,ios_base::end);
    streampos filesize=file.tellg();
    int dataSize_char=filesize;
    file.seekg(0,ios_base::beg);

    char* charData=new char[dataSize_char];
    emit this->readingSignal();
    file.read((char*)charData,sizeof(char)*dataSize_char);

    if(this->parameters->encrypted){
        data=this->bytestohexstring_Unencrypt(charData,dataSize_char);
    }
    else{
        data=this->bytestohexstring_pure(charData,dataSize_char);
    }

//    while (data.contains("55AA55AA")&&data.contains("AA55AA55")) {
//        frameList.append(data.mid(data.indexOf("55AA55AA"),data.indexOf("AA55AA55")+4));
//        data.remove(0,data.indexOf("AA55AA55")+4);
//    }
//    frameList=data.split(QString("AA55AA55"));

    int i = 0;
    while(i<=data.lastIndexOf("55AA55AA")){
        frameList.append(data.mid(i,parameters->frameLength_hard));
        i+=parameters->frameLength_hard;
    }
    int frameNum=frameList.length();
    emit this->newFrameNum(frameNum);

    delete[](charData);
    data.clear();

}

QString DisplayWork::bytestohexstring_pure(char* bytes,int bytelength){
    QString str("");
    QString result("");
    QString str2("0123456789ABCDEF");
    QString d1,d2,d3,d4;
    char low,high,temp;

    for (int i=0;i<bytelength;i++) {

      int b;
      b = 0x0f&(bytes[i]>>4);
      //char s1 = str2.at(b);
      result.append(str2.at(b));
      b = 0x0f & bytes[i];
      result.append(str2.at(b));
      //char s2 = str2.at(b);
    }

    return result;
}

QString DisplayWork::bytestohexstring_Unencrypt(char* bytes,int bytelength){
    QString str("");
    QString result("");
    QString str2("0123456789ABCDEF");
    QString d1,d2,d3,d4;
    char low,high,temp;
  /*
    for (int i=0;i<bytelength;i++) {

      int b;
      b = 0x0f&(bytes[i]>>4);
      //char s1 = str2.at(b);
      result.append(1,str2.at(b));
      b = 0x0f & bytes[i];
      result.append(1,str2.at(b));
      //char s2 = str2.at(b);
    }
  */

      //解密

     for (int i=0;i<bytelength;i++) {
       low=bytes[i]&0x01;
       high=bytes[i]>>7&0x01;
       temp=(bytes[i]&0x7E)|high|((low<<7)&0xFF);

       int b;
       b = 0x0f&(temp>>4);
       //char s1 = str2.at(b);
       str.append(str2.at(b));
       b = 0x0f & temp;
       str.append(str2.at(b));
       //char s2 = str2.at(b);
     }
     for (int j = 0; j < str.length()/8; ++j) {
         d1=str.mid(8*j,2);
         d2=str.mid(8*j+2,2);
         d3=str.mid(8*j+4,2);
         d4=str.mid(8*j+6,2);
         result.append(d2);
         result.append(d4);
         result.append(d1);
         result.append(d3);
     }

     return result;
}

void DisplayWork::getCurrentFrame(){
    if(frameList.isEmpty()){
        return;
    }
    if(currentIndex>=frameList.length()){
        currentIndex=0;
    }
    currentFrame=frameList.at(currentIndex);
    currentIndex++;
}

void DisplayWork::uncodeFrame(){

        getCurrentFrame();
        if(this->currentFrame.isEmpty()){
            return;
        }
        QString frame=currentFrame;                         //更新当前帧


        if(parameters->pipeType=="变形"){
            //解码取信息过程
            this->bxData.append(currentIndex);
            this->bxData.append(this->bxDataExtract(frame.mid(parameters->dataPara.data1_18_start,parameters->dataPara.data1_18_len)));     //1-18路
            this->bxData.append(this->bxDataExtract(frame.mid(parameters->dataPara.data19_36_start,parameters->dataPara.data19_36_len)));    //19-36路
            this->bxData.append(this->bxDataExtract(frame.mid(parameters->dataPara.data37_54_start,parameters->dataPara.data37_54_len)));    //37-54路
            /*
                55：环境温度；     56：处理板温度；        57：姿态检测温度；
                58：优选里程脉冲；  59：原始里程脉冲1；     60：原始里程脉冲2；     61：原始里程脉冲3；
                62：周向角         63：倾角；             64：航向角；
            */
            this->bxData.append(this->temperatureDataExtract(frame));       //环境温度提取
            this->bxData.append(this->distanceDataExtract(frame));          //里程信息提取
            this->bxData.append(this->positionDataExtract(frame));          //姿态信息提取



            emit this->newBxData(this->bxData);
            this->bxData.clear();
        }

        else if(parameters->pipeType=="漏磁"){
            this->MFLData.append(currentIndex);
            this->MFLData.append(this->MFLDataExtract(frame));
            this->MFLData.append(this->temperatureDataExtract(frame));       //环境温度提取
            this->MFLData.append(this->distanceDataExtract(frame));          //里程信息提取
            this->MFLData.append(this->positionDataExtract(frame));          //姿态信息提取

            emit this->newMFLData(this->MFLData);
            this->MFLData.clear();
        }



}

void DisplayWork::uncodeFrame_additional(){

    if(currentFrame.isEmpty()){
        return;
    }
    QString frame = currentFrame;


    //解码取信息
    /*
        时钟脉冲计数
        24V系统供电电压
        24V系统供电电流
        电池组已用电量
        电池累计通电次数
        电池累计通电时间
        电池组额定电量
        电池更换时间
        电池模块环境温度
        供电方式
        5V二次电源电压
        3.3V二次电源电压
    */
    bool flag;
    bxData_additional["时钟脉冲计数"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.clock_start,parameters->addData.clock_len)).toUInt(&flag,16));
    bxData_additional["24V系统供电电压"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.Volt24V_start,parameters->addData.Volt24V_len)).toUInt(&flag,16)*parameters->addData.Volt_24V_para);
    bxData_additional["24V系统供电电流"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.Current_24V_start,parameters->addData.Current_24V_len)).toUInt(&flag,16)*parameters->addData.Current_24V_para);
    bxData_additional["电池组已用电量"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.batUsed_start,parameters->addData.batUsed_len)).toUInt(&flag,16)*parameters->addData.batUsed_para);
    bxData_additional["电池累计通电次数"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.batUsedTimes_start,parameters->addData.batUsedTimes_len)).toUInt(&flag,16));
    bxData_additional["电池累计通电时间"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.batUsedTimelen_start,parameters->addData.batUsedTimelen_len)).toUInt(&flag,16)*parameters->addData.batUsedTimelen_para);
    bxData_additional["电池组额定电量"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.batVolume_start,parameters->addData.batVolume_len)).toUInt(&flag,16)*parameters->addData.batVolume_para);
    int year,month,day;
    year=frame.mid(parameters->addData.timeYear_start,parameters->addData.timeYear_len).toUInt(&flag,16);
    month=frame.mid(parameters->addData.timeMonth_start,parameters->addData.timeMonth_len).toUInt(&flag,16);
    day=frame.mid(parameters->addData.timeDay_start,parameters->addData.timeDay_len).toUInt(&flag,16);
    bxData_additional["电池更换时间"]=QString("%1年%2月%3日").arg(year).arg(month).arg(day);
    bxData_additional["电池模块环境温度"]=QString("%1").arg(parameters->tempData.envirPara1-(parameters->tempData.envirPara2*BindData::frameReverse(frame.mid(parameters->tempData.tempEnvir_start,parameters->tempData.tempEnvir_len)).toUInt(&flag,16)));
    QString batteryMode,batteryModeSubFrame;
    batteryModeSubFrame=frame.mid(parameters->addData.batMode_start,parameters->addData.batMode_len);
    if(batteryModeSubFrame.toInt(&flag,16)==0xBB){
        batteryMode="内电源";
    }
    else if (batteryModeSubFrame.toInt(&flag,16)==0xCC) {
        batteryMode="外电源";
    }
    else {
        batteryMode="N/A";
    }
    bxData_additional["供电方式"]=batteryMode;
    bxData_additional["5V二次电源电压"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.Volt5V_start,parameters->addData.Volt5V_len)).toUInt(&flag,16)*parameters->addData.Volt5V_para);
    bxData_additional["3.3V二次电源电压"]=QString("%1").arg(BindData::frameReverse(frame.mid(parameters->addData.Volt3V_start,parameters->addData.Volt3V_len)).toUInt(&flag,16)*parameters->addData.Volt3V_para);

    emit this->newBxDataAdditional(bxData_additional);
    this->bxData_additional.clear();

}

QList<double> DisplayWork::MFLDataExtract(QString frame){
    QList<double> frameData;
    bool flag;
    for (int i = 1; i <= parameters->dataPara_MFL.MFLData_num; ++i) {
        int startPtr=parameters->dataPara_MFL.MFLData_start+(i-1)*parameters->dataPara_MFL.MFLData_len;
        for (int j = 0; j < MFLCHANNELNUM; ++j) {
            int currentPtr=startPtr+j*8;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((tempFrame.toInt(&flag,16)&0x0fff)/4));
        }
    }
    return frameData;
}



QList<double> DisplayWork::bxDataExtract(QString subframe){
    QList<double> subframeData;
    bool flag;
    for (int  i= 0; i < subframe.length(); i+=4) {
        subframeData.append((double)(BindData::frameReverse(subframe.mid(i,4)).toUInt(&flag,16)&0x0fff)*5/4096);       // 低12位/4096*5
        //subframeData.append(subframe.mid(i,4).right(3).toDouble()*5/4096);       // 低12位/4096*5
    }
    return subframeData;
}

QList<double> DisplayWork::temperatureDataExtract(QString frame){
    //环境温度，处理板温度，姿态温度
    QList<double> output;
    double temperature_environment,temperature_panel,temperature_position;
    QString subframe_TempEnvir,subframe_TempPanel,subframe_TempPos;
    subframe_TempEnvir=BindData::frameReverse(frame.mid(parameters->tempData.tempEnvir_start,parameters->tempData.tempEnvir_len));     //unsigned
    subframe_TempPanel=BindData::frameReverse(frame.mid(parameters->tempData.tempPanel_start,parameters->tempData.tempPanel_len));    //signed
    subframe_TempPos=BindData::frameReverse(frame.mid(parameters->tempData.tempPos_start,parameters->tempData.tempPos_len));      //signed
    bool flag;
    temperature_environment=parameters->tempData.envirPara1-(parameters->tempData.envirPara2*subframe_TempEnvir.toUInt(&flag,16));
    temperature_panel=subframe_TempPanel.toInt(&flag,16)*parameters->tempData.panelPara;
    temperature_position=subframe_TempPos.toInt(&flag,16)*parameters->tempData.positionPara;
    output.append(temperature_environment);
    output.append(temperature_panel);
    output.append(temperature_position);
    return output;

}

QList<double> DisplayWork::distanceDataExtract(QString frame){
    //优选里程，原始里程1,2,3
    QList<double> output;
    double distance_optimized,distance_1,distance_2,distance_3;
    QString subframe_opt,subframe_d1,subframe_d2,subframe_d3;
    subframe_opt=BindData::frameReverse(frame.mid(parameters->disData.opt_start,parameters->disData.opt_len));
    subframe_d1=BindData::frameReverse(frame.mid(parameters->disData.dis1_start,parameters->disData.dis1_len));
    subframe_d2=BindData::frameReverse(frame.mid(parameters->disData.dis2_start,parameters->disData.dis2_len));
    subframe_d3=BindData::frameReverse(frame.mid(parameters->disData.dis3_start,parameters->disData.dis3_len));
    bool flag;
    distance_optimized=subframe_opt.toUInt(&flag,16);
    distance_1=subframe_d1.toUInt(&flag,16);
    distance_2=subframe_d2.toUInt(&flag,16);
    distance_3=subframe_d3.toUInt(&flag,16);
    output.append(distance_optimized);
    output.append(distance_1);
    output.append(distance_2);
    output.append(distance_3);
    return output;
}

QList<double> DisplayWork::positionDataExtract(QString frame){
    //姿态周向角，倾角，航向角，加速度
    QList<double> output;
    double ZXJ,QJ,HXJ;
    QString subframe_ZXJ,subframe_QJ,subframe_HXJ;
    subframe_ZXJ=BindData::frameReverse(frame.mid(parameters->posData.ZXJ_start,parameters->posData.ZXJ_len));
    subframe_QJ=BindData::frameReverse(frame.mid(parameters->posData.QJ_start,parameters->posData.QJ_len));
    subframe_HXJ=BindData::frameReverse(frame.mid(parameters->posData.HXJ_start,parameters->posData.HXJ_len));
    bool flag;
    ZXJ=subframe_ZXJ.toInt(&flag,16)*parameters->posData.ZXJpara;
    QJ=subframe_QJ.toInt(&flag,16)*parameters->posData.QJpara;
    HXJ=subframe_HXJ.toInt(&flag,16)*parameters->posData.HXJpara;
    output.append(ZXJ);
    output.append(QJ);
    output.append(HXJ);
    return output;

}

void DisplayWork::setParameters(ParaGet* para){
    this->parameters=para;
}

