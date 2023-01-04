#include "displaypanel.h"
#include "ui_displaypanel.h"

DisplayPanel::DisplayPanel(QWidget *parent, ParaGet *para) :
    QWidget(parent),
    ui(new Ui::DisplayPanel)
{
    ui->setupUi(this);
    this->parameters=para;
    this->initWorkers();
    this->initPanel();
    this->initPlots();

}

DisplayPanel::~DisplayPanel()
{
    delete ui;
}


void DisplayPanel::initPanel(){
    ui->ParametersLabel->setText(QString("当前产品参数：%1-%2").arg(parameters->pipeSize).arg(parameters->pipeType));
    ui->jumpEdit->setValidator(new QIntValidator(ui->jumpEdit));
    // initiate buttons
    // Select File Button
    connect(ui->SelectFileBtn,&QPushButton::clicked,[=](){
        QString filePath=QFileDialog::getOpenFileName(this,"Open File","C:\\Users\\DELL\\Desktop");
        filePath=QDir::toNativeSeparators(filePath);
        ui->filePathEdit->setText(filePath);
        emit this->newFilePath(filePath);
    });

    // stackWidget Selection comBox
    connect(ui->bxDataRoadsSelectingComboBox,&QComboBox::currentTextChanged,[=](){
        ui->stackedWidget->setCurrentIndex(ui->bxDataRoadsSelectingComboBox->currentIndex());
    });
    // initiate bxDataRoads
    for (int i = 0; i <= bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        this->bxDataList.append(QVector<double>());
    }
    // jumpBtn
    connect(ui->jumpBtn,&QPushButton::clicked,[=](){
        int num = ui->jumpEdit->text().toInt();
        if(frameNum==0){
            QMessageBox::information(this,"提示","请先读入数据文件！");
            return;
        }
        if(num<=0||num>frameNum){
            QMessageBox::information(this,"提示",QString("请输入有效跳转帧序号！（1-%1）").arg(frameNum));
            return;
        }
        emit this->newJumpCommand(num);

    });

    //update plots and additional informations
    connect(this,&DisplayPanel::newBxData,this,&DisplayPanel::updateBxData);
    connect(this,&DisplayPanel::newBxDataAdditional,this,&DisplayPanel::updateBxDataAdditional);
    connect(this,&DisplayPanel::newFrameNum,[=](int num){
        this->frameNum=num;
        ui->dataInfoLabel->setText(QString("数据已读入，共%1帧").arg(frameNum));
    });

}

void DisplayPanel::initWorkers(){
    qRegisterMetaType<QList<double>>("QList<double>");
    qRegisterMetaType<QMap<QString,QString>>("QMap<QString,QString>");
    QThread *subthread = new QThread;
    DisplayWork *displaywork = new DisplayWork;
    displaywork->moveToThread(subthread);
    subthread->start();
    displaywork->setParameters(parameters);
    connect(displaywork,&DisplayWork::newBxData,this,&DisplayPanel::newBxData);
    connect(displaywork,&DisplayWork::newBxDataAdditional,this,&DisplayPanel::newBxDataAdditional);
    connect(displaywork,&DisplayWork::newFrameNum,this,&DisplayPanel::newFrameNum);
    connect(this,&DisplayPanel::newFilePath,displaywork,&DisplayWork::readFile);
    connect(this,&DisplayPanel::newJumpCommand,displaywork,&DisplayWork::jumpCommand);

    QTimer *dataTimer = new QTimer;
    QTimer *additionalTimer = new QTimer;
    connect(dataTimer,&QTimer::timeout,displaywork,&DisplayWork::uncodeFrame);
    connect(additionalTimer,&QTimer::timeout,displaywork,&DisplayWork::uncodeFrame_additional);
    connect(ui->frameSpeedSpinBox,&QSpinBox::textChanged,[=](){
        this->interval=1000/ui->frameSpeedSpinBox->value();
        if(dataTimer->isActive()){
            dataTimer->setInterval(interval);
        }
    });
    connect(ui->StartBtn,&QToolButton::clicked,[=](){
        emit this->newParameters(parameters);
        this->interval=1000/ui->frameSpeedSpinBox->value();
        dataTimer->start(interval);
        additionalTimer->start(500);
        ui->StartBtn->setDisabled(true);
    });
    connect(ui->StopBtn,&QToolButton::clicked,[=](){
        dataTimer->stop();
        additionalTimer->stop();
        ui->StartBtn->setDisabled(false);
    });
    connect(ui->restartBtn,&QToolButton::clicked,[=](){
        emit this->newParameters(parameters);
        this->interval=1000/ui->frameSpeedSpinBox->value();
        displaywork->restartCommand();
        if(!dataTimer->isActive()){
            dataTimer->start(interval);
        }
        if(!additionalTimer->isActive()){
            additionalTimer->start(500);
        }
    });
    connect(this,&DisplayPanel::shutDown,[=](){
        dataTimer->stop();
        additionalTimer->stop();
        subthread->exit();
    });
}

