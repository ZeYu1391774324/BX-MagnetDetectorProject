#include "framework_8_10_12_14_inch_bx.h"

FrameWork_8_10_12_14_Inch_bx::FrameWork_8_10_12_14_Inch_bx()
{
    this->initFrameWork();
}

void FrameWork_8_10_12_14_Inch_bx::initFrameWork(){

    //解码控制器
    QTimer *timer = new QTimer;
    timer->start(10);
    connect(timer,&QTimer::timeout,[=](){

        if(!this->frameList.isEmpty()){
            this->uncodeFrame();
        }
    });

    //额外数字显示信息更新（每1秒）
    QTimer *additionalDataTimer = new QTimer;
    additionalDataTimer->start(1000);
    connect(additionalDataTimer,&QTimer::timeout,[=](){
        if(!this->currentFrame.isEmpty()){
            this->uncodeFrame_additional();
        }
    });


}

void FrameWork_8_10_12_14_Inch_bx::setFrameList(QString newFrame){
    this->frameList.append(newFrame);
}

void FrameWork_8_10_12_14_Inch_bx::uncodeFrame(){
    if(this->uncodeLock&&!this->frameList.isEmpty()){
        this->uncodeLock=false;                     //上锁
        QString frame=this->frameList.first();      //第一个数据报出队列
        currentFrame=frame;                         //更新当前帧
        this->frameList.removeFirst();

        //解密数据帧部分
        frame=BindData::frameUnencrypt(frame);

        //解码取信息过程
        this->bxData.append(this->bxDataExtract(frame.mid(80,72)));     //1-18路
        this->bxData.append(this->bxDataExtract(frame.mid(154,72)));    //19-36路
        this->bxData.append(this->bxDataExtract(frame.mid(228,72)));    //37-54路
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

        this->uncodeLock=true;                      //解锁
    }
    else {
        QThread::msleep(10);
    }
}

void FrameWork_8_10_12_14_Inch_bx::uncodeFrame_additional(){
    QString frame = currentFrame;

    //解密数据帧部分
    frame = BindData::frameUnencrypt(frame);

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
    bxData_additional["时钟脉冲计数"]=QString("%1").arg(BindData::frameReverse(frame.mid(16,12)).toUInt(&flag,16));
    bxData_additional["24V系统供电电压"]=QString("%1").arg(BindData::frameReverse(frame.mid(28,4)).toUInt(&flag,16)*0.001);
    bxData_additional["24V系统供电电流"]=QString("%1").arg(BindData::frameReverse(frame.mid(32,4)).toUInt(&flag,16)*0.001);
    bxData_additional["电池组已用电量"]=QString("%1").arg(BindData::frameReverse(frame.mid(36,4)).toUInt(&flag,16)*0.1);
    bxData_additional["电池累计通电次数"]=QString("%1").arg(BindData::frameReverse(frame.mid(40,4)).toUInt(&flag,16));
    bxData_additional["电池累计通电时间"]=QString("%1").arg(BindData::frameReverse(frame.mid(44,4)).toUInt(&flag,16)*0.01);
    bxData_additional["电池组额定电量"]=QString("%1").arg(BindData::frameReverse(frame.mid(48,4)).toUInt(&flag,16)*0.1);
    int year,month,day;
    year=frame.mid(52,4).toUInt(&flag,16);
    month=frame.mid(56,2).toUInt(&flag,16);
    day=frame.mid(58,2).toUInt(&flag,16);
    bxData_additional["电池更换时间"]=QString("%1年%2月%3日").arg(year).arg(month).arg(day);
    bxData_additional["电池模块环境温度"]=QString("%1").arg(139.23-(0.23*BindData::frameReverse(frame.mid(60,4)).toUInt(&flag,16)));
    QString batteryMode,batteryModeSubFrame;
    batteryModeSubFrame=frame.mid(66,2);
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
    bxData_additional["5V二次电源电压"]=QString("%1").arg(BindData::frameReverse(frame.mid(68,4)).toUInt(&flag,16)*0.0078);
    bxData_additional["3.3V二次电源电压"]=QString("%1").arg(BindData::frameReverse(frame.mid(72,4)).toUInt(&flag,16)*0.0036);

    emit this->newBxDataAdditional(bxData_additional);
    this->bxData_additional.clear();

}

QList<double> FrameWork_8_10_12_14_Inch_bx::bxDataExtract(QString subframe){
    QList<double> subframeData;
    bool flag;
    for (int  i= 0; i < subframe.length(); i+=4) {
        subframeData.append((double)(subframe.mid(i,4).toUInt(&flag,16)&0x0fff)*5/4096);       // 低12位/4096*5
        //subframeData.append(subframe.mid(i,4).right(3).toDouble()*5/4096);       // 低12位/4096*5
    }
    return subframeData;
}

QList<double> FrameWork_8_10_12_14_Inch_bx::temperatureDataExtract(QString frame){
    //环境温度，处理板温度，姿态温度
    QList<double> output;
    double temperature_environment,temperature_panel,temperature_position;
    QString subframe_TempEnvir,subframe_TempPanel,subframe_TempPos;
    subframe_TempEnvir=BindData::frameReverse(frame.mid(60,4));     //unsigned
    subframe_TempPanel=BindData::frameReverse(frame.mid(302,4));    //signed
    subframe_TempPos=BindData::frameReverse(frame.mid(330,4));      //signed
    bool flag;
    temperature_environment=193.23-(0.23*subframe_TempEnvir.toUInt(&flag,16));
    temperature_panel=subframe_TempPanel.toInt(&flag,16)*0.0625;
    temperature_position=subframe_TempPos.toInt(&flag,16)*0.0625;
    output.append(temperature_environment);
    output.append(temperature_panel);
    output.append(temperature_position);
    return output;

}

QList<double> FrameWork_8_10_12_14_Inch_bx::distanceDataExtract(QString frame){
    //优选里程，原始里程1,2,3
    QList<double> output;
    double distance_optimized,distance_1,distance_2,distance_3;
    QString subframe_opt,subframe_d1,subframe_d2,subframe_d3;
    subframe_opt=BindData::frameReverse(frame.mid(8,8));
    subframe_d1=BindData::frameReverse(frame.mid(360,8));
    subframe_d2=BindData::frameReverse(frame.mid(368,8));
    subframe_d3=BindData::frameReverse(frame.mid(376,8));
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

QList<double> FrameWork_8_10_12_14_Inch_bx::positionDataExtract(QString frame){
    //姿态周向角，倾角，航向角，加速度
    QList<double> output;
    double ZXJ,QJ,HXJ;
    QString subframe_ZXJ,subframe_QJ,subframe_HXJ;
    subframe_ZXJ=BindData::frameReverse(frame.mid(306,4));
    subframe_QJ=BindData::frameReverse(frame.mid(310,4));
    subframe_HXJ=BindData::frameReverse(frame.mid(314,4));
    bool flag;
    ZXJ=subframe_ZXJ.toInt(&flag,16)*0.1;
    QJ=subframe_QJ.toInt(&flag,16)*0.1;
    HXJ=subframe_HXJ.toInt(&flag,16)*0.1;
    output.append(ZXJ);
    output.append(QJ);
    output.append(HXJ);
    return output;

}

