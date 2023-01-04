#ifndef DISPLAYWORK_H
#define DISPLAYWORK_H

#include "paraget.h"
#include <QObject>
#include <fstream>
#include "paraget.h"
#include "binddata.h"
#include <QTimer>


using namespace std;


class DisplayWork : public QObject
{
    Q_OBJECT
public:
    DisplayWork();

    bool displayControll=false;
    QString filePath;
    QString data;
    ParaGet *parameters;

    int currentIndex=0;
    int interval=0;
    QString currentFrame;
    QList<double> bxData;                       //图像信息
    QMap<QString,QString> bxData_additional;    //额外数字显示信息
    QStringList frameList;

    void readFile(QString path);
    QString bytestohexstring_pure(char* bytes,int bytelength);
    QString bytestohexstring_Unencrypt(char* bytes,int bytelength);
    void getCurrentFrame();

    //解码提取图像信息 & 额外辅助信息
    void uncodeFrame();
    void uncodeFrame_additional();


    // Data extracting tool functions
    QList<double> bxDataExtract(QString subframe);
    QList<double> temperatureDataExtract(QString frame);
    QList<double> distanceDataExtract(QString frame);
    QList<double> positionDataExtract(QString frame);

    void setParameters(ParaGet*);
    void jumpCommand(int num);
    void restartCommand();

signals:
    void newBxData(QList<double> bxData);
    void newBxDataAdditional(QMap<QString,QString> bxData_additional);
    void newFrameNum(int num);

};

#endif // DISPLAYWORK_H
