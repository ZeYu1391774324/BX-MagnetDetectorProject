#include "testpanel.h"
#include "ui_testpanel.h"

TestPanel::TestPanel(QWidget *parent, QSerialPort *serial, ParaGet* para) :
    QWidget(parent),
    ui(new Ui::TestPanel)
{
    ui->setupUi(this);

    this->serial=serial;
    this->parameters=para;
    this->MFLData_RoadsNum=parameters->dataPara_MFL.MFLData_num;
    if(parameters->pipeType=="变形"){
        this->initPanel();
        this->initPlots();
    }
    else if (parameters->pipeType=="漏磁") {
        this->initPanel_MFL();
        this->initPlots_MFL();
    }
}

TestPanel::~TestPanel()
{
    delete ui;
}

void TestPanel::initPanel(){
    // initiate buttons
    // Test start button
    connect(ui->TestPanel_StartBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(COLLECTBYDISTANCEFRAME).toLatin1().data()));});
    //Test stop button
    connect(ui->TestPanel_StopBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(STOPCOLLECTFRAME).toLatin1().data()));});
    // stackWidget Selection comBox
    ui->bxDataRoadsSelectingComboBox->setVisible(true);
    ui->MFLRoadscomboBox->setVisible(false);
    connect(ui->bxDataRoadsSelectingComboBox,&QComboBox::currentTextChanged,[=](){
        ui->stackedWidget->setCurrentIndex(ui->bxDataRoadsSelectingComboBox->currentIndex());
    });
    ui->stackedWidget->setCurrentIndex(0);
    // testObjects Btn
    connect(ui->TestObjectsBtn,&QPushButton::clicked,[=](){
        this->testObjects();
    });
    // initiate bxDataRoads
    for (int i = 0; i <= bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        this->bxDataList.append(QVector<double>());
    }

    //initiate testObjectCombox
    QStringList strlist;
    for (int i = 0; i < bxData_RoadsNum; ++i) {
        strlist.append(QString("第%1路传感器").arg(i+1));
    }
    ui->testObjectComboBox->addItems(strlist);
    ui->stackedWidget->setCurrentIndex(0);
}

