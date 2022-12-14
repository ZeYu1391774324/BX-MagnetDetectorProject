#include "connection.h"
#pragma execution_character_set("utf-8")

#include "frmmain.h"
#include "ui_frmmain.h"
#include "iconhelper.h"
#include "quihelper.h"
#include "panel_password.h"
#include <QDebug>
#include "localpanel.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "binddata.h"



frmMain::frmMain(QWidget *parent) : QWidget(parent), ui(new Ui::frmMain)
{

    ui->setupUi(this);

    // Initiations
    this->initForm();
    this->initStyle();
    this->initLeftMain();
    this->initLeftConfig();
    this->initTableWidget();
    this->initTableWidget_2();
    this->initTableWidget_3();
    this->initConfigPanel();
    this->initConnectionConfigPage();
    this->initParametersConfigPage();
    this->initDiskCtrlPage();
    this->serialPortInit();
    this->initDataWork();
    this->initFrameWork();
    this->initSysInfoLabel();

    //Controllers
    //this->receivingControl();
    this->currentFrameControl();

    //ui->DataReceived->setVisible(false);

    // testBtn
    QString str("55AADC03D4D42B2B00008000000000003D00DC820E2B8000942D8000FF69DFFD415302CDFE64024D3CFE82022E32B030C2ACAC58C2304CB04AACD2B050AC00B00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000080007E00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002B2BD4D4");

    connect(ui->testBtn,&QPushButton::clicked,[=]()mutable{
        qDebug()<<str<<endl;
        qDebug()<<BindData::frameUnencrypt(str)<<endl;
    });



    panel_password * panel_pwd = new panel_password;
    panel_pwd->show();

}

frmMain::~frmMain()
{
    delete ui;
}

bool frmMain::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->widgetTitle) {
        if (event->type() == QEvent::MouseButtonDblClick) {
            on_btnMenu_Max_clicked();
        }
    }
    return QWidget::eventFilter(watched, event);
}

void frmMain::getQssColor(const QString &qss, const QString &flag, QString &color)
{
    int index = qss.indexOf(flag);
    if (index >= 0) {
        color = qss.mid(index + flag.length(), 7);
    }
    //qDebug() << TIMEMS << flag << color;
}

void frmMain::getQssColor(const QString &qss, QString &textColor, QString &panelColor,
                          QString &borderColor, QString &normalColorStart, QString &normalColorEnd,
                          QString &darkColorStart, QString &darkColorEnd, QString &highColor)
{
    getQssColor(qss, "TextColor:", textColor);
    getQssColor(qss, "PanelColor:", panelColor);
    getQssColor(qss, "BorderColor:", borderColor);
    getQssColor(qss, "NormalColorStart:", normalColorStart);
    getQssColor(qss, "NormalColorEnd:", normalColorEnd);
    getQssColor(qss, "DarkColorStart:", darkColorStart);
    getQssColor(qss, "DarkColorEnd:", darkColorEnd);
    getQssColor(qss, "HighColor:", highColor);
}

/*************************************** Initiation -- Start ************************************************************/

void frmMain::initSysInfoLabel(){
    //????????????????????????
    ui->sysInfoLabel->setText("?????????????????????...");
    connect(this,&frmMain::newParameters,[=](ParaGet* para){
        if(para->initiated){
            ui->sysInfoLabel->setText(QString("?????????????????????%1-%2").arg(para->pipeSize,para->pipeType));
            if(para->encrypted){
                qDebug()<<"??????????????????";
            }

        }
        else {
            ui->sysInfoLabel->setText("?????????????????????...");
        }
    });

    //????????????????????????
    connect(this,&frmMain::newByteSpeed,[=](int ByteSpeed){
        ui->byteSpeedLabel->setText(QString("???????????????????????????%1 Byte/s").arg(ByteSpeed));
    });
}

void frmMain::initTableWidget(){
    //?????????????????????
    int width = 1920;
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setColumnWidth(0, width * 0.06);
    ui->tableWidget->setColumnWidth(1, width * 0.10);
    ui->tableWidget->setColumnWidth(2, width * 0.06);
    ui->tableWidget->setColumnWidth(3, width * 0.10);
    ui->tableWidget->setColumnWidth(4, width * 0.10);
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "???????????????" << "???????????????" << "???????????????" << "????????????" << "????????????";
    ui->tableWidget->setHorizontalHeaderLabels(headText);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setAlternatingRowColors(true);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    //????????????
    ui->tableWidget->setRowCount(300);

    for (int i = 0; i < 300; i++) {
        ui->tableWidget->setRowHeight(i, 24);
        QTableWidgetItem * itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem * itemDeviceName = new QTableWidgetItem(QString("???????????????%1").arg(i + 1));
        QTableWidgetItem * itemDeviceAddr = new QTableWidgetItem(QString("?????????"));
        QTableWidgetItem * itemContent = new QTableWidgetItem("???");
        QTableWidgetItem * itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));


        ui->tableWidget->setItem(i, 0, itemDeviceID);
        ui->tableWidget->setItem(i, 1, itemDeviceName);
        ui->tableWidget->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget->setItem(i, 3, itemContent);
        ui->tableWidget->setItem(i, 4, itemTime);
    }
}

void frmMain::initTableWidget_2(){
    //?????????????????????
    int width = 1920;
    ui->tableWidget_2->setColumnCount(5);
    ui->tableWidget_2->setColumnWidth(0, width * 0.06);
    ui->tableWidget_2->setColumnWidth(1, width * 0.10);
    ui->tableWidget_2->setColumnWidth(2, width * 0.06);
    ui->tableWidget_2->setColumnWidth(3, width * 0.10);
    ui->tableWidget_2->setColumnWidth(4, width * 0.10);
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "???????????????" << "???????????????" << "???????????????" << "????????????" << "????????????";
    ui->tableWidget_2->setHorizontalHeaderLabels(headText);
    ui->tableWidget_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_2->setAlternatingRowColors(true);
    ui->tableWidget_2->verticalHeader()->setVisible(false);
    ui->tableWidget_2->horizontalHeader()->setStretchLastSection(true);

    //????????????
    ui->tableWidget_2->setRowCount(150);

    for (int i = 0; i < 150; i++) {
        ui->tableWidget_2->setRowHeight(i, 24);
        QTableWidgetItem * itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem * itemDeviceName = new QTableWidgetItem(QString("???????????????%1").arg(i + 1));
        QTableWidgetItem * itemDeviceAddr = new QTableWidgetItem(QString("?????????"));
        QTableWidgetItem * itemContent = new QTableWidgetItem("???");
        QTableWidgetItem * itemTime = new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));

        ui->tableWidget_2->setItem(i, 0, itemDeviceID);
        ui->tableWidget_2->setItem(i, 1, itemDeviceName);
        ui->tableWidget_2->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget_2->setItem(i, 3, itemContent);
        ui->tableWidget_2->setItem(i, 4, itemTime);
    }
}

