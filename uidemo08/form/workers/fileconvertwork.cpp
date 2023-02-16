#include "fileconvertwork.h"

FileConvertWork::FileConvertWork()
{
//    QTimer *timer = new QTimer;     //每个半秒上传文件转换进度
//    timer->start(500);
//    connect(timer,&QTimer::timeout,[=](){
//        emit this->fileConvertProcess(this->process);
//    });


}

void FileConvertWork::initParameters(ParaGet_hard *para){
    this->parameters=*para;
}

void FileConvertWork::convertFiles(){
    int count=0;
    int total=0;
    this->restData.clear();
    for (int i = 0; i < localfilelist.length(); ++i) {
        if(localfilelist.at(i).localFileSelectedFlag){
            total++;
        }
    }

    for (int i = 0; i < this->localfilelist.length(); ++i) {
        if(localfilelist.at(i).localFileSelectedFlag){

            qDebug()<<QString("正在转换文件%1").arg(localfilelist.at(i).localFilePath);
            if(parameters.encrypted){
                qDebug()<<QString("系统产品变量：%1-%2-加密").arg(parameters.pipeSize,parameters.pipeType);
            }
            else {
                qDebug()<<QString("系统产品变量：%1-%2-未加密").arg(parameters.pipeSize,parameters.pipeType);
            }

            count++;
            emit this->fileConvertProgress_total(count,total);

            //return -1：转换失败； return 0：已转换； return 1：未转换；
            //flag 1=进管文件，2=出管文件，3=既是进管文件又是出管文件，0=中间文件；
            int flag;
            if(total==1){//仅一个文件时为既进管又出管文件
                flag=3;
            }
            else if((total>1)&&(count==1)){//第一个文件为进管文件
                flag=1;
            }
            else if((total>1)&&(count==total)){//最后一个文件为出管文件
                flag=2;
            }
            else{
                flag=0;
            }

            int convertFlag = this->HexToDecimalFile(localfilelist.at(i),flag);

            if(convertFlag==-1){
                emit this->fileConvertedIndex(i,"转换失败");
            }
            else if(convertFlag==0){
                emit this->fileConvertedIndex(i,"已转换");
            }
            else if(convertFlag==1){
                emit this->fileConvertedIndex(i,"未转换");
            }
        }
        else {
            continue;
        }

    }
    emit this->workFinished();

}