void TestPanel::initPlots(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
            ui->TestPlot1->addGraph();     //添加曲线
            ui->TestPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 2:
            ui->TestPlot1->addGraph();     //添加曲线
            ui->TestPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 3:
            ui->TestPlot1->addGraph();     //添加曲线
            ui->TestPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 4:
            ui->TestPlot1->addGraph();     //添加曲线
            ui->TestPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 5:
            ui->TestPlot1->addGraph();     //添加曲线
            ui->TestPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 6:
            ui->TestPlot1->addGraph();     //添加曲线
            ui->TestPlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 7:
            ui->TestPlot2->addGraph();     //添加曲线
            ui->TestPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 8:
            ui->TestPlot2->addGraph();     //添加曲线
            ui->TestPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 9:
            ui->TestPlot2->addGraph();     //添加曲线
            ui->TestPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 10:
            ui->TestPlot2->addGraph();     //添加曲线
            ui->TestPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 11:
            ui->TestPlot2->addGraph();     //添加曲线
            ui->TestPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 12:
            ui->TestPlot2->addGraph();     //添加曲线
            ui->TestPlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 13:
            ui->TestPlot3->addGraph();     //添加曲线
            ui->TestPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 14:
            ui->TestPlot3->addGraph();     //添加曲线
            ui->TestPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 15:
            ui->TestPlot3->addGraph();     //添加曲线
            ui->TestPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 16:
            ui->TestPlot3->addGraph();     //添加曲线
            ui->TestPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 17:
            ui->TestPlot3->addGraph();     //添加曲线
            ui->TestPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 18:
            ui->TestPlot3->addGraph();     //添加曲线
            ui->TestPlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 19:
            ui->TestPlot4->addGraph();     //添加曲线
            ui->TestPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 20:
            ui->TestPlot4->addGraph();     //添加曲线
            ui->TestPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 21:
            ui->TestPlot4->addGraph();     //添加曲线
            ui->TestPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 22:
            ui->TestPlot4->addGraph();     //添加曲线
            ui->TestPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 23:
            ui->TestPlot4->addGraph();     //添加曲线
            ui->TestPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 24:
            ui->TestPlot4->addGraph();     //添加曲线
            ui->TestPlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 25:
            ui->TestPlot5->addGraph();     //添加曲线
            ui->TestPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 26:
            ui->TestPlot5->addGraph();     //添加曲线
            ui->TestPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 27:
            ui->TestPlot5->addGraph();     //添加曲线
            ui->TestPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 28:
            ui->TestPlot5->addGraph();     //添加曲线
            ui->TestPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 29:
            ui->TestPlot5->addGraph();     //添加曲线
            ui->TestPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 30:
            ui->TestPlot5->addGraph();     //添加曲线
            ui->TestPlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 31:
            ui->TestPlot6->addGraph();     //添加曲线
            ui->TestPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 32:
            ui->TestPlot6->addGraph();     //添加曲线
            ui->TestPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 33:
            ui->TestPlot6->addGraph();     //添加曲线
            ui->TestPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 34:
            ui->TestPlot6->addGraph();     //添加曲线
            ui->TestPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 35:
            ui->TestPlot6->addGraph();     //添加曲线
            ui->TestPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 36:
            ui->TestPlot6->addGraph();     //添加曲线
            ui->TestPlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 37:
            ui->TestPlot7->addGraph();     //添加曲线
            ui->TestPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 38:
            ui->TestPlot7->addGraph();     //添加曲线
            ui->TestPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 39:
            ui->TestPlot7->addGraph();     //添加曲线
            ui->TestPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 40:
            ui->TestPlot7->addGraph();     //添加曲线
            ui->TestPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 41:
            ui->TestPlot7->addGraph();     //添加曲线
            ui->TestPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 42:
            ui->TestPlot7->addGraph();     //添加曲线
            ui->TestPlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 43:
            ui->TestPlot8->addGraph();     //添加曲线
            ui->TestPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 44:
            ui->TestPlot8->addGraph();     //添加曲线
            ui->TestPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 45:
            ui->TestPlot8->addGraph();     //添加曲线
            ui->TestPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 46:
            ui->TestPlot8->addGraph();     //添加曲线
            ui->TestPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 47:
            ui->TestPlot8->addGraph();     //添加曲线
            ui->TestPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 48:
            ui->TestPlot8->addGraph();     //添加曲线
            ui->TestPlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 49:
            ui->TestPlot9->addGraph();     //添加曲线
            ui->TestPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->TestPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 50:
            ui->TestPlot9->addGraph();     //添加曲线
            ui->TestPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->TestPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 51:
            ui->TestPlot9->addGraph();     //添加曲线
            ui->TestPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->TestPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 52:
            ui->TestPlot9->addGraph();     //添加曲线
            ui->TestPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->TestPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 53:
            ui->TestPlot9->addGraph();     //添加曲线
            ui->TestPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->TestPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 54:
            ui->TestPlot9->addGraph();     //添加曲线
            ui->TestPlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->TestPlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
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
        default:
            break;
        }

        ui->TestPlot1->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot1->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot1->legend->setVisible(true);
        ui->TestPlot1->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot1->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot2->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot2->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot2->legend->setVisible(true);
        ui->TestPlot2->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot3->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot3->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot3->legend->setVisible(true);
        ui->TestPlot3->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot4->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot4->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot4->legend->setVisible(true);
        ui->TestPlot4->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot4->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot5->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot5->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot5->legend->setVisible(true);
        ui->TestPlot5->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot5->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot6->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot6->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot6->legend->setVisible(true);
        ui->TestPlot6->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot6->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot7->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot7->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot7->legend->setVisible(true);
        ui->TestPlot7->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot7->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot8->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot8->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot8->legend->setVisible(true);
        ui->TestPlot8->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot8->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->TestPlot9->xAxis->setLabel("X/数据报信息序号");
        ui->TestPlot9->yAxis->setLabel("Y/电压(Volt)");
        ui->TestPlot9->legend->setVisible(true);
        ui->TestPlot9->setBackground(QColorConstants::Svg::dimgray);
        ui->TestPlot9->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);


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