void frmMain::initTableWidget_3(){
    //?????????????????????
    int width = 1920;
    ui->tableWidget_3->setColumnCount(5);
    ui->tableWidget_3->setColumnWidth(0, width * 0.06);
    ui->tableWidget_3->setColumnWidth(1, width * 0.10);
    ui->tableWidget_3->setColumnWidth(2, width * 0.06);
    ui->tableWidget_3->setColumnWidth(3, width * 0.06);
    ui->tableWidget_3->setColumnWidth(4, width * 0.06);
    ui->tableWidget_3->verticalHeader()->setDefaultSectionSize(25);

    QStringList headText;
    headText << "??????" <<"????????????" << "????????????" << "????????????" << "??????";
    ui->tableWidget_3->setHorizontalHeaderLabels(headText);
    ui->tableWidget_3->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget_3->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget_3->setAlternatingRowColors(true);
    ui->tableWidget_3->verticalHeader()->setVisible(false);
    ui->tableWidget_3->horizontalHeader()->setStretchLastSection(true);

    //????????????
    ui->tableWidget_3->setRowCount(10);

    QStringList name;
    name << "??????/???????????????" << "??????1????????????" << "??????2????????????" << "??????3????????????" <<
            "??????????????????" << "???????????????" << "??????????????????" << "????????????" << "????????????" << "????????????";

    for (int i = 0; i < 10; i++) {
        ui->tableWidget_3->setRowHeight(i, 24);
        QTableWidgetItem * itemDeviceID = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem * itemDeviceName = new QTableWidgetItem(name.at(i));
        QTableWidgetItem * itemDeviceAddr = new QTableWidgetItem(QString("???????????????"));
        QTableWidgetItem * itemContent = new QTableWidgetItem("15s");
        QTableWidgetItem * itemTime = new QTableWidgetItem("-");

        ui->tableWidget_3->setItem(i, 0, itemDeviceID);
        ui->tableWidget_3->setItem(i, 1, itemDeviceName);
        ui->tableWidget_3->setItem(i, 2, itemDeviceAddr);
        ui->tableWidget_3->setItem(i, 3, itemContent);
        ui->tableWidget_3->setItem(i, 4, itemTime);

    }
}


void frmMain::initForm()
{
    //???????????????
    QUIHelper::setFramelessForm(this);
    //????????????
    IconHelper::setIcon(ui->labIco, 0xf073, 30);
    IconHelper::setIcon(ui->btnMenu_Min, 0xf068);
    IconHelper::setIcon(ui->btnMenu_Max, 0xf067);
    IconHelper::setIcon(ui->btnMenu_Close, 0xf00d);

    //ui->widgetMenu->setVisible(false);
    ui->widgetTitle->setProperty("form", "title");
    //???????????????????????????????????????
    ui->widgetTitle->installEventFilter(this);
    ui->widgetTop->setProperty("nav", "top");

    QFont font;
    font.setPixelSize(25);
    ui->labTitle->setFont(font);
    ui->labTitle->setText("??????/????????????????????????????????????");
    this->setWindowTitle(ui->labTitle->text());

    ui->stackedWidget->setStyleSheet("QLabel{font:12px;}");

    QSize icoSize(32, 32);
    int icoWidth = 85;

    //????????????????????????
    QList<QAbstractButton *> tbtns = ui->widgetTop->findChildren<QAbstractButton *>();
    foreach (QAbstractButton *btn, tbtns) {
        btn->setIconSize(icoSize);
        btn->setMinimumWidth(icoWidth);
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    ui->btnMain->click();

    ui->widgetLeftMain->setProperty("flag", "left");
    ui->widgetLeftConfig->setProperty("flag", "left");
    ui->page1->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(60));
    ui->page2->setStyleSheet(QString("QWidget[flag=\"left\"] QAbstractButton{min-height:%1px;max-height:%1px;}").arg(25));

    // localBtn
    connect(ui->localBtn,&QToolButton::clicked,[=](){
        //qDebug() << "localBtn clicked!";
//        LocalPanel * localpanel = new LocalPanel();
//        localpanel->show();
        FileConversionPanel * fc_Panel = new FileConversionPanel(nullptr,this->localFileList);
        fc_Panel->show();
        connect(fc_Panel,&FileConversionPanel::newLocalFileList,[=](QList<localFile>* lfList){
            this->localFileList=lfList;
        });

    });
}

void frmMain::initStyle()
{
    //???????????????
    QString qss;
    QFile file(":/qss/blacksoft.css");
    if (file.open(QFile::ReadOnly)) {
        qss = QLatin1String(file.readAll());
        QString paletteColor = qss.mid(20, 7);
        qApp->setPalette(QPalette(paletteColor));
        qApp->setStyleSheet(qss);
        file.close();
    }

    //???????????????????????????????????????
    QString textColor, panelColor, borderColor, normalColorStart, normalColorEnd, darkColorStart, darkColorEnd, highColor;
    getQssColor(qss, textColor, panelColor, borderColor, normalColorStart, normalColorEnd, darkColorStart, darkColorEnd, highColor);

    //??????????????????????????????
    this->borderColor = highColor;
    this->normalBgColor = normalColorStart;
    this->darkBgColor = panelColor;
    this->normalTextColor = textColor;
    this->darkTextColor = normalTextColor;
}