int FileConvertWork::HexToDecimalFile(localFile file, int fileFlag){      //return -1：转换失败； return 0：已转换； return 1：未转换；
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

    emit this->newInfo("文件读取中，请稍后...");
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
    emit this->newInfo("文件读取完成...");
    if(parameters.encrypted){
        emit this->newInfo("文件解码中，请稍后...");
        hexData=this->hardUnencrypt(hexData);   //解码
        emit this->newInfo("文件解码完成...");
    }

    delete[](byteDataArray);


    /********** 数据解析 **********/
    if(hexData.length()%parameters.frameLength_hard!=0){
        qDebug()<<"数据文件与参数设置不匹配！";
        return -1; // 转换失败
    }
    int frameNum=hexData.length()/parameters.frameLength_hard;
    int fileNum=ceil(frameNum/DECIMALFILEFRAMENUM_MAX);
    if(fileFlag==1||fileFlag==3){
        frameCount=0;
    }
    int fileCount=0;
    QStringList typelist,sizelist;
    typelist<<"请选择产品类型"<<"变形"<<"漏磁";
    sizelist<<"请选择产品尺寸"<<"8inch"<<"10inch"<<"12inch"<<"14inch";
    switch (typelist.indexOf(parameters.pipeType)) {
    case 0:
        break;
    case 1: //变形
        switch (sizelist.indexOf(parameters.pipeSize)) {
        case 0:
            break;
        case 1:         //8inch-变形
        {
/******************************************************** 8inch-变形 Start ****************************************************************************/
            QList <double> DecimalData;
            //前一文件续写
            if(!this->restData.isEmpty()){
                DecimalData.append(restData);
                this->restData.clear();
            }
            double dis_opt,clock,Volt24_voltage;
            QList<double> bxData;
            double temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;
            bool flag;
            ofstream ofs;
            emit this->newInfo("数据提取中，请稍后...");
            int i;
            if((fileFlag==1)||(fileFlag==3)){// 1||3为进管文件
                i = STARTPOINT-1;   // 进管文件舍去前六帧
            }
            else {
                i=0;
            }
            for (i ; i < frameNum; ++i)
            {
                QString currentFrame=hexData.mid(i*parameters.frameLength_hard,parameters.frameLength_hard);
                //优选里程
                dis_opt=BindData::frameReverse(currentFrame.mid(parameters.disData.opt_start,parameters.disData.opt_len)).toULongLong(&flag,16);
                //时钟
                clock=BindData::frameReverse(currentFrame.mid(parameters.dataPara.clock_start,parameters.dataPara.clock_len)).toULongLong(&flag,16);

                //24v
                Volt24_voltage=BindData::frameReverse(currentFrame.mid(parameters.addData.Volt24V_start,parameters.addData.Volt24V_len)).toUInt(&flag,16)*parameters.addData.Volt_24V_para;
                //bxData(1-36路)
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data1_18_start,parameters.dataPara.data1_18_len)));
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data19_36_start,parameters.dataPara.data19_36_len)));
                //信号板温度
                temp_bat=parameters.tempData.envirPara1-(parameters.tempData.envirPara2*BindData::frameReverse(currentFrame.mid(parameters.tempData.tempEnvir_start,parameters.tempData.tempEnvir_len)).toInt(&flag,16));
                //处理板温度
                temp_panel=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPanel_start,parameters.tempData.tempPanel_len)).toInt(&flag,16)*parameters.tempData.panelPara;
                //姿态温度
                temp_pos=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPos_start,parameters.tempData.tempPos_len)).toInt(&flag,16)*parameters.tempData.positionPara;
                //周向角
                ZXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.ZXJ_start,parameters.posData.ZXJ_len)).toInt(&flag,16)*parameters.posData.ZXJpara;
                //倾角
                QJ=BindData::frameReverse(currentFrame.mid(parameters.posData.QJ_start,parameters.posData.QJ_len)).toInt(&flag,16)*parameters.posData.QJpara;
                //航向角
                HXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.HXJ_start,parameters.posData.HXJ_len)).toInt(&flag,16)*parameters.posData.HXJpara;
                //X加速度
                acc_x=BindData::frameReverse(currentFrame.mid(parameters.addData.accX_start,parameters.addData.accX_len)).toInt(&flag,16)*parameters.addData.accX_para;
                //Y加速度
                acc_y=BindData::frameReverse(currentFrame.mid(parameters.addData.accY_start,parameters.addData.accY_len)).toInt(&flag,16)*parameters.addData.accY_para;
                //Z加速度
                acc_z=BindData::frameReverse(currentFrame.mid(parameters.addData.accZ_start,parameters.addData.accZ_len)).toInt(&flag,16)*parameters.addData.accZ_para;
                //里程1
                dis_1=BindData::frameReverse(currentFrame.mid(parameters.disData.dis1_start,parameters.disData.dis1_len)).toInt(&flag,16);
                //里程2
                dis_2=BindData::frameReverse(currentFrame.mid(parameters.disData.dis2_start,parameters.disData.dis2_len)).toInt(&flag,16);
                //里程3
                dis_3=BindData::frameReverse(currentFrame.mid(parameters.disData.dis3_start,parameters.disData.dis3_len)).toInt(&flag,16);
                //status
                stat=currentFrame.mid(parameters.addData.status_start,parameters.addData.status_len).toUInt(&flag,16);

                //拼接十进制文件数据
                /*  dis_opt,clock,Volt24_voltage;
                    QList<double> bxData;
                    temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;*/
                DecimalData.append(dis_opt);
                DecimalData.append(clock);
                DecimalData.append(Volt24_voltage);
                DecimalData.append(bxData);
                bxData.clear();
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
                frameCount++;
                emit this->fileConvertProcess((double)(frameCount%frameNum)/(double)frameNum*100);

                //写文件
//                int outputSize_double=DecimalData.length();
//                double *outByteArray=new double[outputSize_double];
//                for (int j = 0; j < outputSize_double; ++j) {
//                    outByteArray[j]=DecimalData.at(j);
//                }
//                if(frameCount%50000==1){
//                    ofs.close();
//                    fileCount++;
//                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
//                    ofs.open(outputPath.toStdString(),ios::app|ios::binary);
//                }
//                ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
//                delete[](outByteArray);
//                DecimalData.clear();

                // 写文件
                if(frameCount%50000==0){
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    delete[](outByteArray);
                    DecimalData.clear();
                    ofs.close();
                }
            }
            if(!DecimalData.isEmpty()){
                if((fileFlag==2)||(fileFlag==3)){       //如果是出管文件写剩余文件
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    //写剩余文件
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    ofs.close();
                    delete[](outByteArray);
                    DecimalData.clear();
                }
                else { //其他文件在下一文件中续写
                    this->restData.append(DecimalData);
                    DecimalData.clear();
                }

            }
            ofs.close();
            ifs.close();
            emit this->newInfo("文件转换完成！");
            return 0; //已转换

