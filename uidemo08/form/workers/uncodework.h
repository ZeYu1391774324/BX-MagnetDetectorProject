#ifndef UNCODEWORK_H
#define UNCODEWORK_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include "binddata.h"


#define FRAMEHEAD "55AA"
// BufferCtrl Parameters
#define CLEARBUffER 4096        // 一级缓存区清理阈值

class UncodeWork : public QObject
{
    Q_OBJECT
public:
    UncodeWork();

    int Uncode_head=0;
    int Uncode_end=0;
    QString data;
    QString CurrentFrame;
    QTimer *overtimeTimer;

    void setData(QString newData);
    void initUncodeWork();
    void dataUncode();
    void clearBuffer();
    void resetHeadandEnd();


signals:
    void currentFrameChanges(QString frame);
    void clearDataWork(int head,int end);

};

#endif // UNCODEWORK_H