void frmMain::buttonClick()
{
    QAbstractButton *b = (QAbstractButton *)sender();
    QString name = b->text();

    QList<QAbstractButton *> tbtns = ui->widgetTop->findChildren<QAbstractButton *>();
    foreach (QAbstractButton *btn, tbtns) {
        btn->setChecked(btn == b);
    }

    if (name == "?????????") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (name == "????????????") {
        ui->stackedWidget->setCurrentIndex(1);
    } else if (name == "????????????") {
        ui->stackedWidget->setCurrentIndex(2);
    } else if (name == "????????????") {
        //ui->stackedWidget->setCurrentIndex(3);
    } else if (name == "????????????") {
        exit(0);
    }
}

void frmMain::initLeftMain()
{
    iconsMain << 0xf030 << 0xf03e << 0xf247 << 0xf247 << 0xf247 << 0xf247 << 0xf247;
    btnsMain << ui->tbtnMain1 << ui->tbtnMain2 << ui->tbtnMain3 << ui->tbtnMain4<< ui->tbtnMain5 << ui->tbtnMain6 << ui->tbtnMain7;

    int count = btnsMain.count();
    for (int i = 0; i < count; ++i) {
        QToolButton *btn = (QToolButton *)btnsMain.at(i);
        btn->setCheckable(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        //ui->stackedWidget_2->setCurrentIndex(i);
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(leftMainClick()));
    }

    IconHelper::StyleColor styleColor;
    styleColor.position = "left";
    styleColor.iconSize = 18;
    styleColor.iconWidth = 35;
    styleColor.iconHeight = 25;
    styleColor.borderWidth = 4;
    styleColor.borderColor = borderColor;
    styleColor.setColor(normalBgColor, normalTextColor, darkBgColor, darkTextColor);
    IconHelper::setStyle(ui->widgetLeftMain, btnsMain, iconsMain, styleColor);
    ui->tbtnMain1->click();
}

void frmMain::initLeftConfig()
{
    iconsConfig << 0xf031 << 0xf036 << 0xf249 << 0xf055 << 0xf05a << 0xf249;
    btnsConfig  << ui->PowerConfigBtn << ui->UserConfigBtn;

    int count = btnsConfig.count();
    for (int i = 0; i < count; ++i) {
        QToolButton *btn = (QToolButton *)btnsConfig.at(i);
        btn->setCheckable(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        connect(btn, SIGNAL(clicked(bool)), this, SLOT(leftConfigClick()));
    }

    IconHelper::StyleColor styleColor;
    styleColor.position = "left";
    styleColor.iconSize = 16;
    styleColor.iconWidth = 20;
    styleColor.iconHeight = 20;
    styleColor.borderWidth = 3;
    styleColor.borderColor = borderColor;
    styleColor.setColor(normalBgColor, normalTextColor, darkBgColor, darkTextColor);
    IconHelper::setStyle(ui->widgetLeftConfig, btnsConfig, iconsConfig, styleColor);
    ui->PowerConfigBtn->click();
}

void frmMain::initConfigPanel(){

    // Buttons Initiation
    connect(ui->ConnectionConfigBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget_Config->setCurrentIndex(0);
    });
    connect(ui->ParameterConfigBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget_Config->setCurrentIndex(2);
    });
    connect(ui->UserConfigBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget_Config->setCurrentIndex(3);
    });
    connect(ui->PowerConfigBtn,&QPushButton::clicked,[=](){
        ui->stackedWidget_Config->setCurrentIndex(1);
    });
}

void frmMain::initConnectionConfigPage(){
    // Initiate Buttons
    connect(ui->setParametersBtn,&QPushButton::clicked,[=](){

        if(ui->pipeTypecomboBox->currentIndex()==0){
            QMessageBox::information(this,"??????","????????????????????????");
            return;
        }
        if(ui->pipeSizecomboBox->currentIndex()==0){
            QMessageBox::information(this,"??????","????????????????????????");
            return;
        }
        this->initParameters(ui->pipeTypecomboBox->currentText(),ui->pipeSizecomboBox->currentText());


    });
    //??????????????????
    connect(ui->OpenSerialButton,&QPushButton::clicked,[=](){
        if(serial->isOpen())                                  // ???????????????????????????????????????
            {
                serial->clear();
                serial->close();
                this->connected=false;
                // ?????????????????????????????????????????????
                ui->OpenSerialButton->setText("????????????");
                // ?????????????????????????????????
                ui->BaudComboBox->setDisabled(false);
                ui->PortBox->setDisabled(false);
                //ui->ParityBox->setDisabled(false);
                //ui->BitBox->setDisabled(false);
                //ui->StopBox->setDisabled(false);
                //ui->ControlBox->setDisabled(false);
                // ????????????????????????????????????
                //ui->SendWordOrder->setDisabled(true);
                ui->SendButton->setDisabled(true);
                // ??????????????????????????????
                ui->OpenSerialButton->setStyleSheet("color: green;");
                // ???????????????????????????
                LED(true);
                // ????????????
                this->clearBuffer();
                ui->DataSend->clear();
            }
            else                                             // ???????????????????????????????????????
            {
                //???????????????????????????
                serial->setPortName(ui->PortBox->currentText());
                //???ReadWrite ??????????????????????????????????????????????????????????????????
                if(!serial->open(QIODevice::ReadWrite))
                {
                    QMessageBox::warning(this,tr("??????"),tr("??????????????????!"),QMessageBox::Ok);
                    return;
                 }
                // ?????????????????????????????????????????????
                ui->OpenSerialButton->setText("????????????");
                // ?????????????????????????????????
                ui->BaudComboBox->setDisabled(true);
                ui->PortBox->setDisabled(true);
                //ui->ParityBox->setDisabled(true);
                //ui->BitBox->setDisabled(true);
                //ui->StopBox->setDisabled(true);
                //ui->ControlBox->setDisabled(true);
                // ????????????????????????????????????
                //ui->SendWordOrder->setDisabled(false);
                ui->SendButton->setDisabled(false);
                // ??????????????????????????????
                ui->OpenSerialButton->setStyleSheet("color: red;");
                // ???????????????????????????
                LED(false);
            }

    });

    // ??????????????????
    connect(ui->CheckModeBtn,&QPushButton::clicked,[=](){
        this->checkMode();
    });

    // CPIO????????????
    connect(ui->CheckGPIOBtn,&QPushButton::clicked,[=](){this->checkGPIO();});

    // ???????????????????????????
    connect(ui->disconnectBtn,&QPushButton::clicked,[=](){
        if(this->checkConnection()){
            this->systemDisconnect();
        }
    });
}