/******************************************************** 8inch-变形 End ****************************************************************************/

        }
            break;

        case 2:         //10inch-变形
        {
/******************************************************** 10inch-变形 Start ****************************************************************************/
            QList <double> DecimalData;
            //前一文件续写
            if(!this->restData.isEmpty()){
                DecimalData.append(restData);
                this->restData.clear();
            }
            double dis_opt,clock,Volt24_voltage;
            QList<double> bxData;
            double temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;
            bool flag;
            ofstream ofs;
            emit this->newInfo("数据提取中，请稍后...");
            int i;
            if((fileFlag==1)||(fileFlag==3)){// 1||3为进管文件
                i = STARTPOINT-1;   // 进管文件舍去前六帧
            }
            else {
                i=0;
            }
            for (i ; i < frameNum; ++i)
            {
                QString currentFrame=hexData.mid(i*parameters.frameLength_hard,parameters.frameLength_hard);
                //优选里程
                dis_opt=BindData::frameReverse(currentFrame.mid(parameters.disData.opt_start,parameters.disData.opt_len)).toULongLong(&flag,16);
                //时钟
                clock=BindData::frameReverse(currentFrame.mid(parameters.dataPara.clock_start,parameters.dataPara.clock_len)).toULongLong(&flag,16);
                //24v
                Volt24_voltage=BindData::frameReverse(currentFrame.mid(parameters.addData.Volt24V_start,parameters.addData.Volt24V_len)).toUInt(&flag,16)*parameters.addData.Volt_24V_para;
                //bxData(1-36路)
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data1_18_start,parameters.dataPara.data1_18_len)));
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data19_36_start,parameters.dataPara.data19_36_len)));
                //信号板温度
                temp_bat=parameters.tempData.envirPara1-(parameters.tempData.envirPara2*BindData::frameReverse(currentFrame.mid(parameters.tempData.tempEnvir_start,parameters.tempData.tempEnvir_len)).toInt(&flag,16));
                //处理板温度
                temp_panel=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPanel_start,parameters.tempData.tempPanel_len)).toInt(&flag,16)*parameters.tempData.panelPara;
                //姿态温度
                temp_pos=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPos_start,parameters.tempData.tempPos_len)).toInt(&flag,16)*parameters.tempData.positionPara;
                //周向角
                ZXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.ZXJ_start,parameters.posData.ZXJ_len)).toInt(&flag,16)*parameters.posData.ZXJpara;
                //倾角
                QJ=BindData::frameReverse(currentFrame.mid(parameters.posData.QJ_start,parameters.posData.QJ_len)).toInt(&flag,16)*parameters.posData.QJpara;
                //航向角
                HXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.HXJ_start,parameters.posData.HXJ_len)).toInt(&flag,16)*parameters.posData.HXJpara;
                //X加速度
                acc_x=BindData::frameReverse(currentFrame.mid(parameters.addData.accX_start,parameters.addData.accX_len)).toInt(&flag,16)*parameters.addData.accX_para;
                //Y加速度
                acc_y=BindData::frameReverse(currentFrame.mid(parameters.addData.accY_start,parameters.addData.accY_len)).toInt(&flag,16)*parameters.addData.accY_para;
                //Z加速度
                acc_z=BindData::frameReverse(currentFrame.mid(parameters.addData.accZ_start,parameters.addData.accZ_len)).toInt(&flag,16)*parameters.addData.accZ_para;
                //里程1
                dis_1=BindData::frameReverse(currentFrame.mid(parameters.disData.dis1_start,parameters.disData.dis1_len)).toInt(&flag,16);
                //里程2
                dis_2=BindData::frameReverse(currentFrame.mid(parameters.disData.dis2_start,parameters.disData.dis2_len)).toInt(&flag,16);
                //里程3
                dis_3=BindData::frameReverse(currentFrame.mid(parameters.disData.dis3_start,parameters.disData.dis3_len)).toInt(&flag,16);
                //status
                stat=currentFrame.mid(parameters.addData.status_start,parameters.addData.status_len).toUInt(&flag,16);

                //拼接十进制文件数据
                /*  dis_opt,clock,Volt24_voltage;
                    QList<double> bxData;
                    temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;*/
                DecimalData.append(dis_opt);
                DecimalData.append(clock);
                DecimalData.append(Volt24_voltage);
                DecimalData.append(bxData);
                bxData.clear();
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
                frameCount++;
                emit this->fileConvertProcess((double)(frameCount%frameNum)/(double)frameNum*100);

                //写文件
//                int outputSize_double=DecimalData.length();
//                double *outByteArray=new double[outputSize_double];
//                for (int j = 0; j < outputSize_double; ++j) {
//                    outByteArray[j]=DecimalData.at(j);
//                }
//                if(frameCount%50000==1){
//                    ofs.close();
//                    fileCount++;
//                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
//                    ofs.open(outputPath.toStdString(),ios::app|ios::binary);
//                }
//                ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
//                delete[](outByteArray);
//                DecimalData.clear();

                // 写文件
                if(frameCount%50000==0){
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    delete[](outByteArray);
                    DecimalData.clear();
                    ofs.close();
                }
            }
            if(!DecimalData.isEmpty()){
                if((fileFlag==2)||(fileFlag==3)){       //如果是出管文件写剩余文件
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    //写剩余文件
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    ofs.close();
                    delete[](outByteArray);
                    DecimalData.clear();
                }
                else { //其他文件在下一文件中续写
                    this->restData.append(DecimalData);
                    DecimalData.clear();
                }

            }
            ofs.close();
            ifs.close();
            emit this->newInfo("文件转换完成！");
            return 0; //已转换

