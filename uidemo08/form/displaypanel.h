#ifndef DISPLAYPANEL_H
#define DISPLAYPANEL_H

#include <QWidget>
#include <QThread>
#include "paraget.h"
#include "workers/displaywork.h"


// Plots Definitions
#define LINENUM 6       // 每个图表中绘制图像数量
#define CLEARNUM 150        // 图表中清除缓存取数据阈值
#define MFLCHANNELNUM 6 //每个漏磁通道有6个传感器

// BufferCtrl Parameters
#define CLEARBUffER 4096        // 一级缓存区清理阈值


namespace Ui {
class DisplayPanel;
}

class DisplayPanel : public QWidget
{
    Q_OBJECT

public:
    explicit DisplayPanel(QWidget *parent = nullptr,ParaGet *para=nullptr);
    ~DisplayPanel();

    int interval=1000;
    int frameNum;
    void initPanel();
    void initPlots();
    void initWorkers();
    void updatePlots();
    void updateBxData(QList<double> newBxData);
    void updateBxDataAdditional(QMap<QString,QString> newBxDataAdditional);
    void updateSpeedLabel(int speed);
    void updateParametersLabel(ParaGet*);
    void closeEvent(QCloseEvent *e);
    ParaGet *parameters;

    // MFL
    void initPanel_MFL();
    void initPlots_MFL();
    void updatePlots_MFL();
    void updateMFLData(QList<double> newMFLData);


    // 变形漏磁数据
    QList<QVector<double>> bxDataList;
    QList<QVector<double>> MFLDataList;
    int bxData_RoadsNum=54;         //54个变形臂
    int MFLData_RoadsNum=80;        //80个漏磁通道


    /*
        55：环境温度；     56：处理板温度；        57：姿态检测温度；
        58：优选里程脉冲；  59：原始里程脉冲1；     60：原始里程脉冲2；     61：原始里程脉冲3；
        62：周向角         63：倾角；             64：航向角；
    */
    int temperature_RoadsNum=3;     //3个温度曲线
    int distance_RoadsNum=4;        //4个里程曲线
    int position_RoadsNum=3;        //3姿态曲线
    int dataCount=0;

private:
    Ui::DisplayPanel *ui;

signals:
    void newFilePath(QString path);
    void newSpeed(int speed);
    void newBxData(QList<double> newBxData);
    void newMFLData(QList<double> newMFLData);
    void newBxDataAdditional(QMap<QString,QString> newBxDataAdditional);
    void newParameters(ParaGet* para);
    void newFrameNum(int num);
    void newJumpCommand(int num);
    void shutDown();


};

#endif // DISPLAYPANEL_H