void DisplayPanel::initPlots(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
            ui->DisplayPlot1->addGraph();     //添加曲线
            ui->DisplayPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 2:
            ui->DisplayPlot1->addGraph();     //添加曲线
            ui->DisplayPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 3:
            ui->DisplayPlot1->addGraph();     //添加曲线
            ui->DisplayPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 4:
            ui->DisplayPlot1->addGraph();     //添加曲线
            ui->DisplayPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 5:
            ui->DisplayPlot1->addGraph();     //添加曲线
            ui->DisplayPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 6:
            ui->DisplayPlot1->addGraph();     //添加曲线
            ui->DisplayPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 7:
            ui->DisplayPlot2->addGraph();     //添加曲线
            ui->DisplayPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 8:
            ui->DisplayPlot2->addGraph();     //添加曲线
            ui->DisplayPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 9:
            ui->DisplayPlot2->addGraph();     //添加曲线
            ui->DisplayPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 10:
            ui->DisplayPlot2->addGraph();     //添加曲线
            ui->DisplayPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 11:
            ui->DisplayPlot2->addGraph();     //添加曲线
            ui->DisplayPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 12:
            ui->DisplayPlot2->addGraph();     //添加曲线
            ui->DisplayPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 13:
            ui->DisplayPlot3->addGraph();     //添加曲线
            ui->DisplayPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 14:
            ui->DisplayPlot3->addGraph();     //添加曲线
            ui->DisplayPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 15:
            ui->DisplayPlot3->addGraph();     //添加曲线
            ui->DisplayPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 16:
            ui->DisplayPlot3->addGraph();     //添加曲线
            ui->DisplayPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 17:
            ui->DisplayPlot3->addGraph();     //添加曲线
            ui->DisplayPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 18:
            ui->DisplayPlot3->addGraph();     //添加曲线
            ui->DisplayPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 19:
            ui->DisplayPlot4->addGraph();     //添加曲线
            ui->DisplayPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 20:
            ui->DisplayPlot4->addGraph();     //添加曲线
            ui->DisplayPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 21:
            ui->DisplayPlot4->addGraph();     //添加曲线
            ui->DisplayPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 22:
            ui->DisplayPlot4->addGraph();     //添加曲线
            ui->DisplayPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 23:
            ui->DisplayPlot4->addGraph();     //添加曲线
            ui->DisplayPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 24:
            ui->DisplayPlot4->addGraph();     //添加曲线
            ui->DisplayPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 25:
            ui->DisplayPlot5->addGraph();     //添加曲线
            ui->DisplayPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 26:
            ui->DisplayPlot5->addGraph();     //添加曲线
            ui->DisplayPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 27:
            ui->DisplayPlot5->addGraph();     //添加曲线
            ui->DisplayPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 28:
            ui->DisplayPlot5->addGraph();     //添加曲线
            ui->DisplayPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 29:
            ui->DisplayPlot5->addGraph();     //添加曲线
            ui->DisplayPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 30:
            ui->DisplayPlot5->addGraph();     //添加曲线
            ui->DisplayPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 31:
            ui->DisplayPlot6->addGraph();     //添加曲线
            ui->DisplayPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 32:
            ui->DisplayPlot6->addGraph();     //添加曲线
            ui->DisplayPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 33:
            ui->DisplayPlot6->addGraph();     //添加曲线
            ui->DisplayPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 34:
            ui->DisplayPlot6->addGraph();     //添加曲线
            ui->DisplayPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 35:
            ui->DisplayPlot6->addGraph();     //添加曲线
            ui->DisplayPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 36:
            ui->DisplayPlot6->addGraph();     //添加曲线
            ui->DisplayPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 37:
            ui->DisplayPlot7->addGraph();     //添加曲线
            ui->DisplayPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 38:
            ui->DisplayPlot7->addGraph();     //添加曲线
            ui->DisplayPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 39:
            ui->DisplayPlot7->addGraph();     //添加曲线
            ui->DisplayPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 40:
            ui->DisplayPlot7->addGraph();     //添加曲线
            ui->DisplayPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 41:
            ui->DisplayPlot7->addGraph();     //添加曲线
            ui->DisplayPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 42:
            ui->DisplayPlot7->addGraph();     //添加曲线
            ui->DisplayPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 43:
            ui->DisplayPlot8->addGraph();     //添加曲线
            ui->DisplayPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 44:
            ui->DisplayPlot8->addGraph();     //添加曲线
            ui->DisplayPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 45:
            ui->DisplayPlot8->addGraph();     //添加曲线
            ui->DisplayPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 46:
            ui->DisplayPlot8->addGraph();     //添加曲线
            ui->DisplayPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 47:
            ui->DisplayPlot8->addGraph();     //添加曲线
            ui->DisplayPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 48:
            ui->DisplayPlot8->addGraph();     //添加曲线
            ui->DisplayPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 49:
            ui->DisplayPlot9->addGraph();     //添加曲线
            ui->DisplayPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->DisplayPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 50:
            ui->DisplayPlot9->addGraph();     //添加曲线
            ui->DisplayPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->DisplayPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 51:
            ui->DisplayPlot9->addGraph();     //添加曲线
            ui->DisplayPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->DisplayPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 52:
            ui->DisplayPlot9->addGraph();     //添加曲线
            ui->DisplayPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->DisplayPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 53:
            ui->DisplayPlot9->addGraph();     //添加曲线
            ui->DisplayPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->DisplayPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 54:
            ui->DisplayPlot9->addGraph();     //添加曲线
            ui->DisplayPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->DisplayPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
            /*
                55：环境温度；     56：处理板温度；        57：姿态检测温度；
                58：优选里程脉冲；  59：原始里程脉冲1；     60：原始里程脉冲2；     61：原始里程脉冲3；
                62：周向角         63：倾角；             64：航向角；           65：加速度；
            */
        case 55:
            ui->temperaturePlot->addGraph();
            ui->temperaturePlot->graph(0)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->temperaturePlot->graph(0)->setName(QString("环境温度"));
            break;
        case 56:
            ui->temperaturePlot->addGraph();
            ui->temperaturePlot->graph(1)->setPen(QPen(QColorConstants::Svg::gold));
            ui->temperaturePlot->graph(1)->setName(QString("处理板温度"));
            break;
        case 57:
            ui->temperaturePlot->addGraph();
            ui->temperaturePlot->graph(2)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->temperaturePlot->graph(2)->setName(QString("姿态检测温度"));
            break;
        case 58:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(0)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->distancePlot->graph(0)->setName(QString("优选里程脉冲"));
            break;
        case 59:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(1)->setPen(QPen(QColorConstants::Svg::gold));
            ui->distancePlot->graph(1)->setName(QString("原始里程脉冲1"));
            break;
        case 60:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(2)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->distancePlot->graph(2)->setName(QString("原始里程脉冲2"));
            break;
        case 61:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(3)->setPen(QPen(QColorConstants::Svg::violet));
            ui->distancePlot->graph(3)->setName(QString("原始里程脉冲3"));
            break;
        case 62:
            ui->positionPlot->addGraph();
            ui->positionPlot->graph(0)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->positionPlot->graph(0)->setName(QString("周向角"));
            break;
        case 63:
            ui->positionPlot->addGraph();
            ui->positionPlot->graph(1)->setPen(QPen(QColorConstants::Svg::gold));
            ui->positionPlot->graph(1)->setName(QString("倾角"));
            break;
        case 64:
            ui->positionPlot->addGraph();
            ui->positionPlot->graph(2)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->positionPlot->graph(2)->setName(QString("航向角"));
            break;
//        case 65:
//            ui->positionPlot->addGraph();
//            ui->positionPlot->graph(3)->setPen(QPen(QColorConstants::Svg::violet));
//            ui->positionPlot->graph(3)->setName(QString("加速度"));
//            break;
        default:
            break;
        }

        ui->DisplayPlot1->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot1->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot1->legend->setVisible(true);
        ui->DisplayPlot1->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot1->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot2->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot2->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot2->legend->setVisible(true);
        ui->DisplayPlot2->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot3->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot3->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot3->legend->setVisible(true);
        ui->DisplayPlot3->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot4->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot4->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot4->legend->setVisible(true);
        ui->DisplayPlot4->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot4->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot5->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot5->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot5->legend->setVisible(true);
        ui->DisplayPlot5->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot5->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot6->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot6->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot6->legend->setVisible(true);
        ui->DisplayPlot6->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot6->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot7->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot7->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot7->legend->setVisible(true);
        ui->DisplayPlot7->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot7->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot8->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot8->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot8->legend->setVisible(true);
        ui->DisplayPlot8->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot8->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->DisplayPlot9->xAxis->setLabel("X/数据报信息序号");
        ui->DisplayPlot9->yAxis->setLabel("Y/电压(Volt)");
        ui->DisplayPlot9->legend->setVisible(true);
        ui->DisplayPlot9->setBackground(QColorConstants::Svg::dimgray);
        ui->DisplayPlot9->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->temperaturePlot->xAxis->setLabel("X/温度信息序号");
        ui->temperaturePlot->yAxis->setLabel("Y/温度(℃)");
        ui->temperaturePlot->legend->setVisible(true);
        ui->temperaturePlot->setBackground(QColorConstants::Svg::dimgray);
        ui->temperaturePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->distancePlot->xAxis->setLabel("X/里程信息序号");
        ui->distancePlot->yAxis->setLabel("Y/里程(mm)");
        ui->distancePlot->legend->setVisible(true);
        ui->distancePlot->setBackground(QColorConstants::Svg::dimgray);
        ui->distancePlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->positionPlot->xAxis->setLabel("X/姿态信息序号");
        ui->positionPlot->yAxis->setLabel("Y/角度(°)");
        ui->positionPlot->legend->setVisible(true);
        ui->positionPlot->setBackground(QColorConstants::Svg::dimgray);
        ui->positionPlot->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

    }

}

