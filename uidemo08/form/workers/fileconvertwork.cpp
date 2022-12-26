#include "fileconvertwork.h"

FileConvertWork::FileConvertWork()
{

}

void FileConvertWork::initParameters(ParaGet_hard *para){
    this->parameters=para;
}

void FileConvertWork::convertFiles(){
    for (int i = 0; i < this->localfilelist->length(); ++i) {
        if(localfilelist->at(i).localFileSelectedFlag){
            this->HexToDecimalFile(localfilelist->at(i));
        }
        else {
            continue;
        }

    }

}

void FileConvertWork::HexToDecimalFile(localFile file){
    //read file
    QString hexData;
    QString filepath=file.localFilePath;
    ifstream ifs;
    ifs.open(filepath.toStdString(),ios::in|ios::binary);
    //获取文件长度
    ifs.seekg(0,ios_base::end);
    streampos filetailpos=ifs.tellg();
    int filesize_char=filetailpos;
    ifs.seekg(0,ios_base::beg);

    char* byteDataArray= new char[filesize_char];
    ifs.read(byteDataArray,filesize_char);
    string hexList("0123456789ABCDEF");

    for (int i=0;i<filesize_char;i++) {
      int b;
      b = 0x0f&(byteDataArray[i]>>4);
      hexData.append(hexList.at(b));
      b = 0x0f & byteDataArray[i];
      hexData.append(hexList.at(b));
    }

    hexData=BindData::hardUnencrypt(hexData);   //解码
    delete[](byteDataArray);


    /********** 数据解析 **********/
    int frameNum=hexData.length()/parameters->frameLength_hard;
    int frameCount=1;
    int fileCount=1;
    QStringList typelist,sizelist;
    typelist<<"请选择产品类型"<<"变形"<<"漏磁";
    sizelist<<"请选择产品尺寸"<<"8inch"<<"10inch"<<"12inch"<<"14inch";
    switch (typelist.indexOf(parameters->pipeType)) {
    case 0:
        break;
    case 1: //变形
        switch (sizelist.indexOf(parameters->pipeSize)) {
        case 0:
            break;
        case 1:
            break;
        case 2:         //10inch-变形
        {
            QList <double> DecimalData;
            double dis_opt,clock,Volt24_voltage;
            QList<double> bxData;
            double temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;
            bool flag;
            for (int i = STARTPOINT-1; i < frameNum; ++i) {
                QString currentFrame=hexData.mid(i*parameters->frameLength_hard,parameters->frameLength_hard);
                //优选里程
                dis_opt=BindData::frameReverse(currentFrame.mid(parameters->disData.opt_start,parameters->disData.opt_len)).toInt(&flag,16);
                //时钟
                clock=BindData::frameReverse(currentFrame.mid(parameters->dataPara.clock_start,parameters->dataPara.clock_len)).toInt(&flag,16);
                //24v
                Volt24_voltage=BindData::frameReverse(currentFrame.mid(parameters->addData.Volt24V_start,parameters->addData.Volt24V_len)).toUInt(&flag,16)*parameters->addData.Volt_24V_para;
                //bxData(1-36路)
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters->dataPara.data1_18_start,parameters->dataPara.data1_18_len)));
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters->dataPara.data19_36_start,parameters->dataPara.data19_36_len)));
                //信号板温度
                temp_bat=parameters->tempData.envirPara1-(parameters->tempData.envirPara2*BindData::frameReverse(currentFrame.mid(parameters->tempData.tempEnvir_start,parameters->tempData.tempEnvir_len)).toInt(&flag,16));
                //处理板温度
                temp_panel=BindData::frameReverse(currentFrame.mid(parameters->tempData.tempPanel_start,parameters->tempData.tempPanel_len)).toInt(&flag,16)*parameters->tempData.panelPara;
                //姿态温度
                temp_pos=BindData::frameReverse(currentFrame.mid(parameters->tempData.tempPos_start,parameters->tempData.tempPos_len)).toInt(&flag,16)*parameters->tempData.positionPara;
                //周向角
                ZXJ=BindData::frameReverse(currentFrame.mid(parameters->posData.ZXJ_start,parameters->posData.ZXJ_len)).toInt(&flag,16)*parameters->posData.ZXJpara;
                //倾角
                QJ=BindData::frameReverse(currentFrame.mid(parameters->posData.QJ_start,parameters->posData.QJ_len)).toInt(&flag,16)*parameters->posData.QJpara;
                //航向角
                HXJ=BindData::frameReverse(currentFrame.mid(parameters->posData.HXJ_start,parameters->posData.HXJ_len)).toInt(&flag,16)*parameters->posData.HXJpara;
                //X加速度
                acc_x=BindData::frameReverse(currentFrame.mid(parameters->addData.accX_start,parameters->addData.accX_len)).toInt(&flag,16)*parameters->addData.accX_para;
                //Y加速度
                acc_y=BindData::frameReverse(currentFrame.mid(parameters->addData.accY_start,parameters->addData.accY_len)).toInt(&flag,16)*parameters->addData.accY_para;
                //Z加速度
                acc_x=BindData::frameReverse(currentFrame.mid(parameters->addData.accZ_start,parameters->addData.accZ_len)).toInt(&flag,16)*parameters->addData.accZ_para;
                //里程1
                dis_1=BindData::frameReverse(currentFrame.mid(parameters->disData.dis1_start,parameters->disData.dis1_len)).toInt(&flag,16);
                //里程2
                dis_2=BindData::frameReverse(currentFrame.mid(parameters->disData.dis2_start,parameters->disData.dis2_len)).toInt(&flag,16);
                //里程3
                dis_3=BindData::frameReverse(currentFrame.mid(parameters->disData.dis3_start,parameters->disData.dis3_len)).toInt(&flag,16);
                //status
                stat=currentFrame.mid(parameters->addData.status_start,parameters->addData.status_len).toUInt(&flag,16);

                //拼接十进制文件数据
                /*  dis_opt,clock,Volt24_voltage;
                    QList<double> bxData;
                    temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;*/
                DecimalData.append(dis_opt);
                DecimalData.append(clock);
                DecimalData.append(Volt24_voltage);
                DecimalData.append(bxData);
                DecimalData.append(temp_bat);
                DecimalData.append(temp_panel);
                DecimalData.append(temp_pos);
                DecimalData.append(ZXJ);
                DecimalData.append(QJ);
                DecimalData.append(HXJ);
                DecimalData.append(acc_x);
                DecimalData.append(acc_y);
                DecimalData.append(acc_z);
                DecimalData.append(dis_1);
                DecimalData.append(dis_2);
                DecimalData.append(dis_3);
                DecimalData.append(stat);

                //写文件
                ofstream ofs;
                QString outputPath=SavePath.append(QString("%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf(".")),fileCount));
                ofs.open(outputPath.toStdString(),ios::out|ios::binary|ios::app);
                int outputSize_double=DecimalData.length();
                double *outByteArray=new double[outputSize_double];
                for (int j = 0; j < outputSize_double; ++j) {
                    outByteArray[j]=DecimalData.at(j);
                }
                ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                ofs.close();
                delete[](outByteArray);
                frameCount++;
                if(frameCount>=DECIMALFILEFRAMENUM_MAX){
                    fileCount++;
                    frameCount=0;
                }
                emit this->fileConvertProcess(((double)(i/frameNum))*100);

            }
            ifs.close();

        }
            break;
        default:
            break;
        }
        break;
    case 2: //漏磁
        break;
    default:
        break;
    }





}

QList<double> FileConvertWork::bxDataExtract(QString subframe){
    QList<double> subframeData;
    bool flag;
    for (int  i= 0; i < subframe.length(); i+=4) {
        subframeData.append((double)(BindData::frameReverse(subframe.mid(i,4)).toUInt(&flag,16)&0x0fff)*5/4096);       // 低12位/4096*5
        //subframeData.append(subframe.mid(i,4).right(3).toDouble()*5/4096);       // 低12位/4096*5
    }
    return subframeData;
}

void FileConvertWork::updateLocalFileList(QList<localFile> *newList){
    this->localfilelist=newList;
}

void FileConvertWork::updateSavePath(QString newSavePath){
    this->SavePath=newSavePath;
}