void TestPanel::initPanel_MFL(){
    // initiate buttons
    // Collect by time start button
    connect(ui->TestPanel_StartBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(COLLECTBYDISTANCEFRAME).toLatin1().data()));});
    // Collect by time stop button
    connect(ui->TestPanel_StopBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(STOPCOLLECTFRAME).toLatin1().data()));});
    // stackWidget Selection comBox
    ui->bxDataRoadsSelectingComboBox->setVisible(false);
    ui->MFLRoadscomboBox->setVisible(true);
    for (int i = 1; i <= this->MFLData_RoadsNum; ++i) {
        ui->MFLRoadscomboBox->addItem(QString("第%1漏磁通道").arg(i));
    }
    ui->stackedWidget->setCurrentIndex(3);
    // initiate MFLDataRoads
    for (int i = 0; i <= MFLData_RoadsNum*MFLCHANNELNUM*3+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        this->MFLDataList.append(QVector<double>());
    }


    //initiate testObjectCombox
    QStringList strlist;
    for (int i = 0; i < MFLData_RoadsNum; ++i) {
        strlist.append(QString("第%1路传感器").arg(i+1));
    }
    ui->testObjectComboBox->addItems(strlist);


    //TODO TEST OBJECTS of MFL
    // testObjects Btn
    connect(ui->TestObjectsBtn,&QPushButton::clicked,[=](){
        this->testObjects();
    });
}