void frmMain::initParametersConfigPage(){


    BindData *binddata = new BindData();

    // initiate buttons
    // ????????????
    connect(ui->bindBtn,&QPushButton::clicked,[=](){


        // check blanks
        if(!this->connected){QMessageBox::information(this,"??????","???????????????????????????????????????");return;};
        if(ui->pipeLabelEdit->text().isEmpty()){QMessageBox::information(this,"??????","????????????????????????");return;};
        if(ui->pipeLengthEdit->text().isEmpty()){QMessageBox::information(this,"??????","????????????????????????");return;};
        if(ui->pipeThicknessEdit->text().isEmpty()){QMessageBox::information(this,"??????","????????????????????????");return;};
        if(ui->pressureEdit->text().isEmpty()){QMessageBox::information(this,"??????","??????????????????????????????");return;};
        if(ui->batteryDateEdit->text().isEmpty()){QMessageBox::information(this,"??????","??????????????????????????????");return;};
        if(ui->workDateTimeEdit->text().isEmpty()){QMessageBox::information(this,"??????","????????????????????????");return;};
        if(ui->FrequencyComboBox->currentText().isEmpty()){QMessageBox::information(this,"??????","????????????????????????");return;};
        if(ui->PowerEdit->text().isEmpty()){QMessageBox::information(this,"??????","????????????????????????");return;};


        // set data
        binddata->pipeLabel=ui->pipeLabelEdit->text();
        binddata->pipeLength=ui->pipeLengthEdit->text();
        binddata->pipeThickness=ui->pipeThicknessEdit->text();
        binddata->Pressure=ui->pressureEdit->text();
        binddata->batteryTime=ui->batteryDateEdit->date();
        binddata->workTime=ui->workDateTimeEdit->dateTime();
        binddata->Frequency=ui->FrequencyComboBox->currentText();
        binddata->Power=ui->PowerEdit->text();

        // check data validation
        if(binddata->pipeThickness.toDouble()<1.0||binddata->pipeThickness.toDouble()>30.0){QMessageBox::warning(this,"??????","??????????????????1.0mm-30.0mm?????????");return;}
        if(binddata->pipeLength.toDouble()<0.1||binddata->pipeLength.toDouble()>500.0){QMessageBox::warning(this,"??????","??????????????????0.1km-500.0km?????????");return;}
        if(binddata->Pressure.toDouble()<0.1||binddata->Pressure.toDouble()>50.0){QMessageBox::warning(this,"??????","????????????????????????0.1MPa-50.0MPa?????????");return;}


        // disable the btn
        ui->bindBtn->setDisabled(true);
        ui->bindingBar->setValue(0);


        qDebug()<<binddata->toString();
        // check if it's in slient mode
        QTimer *timer = new QTimer(this);
        QTimer *timer_second = new QTimer(this);
        timer->start(5000);
        timer_second->start(1000);
        connect(timer_second,&QTimer::timeout,[=](){
            ui->bindingBar->setValue(ui->bindingBar->value()+20);
        });
        this->checkMode();


        // ??????
        connect(timer,&QTimer::timeout,[=](){

            QMessageBox::warning(this,"??????","???????????????????????????????????????????????????");
            ui->bindingBar->setValue(0);
            ui->bindBtn->setDisabled(false);

            timer->stop();
            timer_second->stop();
            timer_second->disconnect();
            ui->ModeEdit->disconnect();
            timer->disconnect();
            return;
        });

        connect(ui->ModeEdit,&QLineEdit::textChanged,[=](){
            if(ui->ModeEdit->text().contains("????????????")){

                timer->stop();
                timer_second->stop();
                ui->bindBtn->setDisabled(false);
                timer_second->disconnect();
                ui->ModeEdit->disconnect();
                timer->disconnect();
                ui->bindingBar->setValue(0);
                //QMessageBox::information(this,"??????","?????????????????????");
                // ??????????????????
                QString systemDateTimeFrame;
                systemDateTimeFrame.append(binddata->bindSystemDateTime());
                systemDateTimeFrame.append(BindData::frameCalculate(binddata->bindSystemDateTime().mid(8)));
                systemDateTimeFrame.append(QString("00"));

                this->ReceiveMode=NULLMODE;     //??????????????????
                serial->write(QByteArray::fromHex(systemDateTimeFrame.toLatin1().data()));  // ??????????????????
                QTimer * timer = new QTimer(this);
                timer->start(50);
                int i=0;            // ???????????????
                connect(timer,&QTimer::timeout,[=]()mutable{
                    ui->bindingBar->setValue(i);
                    i++;
                    if(i>=100||ReceiveMode==UNSUCCESS){         //??????
                        timer->stop();
                        timer->disconnect();
                        QMessageBox::information(this,"??????","???????????????????????????");
                        ui->bindingBar->setValue(0);
                        return;
                    }
                    if(ReceiveMode==SUCCESS){
                        timer->stop();
                        timer->disconnect();
                        serial->write(QByteArray::fromHex(binddata->dataBinding().toLatin1().data()));
                        ui->bindingBar->setValue(100);
                        QMessageBox::information(this,"??????","?????????????????????");
                        return;
                    }
                });


            }
            else if(ui->ModeEdit->text().contains("????????????")){
                timer->stop();
                timer_second->stop();

                ui->bindBtn->setDisabled(false);
                timer_second->disconnect();
                ui->ModeEdit->disconnect();
                timer->disconnect();
                QMessageBox::information(this,"??????","??????????????????????????????????????????????????????");
                ui->bindingBar->setValue(0);
                return;
            }
            else if(ui->ModeEdit->text().contains("????????????")){
                timer->stop();
                timer_second->stop();

                ui->bindBtn->setDisabled(false);
                timer_second->disconnect();
                ui->ModeEdit->disconnect();
                timer->disconnect();
                QMessageBox::information(this,"??????","??????????????????????????????????????????????????????");
                ui->bindingBar->setValue(0);
                return;
            }

        });


    });

    // ??????????????????
    connect(ui->CollectByTimeBtn,&QToolButton::clicked,[=](){
        if(this->connected&&serial->isOpen()){
            if(parameters->initiated){
            QString str=COLLECTMODEHEAD;
            str.append(QString("%1").arg(ui->FrequencyComboBox->currentIndex()+1,2,16,QLatin1Char('0')));
            str.append(BindData::frameCalculate(str.right(BindData::frameDataLength(str))));
            serial->write(QByteArray::fromHex(str.toLatin1().data()));
            cbtPanel = new CollectByTimePanel(nullptr,this->serial);
            //??????????????????????????????
            connect(this,&frmMain::newBxData,cbtPanel,&CollectByTimePanel::updateBxData);               //????????????????????????
            connect(this,&frmMain::newBxDataAdditional,cbtPanel,&CollectByTimePanel::updateBxDataAdditional);   //????????????????????????
            connect(this,&frmMain::newByteSpeed,cbtPanel,&CollectByTimePanel::updateSpeedLabel);                //??????????????????
            connect(this,&frmMain::newParameters,cbtPanel,&CollectByTimePanel::updateParametersLabel);          //????????????????????????
            cbtPanel->setWindowState(Qt::WindowMaximized);
            cbtPanel->show();
            emit this->newParameters(parameters);                                                               //????????????????????????
            }
            else {
                QMessageBox::warning(this,"??????","???????????????????????????");
            }
        }
        else{
            QMessageBox::warning(this,"??????","???????????????????????????");
        }

    });

    // ??????????????????
    connect(ui->CollectByDistanceBtn,&QToolButton::clicked,[=](){
        if(this->connected&&serial->isOpen()){
            if(parameters->initiated){
            QString str=COLLECTMODEHEAD;
            str.append(QString("%1").arg(ui->FrequencyComboBox->currentIndex()+1,2,16,QLatin1Char('0')));
            str.append(BindData::frameCalculate(str.right(BindData::frameDataLength(str))));
            serial->write(QByteArray::fromHex(str.toLatin1().data()));
            cbdPanel = new CollectByDistancePanel(nullptr, this->serial);
            //??????????????????????????????
            connect(this,&frmMain::newBxData,cbdPanel,&CollectByDistancePanel::updateBxData);               //????????????????????????
            connect(this,&frmMain::newBxDataAdditional,cbdPanel,&CollectByDistancePanel::updateBxDataAdditional);   //????????????????????????
            connect(this,&frmMain::newByteSpeed,cbdPanel,&CollectByDistancePanel::updateSpeedLabel);                //??????????????????
            connect(this,&frmMain::newParameters,cbdPanel,&CollectByDistancePanel::updateParametersLabel);          //????????????????????????
            cbdPanel->setWindowState(Qt::WindowMaximized);
            cbdPanel->show();
            emit this->newParameters(parameters);                                                                   //????????????????????????
            }
            else {
                QMessageBox::warning(this,"??????","???????????????????????????");
            }
        }
        else{
            QMessageBox::warning(this,"??????","???????????????????????????");
        }

    });

}

