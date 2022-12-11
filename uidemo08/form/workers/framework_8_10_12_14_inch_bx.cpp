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
}

void FrameWork_8_10_12_14_Inch_bx::setFrameList(QString newFrame){
    this->frameList.append(newFrame);
}

void FrameWork_8_10_12_14_Inch_bx::uncodeFrame(){
    if(this->uncodeLock&&!this->frameList.isEmpty()){
        this->uncodeLock=false;                     //上锁
        QString frame=this->frameList.first();      //第一个数据报出队列
        this->frameList.removeFirst();

        //解密数据帧部分
        frame=BindData::frameUnencrypt(frame);

        //解码取信息过程
        this->bxData.append(this->bxDataExtract(frame.mid(80,72)));     //1-18路
        this->bxData.append(this->bxDataExtract(frame.mid(154,72)));    //19-36路
        this->bxData.append(this->bxDataExtract(frame.mid(228,72)));    //37-54路

        emit this->newBxData(this->bxData);
        this->bxData.clear();

        this->uncodeLock=true;                      //解锁
    }
    else {
        QThread::msleep(10);
    }
}

QList<double> FrameWork_8_10_12_14_Inch_bx::bxDataExtract(QString subframe){
    QList<double> subframeData;
    for (int  i= 0; i < subframe.length(); i+=4) {
        subframeData.append((double)(subframe.mid(i,4).toUInt()&0x0fff)*5/4096);       // 低12位/4096*5
        //subframeData.append(subframe.mid(i,4).right(3).toDouble()*5/4096);       // 低12位/4096*5
    }
    return subframeData;
}
