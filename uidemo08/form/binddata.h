#ifndef BINDDATA_H
#define BINDDATA_H
#include "workers/fileconvertwork.h"
#include <QString>
#include <QDate>
#include <QProgressDialog>

class BindData
{
public:
    BindData();

    QString pipeLabel;          //管道标识
    QString pipeLength;         //管道长度
    QString pipeThickness;      //管道壁厚
    QString Pressure;           //管道设计运行压力
    QDate batteryTime;          //电池更换时间
    QDateTime workTime;             //检测时间
    QString Frequency;          //采集频率
    QString Power;              //额定电量



    QString bindSystemDateTime();
    QString dataBinding();

    static QString frameCalculate(QString dataFrame);
    static int frameDataLength(QString frame);
    static QString frameReverse(QString frame);
    static QString frameUnencrypt(QString frame);
    static QString hardUnencrypt(QString frame);
    QString toString();



};

#endif // BINDDATA_H