void frmMain::serialPortInit(){
    serial=new QSerialPort;
    // ??????????????????????????????????????????????????????????????????????????????
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()){
        serial->setPort(info);
        if(serial->open(QIODevice::ReadWrite)){
            ui->PortBox->addItem(info.portName());
            serial->close();
        }
        else {
            qDebug() << "?????????????????????????????????";
        }
    }

    // Configuration
    serial->setBaudRate(QSerialPort::Baud115200);       // ???????????????
    serial->setParity(QSerialPort::NoParity);           //??????????????????????????????
    serial->setStopBits(QSerialPort::OneStop);           //?????????????????????1???
    serial->setFlowControl(QSerialPort::NoFlowControl);  // ????????????????????????


    ReFreshSerialPort(0);

    //connect(serial,&QSerialPort::readyRead,this,&frmMain::dataReveived);
    connect(ui->SetConnectionBtn,&QPushButton::clicked,this,&frmMain::connectSerialPort);
    connect(ui->SendButton,&QPushButton::clicked,this,&frmMain::dataSend);

}

void frmMain::LED(bool changeColor){
    if(changeColor == false)
        {
            // ????????????
            ui->LED->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(0, 229, 0, 255), stop:1 rgba(255, 255, 255, 255));border-radius:12px;");
            ui->ConnectionStateEdit->setText("??????????????????");
        }
        else
        {
            // ????????????
            ui->LED->setStyleSheet("background-color: qradialgradient(spread:pad, cx:0.5, cy:0.5, radius:0.5, fx:0.5, fy:0.5, stop:0 rgba(255, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));border-radius:12px;");
            ui->ConnectionStateEdit->setText("??????????????????");
        }
}

bool frmMain::checkConnection(){
    if(this->connected&&serial->isOpen()){
        return true;
    }
    else{
        QMessageBox::warning(this,"??????","?????????????????????????????????????????????????????????");
        return false;
    }
}

bool frmMain::checkParameters(){
    bool flag=this->parameters->initiated;
    if(!flag){
        QMessageBox::warning(this,"??????","????????????????????????");
    }
    return flag;
}

void frmMain::clearBuffer(){

    //ui->DataReceived->setText(ui->DataReceived->toPlainText().remove(0,Uncode_head));

    //  clear in mainthread
//    this->data.remove(0,Uncode_head);
//    emit this->dataChanges();
//    this->Uncode_head=0;
//    this->Uncode_end=0;

    //clear in subthread
    emit this->clearDataWork(this->Uncode_head,this->Uncode_end);


}


// Disk Control Page Initiation
void frmMain::initDiskCtrlPage(){

    //Initiate Buttons
    connect(ui->DiskConnectBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(DISKCONNECTFRAME).toLatin1().data()));});
    connect(ui->DiskDisconnectBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(DISKDISCONNECTFRAME).toLatin1().data()));});
}


