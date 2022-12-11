#ifndef COLLECTBYTIMEPANEL_H
#define COLLECTBYTIMEPANEL_H

#include <QWidget>
#include <QSerialPort>

// BufferCtrl Parameters
#define CLEARBUffER 4096        // 一级缓存区清理阈值

// Frame Head 用于分发数据报
#define MODECHECKHEAD "55AA0200"
#define THREEBYTEHEAD "55AA0300"
#define GPIOCHECKHEAD "55AA03008001"

// Frames of Commands (Software to Device)
// heads
#define COLLECTMODEHEAD "55AA04006C6C01"
// frames
#define MODECHECKFRAME "55AA02005151A2"
#define GPIOCHECKFRAME "55AA0200800181"
#define DISKCONNECTFRAME "55AA03005B5B01B7"
#define DISKDISCONNECTFRAME "55AA0300595902B4"
#define COLLECTBYTIMEFRAME "55AA0300585801B1"
#define COLLECTBYDISTANCEFRAME "55AA0300585803B3"
#define STOPCOLLECTFRAME "55AA0300585802B2"

// Receive Mode Definition
#define SLIENTMODE "5656"
#define TESTMODE "5757"
#define WORKMODE "5858"
#define NULLMODE "0000"
#define SUCCESS "0001"
#define UNSUCCESS "0002"
#define FRAMEHEAD "55AA"

// Send Mode Definition
#define CONFIGUREWORKMODE "5757"


namespace Ui {
class CollectByTimePanel;
}

class CollectByTimePanel : public QWidget
{
    Q_OBJECT

public:
    explicit CollectByTimePanel(QWidget *parent = nullptr, QSerialPort *serial= nullptr);
    ~CollectByTimePanel();

    // 变形数据列表
    QList<QVector<double>> bxDataList;
    int bxData_RoadsNum=54;
    int dataCount=0;

    QSerialPort *serial;
    void initPanel();
    void initPlots();

private:
    Ui::CollectByTimePanel *ui;
};

#endif // COLLECTBYTIMEPANEL_H
