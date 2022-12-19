#include "collectbydistancepanel.h"
#include "ui_collectbydistancepanel.h"

CollectByDistancePanel::CollectByDistancePanel(QWidget *parent, QSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::CollectByDistancePanel)
{
    ui->setupUi(this);

    this->serial=serial;
    this->initPanel();
    this->initPlots();
}

CollectByDistancePanel::~CollectByDistancePanel()
{
    delete ui;
}

void CollectByDistancePanel::initPanel(){
    // initiate buttons
    // Collect by time start button
    connect(ui->CollectByDistance_StartBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(COLLECTBYDISTANCEFRAME).toLatin1().data()));});
    // Collect by time stop button
    connect(ui->CollectByDistance_StopBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(STOPCOLLECTFRAME).toLatin1().data()));});
    // stackWidget Selection comBox
    connect(ui->bxDataRoadsSelectingComboBox,&QComboBox::currentTextChanged,[=](){
        ui->stackedWidget->setCurrentIndex(ui->bxDataRoadsSelectingComboBox->currentIndex());
    });
    // initiate bxDataRoads
    for (int i = 0; i <= bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        this->bxDataList.append(QVector<double>());
    }

}



void CollectByDistancePanel::initPlots(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
            ui->CollectByDistancePlot1->addGraph();     //添加曲线
            ui->CollectByDistancePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 2:
            ui->CollectByDistancePlot1->addGraph();     //添加曲线
            ui->CollectByDistancePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 3:
            ui->CollectByDistancePlot1->addGraph();     //添加曲线
            ui->CollectByDistancePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 4:
            ui->CollectByDistancePlot1->addGraph();     //添加曲线
            ui->CollectByDistancePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 5:
            ui->CollectByDistancePlot1->addGraph();     //添加曲线
            ui->CollectByDistancePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 6:
            ui->CollectByDistancePlot1->addGraph();     //添加曲线
            ui->CollectByDistancePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 7:
            ui->CollectByDistancePlot2->addGraph();     //添加曲线
            ui->CollectByDistancePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 8:
            ui->CollectByDistancePlot2->addGraph();     //添加曲线
            ui->CollectByDistancePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 9:
            ui->CollectByDistancePlot2->addGraph();     //添加曲线
            ui->CollectByDistancePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 10:
            ui->CollectByDistancePlot2->addGraph();     //添加曲线
            ui->CollectByDistancePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 11:
            ui->CollectByDistancePlot2->addGraph();     //添加曲线
            ui->CollectByDistancePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 12:
            ui->CollectByDistancePlot2->addGraph();     //添加曲线
            ui->CollectByDistancePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 13:
            ui->CollectByDistancePlot3->addGraph();     //添加曲线
            ui->CollectByDistancePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 14:
            ui->CollectByDistancePlot3->addGraph();     //添加曲线
            ui->CollectByDistancePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 15:
            ui->CollectByDistancePlot3->addGraph();     //添加曲线
            ui->CollectByDistancePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 16:
            ui->CollectByDistancePlot3->addGraph();     //添加曲线
            ui->CollectByDistancePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 17:
            ui->CollectByDistancePlot3->addGraph();     //添加曲线
            ui->CollectByDistancePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 18:
            ui->CollectByDistancePlot3->addGraph();     //添加曲线
            ui->CollectByDistancePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 19:
            ui->CollectByDistancePlot4->addGraph();     //添加曲线
            ui->CollectByDistancePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 20:
            ui->CollectByDistancePlot4->addGraph();     //添加曲线
            ui->CollectByDistancePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 21:
            ui->CollectByDistancePlot4->addGraph();     //添加曲线
            ui->CollectByDistancePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 22:
            ui->CollectByDistancePlot4->addGraph();     //添加曲线
            ui->CollectByDistancePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 23:
            ui->CollectByDistancePlot4->addGraph();     //添加曲线
            ui->CollectByDistancePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 24:
            ui->CollectByDistancePlot4->addGraph();     //添加曲线
            ui->CollectByDistancePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 25:
            ui->CollectByDistancePlot5->addGraph();     //添加曲线
            ui->CollectByDistancePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 26:
            ui->CollectByDistancePlot5->addGraph();     //添加曲线
            ui->CollectByDistancePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 27:
            ui->CollectByDistancePlot5->addGraph();     //添加曲线
            ui->CollectByDistancePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 28:
            ui->CollectByDistancePlot5->addGraph();     //添加曲线
            ui->CollectByDistancePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 29:
            ui->CollectByDistancePlot5->addGraph();     //添加曲线
            ui->CollectByDistancePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 30:
            ui->CollectByDistancePlot5->addGraph();     //添加曲线
            ui->CollectByDistancePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 31:
            ui->CollectByDistancePlot6->addGraph();     //添加曲线
            ui->CollectByDistancePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 32:
            ui->CollectByDistancePlot6->addGraph();     //添加曲线
            ui->CollectByDistancePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 33:
            ui->CollectByDistancePlot6->addGraph();     //添加曲线
            ui->CollectByDistancePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 34:
            ui->CollectByDistancePlot6->addGraph();     //添加曲线
            ui->CollectByDistancePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 35:
            ui->CollectByDistancePlot6->addGraph();     //添加曲线
            ui->CollectByDistancePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 36:
            ui->CollectByDistancePlot6->addGraph();     //添加曲线
            ui->CollectByDistancePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 37:
            ui->CollectByDistancePlot7->addGraph();     //添加曲线
            ui->CollectByDistancePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 38:
            ui->CollectByDistancePlot7->addGraph();     //添加曲线
            ui->CollectByDistancePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 39:
            ui->CollectByDistancePlot7->addGraph();     //添加曲线
            ui->CollectByDistancePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 40:
            ui->CollectByDistancePlot7->addGraph();     //添加曲线
            ui->CollectByDistancePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 41:
            ui->CollectByDistancePlot7->addGraph();     //添加曲线
            ui->CollectByDistancePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 42:
            ui->CollectByDistancePlot7->addGraph();     //添加曲线
            ui->CollectByDistancePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 43:
            ui->CollectByDistancePlot8->addGraph();     //添加曲线
            ui->CollectByDistancePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 44:
            ui->CollectByDistancePlot8->addGraph();     //添加曲线
            ui->CollectByDistancePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 45:
            ui->CollectByDistancePlot8->addGraph();     //添加曲线
            ui->CollectByDistancePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 46:
            ui->CollectByDistancePlot8->addGraph();     //添加曲线
            ui->CollectByDistancePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 47:
            ui->CollectByDistancePlot8->addGraph();     //添加曲线
            ui->CollectByDistancePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 48:
            ui->CollectByDistancePlot8->addGraph();     //添加曲线
            ui->CollectByDistancePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 49:
            ui->CollectByDistancePlot9->addGraph();     //添加曲线
            ui->CollectByDistancePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByDistancePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 50:
            ui->CollectByDistancePlot9->addGraph();     //添加曲线
            ui->CollectByDistancePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByDistancePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 51:
            ui->CollectByDistancePlot9->addGraph();     //添加曲线
            ui->CollectByDistancePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByDistancePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 52:
            ui->CollectByDistancePlot9->addGraph();     //添加曲线
            ui->CollectByDistancePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByDistancePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 53:
            ui->CollectByDistancePlot9->addGraph();     //添加曲线
            ui->CollectByDistancePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByDistancePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 54:
            ui->CollectByDistancePlot9->addGraph();     //添加曲线
            ui->CollectByDistancePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByDistancePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
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

        ui->CollectByDistancePlot1->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot1->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot1->legend->setVisible(true);
        ui->CollectByDistancePlot1->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot1->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot2->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot2->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot2->legend->setVisible(true);
        ui->CollectByDistancePlot2->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot3->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot3->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot3->legend->setVisible(true);
        ui->CollectByDistancePlot3->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot4->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot4->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot4->legend->setVisible(true);
        ui->CollectByDistancePlot4->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot4->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot5->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot5->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot5->legend->setVisible(true);
        ui->CollectByDistancePlot5->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot5->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot6->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot6->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot6->legend->setVisible(true);
        ui->CollectByDistancePlot6->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot6->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot7->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot7->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot7->legend->setVisible(true);
        ui->CollectByDistancePlot7->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot7->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot8->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot8->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot8->legend->setVisible(true);
        ui->CollectByDistancePlot8->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot8->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByDistancePlot9->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByDistancePlot9->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByDistancePlot9->legend->setVisible(true);
        ui->CollectByDistancePlot9->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByDistancePlot9->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

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

void CollectByDistancePanel::updatePlots(){

    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ui->CollectByDistancePlot1->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            ui->CollectByDistancePlot2->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            ui->CollectByDistancePlot3->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            ui->CollectByDistancePlot4->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            ui->CollectByDistancePlot5->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
            ui->CollectByDistancePlot6->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
            ui->CollectByDistancePlot7->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
            ui->CollectByDistancePlot8->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            ui->CollectByDistancePlot9->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
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
        ui->CollectByDistancePlot1->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot2->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot3->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot4->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot5->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot6->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot7->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot8->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByDistancePlot9->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->temperaturePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->distancePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->positionPlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
    }
    ui->CollectByDistancePlot1->replot();
    ui->CollectByDistancePlot2->replot();
    ui->CollectByDistancePlot3->replot();
    ui->CollectByDistancePlot4->replot();
    ui->CollectByDistancePlot5->replot();
    ui->CollectByDistancePlot6->replot();
    ui->CollectByDistancePlot7->replot();
    ui->CollectByDistancePlot8->replot();
    ui->CollectByDistancePlot9->replot();
    ui->temperaturePlot->replot();
    ui->distancePlot->replot();
    ui->positionPlot->replot();
    for (int i = 0; i < LINENUM; ++i) {
        ui->CollectByDistancePlot1->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot2->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot3->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot4->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot5->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot6->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot7->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot8->graph(i)->rescaleAxes(true);
        ui->CollectByDistancePlot9->graph(i)->rescaleAxes(true);
        if(i<3){
            ui->temperaturePlot->graph(i)->rescaleAxes(true);
            ui->positionPlot->graph(i)->rescaleAxes(true);
        }
        if(i<4){
            ui->distancePlot->graph(i)->rescaleAxes(true);
        }
    }
}

void CollectByDistancePanel::updateBxData(QList<double> newBxData){
    // 变形数据更新
    for (int i = 0; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        if(i==0){
            this->bxDataList[i].append(this->dataCount++);
        }
        else {
            this->bxDataList[i].append(newBxData.at(i-1));
        }
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

void CollectByDistancePanel::updateBxDataAdditional(QMap<QString,QString> additionalBxData){
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