void frmMain::initDataWork(){
    QThread * dataThread = new QThread;
    DataWork * datawork = new DataWork(this->serial);
    datawork->moveToThread(dataThread);
    dataThread->start();
    connect(serial,&QSerialPort::readyRead,datawork,&DataWork::receiveData);

//    QThread * uncodeThread=new QThread;
//    UncodeWork * uncodework = new UncodeWork;
//    uncodework->moveToThread(uncodeThread);
//    uncodeThread->start();
    UncodeWork * uncodework = new UncodeWork;
    connect(datawork,&DataWork::dataChanged,uncodework,&UncodeWork::setData);
    connect(uncodework,&UncodeWork::clearDataWork,datawork,&DataWork::clearBuffer);
    connect(datawork,&DataWork::DataWorkCleared,uncodework,&UncodeWork::resetHeadandEnd);
    connect(uncodework,&UncodeWork::currentFrameChanges,this,&frmMain::currentFrameChanges);
    connect(datawork,&DataWork::newByteSpeed,this,&frmMain::newByteSpeed);
//    connect(datawork,&DataWork::dataChanged,[=](QString newData){
//        this->data=newData;
//        emit this->dataChanges();
//    });
//    connect(this,&frmMain::clearDataWork,datawork,&DataWork::clearBuffer);
//    connect(datawork,&DataWork::DataWorkCleared,[=](){
//        this->Uncode_head=0;
//        this->Uncode_end=0;
//    });

}

void frmMain::initFrameWork(){

    // 8&10&12&14inch???????????????????????????????????????
    QThread * frameWorkThread = new QThread;
    FrameWork_8_10_12_14_Inch_bx * framework_8_10_12_14_inch_bx = new FrameWork_8_10_12_14_Inch_bx;
    framework_8_10_12_14_inch_bx->moveToThread(frameWorkThread);
    frameWorkThread->start();
    connect(this,&frmMain::newFrame_8_10_12_14_inch_bx,framework_8_10_12_14_inch_bx,&FrameWork_8_10_12_14_Inch_bx::setFrameList);  //???8&10&12&14inch????????????????????????frameWork??????????????????????????????
    connect(this,&frmMain::newParameters,framework_8_10_12_14_inch_bx,&FrameWork_8_10_12_14_Inch_bx::setParameters);
    //frameWork???????????????????????????
    connect(framework_8_10_12_14_inch_bx,&FrameWork_8_10_12_14_Inch_bx::newBxData,this,&frmMain::newBxData);    //?????????????????????????????????????????????
    connect(framework_8_10_12_14_inch_bx,&FrameWork_8_10_12_14_Inch_bx::newBxDataAdditional,this,&frmMain::newBxDataAdditional);    //???????????????????????????????????????????????????


}

/*************************************** Initiation -- End ************************************************************/



void frmMain::ReFreshSerialPort(int index){
    QStringList portNameList;
    if(index!=0){
        serial->setPortName(ui->PortBox->currentText());
    }
    else{
        ui->PortBox->clear();
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()){     //???????????????
            portNameList.append(info.portName());
        }
            ui->PortBox->addItems(portNameList);
            ui->PortBox->setCurrentIndex(0);                             // ??????????????????COM1
            serial->setPortName(ui->PortBox->currentText());
    }
}


void frmMain::leftMainClick()
{
    QAbstractButton *b = (QAbstractButton *)sender();
    QString name = b->text();

    int count = btnsMain.count();
    for (int i = 0; i < count; ++i) {
        QAbstractButton *btn = btnsMain.at(i);
        btn->setChecked(btn == b);
        if(btn == b){
           ui->stackedWidget_2->setCurrentIndex(i);
        }
    }
    //ui->lab1->setText(name);
}

void frmMain::leftConfigClick()
{
    QToolButton *b = (QToolButton *)sender();
    QString name = b->text();

    int count = btnsConfig.count();
    for (int i = 0; i < count; ++i) {
        QAbstractButton *btn = btnsConfig.at(i);
        btn->setChecked(btn == b);
    }

    //ui->lab2->setText(name);
}

void frmMain::on_btnMenu_Min_clicked()
{
    showMinimized();
}



void frmMain::on_btnMenu_Max_clicked()
{
    static bool max = false;
    static QRect location = this->geometry();

    if (max) {
        this->setGeometry(location);
    } else {
        location = this->geometry();
        this->setGeometry(QUIHelper::getScreenRect());
    }

    this->setProperty("canMove", max);
    max = !max;
}

void frmMain::on_btnMenu_Close_clicked()
{
    close();
}

void frmMain::closeEvent(QCloseEvent * e){
    if (QMessageBox::question(this,"????????????????????????","???????????????????????????")==QMessageBox::Yes){
//        qDebug() << "Exit the application!";
//        QApplication * app;
//        app->exit(0);
        exit(0);
    }
    else{
        e->ignore();
    }
}