void TestPanel::initPlots_MFL(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= MFLCHANNELNUM+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
            ui->MFLPlot_X->addGraph();     //添加曲线
            ui->MFLPlot_X->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->MFLPlot_X->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Y->addGraph();     //添加曲线
            ui->MFLPlot_Y->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->MFLPlot_Y->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Z->addGraph();     //添加曲线
            ui->MFLPlot_Z->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->MFLPlot_Z->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));
            break;
        case 2:
            ui->MFLPlot_X->addGraph();     //添加曲线
            ui->MFLPlot_X->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->MFLPlot_X->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Y->addGraph();     //添加曲线
            ui->MFLPlot_Y->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->MFLPlot_Y->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Z->addGraph();     //添加曲线
            ui->MFLPlot_Z->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->MFLPlot_Z->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));
            break;
        case 3:
            ui->MFLPlot_X->addGraph();     //添加曲线
            ui->MFLPlot_X->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->MFLPlot_X->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Y->addGraph();     //添加曲线
            ui->MFLPlot_Y->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->MFLPlot_Y->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Z->addGraph();     //添加曲线
            ui->MFLPlot_Z->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->MFLPlot_Z->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));
            break;
        case 4:
            ui->MFLPlot_X->addGraph();     //添加曲线
            ui->MFLPlot_X->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->MFLPlot_X->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Y->addGraph();     //添加曲线
            ui->MFLPlot_Y->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->MFLPlot_Y->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Z->addGraph();     //添加曲线
            ui->MFLPlot_Z->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->MFLPlot_Z->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));
            break;
        case 5:
            ui->MFLPlot_X->addGraph();     //添加曲线
            ui->MFLPlot_X->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->MFLPlot_X->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Y->addGraph();     //添加曲线
            ui->MFLPlot_Y->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->MFLPlot_Y->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Z->addGraph();     //添加曲线
            ui->MFLPlot_Z->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->MFLPlot_Z->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));
            break;
        case 6:
            ui->MFLPlot_X->addGraph();     //添加曲线
            ui->MFLPlot_X->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->MFLPlot_X->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Y->addGraph();     //添加曲线
            ui->MFLPlot_Y->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->MFLPlot_Y->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));

            ui->MFLPlot_Z->addGraph();     //添加曲线
            ui->MFLPlot_Z->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->MFLPlot_Z->graph((i-1)%6)->setName(QString("传感器%1数据").arg(i));
            break;

            /*
                7：环境温度；     8：处理板温度；        9：姿态检测温度；
                10：优选里程脉冲；  11：原始里程脉冲1；    12：原始里程脉冲2；     13：原始里程脉冲3；
                14：周向角         15：倾角；             16：航向角；           17：加速度；
            */
        case 7:
            ui->temperaturePlot->addGraph();
            ui->temperaturePlot->graph(0)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->temperaturePlot->graph(0)->setName(QString("环境温度"));
            break;
        case 8:
            ui->temperaturePlot->addGraph();
            ui->temperaturePlot->graph(1)->setPen(QPen(QColorConstants::Svg::gold));
            ui->temperaturePlot->graph(1)->setName(QString("处理板温度"));
            break;
        case 9:
            ui->temperaturePlot->addGraph();
            ui->temperaturePlot->graph(2)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->temperaturePlot->graph(2)->setName(QString("姿态检测温度"));
            break;
        case 10:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(0)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->distancePlot->graph(0)->setName(QString("优选里程脉冲"));
            break;
        case 11:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(1)->setPen(QPen(QColorConstants::Svg::gold));
            ui->distancePlot->graph(1)->setName(QString("原始里程脉冲1"));
            break;
        case 12:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(2)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->distancePlot->graph(2)->setName(QString("原始里程脉冲2"));
            break;
        case 13:
            ui->distancePlot->addGraph();
            ui->distancePlot->graph(3)->setPen(QPen(QColorConstants::Svg::violet));
            ui->distancePlot->graph(3)->setName(QString("原始里程脉冲3"));
            break;
        case 14:
            ui->positionPlot->addGraph();
            ui->positionPlot->graph(0)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->positionPlot->graph(0)->setName(QString("周向角"));
            break;
        case 15:
            ui->positionPlot->addGraph();
            ui->positionPlot->graph(1)->setPen(QPen(QColorConstants::Svg::gold));
            ui->positionPlot->graph(1)->setName(QString("倾角"));
            break;
        case 16:
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
}
        ui->MFLPlot_X->xAxis->setLabel("X/数据报信息序号");
        ui->MFLPlot_X->yAxis->setLabel("Y/磁感应强度(Gs)");
        ui->MFLPlot_X->legend->setVisible(true);
        ui->MFLPlot_X->setBackground(QColorConstants::Svg::dimgray);
        ui->MFLPlot_X->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->MFLPlot_Y->xAxis->setLabel("X/数据报信息序号");
        ui->MFLPlot_Y->yAxis->setLabel("Y/磁感应强度(Gs)");
        ui->MFLPlot_Y->legend->setVisible(true);
        ui->MFLPlot_Y->setBackground(QColorConstants::Svg::dimgray);
        ui->MFLPlot_Y->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->MFLPlot_Z->xAxis->setLabel("X/数据报信息序号");
        ui->MFLPlot_Z->yAxis->setLabel("Y/磁感应强度(Gs)");
        ui->MFLPlot_Z->legend->setVisible(true);
        ui->MFLPlot_Z->setBackground(QColorConstants::Svg::dimgray);
        ui->MFLPlot_Z->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

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


void TestPanel::updatePlots_MFL(){

    for (int i = 1; i <= MFLCHANNELNUM+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ui->MFLPlot_X->graph((i-1)%6)->setData(this->MFLDataList[0],this->MFLDataList[ui->MFLRoadscomboBox->currentIndex()*MFLCHANNELNUM*3+3*(i-1)+1]);
            ui->MFLPlot_Y->graph((i-1)%6)->setData(this->MFLDataList[0],this->MFLDataList[ui->MFLRoadscomboBox->currentIndex()*MFLCHANNELNUM*3+3*(i-1)+2]);
            ui->MFLPlot_Z->graph((i-1)%6)->setData(this->MFLDataList[0],this->MFLDataList[ui->MFLRoadscomboBox->currentIndex()*MFLCHANNELNUM*3+3*(i-1)+3]);
            break;

        /*
            7：环境温度；     8：处理板温度；        9：姿态检测温度；
            10：优选里程脉冲； 11：原始里程脉冲1；    12：原始里程脉冲2；     13：原始里程脉冲3；
            14：周向角        15：倾角；            16：航向角；
        */
        case 7:
        case 8:
        case 9:
            ui->temperaturePlot->graph(i%7)->setData(this->MFLDataList[0],this->MFLDataList[3*MFLCHANNELNUM*this->MFLData_RoadsNum+(i-6)]);
            break;
        case 10:
        case 11:
        case 12:
        case 13:
            ui->distancePlot->graph(i%10)->setData(this->MFLDataList[0],this->MFLDataList[3*MFLCHANNELNUM*this->MFLData_RoadsNum+(i-6)]);
            break;
        case 14:
        case 15:
        case 16:
            ui->positionPlot->graph(i%14)->setData(this->MFLDataList[0],this->MFLDataList[3*MFLCHANNELNUM*this->MFLData_RoadsNum+(i-6)]);
            break;
        default:
            break;
            }
    }

    //每个表中有六条曲线