/******************************************************** 10inch-变形 End ****************************************************************************/

        }
            break;
        case 3: //12inch-变形
        {
/******************************************************** 12inch-变形 Start ****************************************************************************/
            QList <double> DecimalData;
            //前一文件续写
            if(!this->restData.isEmpty()){
                DecimalData.append(restData);
                this->restData.clear();
            }
            double dis_opt,clock,Volt24_voltage;
            QList<double> bxData;
            double temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;
            bool flag;
            ofstream ofs;
            emit this->newInfo("数据提取中，请稍后...");
            int i;
            if((fileFlag==1)||(fileFlag==3)){// 1||3为进管文件
                i = STARTPOINT-1;   // 进管文件舍去前六帧
            }
            else {
                i=0;
            }
            for (i ; i < frameNum; ++i)
            {
                QString currentFrame=hexData.mid(i*parameters.frameLength_hard,parameters.frameLength_hard);
                //优选里程
                dis_opt=BindData::frameReverse(currentFrame.mid(parameters.disData.opt_start,parameters.disData.opt_len)).toULongLong(&flag,16);
                //时钟
                clock=BindData::frameReverse(currentFrame.mid(parameters.dataPara.clock_start,parameters.dataPara.clock_len)).toULongLong(&flag,16);
                //24v
                Volt24_voltage=BindData::frameReverse(currentFrame.mid(parameters.addData.Volt24V_start,parameters.addData.Volt24V_len)).toUInt(&flag,16)*parameters.addData.Volt_24V_para;
                //bxData(1-36路)
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data1_18_start,parameters.dataPara.data1_18_len)));
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data19_36_start,parameters.dataPara.data19_36_len)));
                //信号板温度
                temp_bat=parameters.tempData.envirPara1-(parameters.tempData.envirPara2*BindData::frameReverse(currentFrame.mid(parameters.tempData.tempEnvir_start,parameters.tempData.tempEnvir_len)).toInt(&flag,16));
                //处理板温度
                temp_panel=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPanel_start,parameters.tempData.tempPanel_len)).toInt(&flag,16)*parameters.tempData.panelPara;
                //姿态温度
                temp_pos=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPos_start,parameters.tempData.tempPos_len)).toInt(&flag,16)*parameters.tempData.positionPara;
                //周向角
                ZXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.ZXJ_start,parameters.posData.ZXJ_len)).toInt(&flag,16)*parameters.posData.ZXJpara;
                //倾角
                QJ=BindData::frameReverse(currentFrame.mid(parameters.posData.QJ_start,parameters.posData.QJ_len)).toInt(&flag,16)*parameters.posData.QJpara;
                //航向角
                HXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.HXJ_start,parameters.posData.HXJ_len)).toInt(&flag,16)*parameters.posData.HXJpara;
                //X加速度
                acc_x=BindData::frameReverse(currentFrame.mid(parameters.addData.accX_start,parameters.addData.accX_len)).toInt(&flag,16)*parameters.addData.accX_para;
                //Y加速度
                acc_y=BindData::frameReverse(currentFrame.mid(parameters.addData.accY_start,parameters.addData.accY_len)).toInt(&flag,16)*parameters.addData.accY_para;
                //Z加速度
                acc_z=BindData::frameReverse(currentFrame.mid(parameters.addData.accZ_start,parameters.addData.accZ_len)).toInt(&flag,16)*parameters.addData.accZ_para;
                //里程1
                dis_1=BindData::frameReverse(currentFrame.mid(parameters.disData.dis1_start,parameters.disData.dis1_len)).toInt(&flag,16);
                //里程2
                dis_2=BindData::frameReverse(currentFrame.mid(parameters.disData.dis2_start,parameters.disData.dis2_len)).toInt(&flag,16);
                //里程3
                dis_3=BindData::frameReverse(currentFrame.mid(parameters.disData.dis3_start,parameters.disData.dis3_len)).toInt(&flag,16);
                //status
                stat=currentFrame.mid(parameters.addData.status_start,parameters.addData.status_len).toUInt(&flag,16);

                //拼接十进制文件数据
                /*  dis_opt,clock,Volt24_voltage;
                    QList<double> bxData;
                    temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;*/
                DecimalData.append(dis_opt);
                DecimalData.append(clock);
                DecimalData.append(Volt24_voltage);
                DecimalData.append(bxData);
                bxData.clear();
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
                frameCount++;
                emit this->fileConvertProcess((double)(frameCount%frameNum)/(double)frameNum*100);

                //写文件
