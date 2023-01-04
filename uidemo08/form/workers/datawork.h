#ifndef DATAWORK_H
#define DATAWORK_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/qserialportinfo.h>
#include <QDebug>
#include <QTimer>
#include "binddata.h"

// Receive Mode Definition
#define SLIENTMODE "5656"
#define TESTMODE "5757"
#define WORKMODE "5858"
#define NULLMODE "0000"
#define SUCCESS "0001"
#define UNSUCCESS "0002"
#define FRAMEHEAD "55AA"



class DataWork : public QObject
{
    Q_OBJECT
public:
    DataWork(QSerialPort *serial=nullptr);

    //Members
    QSerialPort *serial;
    QString data;
    int ByteCount;



    void receiveData();
    void clearBuffer(int head, int end);

    //TODO ByteCurrent speed Detecting
    void ByteSpeedDetecting();



signals:
    void dataChanged(QString data);
    void DataWorkCleared();
    void newByteSpeed(int ByteSpeed);


};

#endif // DATAWORK_H
