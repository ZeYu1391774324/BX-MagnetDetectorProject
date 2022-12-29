#include "datawork.h"

DataWork::DataWork(QSerialPort *serial)

{
    this->serial=serial;
    this->ByteSpeedDetecting();

}

void DataWork::ByteSpeedDetecting(){
    QTimer *timer = new QTimer;
    timer->start(1000);
    connect(timer,&QTimer::timeout,[=](){
        emit this->newByteSpeed(ByteCount);
        ByteCount=0;
    });
}


void DataWork::receiveData(){
    QByteArray res = serial->readAll();                      // 读取数据
    QString hexRes =res.toHex().toUpper();
    ByteCount+=res.length();

    if(!hexRes.isEmpty())                                 // 接收到数据
    {
        data+=hexRes;                         // 数据是一行一行传送的，要保存所有数据
        emit this->dataChanged(data);
    }

}

void DataWork::clearBuffer(int head, int end){
    this->data.remove(0,head);
    emit this->dataChanged(data);
    emit this->DataWorkCleared();
}