//                int outputSize_double=DecimalData.length();
//                double *outByteArray=new double[outputSize_double];
//                for (int j = 0; j < outputSize_double; ++j) {
//                    outByteArray[j]=DecimalData.at(j);
//                }
//                if(frameCount%50000==1){
//                    ofs.close();
//                    fileCount++;
//                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
//                    ofs.open(outputPath.toStdString(),ios::app|ios::binary);
//                }
//                ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
//                delete[](outByteArray);
//                DecimalData.clear();

                // 写文件
                if(frameCount%50000==0){
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    delete[](outByteArray);
                    DecimalData.clear();
                    ofs.close();
                }
            }
            if(!DecimalData.isEmpty()){
                if((fileFlag==2)||(fileFlag==3)){       //如果是出管文件写剩余文件
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    //写剩余文件
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    ofs.close();
                    delete[](outByteArray);
                    DecimalData.clear();
                }
                else { //其他文件在下一文件中续写
                    this->restData.append(DecimalData);
                    DecimalData.clear();
                }

            }
            ofs.close();
            ifs.close();
            emit this->newInfo("文件转换完成！");
            return 0; //已转换

/******************************************************** 12inch-变形 End ****************************************************************************/

        }
            break;

        case 4://14inch-变形
        {
/******************************************************** 14inch-变形 Start ****************************************************************************/
            QList <double> DecimalData;
            //前一文件续写
            if(!this->restData.isEmpty()){
                DecimalData.append(restData);
                this->restData.clear();
            }
            double dis_opt,clock,Volt24_voltage;
            QList<double> bxData;
            double temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;
            bool flag;
            ofstream ofs;
            emit this->newInfo("数据提取中，请稍后...");
            int i;
            if((fileFlag==1)||(fileFlag==3)){// 1||3为进管文件
                i = STARTPOINT-1;   // 进管文件舍去前六帧
            }
            else {
                i=0;
            }
            for (i ; i < frameNum; ++i)
            {
                QString currentFrame=hexData.mid(i*parameters.frameLength_hard,parameters.frameLength_hard);
                //优选里程
                dis_opt=BindData::frameReverse(currentFrame.mid(parameters.disData.opt_start,parameters.disData.opt_len)).toULongLong(&flag,16);
                //时钟
                clock=BindData::frameReverse(currentFrame.mid(parameters.dataPara.clock_start,parameters.dataPara.clock_len)).toULongLong(&flag,16);
                //24v
                Volt24_voltage=BindData::frameReverse(currentFrame.mid(parameters.addData.Volt24V_start,parameters.addData.Volt24V_len)).toUInt(&flag,16)*parameters.addData.Volt_24V_para;
                //bxData(1-36路)
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data1_18_start,parameters.dataPara.data1_18_len)));
                bxData.append(this->bxDataExtract(currentFrame.mid(parameters.dataPara.data19_36_start,parameters.dataPara.data19_36_len)));
                //信号板温度
                temp_bat=parameters.tempData.envirPara1-(parameters.tempData.envirPara2*BindData::frameReverse(currentFrame.mid(parameters.tempData.tempEnvir_start,parameters.tempData.tempEnvir_len)).toInt(&flag,16));
                //处理板温度
                temp_panel=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPanel_start,parameters.tempData.tempPanel_len)).toInt(&flag,16)*parameters.tempData.panelPara;
                //姿态温度
                temp_pos=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPos_start,parameters.tempData.tempPos_len)).toInt(&flag,16)*parameters.tempData.positionPara;
                //周向角
                ZXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.ZXJ_start,parameters.posData.ZXJ_len)).toInt(&flag,16)*parameters.posData.ZXJpara;
                //倾角
                QJ=BindData::frameReverse(currentFrame.mid(parameters.posData.QJ_start,parameters.posData.QJ_len)).toInt(&flag,16)*parameters.posData.QJpara;
                //航向角
                HXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.HXJ_start,parameters.posData.HXJ_len)).toInt(&flag,16)*parameters.posData.HXJpara;
                //X加速度
                acc_x=BindData::frameReverse(currentFrame.mid(parameters.addData.accX_start,parameters.addData.accX_len)).toInt(&flag,16)*parameters.addData.accX_para;
                //Y加速度
                acc_y=BindData::frameReverse(currentFrame.mid(parameters.addData.accY_start,parameters.addData.accY_len)).toInt(&flag,16)*parameters.addData.accY_para;
                //Z加速度
                acc_z=BindData::frameReverse(currentFrame.mid(parameters.addData.accZ_start,parameters.addData.accZ_len)).toInt(&flag,16)*parameters.addData.accZ_para;
                //里程1
                dis_1=BindData::frameReverse(currentFrame.mid(parameters.disData.dis1_start,parameters.disData.dis1_len)).toInt(&flag,16);
                //里程2
                dis_2=BindData::frameReverse(currentFrame.mid(parameters.disData.dis2_start,parameters.disData.dis2_len)).toInt(&flag,16);
                //里程3
                dis_3=BindData::frameReverse(currentFrame.mid(parameters.disData.dis3_start,parameters.disData.dis3_len)).toInt(&flag,16);
                //status
                stat=currentFrame.mid(parameters.addData.status_start,parameters.addData.status_len).toUInt(&flag,16);

                //拼接十进制文件数据
                /*  dis_opt,clock,Volt24_voltage;
                    QList<double> bxData;
                    temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;*/
                DecimalData.append(dis_opt);
                DecimalData.append(clock);
                DecimalData.append(Volt24_voltage);
                DecimalData.append(bxData);
                bxData.clear();
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
                frameCount++;
                emit this->fileConvertProcess((double)(frameCount%frameNum)/(double)frameNum*100);

                //写文件
