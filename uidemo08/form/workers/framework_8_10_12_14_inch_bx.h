#ifndef FRAMEWORK_8_10_12_14_INCH_BX_H
#define FRAMEWORK_8_10_12_14_INCH_BX_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include "binddata.h"
#include "paraget.h"


class FrameWork_8_10_12_14_Inch_bx : public QObject
{
    Q_OBJECT
public:
    FrameWork_8_10_12_14_Inch_bx();

    ParaGet *parameters;
    QList<QString> frameList;
    QString currentFrame;
    QList<double> bxData;                       //图像信息(变形)
    QList<double> MFLData;                       //图像信息(漏磁)
    QMap<QString,QString> bxData_additional;    //额外数字显示信息
    bool uncodeLock=true;

    void initFrameWork();
    void setFrameList(QString newFrame);
    void setParameters(ParaGet*);

    //解码提取图像信息 & 额外辅助信息
    void uncodeFrame();
    void uncodeFrame_additional();

    // Data extracting tool functions
    QList<double> bxDataExtract(QString subframe);
    QList<double> MFLDataExtract(QString frame);
    QList<double> temperatureDataExtract(QString frame);
    QList<double> distanceDataExtract(QString frame);
    QList<double> positionDataExtract(QString frame);


signals:
    void newBxData(QList<double> bxData);
    void newBxDataAdditional(QMap<QString,QString> bxData_additional);

    void newMFLData(QList<double> MFLData);

};

#endif // FRAMEWORK_8_10_12_14_INCH_BX_H