void DisplayPanel::updatePlots(){

    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ui->DisplayPlot1->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            ui->DisplayPlot2->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            ui->DisplayPlot3->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            ui->DisplayPlot4->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            ui->DisplayPlot5->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
            ui->DisplayPlot6->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
            ui->DisplayPlot7->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
            ui->DisplayPlot8->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            ui->DisplayPlot9->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;

        /*
            55：环境温度；     56：处理板温度；        57：姿态检测温度；
            58：优选里程脉冲；  59：原始里程脉冲1；     60：原始里程脉冲2；     61：原始里程脉冲3；
            62：周向角         63：倾角；             64：航向角；
        */
        case 55:
        case 56:
        case 57:
            ui->temperaturePlot->graph(i%55)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 58:
        case 59:
        case 60:
        case 61:
            ui->distancePlot->graph(i%58)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 62:
        case 63:
        case 64:
            ui->positionPlot->graph(i%62)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        default:
            break;
            }
    }

    //每个表中有六条曲线
//    for (int i = 0; i < LINENUM; ++i) {
//        switch (i) {
//        case 0:
//            ui->DisplayPlot1->graph(i)->setData(X,Y1);
//            break;
//        case 1:
//            ui->DisplayPlot1->graph(i)->setData(X,Y2);
//            break;
//        case 2:
//            ui->DisplayPlot1->graph(i)->setData(X,Y3);
//            break;
//        case 3:
//            ui->DisplayPlot1->graph(i)->setData(X,Y4);
//            break;
//        case 4:
//            ui->DisplayPlot1->graph(i)->setData(X,Y5);
//            break;
//        case 5:
//            ui->DisplayPlot1->graph(i)->setData(X,Y6);
//            break;
//        default:
//            break;
//        }
//    }



    if(this->dataCount>=CLEARNUM){
        ui->DisplayPlot1->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot2->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot3->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot4->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot5->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot6->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot7->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot8->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->DisplayPlot9->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->temperaturePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->distancePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->positionPlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
    }
    ui->DisplayPlot1->replot();
    ui->DisplayPlot2->replot();
    ui->DisplayPlot3->replot();
    ui->DisplayPlot4->replot();
    ui->DisplayPlot5->replot();
    ui->DisplayPlot6->replot();
    ui->DisplayPlot7->replot();
    ui->DisplayPlot8->replot();
    ui->DisplayPlot9->replot();
    ui->temperaturePlot->replot();
    ui->distancePlot->replot();
    ui->positionPlot->replot();
    for (int i = 0; i < LINENUM; ++i) {
        ui->DisplayPlot1->graph(i)->rescaleAxes(true);
        ui->DisplayPlot2->graph(i)->rescaleAxes(true);
        ui->DisplayPlot3->graph(i)->rescaleAxes(true);
        ui->DisplayPlot4->graph(i)->rescaleAxes(true);
        ui->DisplayPlot5->graph(i)->rescaleAxes(true);
        ui->DisplayPlot6->graph(i)->rescaleAxes(true);
        ui->DisplayPlot7->graph(i)->rescaleAxes(true);
        ui->DisplayPlot8->graph(i)->rescaleAxes(true);
        ui->DisplayPlot9->graph(i)->rescaleAxes(true);
        if(i<3){
            ui->temperaturePlot->graph(i)->rescaleAxes(true);
            ui->positionPlot->graph(i)->rescaleAxes(true);
        }
        if(i<4){
            ui->distancePlot->graph(i)->rescaleAxes(true);
        }
    }
}