//                int outputSize_double=DecimalData.length();
//                double *outByteArray=new double[outputSize_double];
//                for (int j = 0; j < outputSize_double; ++j) {
//                    outByteArray[j]=DecimalData.at(j);
//                }
//                if(frameCount%50000==1){
//                    ofs.close();
//                    fileCount++;
//                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
//                    ofs.open(outputPath.toStdString(),ios::app|ios::binary);
//                }
//                ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
//                delete[](outByteArray);
//                DecimalData.clear();

                // 写文件
                if(frameCount%50000==0){
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    delete[](outByteArray);
                    DecimalData.clear();
                    ofs.close();
                }
            }
            if(!DecimalData.isEmpty()){
                if((fileFlag==2)||(fileFlag==3)){       //如果是出管文件写剩余文件
                    int outputSize_double=DecimalData.length();
                    double *outByteArray=new double[outputSize_double];
                    for (int j = 0; j < outputSize_double; ++j) {
                        outByteArray[j]=DecimalData.at(j);
                    }
                    //写剩余文件
                    fileCount++;
                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                    ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                    ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                    ofs.close();
                    delete[](outByteArray);
                    DecimalData.clear();
                }
                else { //其他文件在下一文件中续写
                    this->restData.append(DecimalData);
                    DecimalData.clear();
                }

            }
            ofs.close();
            ifs.close();
            emit this->newInfo("文件转换完成！");
            return 0; //已转换

