#ifndef FRAMEWORK_8_10_12_14_INCH_BX_H
#define FRAMEWORK_8_10_12_14_INCH_BX_H

#include <QObject>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include "binddata.h"

class FrameWork_8_10_12_14_Inch_bx : public QObject
{
    Q_OBJECT
public:
    FrameWork_8_10_12_14_Inch_bx();

    QList<QString> frameList;
    QList<double> bxData;
    bool uncodeLock=true;

    void initFrameWork();
    void setFrameList(QString newFrame);
    void uncodeFrame();
    QList<double> bxDataExtract(QString subframe);

signals:
    void newBxData(QList<double> bxData);

};

#endif // FRAMEWORK_8_10_12_14_INCH_BX_H