void DisplayPanel::updateBxData(QList<double> newBxData){

    // 变形数据更新
    for (int i = 0; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
//        if(i==0){
//            this->bxDataList[i].append(this->dataCount++);
//        }
//        else {
//            this->bxDataList[i].append(newBxData.at(i-1));
//        }
        this->dataCount++;
        this->bxDataList[i].append(newBxData.at(i));
    }
    // 前六组变形数据更新
//    X.append(dataCount++);
//    for (int i = 0; i < LINENUM; ++i) {
//        switch (i) {
//        case 0:
//            Y1.append(newBxData.at(i));
//            break;
//        case 1:
//            Y2.append(newBxData.at(i));
//            break;
//        case 2:
//            Y3.append(newBxData.at(i));
//            break;
//        case 3:
//            Y4.append(newBxData.at(i));
//            break;
//        case 4:
//            Y5.append(newBxData.at(i));
//            break;
//        case 5:
//            Y6.append(newBxData.at(i));
//            break;
//        default:
//            break;
//        }
//    }

    // 滚动清除数据
    if(this->bxDataList[0].length()>=CLEARNUM){
        for (int i = 0; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
            this->bxDataList[i].removeFirst();
        }
    }

    //滚动清除数据
//    if(X.length()>=CLEARNUM){
//        X.removeFirst();
//        Y1.removeFirst();
//        Y2.removeFirst();
//        Y3.removeFirst();
//        Y4.removeFirst();
//        Y5.removeFirst();
//        Y6.removeFirst();
//    }
    //更新变形图像
    this->updatePlots();
}

