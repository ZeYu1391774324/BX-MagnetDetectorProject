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
    for (int i = 0; i <= bxData_RoadsNum; ++i) {
        this->bxDataList.append(QVector<double>());
    }

}



void CollectByDistancePanel::initPlots(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= this->bxData_RoadsNum; ++i) {
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

    }

}

void CollectByDistancePanel::updatePlots(){

    for (int i = 1; i <= this->bxData_RoadsNum; ++i) {
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
    }
}

void CollectByDistancePanel::updateBxData(QList<double> newBxData){
    // 变形数据更新
    for (int i = 0; i <= this->bxData_RoadsNum; ++i) {
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
        for (int i = 0; i <= this->bxData_RoadsNum; ++i) {
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
