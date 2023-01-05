#include "testpanel.h"
#include "ui_testpanel.h"

TestPanel::TestPanel(QWidget *parent, QSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::TestPanel)
{
    ui->setupUi(this);

    this->serial=serial;
    this->initPanel();
    this->initPlots();
}

TestPanel::~TestPanel()
{
    delete ui;
}

void TestPanel::initPanel(){
    // initiate buttons
    // Collect by time start button
    connect(ui->CollectByTime_StartBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(COLLECTBYTIMEFRAME).toLatin1().data()));});
    //Collect by time stop button
    connect(ui->CollectByTime_StopBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(STOPCOLLECTFRAME).toLatin1().data()));});
    // stackWidget Selection comBox
    connect(ui->bxDataRoadsSelectingComboBox,&QComboBox::currentTextChanged,[=](){
        ui->stackedWidget->setCurrentIndex(ui->bxDataRoadsSelectingComboBox->currentIndex());
    });
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