void DisplayPanel::updateBxDataAdditional(QMap<QString,QString> additionalBxData){
    /*
        时钟脉冲计数
        24V系统供电电压
        24V系统供电电流
        电池组已用电量
        电池累计通电次数
        电池累计通电时间
        电池组额定电量
        电池更换时间
        电池模块环境温度
        供电方式
        5V二次电源电压
        3.3V二次电源电压
    */
    ui->clockEdit->setText(additionalBxData["时钟脉冲计数"]);
    ui->voltEdit->setText(additionalBxData["24V系统供电电压"]);
    ui->currentEdit->setText(additionalBxData["24V系统供电电流"]);
    ui->usedElectricityEdit->setText(additionalBxData["电池组已用电量"]);
    ui->batteryUsedTimesEdit->setText(additionalBxData["电池累计通电次数"]);
    ui->batteryWorkingTimeEdit->setText(additionalBxData["电池累计通电时间"]);
    ui->electricVolumeEdit->setText(additionalBxData["电池组额定电量"]);
    ui->batteryChangedTimeEdit->setText(additionalBxData["电池更换时间"]);
    ui->temperatureEdit->setText(additionalBxData["电池模块环境温度"]);
    ui->batteryModeEdit->setText(additionalBxData["供电方式"]);
    ui->fiveVoltEdit->setText(additionalBxData["5V二次电源电压"]);
    ui->threePointThreeVoltEdit->setText(additionalBxData["3.3V二次电源电压"]);

}




void DisplayPanel::closeEvent(QCloseEvent *e){
    emit this->shutDown();
}