/******************************************************** 14inch-变形 End ****************************************************************************/

        }
            break;
        default:
            break;
        }
        break;
    case 2: //漏磁
        switch (sizelist.indexOf(parameters.pipeSize)) {
        case 0:
            break;
        case 3:         //12inch 漏磁
        {
        /******************************************************** 12inch-漏磁 Start ****************************************************************************/
                    QList <double> DecimalData;
                    //前一文件续写
                    if(!this->restData.isEmpty()){
                        DecimalData.append(restData);
                        this->restData.clear();
                    }
                    double dis_opt,clock,Volt24_voltage;
                    QList<double> MFLData;
                    double temp_bat,temp_panel,temp_pos,ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,dis_1,dis_2,dis_3,stat;
                    bool flag;
                    ofstream ofs;
                    emit this->newInfo("数据提取中，请稍后...");
                    int i;
                    if((fileFlag==1)||(fileFlag==3)){// 1||3为进管文件
                        i = STARTPOINT-1;   // 进管文件舍去前六帧
                    }
                    else {
                        i=0;
                    }
                    for (i ; i < frameNum; ++i)
                    {
                        QString currentFrame=hexData.mid(i*parameters.frameLength_hard,parameters.frameLength_hard);
                        //优选里程
                        dis_opt=currentFrame.mid(parameters.disData.opt_start,parameters.disData.opt_len).toULongLong(&flag,16);
                        //时钟
                        clock=currentFrame.mid(parameters.dataPara.clock_start,parameters.dataPara.clock_len).toULongLong(&flag,16);
                        //24v
                        Volt24_voltage=BindData::frameReverse(currentFrame.mid(parameters.addData.Volt24V_start,parameters.addData.Volt24V_len)).toUInt(&flag,16)*parameters.addData.Volt_24V_para;
                        //MFLData
                        MFLData.append(this->MFLDataExtract(currentFrame));
                        //第1瓣温度（第1通道温度数据）
                        MFLData.append(this->MFLDataExtract_Temperature(currentFrame,1));
                        //第7瓣温度（第13通道温度数据）
                        MFLData.append(this->MFLDataExtract_Temperature(currentFrame,13));
                        //周向角
                        ZXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.ZXJ_start,parameters.posData.ZXJ_len)).toInt(&flag,16)*parameters.posData.ZXJpara;
                        //倾角
                        QJ=BindData::frameReverse(currentFrame.mid(parameters.posData.QJ_start,parameters.posData.QJ_len)).toInt(&flag,16)*parameters.posData.QJpara;
                        //航向角
                        HXJ=BindData::frameReverse(currentFrame.mid(parameters.posData.HXJ_start,parameters.posData.HXJ_len)).toInt(&flag,16)*parameters.posData.HXJpara;
                        //X加速度
                        acc_x=BindData::frameReverse(currentFrame.mid(parameters.addData.accX_start,parameters.addData.accX_len)).toInt(&flag,16)*parameters.addData.accX_para;
                        //Y加速度
                        acc_y=BindData::frameReverse(currentFrame.mid(parameters.addData.accY_start,parameters.addData.accY_len)).toInt(&flag,16)*parameters.addData.accY_para;
                        //Z加速度
                        acc_z=BindData::frameReverse(currentFrame.mid(parameters.addData.accZ_start,parameters.addData.accZ_len)).toInt(&flag,16)*parameters.addData.accZ_para;
                        //姿态温度
                        temp_pos=BindData::frameReverse(currentFrame.mid(parameters.tempData.tempPos_start,parameters.tempData.tempPos_len)).toInt(&flag,16)*parameters.tempData.positionPara;
                        //环境温度
                        temp_bat=parameters.tempData.envirPara1-(parameters.tempData.envirPara2*BindData::frameReverse(currentFrame.mid(parameters.tempData.tempEnvir_start,parameters.tempData.tempEnvir_len)).toInt(&flag,16));
                        //处理板温度
                        temp_panel=currentFrame.mid(parameters.tempData.tempPanel_start,parameters.tempData.tempPanel_len).toInt(&flag,16)*parameters.tempData.panelPara;
                        //里程1
                        dis_1=currentFrame.mid(parameters.disData.dis1_start,parameters.disData.dis1_len).toInt(&flag,16);
                        //里程2
                        dis_2=currentFrame.mid(parameters.disData.dis2_start,parameters.disData.dis2_len).toInt(&flag,16);
                        //里程3
                        dis_3=currentFrame.mid(parameters.disData.dis3_start,parameters.disData.dis3_len).toInt(&flag,16);
                        //status
                        stat=currentFrame.mid(parameters.addData.status_start,parameters.addData.status_len).toUInt(&flag,16);

                        //拼接十进制文件数据
                        /*  dis_opt,clock,Volt24_voltage;
                            QList<double> MFLData;
                            ZXJ,QJ,HXJ,acc_x,acc_y,acc_z,temp_pos,temp_bat,temp_panel,dis_1,dis_2,dis_3,stat;*/
                        DecimalData.append(dis_opt);
                        DecimalData.append(clock);
                        DecimalData.append(Volt24_voltage);
                        DecimalData.append(MFLData);
                        MFLData.clear();
                        DecimalData.append(ZXJ);
                        DecimalData.append(QJ);
                        DecimalData.append(HXJ);
                        DecimalData.append(acc_x);
                        DecimalData.append(acc_y);
                        DecimalData.append(acc_z);
                        DecimalData.append(temp_pos);
                        DecimalData.append(temp_bat);
                        DecimalData.append(temp_panel);
                        DecimalData.append(dis_1);
                        DecimalData.append(dis_2);
                        DecimalData.append(dis_3);
                        DecimalData.append(stat);
                        frameCount++;
                        emit this->fileConvertProcess((double)(frameCount%frameNum)/(double)frameNum*100);

                        //写文件
        //                int outputSize_double=DecimalData.length();
        //                double *outByteArray=new double[outputSize_double];
        //                for (int j = 0; j < outputSize_double; ++j) {
        //                    outByteArray[j]=DecimalData.at(j);
        //                }
        //                if(frameCount%50000==1){
        //                    ofs.close();
        //                    fileCount++;
        //                    QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
        //                    ofs.open(outputPath.toStdString(),ios::app|ios::binary);
        //                }
        //                ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
        //                delete[](outByteArray);
        //                DecimalData.clear();

                        // 写文件
                        if(frameCount%50000==0){
                            int outputSize_double=DecimalData.length();
                            double *outByteArray=new double[outputSize_double];
                            for (int j = 0; j < outputSize_double; ++j) {
                                outByteArray[j]=DecimalData.at(j);
                            }
                            fileCount++;
                            QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                            ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                            ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                            delete[](outByteArray);
                            DecimalData.clear();
                            ofs.close();
                        }
                    }
                    if(!DecimalData.isEmpty()){
                        if((fileFlag==2)||(fileFlag==3)){       //如果是出管文件写剩余文件
                            int outputSize_double=DecimalData.length();
                            double *outByteArray=new double[outputSize_double];
                            for (int j = 0; j < outputSize_double; ++j) {
                                outByteArray[j]=DecimalData.at(j);
                            }
                            //写剩余文件
                            fileCount++;
                            QString outputPath=SavePath+(QString("\\%1.dat%2IN.bin").arg(file.localFileName.left(file.localFileName.lastIndexOf("."))).arg(fileCount));
                            ofs.open(outputPath.toStdString(),ios::out|ios::binary);
                            ofs.write((char*)outByteArray,sizeof(double)*outputSize_double);
                            ofs.close();
                            delete[](outByteArray);
                            DecimalData.clear();
                        }
                        else { //其他文件在下一文件中续写
                            this->restData.append(DecimalData);
                            DecimalData.clear();
                        }

                    }
                    ofs.close();
                    ifs.close();
                    emit this->newInfo("文件转换完成！");
                    return 0; //已转换

        /******************************************************** 12inch-漏磁 End ****************************************************************************/

        }
            break;


        default:
            break;

        }

        break;
    default:
        break;
    }
    return 1;   //未转换

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