// Serial data Send & Received
void frmMain::connectSerialPort(){
    if(!serial->isOpen()){
        QMessageBox::information(this,"??????","????????????????????????????????????");
        return;
    }
    QTimer *timer =new QTimer(this);
    timer->start(5000);
    ui->ConnectionStateEdit->setText("?????????????????????????????????????????????......");
    this->checkMode();
    connect(timer,&QTimer::timeout,[=](){
        if(!(this->connected)){
            ui->ConnectionStateEdit->setText("?????????????????????");
        }
        else{
            ui->ConnectionStateEdit->setText("??????????????????");
        }
       timer->stop();
       timer->disconnect();
    });


}
void frmMain::dataSend(){
    if(!serial->isOpen()){
        QMessageBox::information(this,"??????","????????????????????????????????????");
        return;
    }
    serial->write(QByteArray::fromHex(ui->DataSend->toPlainText().toLatin1().data()));      // ??????????????????
}
void frmMain::dataReveived(){
    char BUF[512] = {0};                                       // ??????????????????????????????
    //clearBuffer();
        QByteArray res = serial->readAll();                      // ????????????
        QString hexRes =res.toHex().toUpper();


        if(!hexRes.isEmpty())                                 // ???????????????
        {

            data+=hexRes;                         // ??????????????????????????????????????????????????????
            emit this->dataChanges();

            //ui->DataReceived->setText(str);

//            // Update Mode
//            if(ui->DataReceived->toPlainText().contains(SLIENTMODE)){
//                 ui->ModeEdit->setText("????????????");
//            }
//            else if(ui->DataReceived->toPlainText().contains(TESTMODE)){
//                ui->ModeEdit->setText("????????????");
//            }
//            else if(ui->DataReceived->toPlainText().contains(WORKMODE)){
//                 ui->ModeEdit->setText("????????????");
//            }
            //qDebug() << "str info: " << ui->DataReceived->toPlainText();

//             // ???????????????????????????????????????????????????????????????????????????
//            int index = str.indexOf("\r\n");                // ?????????????????????????????????????????????-1
//            if(index != -1)
//            {
//                snprintf(BUF,500,"%s", str.left(index + 2).toUtf8().data()); // QString??????char * ??????
//                qDebug() << "BUF info: " << BUF;        // ????????????????????????
//                str.remove(0,index + 2);

//                // ?????????????????????????????????????????????????????????
//                // .....

//            }

        }
        //this->dataUncode();


}
/*
void frmMain::dataUncode(){


    //data=ui->DataReceived->toPlainText();
    qDebug()<<this->Uncode_head<<"---"<<this->Uncode_end<<"---"<<data.length();

    // ??????????????????
//    while (!data.mid(this->Uncode_head,4).contains(FRAMEHEAD)){   //????????????
//        this->Uncode_head++;
//        if(Uncode_head>data.length()-8){        // ????????????????????????
//            this->Uncode_head=this->Uncode_end;
//            return;
//        }
//    }
//    if(Uncode_head>data.length()-8){        // ????????????????????????
//        this->Uncode_head=this->Uncode_end;
//        return;
//    }


    // ?????????????????????
    if(data.indexOf(FRAMEHEAD,this->Uncode_head)==-1){        // ????????????????????????
        this->Uncode_head=this->Uncode_end;
        return;
    }
    else{
        this->Uncode_head=data.indexOf(FRAMEHEAD,this->Uncode_head);
}




    int frameDataLength=BindData::frameDataLength(data.mid(Uncode_head,8));
    this->Uncode_end=this->Uncode_head+8+frameDataLength;
    if(this->Uncode_end>data.length()-2){             // ????????????????????????

        if(!dataTimer->isActive()){
            //qDebug()<<this->Uncode_end<<"---"<<data.length()-2;
            dataTimer->start(100);                 // ??????0.1????????????????????????
        }
        this->Uncode_end=this->Uncode_head;
        return;
    }
    else{
        dataTimer->stop();
        // ???????????????
        QString frameSum=BindData::frameCalculate(data.mid(Uncode_head+8,frameDataLength));
        QString sumData=data.mid(this->Uncode_end,2);
        //qDebug()<<data.mid(Uncode_head+8,2*frameLength)<<"---"<<frameSum<<"--------"<<sumData;
        if(frameSum==sumData){
            this->CurrentFrame=data.mid(this->Uncode_head,10+frameDataLength);
            emit this->currentFrameChanges(this->CurrentFrame);
            ui->ReceivedFrameEdit->setText(this->CurrentFrame);

            this->Uncode_end+=2;                // ???????????????????????????
            this->Uncode_head=this->Uncode_end;
        }
        if(frameSum!=sumData){
            //?????????????????????????????????
            this->Uncode_end=Uncode_head+4;
            this->Uncode_head=this->Uncode_end;
        }
    }


}
*/
/*
void frmMain::receivingControl(){
    // ????????????????????????
    int ReceivedDataLength_old = 0;
    int ReceivedDataLength_new = 0;
    QTimer * timer = new QTimer(this);
    timer->start(5000);
    connect(timer,&QTimer::timeout,[=]()mutable{
        ReceivedDataLength_new = data.length();
        if((ReceivedDataLength_new>ReceivedDataLength_old) && (data.length()<CLEARBUffER)){
            ReceivedDataLength_old=ReceivedDataLength_new;
        }
        else{
            ReceivedDataLength_old = 0;
            ReceivedDataLength_new = 0;
            this->clearBuffer();              //????????????????????????

        }
    });

    //???????????????
    QTimer * uncodeTimer = new QTimer(this);
    uncodeTimer->start(1);
    connect(uncodeTimer,&QTimer::timeout,[=](){
        this->dataUncode();
    });


    //?????????????????????
    this->dataTimer = new QTimer(this);
    connect(dataTimer,&QTimer::timeout,[=](){

        dataTimer->stop();
        //?????????????????????????????????
        this->Uncode_end=this->Uncode_head+4;
        this->Uncode_head=this->Uncode_end;
    });

    //?????????????????????
//    connect(this,&frmMain::dataChanges,[=](){
//        this->ui->DataReceived->setText(data);
//    });

}
*/

void frmMain::currentFrameControl(){
    QStringList frameHeadList;
    QString frameHead;
    frameHeadList << MODECHECKHEAD << THREEBYTEHEAD << BX_8_10_12_14_INCHHEAD;

    connect(this,&frmMain::currentFrameChanges,[=](QString currentframe)mutable{
        this->CurrentFrame=currentframe;
        this->ui->ReceivedFrameEdit->setText(this->CurrentFrame);
        frameHead=currentframe.left(8);

        // ??????????????????????????????????????????
        switch (frameHeadList.indexOf(frameHead)) {         //?????????????????????
        case 0:
            this->modeControl(currentframe);
            break;
        case 1:
            if(currentframe.left(12)==GPIOCHECKHEAD){       //??????????????????GPIO??????
                this->GPIOControl(currentframe);
            }
            break;
        case 2:
            if(currentframe.length()==BX_8_10_12_14_INCHFRAMELENGTH){
                emit this->newFrame_8_10_12_14_inch_bx(currentframe);       //??????????????????????????????????????????
            }
            break;
        default:
                emit this->newFrame_8_10_12_14_inch_bx(currentframe);       //??????????????????????????????????????????
            break;
        }

    });
}

