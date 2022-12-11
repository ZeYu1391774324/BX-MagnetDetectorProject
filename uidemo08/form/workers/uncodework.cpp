#include "uncodework.h"

UncodeWork::UncodeWork()

{
    this->initUncodeWork();
}



void UncodeWork::initUncodeWork(){

    // 初始化子线程
    QThread * uncodeThread=new QThread;
    moveToThread(uncodeThread);
    uncodeThread->start();

    // 清理缓存区控制器
    int ReceivedDataLength_old = 0;
    int ReceivedDataLength_new = 0;
    QTimer * timer = new QTimer;
    timer->start(5000);
    connect(timer,&QTimer::timeout,[=]()mutable{
        ReceivedDataLength_new = data.length();
        if((ReceivedDataLength_new>ReceivedDataLength_old) && (data.length()<CLEARBUffER)){
            ReceivedDataLength_old=ReceivedDataLength_new;
        }
        else{
            ReceivedDataLength_old = 0;
            ReceivedDataLength_new = 0;
            this->clearBuffer();              //主程序清理缓存区

        }
    });

    //解码控制器
    QTimer * uncodeTimer = new QTimer;
    uncodeTimer->start(1);
    connect(uncodeTimer,&QTimer::timeout,[=](){
        this->dataUncode();
    });


    // 传输超时控制器
    this->overtimeTimer = new QTimer;
    connect(overtimeTimer,&QTimer::timeout,[=](){

        overtimeTimer->stop();
        //当前帧超时，检测下一帧
        this->Uncode_end=this->Uncode_head+4;
        this->Uncode_head=this->Uncode_end;
    });



}

void UncodeWork::dataUncode(){


    //data=ui->DataReceived->toPlainText();
    //qDebug()<<this->Uncode_head<<"---"<<this->Uncode_end<<"---"<<data.length();

    // 按位检测报头
//    while (!data.mid(this->Uncode_head,4).contains(FRAMEHEAD)){   //检测报头
//        this->Uncode_head++;
//        if(Uncode_head>data.length()-8){        // 没有完整的下一帧
//            this->Uncode_head=this->Uncode_end;
//            return;
//        }
//    }
//    if(Uncode_head>data.length()-8){        // 没有完整的下一帧
//        this->Uncode_head=this->Uncode_end;
//        return;
//    }


    // 按报头检测报头
    if(data.indexOf(FRAMEHEAD,this->Uncode_head)==-1){        // 没有完整的下一帧
        this->Uncode_head=this->Uncode_end;
        return;
    }
    else{
        this->Uncode_head=data.indexOf(FRAMEHEAD,this->Uncode_head);
}




    int frameDataLength=BindData::frameDataLength(data.mid(Uncode_head,8));
    this->Uncode_end=this->Uncode_head+8+frameDataLength;
    if(this->Uncode_end>data.length()-2){             // 当前帧未传输完成

        if(!overtimeTimer->isActive()){
            //qDebug()<<this->Uncode_end<<"---"<<data.length()-2;
            overtimeTimer->start(100);                 // 计时0.1秒钟传输超时时间
        }
        this->Uncode_end=this->Uncode_head;
        return;
    }
    else{
        overtimeTimer->stop();
        // 计算校验和
        QString frameSum=BindData::frameCalculate(data.mid(Uncode_head+8,frameDataLength));
        QString sumData=data.mid(this->Uncode_end,2);
        //qDebug()<<data.mid(Uncode_head+8,2*frameLength)<<"---"<<frameSum<<"--------"<<sumData;
        if(frameSum==sumData){
            this->CurrentFrame=data.mid(this->Uncode_head,10+frameDataLength);
            emit this->currentFrameChanges(this->CurrentFrame);

            this->Uncode_end+=2;                // 开始新的数据报解析
            this->Uncode_head=this->Uncode_end;
        }
        if(frameSum!=sumData){
            //当前帧错误，检测下一帧
            this->Uncode_end=Uncode_head+4;
            this->Uncode_head=this->Uncode_end;
        }
    }


}


void UncodeWork::clearBuffer(){

    emit this->clearDataWork(this->Uncode_head,this->Uncode_end);


}

void UncodeWork::setData(QString newData){
    this->data=newData;
}

void UncodeWork::resetHeadandEnd(){
    this->Uncode_head=0;
    this->Uncode_end=0;
}