//    for (int i = 0; i < LINENUM; ++i) {
//        switch (i) {
//        case 0:
//            ui->CollectByDistancePlot1->graph(i)->setData(X,Y1);
//            break;
//        case 1:
//            ui->CollectByDistancePlot1->graph(i)->setData(X,Y2);
//            break;
//        case 2:
//            ui->CollectByDistancePlot1->graph(i)->setData(X,Y3);
//            break;
//        case 3:
//            ui->CollectByDistancePlot1->graph(i)->setData(X,Y4);
//            break;
//        case 4:
//            ui->CollectByDistancePlot1->graph(i)->setData(X,Y5);
//            break;
//        case 5:
//            ui->CollectByDistancePlot1->graph(i)->setData(X,Y6);
//            break;
//        default:
//            break;
//        }
//    }



    if(this->dataCount>=CLEARNUM){
        ui->MFLPlot_X->xAxis->setRange(this->MFLDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->MFLPlot_Y->xAxis->setRange(this->MFLDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->MFLPlot_Z->xAxis->setRange(this->MFLDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->temperaturePlot->xAxis->setRange(this->MFLDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->distancePlot->xAxis->setRange(this->MFLDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->positionPlot->xAxis->setRange(this->MFLDataList[0].first(),CLEARNUM,Qt::AlignLeft);
    }
    ui->MFLPlot_X->replot();
    ui->MFLPlot_Y->replot();
    ui->MFLPlot_Z->replot();
    ui->temperaturePlot->replot();
    ui->distancePlot->replot();
    ui->positionPlot->replot();
    for (int i = 0; i < LINENUM; ++i) {
        ui->MFLPlot_X->graph(i)->rescaleAxes(true);
        ui->MFLPlot_Y->graph(i)->rescaleAxes(true);
        ui->MFLPlot_Z->graph(i)->rescaleAxes(true);
        if(i<3){
            ui->temperaturePlot->graph(i)->rescaleAxes(true);
            ui->positionPlot->graph(i)->rescaleAxes(true);
        }
        if(i<4){
            ui->distancePlot->graph(i)->rescaleAxes(true);
        }
    }
}


void TestPanel::updatePlots(){

    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ui->TestPlot1->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            ui->TestPlot2->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            ui->TestPlot3->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            ui->TestPlot4->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            ui->TestPlot5->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
            ui->TestPlot6->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
            ui->TestPlot7->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
            ui->TestPlot8->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            ui->TestPlot9->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
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
    if(this->dataCount>=CLEARNUM){
        ui->TestPlot1->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot2->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot3->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot4->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot5->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot6->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot7->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot8->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->TestPlot9->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->temperaturePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->distancePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->positionPlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
    }
    ui->TestPlot1->replot();
    ui->TestPlot2->replot();
    ui->TestPlot3->replot();
    ui->TestPlot4->replot();
    ui->TestPlot5->replot();
    ui->TestPlot6->replot();
    ui->TestPlot7->replot();
    ui->TestPlot8->replot();
    ui->TestPlot9->replot();
    ui->temperaturePlot->replot();
    ui->distancePlot->replot();
    ui->positionPlot->replot();
    for (int i = 0; i < LINENUM; ++i) {
        ui->TestPlot1->graph(i)->rescaleAxes(true);
        ui->TestPlot2->graph(i)->rescaleAxes(true);
        ui->TestPlot3->graph(i)->rescaleAxes(true);
        ui->TestPlot4->graph(i)->rescaleAxes(true);
        ui->TestPlot5->graph(i)->rescaleAxes(true);
        ui->TestPlot6->graph(i)->rescaleAxes(true);
        ui->TestPlot7->graph(i)->rescaleAxes(true);
        ui->TestPlot8->graph(i)->rescaleAxes(true);
        ui->TestPlot9->graph(i)->rescaleAxes(true);
        if(i<3){
            ui->temperaturePlot->graph(i)->rescaleAxes(true);
            ui->positionPlot->graph(i)->rescaleAxes(true);
        }
        if(i<4){
            ui->distancePlot->graph(i)->rescaleAxes(true);
        }
    }
}



void TestPanel::updateMFLData(QList<double> newMFLData){
    // 数据更新
    for (int i = 0; i <= this->MFLData_RoadsNum*MFLCHANNELNUM*3+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        if(i==0){
            this->MFLDataList[i].append(this->dataCount++);
        }
        else {
            this->MFLDataList[i].append(newMFLData.at(i-1));
        }
    }
    // 前六组数据更新
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
    if(this->MFLDataList[0].length()>=CLEARNUM){
        for (int i = 0; i <= this->MFLData_RoadsNum*MFLCHANNELNUM*3+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
            this->MFLDataList[i].removeFirst();
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
    this->updatePlots_MFL();
}




void TestPanel::updateBxData(QList<double> newBxData){
    // 数据更新
    for (int i = 0; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        if(i==0){
            this->bxDataList[i].append(this->dataCount++);
        }
        else {
            this->bxDataList[i].append(newBxData.at(i-1));
        }
    }

    // 滚动清除数据
    if(this->bxDataList[0].length()>=CLEARNUM){
        for (int i = 0; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
            this->bxDataList[i].removeFirst();
        }
    }

    //更新变形图像
    this->updatePlots();
}

void TestPanel::updateBxDataAdditional(QMap<QString,QString> additionalBxData){
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

void TestPanel::updateSpeedLabel(int speed){
    ui->ByteSpeedLabel->setText(QString("当前串口传输速率：%1 Byte/s.").arg(speed));
}

void TestPanel::updateParametersLabel(ParaGet* para){
    ui->ParametersLabel->setText(QString("当前产品参数：%1-%2").arg(para->pipeSize).arg(para->pipeType));
}

void TestPanel::testObjects(){

    QList<int> objects=ui->testObjectComboBox->currentIndex();
    if(objects.isEmpty()){
        QMessageBox::information(this,"提示","请选择您要测试的传感器！");
        return;
    }

    if(parameters->pipeType=="变形"){
        QTimer *timer = new QTimer;
        timer->start(5000);
        ui->testInfoLabel->setText("检测中...请保持传感器为高电压状态并等候5s");
        connect(timer,&QTimer::timeout,[=](){
            QList<int> errList;
            for (int i = 0; i < objects.length(); ++i) {
                QVector<double> testData = bxDataList.at(objects.at(i)+1);
                bool flag=true;
                for (int j = 0; j < testData.length(); ++j) {
                    if(testData.at(j)<4){       //高电压阈值=4
                        flag = false;
                        errList.append(objects.at(i)+1);
                        emit this->newTestResult(objects.at(i),false);  //返回传感器index,检测结果异常（false）
                        break;
                    }
                }
                if(flag){
                    emit this->newTestResult(objects.at(i),true);   //返回传感器index,检测结果正常（true）
                }

            }
            if(errList.isEmpty()){
                QMessageBox::information(this,"消息","所选测试传感器均运行正常！");
                ui->testInfoLabel->setText("上次检测结果正常！");
            }
            else{
                QString testInfo;
                for (int k = 0; k < errList.length(); ++k) {
                    if(k!=errList.length()-1){
                        testInfo.append(QString("%1, ").arg(errList.at(k)));
                    }
                    else {
                        testInfo.append(QString("%1. ").arg(errList.at(k)));
                    }
                }

                QMessageBox::information(this,"消息", "测试结果：异常传感器编号 "+testInfo);
                ui->testInfoLabel->setText("上次检测结果：异常传感器编号 "+testInfo);
            }

            timer->stop();
            timer->disconnect();
        });
    }
    else{       //漏磁
        QTimer *timer = new QTimer;
        timer->start(5000);
        ui->testInfoLabel->setText("检测中...请使用金属干扰待检测的传感器");
        connect(timer,&QTimer::timeout,[=](){
            QList<QVector<double>> currentMFLDataList=MFLDataList;
            QList<int> errList;
            QVector<QVector<QVector<double>>> testData;     //testData<objects index<Vector of 3 axis<6 Roads summation of data of 3 axis>>>
            QVector<QVector<double>> tempVector;
            for (int i = 0; i < objects.length(); ++i) {
                QVector<double> Xaxis,Yaxis,Zaxis;
                for (int ii = 0; ii < MFLCHANNELNUM; ++ii) {
                    if(ii==0){
                        Xaxis=currentMFLDataList.at(objects.at(i)*3*MFLCHANNELNUM+1);
                        Yaxis=currentMFLDataList.at(objects.at(i)*3*MFLCHANNELNUM+2);
                        Zaxis=currentMFLDataList.at(objects.at(i)*3*MFLCHANNELNUM+3);
                    }
                    else {
                        Xaxis=this->QV_add(Xaxis,currentMFLDataList.at(objects.at(i)*3*MFLCHANNELNUM+ii*3+1));
                        Yaxis=this->QV_add(Yaxis,currentMFLDataList.at(objects.at(i)*3*MFLCHANNELNUM+ii*3+2));
                        Zaxis=this->QV_add(Zaxis,currentMFLDataList.at(objects.at(i)*3*MFLCHANNELNUM+ii*3+3));
                    }
                }
                tempVector.append(Xaxis);
                tempVector.append(Yaxis);
                tempVector.append(Zaxis);
                testData.append(tempVector);
                tempVector.clear();
                Xaxis.clear();
                Yaxis.clear();
                Zaxis.clear();
            }
            currentMFLDataList.clear();
            bool flag=false;
            for (int j = 0; j < testData.length(); ++j) {
                flag=false;
                QVector<double> Yaxis,Zaxis;
                Yaxis = testData.at(j).at(1);
                Zaxis = testData.at(j).at(2);
                for (int k = 0; k < Yaxis.length(); ++k) {
                    if(Yaxis.at(k)>=300){                   // 被人为干扰的6路传感器Gs跳变和大于300判定为传感器正常（径向）
                        flag=true;
                        break;
                    }
                }
                for (int m = 0; m < Zaxis.length(); ++m) {
                    if(Zaxis.at(m)>=300){                   // 被人为干扰的6路传感器Gs跳变和大于300判定为传感器正常（周向）
                        flag=true;
                        break;
                    }
                }
                if(flag){
                    emit this->newTestResult_MFL(objects.at(j),true);   //返回传感器index,检测结果正常（true）
                }
                else {
                    errList.append(objects.at(j)+1);
                    emit this->newTestResult_MFL(objects.at(j),false);  //返回传感器index,检测结果异常（false）
                }

            }

            if(errList.isEmpty()){
                QMessageBox::information(this,"消息","所选测试传感器均运行正常！");
                ui->testInfoLabel->setText("上次检测结果正常！");
            }
            else{
                QString testInfo;
                for (int k = 0; k < errList.length(); ++k) {
                    if(k!=errList.length()-1){
                        testInfo.append(QString("%1, ").arg(errList.at(k)));
                    }
                    else {
                        testInfo.append(QString("%1. ").arg(errList.at(k)));
                    }
                }

                QMessageBox::information(this,"消息", "测试结果：异常传感器编号 "+testInfo);
                ui->testInfoLabel->setText("上次检测结果：异常传感器编号 "+testInfo);
            }

            timer->stop();
            timer->disconnect();
        });
 }
}

QVector<double> TestPanel::QV_add(const QVector<double> &A, const QVector<double> &B){
    int A_len,B_len;
    A_len=A.length();
    B_len=B.length();

    if(A_len!=B_len){
        qDebug()<<QString("相加向量长度不一致！A_len=%1, B_len=%2.").arg(A_len).arg(B_len);
        exit(0);
    }

    QVector<double> sum;
    for (int i = 0; i < A_len; ++i) {
        sum.append(A.at(i)+B.at(i));
    }
    return sum;
}