void frmMain::modeControl(QString frame){
    QStringList modeList;
    QString mode;
    modeList<<SLIENTMODE<<TESTMODE<<WORKMODE<<SUCCESS<<UNSUCCESS;
    mode=NULLMODE;
    mode=BindData::frameReverse(frame.mid(8,4));

    switch (modeList.indexOf(mode)) {
        case 0:
            this->ReceiveMode=SLIENTMODE;
            break;
        case 1:
            this->ReceiveMode=TESTMODE;
            break;
        case 2:
            this->ReceiveMode=WORKMODE;
            break;
        case 3:
            this->ReceiveMode=SUCCESS;
            emit this->returnedFrame_SUCCESS();
            break;
        case 4:
            this->ReceiveMode=UNSUCCESS;
            emit this->returnedFrame_UNSUCCESS();
            break;
        default:
            break;
    }

//    connect(ui->ReceivedFrameEdit,&QTextEdit::textChanged,[=]()mutable{
//        mode=NULLMODE;
//        if(ui->ReceivedFrameEdit->toPlainText().left(8).contains("55AA0200")){
//            mode=BindData::frameReverse(ui->ReceivedFrameEdit->toPlainText().mid(8,4));
//        }
//        switch (modeList.indexOf(mode)) {
//        case 0:
//            this->ReceiveMode=SLIENTMODE;
//            break;
//        case 1:
//            this->ReceiveMode=TESTMODE;
//            break;
//        case 2:
//            this->ReceiveMode=WORKMODE;
//            break;
//        case 3:
//            this->ReceiveMode=SUCCESS;
//            break;
//        case 4:
//            this->ReceiveMode=UNSUCCESS;
//            break;
//        default:
//            break;
//        }
//    });

}

void frmMain::GPIOControl(QString frame){
    bool flag;
    this->GPIO=QString("%1").arg(frame.mid(12,2).toInt(&flag,16),8,2,QLatin1Char('0'));
    ui->GPIOEdit->setText(this->GPIO);
    //qDebug()<<this->GPIO<<"---"<<frame.mid(12,2);
}

void frmMain::checkMode(){

    this->ReceiveMode=NULLMODE;
    QTimer *timer = new QTimer(this);
    QTimer * questTimer = new QTimer(this);
    timer->start(5000);
    ui->ModeEdit->setText("???????????????...");
    serial->write(QByteArray::fromHex(QString(MODECHECKFRAME).toLatin1().data()));  //???????????????
//    connect(ui->ReceivedFrameEdit,&QTextEdit::textChanged,[=](){
//        if(ui->ReceivedFrameEdit->toPlainText().contains(SLIENTMODE)){
//             ui->ConnectionStateEdit->setText("??????????????????");
//             this->conncted=true;
//             ui->ModeEdit->setText("????????????");
//        }
//        else if(ui->ReceivedFrameEdit->toPlainText().contains(TESTMODE)){
//            ui->ConnectionStateEdit->setText("??????????????????");
//            this->conncted=true;
//            ui->ModeEdit->setText("????????????");
//        }
//        else if(ui->ReceivedFrameEdit->toPlainText().contains(WORKMODE)){
//            ui->ConnectionStateEdit->setText("??????????????????");
//            this->conncted=true;
//            ui->ModeEdit->setText("????????????");
//        }
//    });
    questTimer->start(50);
    connect(questTimer,&QTimer::timeout,[=](){
        if(this->ReceiveMode==SLIENTMODE){
            ui->ConnectionStateEdit->setText("??????????????????");
            this->connected=true;
            ui->ModeEdit->setText("????????????");
            questTimer->stop();
            timer->stop();
            questTimer->disconnect();
            timer->disconnect();
        }
        else if(this->ReceiveMode==TESTMODE){
            ui->ConnectionStateEdit->setText("??????????????????");
            this->connected=true;
            ui->ModeEdit->setText("????????????");
            questTimer->stop();
            timer->stop();
            questTimer->disconnect();
            timer->disconnect();
        }
        else if(this->ReceiveMode==WORKMODE){
            ui->ConnectionStateEdit->setText("??????????????????");
            this->connected=true;
            ui->ModeEdit->setText("????????????");
            questTimer->stop();
            timer->stop();
            questTimer->disconnect();
            timer->disconnect();
        }
    });
    connect(timer,&QTimer::timeout,[=](){
        if(!(this->ReceiveMode==SLIENTMODE||this->ReceiveMode==TESTMODE||this->ReceiveMode==WORKMODE)){
            ui->ModeEdit->setText("??????????????????...");
        }
        questTimer->stop();
        timer->stop();
        questTimer->disconnect();
        timer->disconnect();
    });



}

void frmMain::checkGPIO(){
    serial->write(QByteArray::fromHex(QString(GPIOCHECKFRAME).toLatin1().data()));

}

void frmMain::systemDisconnect(){
    QTimer *timer = new QTimer;
    timer->start(50);
    int count=0;
    this->ReceiveMode=NULLMODE;
    serial->write(QByteArray::fromHex(QString(DISCONNECTFRAME).toLatin1().data()));
    connect(timer,&QTimer::timeout,[=]()mutable{
        count++;
        if(count==100){    //????????????????????????
            timer->stop();
            timer->disconnect();
            QMessageBox::warning(this,"??????????????????","???????????????????????????????????????????????????");
        }

        else if(ReceiveMode==SUCCESS){
            this->connected=false;
            timer->stop();
            timer->disconnect();
            QMessageBox::information(this,"??????????????????","?????????????????????????????????");
        }
        else if(ReceiveMode==UNSUCCESS){
            timer->stop();
            timer->disconnect();
            QMessageBox::warning(this,"??????????????????","???????????????????????????????????????????????????");
        }
    });

}

void frmMain::initParameters(QString type, QString size){
    parameters = new ParaGet(type,size,ui->encryptStatComboBox->currentIndex());
    //qDebug()<<this->parameters->dataPara.data19_36_len<<this->parameters->initiated;
    emit this->newParameters(parameters);
    if(this->parameters->initiated){
        QMessageBox::information(this,"??????","???????????????????????????");
    }
    else {
        QMessageBox::information(this,"??????","????????????????????????");
    }
}



