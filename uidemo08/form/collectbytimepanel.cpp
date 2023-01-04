#include "collectbytimepanel.h"
#include "ui_collectbytimepanel.h"

CollectByTimePanel::CollectByTimePanel(QWidget *parent, QSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::CollectByTimePanel)
{
    ui->setupUi(this);

    this->serial=serial;
    this->initPanel();
    this->initPlots();
}

CollectByTimePanel::~CollectByTimePanel()
{
    delete ui;
}


void CollectByTimePanel::initPanel(){
    // initiate buttons
    // Collect by time start button
    connect(ui->CollectByTime_StartBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(COLLECTBYTIMEFRAME).toLatin1().data()));});
    //Collect by time stop button
    connect(ui->CollectByTime_StopBtn,&QPushButton::clicked,[=](){serial->write(QByteArray::fromHex(QString(STOPCOLLECTFRAME).toLatin1().data()));});
    // stackWidget Selection comBox
    connect(ui->bxDataRoadsSelectingComboBox,&QComboBox::currentTextChanged,[=](){
        ui->stackedWidget->setCurrentIndex(ui->bxDataRoadsSelectingComboBox->currentIndex());
    });
    // initiate bxDataRoads
    for (int i = 0; i <= bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        this->bxDataList.append(QVector<double>());
    }

}

void CollectByTimePanel::initPlots(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 2:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 3:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 4:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 5:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 6:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 7:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 8:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 9:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 10:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 11:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 12:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 13:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 14:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 15:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 16:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 17:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 18:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 19:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 20:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 21:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 22:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 23:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 24:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 25:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 26:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 27:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 28:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 29:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 30:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 31:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 32:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 33:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 34:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 35:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 36:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 37:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 38:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 39:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 40:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 41:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 42:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 43:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 44:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 45:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 46:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 47:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 48:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;

        case 49:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 50:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 51:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 52:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 53:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
            break;
        case 54:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路数据").arg(i));
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

        ui->CollectByTimePlot1->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot1->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot1->legend->setVisible(true);
        ui->CollectByTimePlot1->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot1->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot2->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot2->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot2->legend->setVisible(true);
        ui->CollectByTimePlot2->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot3->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot3->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot3->legend->setVisible(true);
        ui->CollectByTimePlot3->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot4->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot4->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot4->legend->setVisible(true);
        ui->CollectByTimePlot4->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot4->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot5->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot5->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot5->legend->setVisible(true);
        ui->CollectByTimePlot5->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot5->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot6->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot6->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot6->legend->setVisible(true);
        ui->CollectByTimePlot6->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot6->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot7->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot7->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot7->legend->setVisible(true);
        ui->CollectByTimePlot7->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot7->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot8->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot8->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot8->legend->setVisible(true);
        ui->CollectByTimePlot8->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot8->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot9->xAxis->setLabel("X/数据报信息序号");
        ui->CollectByTimePlot9->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot9->legend->setVisible(true);
        ui->CollectByTimePlot9->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot9->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);


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

void CollectByTimePanel::updatePlots(){

    for (int i = 1; i <= this->bxData_RoadsNum+temperature_RoadsNum+distance_RoadsNum+position_RoadsNum; ++i) {
        switch (i) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            ui->CollectByTimePlot1->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
            ui->CollectByTimePlot2->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            ui->CollectByTimePlot3->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 19:
        case 20:
        case 21:
        case 22:
        case 23:
        case 24:
            ui->CollectByTimePlot4->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 25:
        case 26:
        case 27:
        case 28:
        case 29:
        case 30:
            ui->CollectByTimePlot5->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 31:
        case 32:
        case 33:
        case 34:
        case 35:
        case 36:
            ui->CollectByTimePlot6->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 37:
        case 38:
        case 39:
        case 40:
        case 41:
        case 42:
            ui->CollectByTimePlot7->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 43:
        case 44:
        case 45:
        case 46:
        case 47:
        case 48:
            ui->CollectByTimePlot8->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
            break;
        case 49:
        case 50:
        case 51:
        case 52:
        case 53:
        case 54:
            ui->CollectByTimePlot9->graph((i-1)%6)->setData(this->bxDataList[0],this->bxDataList[i]);
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
        ui->CollectByTimePlot1->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot2->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot3->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot4->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot5->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot6->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot7->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot8->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->CollectByTimePlot9->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->temperaturePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->distancePlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
        ui->positionPlot->xAxis->setRange(this->bxDataList[0].first(),CLEARNUM,Qt::AlignLeft);
    }
    ui->CollectByTimePlot1->replot();
    ui->CollectByTimePlot2->replot();
    ui->CollectByTimePlot3->replot();
    ui->CollectByTimePlot4->replot();
    ui->CollectByTimePlot5->replot();
    ui->CollectByTimePlot6->replot();
    ui->CollectByTimePlot7->replot();
    ui->CollectByTimePlot8->replot();
    ui->CollectByTimePlot9->replot();
    ui->temperaturePlot->replot();
    ui->distancePlot->replot();
    ui->positionPlot->replot();
    for (int i = 0; i < LINENUM; ++i) {
        ui->CollectByTimePlot1->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot2->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot3->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot4->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot5->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot6->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot7->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot8->graph(i)->rescaleAxes(true);
        ui->CollectByTimePlot9->graph(i)->rescaleAxes(true);
        if(i<3){
            ui->temperaturePlot->graph(i)->rescaleAxes(true);
            ui->positionPlot->graph(i)->rescaleAxes(true);
        }
        if(i<4){
            ui->distancePlot->graph(i)->rescaleAxes(true);
        }
    }
}

void CollectByTimePanel::updateBxData(QList<double> newBxData){
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

void CollectByTimePanel::updateBxDataAdditional(QMap<QString,QString> additionalBxData){
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

void CollectByTimePanel::updateSpeedLabel(int speed){
    ui->ByteSpeedLabel->setText(QString("当前串口传输速率：%1 Byte/s.").arg(speed));
}

void CollectByTimePanel::updateParametersLabel(ParaGet* para){
    ui->ParametersLabel->setText(QString("当前产品参数：%1-%2").arg(para->pipeSize).arg(para->pipeType));
}
