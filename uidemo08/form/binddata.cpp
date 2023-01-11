#include "binddata.h"
#include <QDebug>
#include "frmmain.h"

BindData::BindData()
{
    this->pipeLabel="N/A";
    this->pipeLength="N/A";
    this->pipeThickness="N/A";
    this->Pressure="N/A";
    this->Frequency="N/A";
    this->Power="N/A";
    this->workTime=QDateTime::currentDateTime();
    this->batteryTime=QDate::currentDate();

}

QString BindData::toString(){
    QString str = "管道标识: "+this->pipeLabel+" 管道长度: "+this->pipeLength+"km 管壁厚度: "+this->pipeThickness+
            "mm 设计压力: "+this->Pressure+"MPa 采集频率: "+this->Frequency+" 设计电压: "+this->Power+
            "Wh 电池更换时间："+this->batteryTime.toString()+" 采集时间："+this->workTime.toString()+".";
    return str;
}

QString BindData::bindSystemDateTime(){
    int y,M,d,h,m,s;
    QDateTime systemDateTime=QDateTime::currentDateTime();
    systemDateTime.date().getDate(&y,&M,&d);
    h=systemDateTime.time().hour();
    m=systemDateTime.time().minute();
    s=systemDateTime.time().second();
    //qDebug()<<y<<M<<d<<h<<m<<s;

    QString str="55AA09005252";     // 0x 52 52时间设置
    str.append(QString("%1%2%3%4%5%6%7").arg(y&0xff,2,16,QLatin1Char('0')).arg(y>>8,2,16,QLatin1Char('0')).arg(M,2,16,QLatin1Char('0')).arg(d,2,16,QLatin1Char('0')).arg(h,2,16,QLatin1Char('0'))
               .arg(m,2,16,QLatin1Char('0')).arg(s,2,16,QLatin1Char('0')));
    int sum=0;
    for (int i = 0; i < 9; ++i) {
//+++++++++++++++++++++++++++++++++++++++++++++++++求和帧
    }

    return str;
}

QString BindData::frameCalculate(QString dataFrame){
    int sum=0;
    bool flag;
    for (int i = 0; i < dataFrame.length(); i+=2) {
        //qDebug()<<dataFrame.mid(i,2)<<"-----"<<dataFrame.mid(i,2).toInt(&flag,16);
        sum+=dataFrame.mid(i,2).toInt(&flag,16);
    }
    return QString("%1").arg(sum,2,16,QLatin1Char('0')).right(2).toUpper();

}
int BindData::frameDataLength(QString frame){
    if(frame.length()<8){
        return 0;
    }
    QString lengthFrame = frame.mid(4,4);
    QString lower=lengthFrame.left(2);      //先低后高
    QString higher=lengthFrame.right(2);
    QString length_Hex=higher+lower;
    bool flag;
    int length=length_Hex.toInt(&flag,16)*2;
    return length;
}

QString BindData::frameReverse(QString frame){
    if(frame.length()%2!=0||frame.isEmpty()){        //如果帧长度不是整字节（不是一对一对的）不进行转换
        qDebug()<<QString("高低位转换的帧不是偶数位，字节长度有误！ Frame length: %1.").arg(frame.length());
        return frame;
    }
    else{
        QString reversedFrame;
        for (int i = frame.length()-2; i >=0; i=i-2) {
            reversedFrame.append(frame.mid(i,2));
        }
        return reversedFrame;
    }
}

QString BindData::dataBinding(){
    QString frame;

    QString head = "55AA";
    QString len = "2300";
    QString sendMode=frameReverse(QString(CONFIGUREWORKMODE));
    QString data = "02";
    QString HexThickness,HexLength,HexTime,HexID,HexPressure,HexSum;
    HexThickness=frameReverse(QString("%1").arg(pipeThickness.toInt()*10,4,16,QLatin1Char('0')));
    HexLength=frameReverse(QString("%1").arg(pipeLength.toInt()*10,4,16,QLatin1Char('0')));

    int y,M,d,h,m;
    workTime.date().getDate(&y,&M,&d);
    h=workTime.time().hour();
    m=workTime.time().minute();

    HexTime=QString("%1%2%3%4%5").arg(y,4,16,QLatin1Char('0')).arg(M,2,16,QLatin1Char('0')).arg(d,2,16,QLatin1Char('0')).arg(h,2,16,QLatin1Char('0')).arg(m,2,16,QLatin1Char('0'));
    HexTime=frameReverse(HexTime.left(4)).append(HexTime.mid(4));

    HexID=QString("%1").arg(pipeLabel.toInt(),40,16,QLatin1Char('0'));
    HexPressure=frameReverse(QString("%1").arg(Pressure.toInt()*10,4,16,QLatin1Char('0')));

    frame+=head+len+sendMode+data+HexThickness+HexLength+HexTime+HexID+HexPressure;
    HexSum=frameCalculate(frame.mid(8));
    frame.append(HexSum);

    return frame.toUpper();

}

QString BindData::frameUnencrypt(QString frame){
    bool flag;
    int dataLength=BindData::frameDataLength(frame);
    QString data_1,data_2,data_3,data_4;
    QList<uint> data_test;
    uint data_low,data_high;
    QString dataFrame=frame.mid(8,dataLength);
    QString unencryptedDataFrame=frame.left(8);
    for (int i = 0; i < dataLength; i=i+2) {
        data_low=(dataFrame.mid(i,2).toUInt(&flag,16)&0x01);
        data_high=((dataFrame.mid(i,2).toUInt(&flag,16)>>7)&0x01);
        data_test.append((((dataFrame.mid(i,2).toUInt(&flag,16))&0x7E)|data_high|(data_low<<7))&0xff);
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
    }
    unencryptedDataFrame.append(BindData::frameCalculate(unencryptedDataFrame.mid(8)));
    return unencryptedDataFrame.toUpper();
}

QString BindData::hardUnencrypt(QString frame){
    bool flag;
    int dataLength=frame.length();
    QString data_1,data_2,data_3,data_4;
    QList<uint> data_test;
    uint data_low,data_high;
    QString dataFrame=frame;
    QString unencryptedDataFrame;
    for (int i = 0; i < dataLength/2; i=i+2) {
        data_low=(dataFrame.mid(i,2).toUInt(&flag,16)&0x01);
        data_high=((dataFrame.mid(i,2).toUInt(&flag,16)>>7)&0x01);
        data_test.append((((dataFrame.mid(i,2).toUInt(&flag,16))&0x7E)|data_high|(data_low<<7))&0xff);
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
    }

    return unencryptedDataFrame.toUpper();
}