QList<double> FileConvertWork::MFLDataExtract(QString frame){       //包含12路轴向数据、12路径向数据，12路周向数据，4路内外区分数据 (当前通道6路与相邻下移通道6路拼接为12路数据)
    QList<double> frameData;
    bool flag;
    for (int i = 0; i < parameters.dataPara_MFL.MFLData_num; i+=2) {
        int startPtr=parameters.dataPara_MFL.MFLData_start+(i)*parameters.dataPara_MFL.MFLData_len;
        // 两组12路轴向
        for (int j = 0; j < MFLCHANNELNUM; ++j) {       // 第一组6路轴向
            int currentPtr=startPtr+j*8;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((tempFrame.toInt(&flag,16)&0x0fff)/4)); //轴向
        }

        for (int j = 0; j < MFLCHANNELNUM; ++j) {       // 第二组6路轴向
            int currentPtr=startPtr+parameters.dataPara_MFL.MFLData_len+j*8;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((tempFrame.toInt(&flag,16)&0x0fff)/4)); //轴向
        }

        // 两组12路径向
        for (int j = 0; j < MFLCHANNELNUM; ++j) {       // 第一组6路径向
            int currentPtr=startPtr+4+j*8;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((tempFrame.toInt(&flag,16)&0x0fff)/4));
        }

        for (int j = 0; j < MFLCHANNELNUM; ++j) {       // 第二组6路径向
            int currentPtr=startPtr+4+parameters.dataPara_MFL.MFLData_len+j*8;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((tempFrame.toInt(&flag,16)&0x0fff)/4));
        }


        // 两组12路周向
        for (int j = 0; j < MFLCHANNELNUM; ++j) {       // 第一组6路周向
            int currentPtr=startPtr+48+j*4;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((double)(tempFrame.toUInt(&flag,16)&0x0fff)/4096)*3);
        }

        for (int j = 0; j < MFLCHANNELNUM; ++j) {       // 第二组6路周向
            int currentPtr=startPtr+48+parameters.dataPara_MFL.MFLData_len+j*4;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((double)(tempFrame.toUInt(&flag,16)&0x0fff)/4096)*3);
        }


        // 两组4路内外区分
        for (int j = 0; j < 2; ++j) {       // 第一组2路内外区分
            int currentPtr=startPtr+76+j*4;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((double)(tempFrame.toUInt(&flag,16)&0x0fff)/4096)*3);
        }

        for (int j = 0; j < 2; ++j) {       // 第二组2路内外区分
            int currentPtr=startPtr+76+parameters.dataPara_MFL.MFLData_len+j*4;
            QString tempFrame=frame.mid(currentPtr,4);
            frameData.append((double)((double)(tempFrame.toUInt(&flag,16)&0x0fff)/4096)*3);
        }


    }
    return frameData;
}

double FileConvertWork::MFLDataExtract_Temperature(QString frame, int position){
    bool flag;
    int startPtr=parameters.dataPara_MFL.MFLData_start+(position-1)*parameters.dataPara_MFL.MFLData_len;
    int currentPtr=startPtr+72;
    QString tempFrame=frame.mid(currentPtr,4);
    double result = (double)((double)((tempFrame.toUInt(&flag,16)&0x0fff-1708)*302)/4096);
    return result;
}

void FileConvertWork::updateLocalFileList(QList<localFile> *newList){
    this->localfilelist=*newList;
}

void FileConvertWork::updateSavePath(QString newSavePath){
    this->SavePath=newSavePath;
}

QString FileConvertWork::hardUnencrypt(QString frame){


    bool Hex2Decflag;
    int dataLength=frame.length();
    QString data_1,data_2,data_3,data_4;
    QList<uint> data_test;
    uint data_low,data_high;
    QString dataFrame=frame;
    QString unencryptedDataFrame;

    for (int i = 0; i < dataLength; i=i+2) {
        data_low=(dataFrame.mid(i,2).toUInt(&Hex2Decflag,16)&0x01);
        data_high=((dataFrame.mid(i,2).toUInt(&Hex2Decflag,16)>>7)&0x01);
        data_test.append((((dataFrame.mid(i,2).toUInt(&Hex2Decflag,16))&0x7E)|data_high|(data_low<<7))&0xff);

        emit this->fileConvertProcess(((double)i/(double)(dataLength))*100);
    }
    for (int j = 0; j < data_test.length()/4; ++j) {
        data_1=QString("%1").arg(data_test.at(4*j+0),2,16,QLatin1Char('0'));
        data_2=QString("%1").arg(data_test.at(4*j+1),2,16,QLatin1Char('0'));
        data_3=QString("%1").arg(data_test.at(4*j+2),2,16,QLatin1Char('0'));
        data_4=QString("%1").arg(data_test.at(4*j+3),2,16,QLatin1Char('0'));
        unencryptedDataFrame.append(data_2);
        unencryptedDataFrame.append(data_4);
        unencryptedDataFrame.append(data_1);
        unencryptedDataFrame.append(data_3);

        emit this->fileConvertProcess(((double)j/(double)(data_test.length()/4))*100);
    }

    return unencryptedDataFrame.toUpper();
}
