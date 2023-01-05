#ifndef FRMMAIN_H
#define FRMMAIN_H

#include "QtSerialPort/qserialport.h"
#include "connection.h"
#include "displaypanel.h"
#include "testpanel.h"
#include "collectbytimepanel.h"
#include "collectbydistancepanel.h"
#include "workers/datawork.h"
#include "workers/uncodework.h"
#include "workers/framework_8_10_12_14_inch_bx.h"
#include "paraget.h"
#include "fileconversionpanel.h"

#include <QWidget>
#include <QCloseEvent>

// BufferCtrl Parameters
#define CLEARBUffER 4096        // 一级缓存区清理阈值

// Frame Head 用于分发数据报
#define MODECHECKHEAD "55AA0200"
#define THREEBYTEHEAD "55AA0300"
#define GPIOCHECKHEAD "55AA03008001"
#define BX_8_10_12_14_INCHHEAD "55AABE00"

// Frame Length 用于分发数据报
#define BX_8_10_12_14_INCHFRAMELENGTH 390

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
#define DISCONNECTFRAME "55AA0300696901D3"

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

class QAbstractButton;

namespace Ui {
class frmMain;
}

class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

    void closeEvent(QCloseEvent * e);
    Connection *connection;

    // Serial Port
    void serialPortInit();                  //初始化串口
    void ReFreshSerialPort(int index);      //刷新串口
    void connectSerialPort();               //打开串口
    void LED(bool changeColor);             //串口指示灯
    bool checkConnection();                  //检查串口连接状态
    bool checkParameters();                 //检查参数设置

    // Data Receiving and Uncoding
    void dataSend();
    void dataReveived();                    //一级缓存区持续接收
    void dataUncode();                      //二级缓存区解析数据报
    void receivingControl();                //数据接收控制
    void clearBuffer();                     //清理一级缓存区

    // Frame Analizing
    void currentFrameControl();             //当前帧处理
    void modeControl(QString frame);        //模式解析
    void GPIOControl(QString frame);        //GPIO解析

    // User Commands
    void checkMode();                       //模式检查
    void checkGPIO();                       //CPIO检查
    void systemDisconnect();                //断开连接并关机

    // Global parameters
    QSerialPort *serial;                    //串口指针
    bool connected = false;                 //串口连接状态
    CollectByTimePanel *cbtPanel;           //时间采集面板
    CollectByDistancePanel *cbdPanel;       //里程采集面板
    TestPanel *testPanel;                   //传感器测试面板
    ParaGet *parameters=new ParaGet("请选择产品类型","请选择产品尺寸",0);                    //系统参数信息
    QList<localFile>* localFileList=nullptr;        //本地文件信息

protected:
    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::frmMain *ui;

    QList<int> iconsMain;
    QList<QAbstractButton *> btnsMain;

    QList<int> iconsConfig;
    QList<QAbstractButton *> btnsConfig;

private:
    //根据QSS样式获取对应颜色值
    QString borderColor;
    QString normalBgColor;
    QString darkBgColor;
    QString normalTextColor;
    QString darkTextColor;


    // Global parameters
    QTimer *dataTimer;              //超时计时器
    QString data;                   //当前全部数据
    QString CurrentFrame;           //当前数据报
    QString ReceiveMode="0000";     //接收模式
    QString GPIO="0";               //GPIO
    int Uncode_head=0;              //解析报头
    int Uncode_end=0;               //解析报尾
    int ByteSpeed=0;                //串口流量



    void getQssColor(const QString &qss, const QString &flag, QString &color);
    void getQssColor(const QString &qss, QString &textColor,
                     QString &panelColor, QString &borderColor,
                     QString &normalColorStart, QString &normalColorEnd,
                     QString &darkColorStart, QString &darkColorEnd,
                     QString &highColor);
    void initTableWidget();
    void initTableWidget_2();
    void initTableWidget_3();


/*****************  Initiation Functions Start  *****************************/
    // Initiate Pages and Panels
    void initDataWork();                //初始化数据接收子线程
    void initFrameWork();               //初始化数据报解析子线程
    void initConfigPanel();             //初始化系统设置页
    void initConnectionConfigPage();    //初始化串口设置页面
    void initParametersConfigPage();    //初始化参数设置页面
    void initParameters(QString type, QString size);//初始化参数
    void initSysInfoLabel();             //初始化系统信息显示

    //硬盘链接页初始化
    void initDiskCtrlPage();            //初始化硬盘连接页

/*****************  Initiation Functions End  *****************************/

signals:
    void dataChanges();
    void clearDataWork(int head, int end);
    void currentFrameChanges(QString currentframe);     // 解析到新的数据报信号
    void newFrame_8_10_12_14_inch_bx(QString frame);    //解析出新的8&10&12&14inch变形帧
    void newBxData(QList<double> bxData);               //得到新的一组变形数据
    void newBxDataAdditional(QMap<QString,QString> bxDataAdditional);     //得到新的一组额外显示数据
    void returnedFrame_SUCCESS();                       //串口返回成功指令（SUCCESS FRAME）
    void returnedFrame_UNSUCCESS();                       //串口返回失败指令（UNSUCCESS FRAME）
    void newParameters(ParaGet*);                       //初始化产品型号参数
    void newByteSpeed(int);                             //更新串口流量信息
    void newTestResult(int index, bool stat);                                //更新传感器检测结果信息


private slots:
    void initForm();
    void initStyle();
    void buttonClick();
    void initLeftMain();
    void initLeftConfig();
    void leftMainClick();
    void leftConfigClick();


private slots:
    void on_btnMenu_Min_clicked();
    void on_btnMenu_Max_clicked();
    void on_btnMenu_Close_clicked();
};

#endif // FRMMAIN_H
