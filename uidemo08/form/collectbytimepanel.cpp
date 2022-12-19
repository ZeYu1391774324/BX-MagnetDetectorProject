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
    for (int i = 0; i <= bxData_RoadsNum; ++i) {
        this->bxDataList.append(QVector<double>());
    }

}

void CollectByTimePanel::initPlots(){
    // 每个图表中绘制6条曲线
    for (int i = 1; i <= this->bxData_RoadsNum; ++i) {
        switch (i) {
        case 1:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 2:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 3:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 4:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 5:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 6:
            ui->CollectByTimePlot1->addGraph();     //添加曲线
            ui->CollectByTimePlot1->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot1->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 7:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 8:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 9:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 10:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 11:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 12:
            ui->CollectByTimePlot2->addGraph();     //添加曲线
            ui->CollectByTimePlot2->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot2->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 13:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 14:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 15:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 16:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 17:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 18:
            ui->CollectByTimePlot3->addGraph();     //添加曲线
            ui->CollectByTimePlot3->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot3->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 19:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 20:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 21:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 22:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 23:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 24:
            ui->CollectByTimePlot4->addGraph();     //添加曲线
            ui->CollectByTimePlot4->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot4->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 25:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 26:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 27:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 28:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 29:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 30:
            ui->CollectByTimePlot5->addGraph();     //添加曲线
            ui->CollectByTimePlot5->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot5->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 31:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 32:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 33:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 34:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 35:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 36:
            ui->CollectByTimePlot6->addGraph();     //添加曲线
            ui->CollectByTimePlot6->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot6->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 37:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 38:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 39:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 40:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 41:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 42:
            ui->CollectByTimePlot7->addGraph();     //添加曲线
            ui->CollectByTimePlot7->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot7->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 43:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 44:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 45:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 46:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 47:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 48:
            ui->CollectByTimePlot8->addGraph();     //添加曲线
            ui->CollectByTimePlot8->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot8->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;

        case 49:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::crimson));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 50:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::darkorange));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 51:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::gold));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 52:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::lime));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 53:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::cyan));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        case 54:
            ui->CollectByTimePlot9->addGraph();     //添加曲线
            ui->CollectByTimePlot9->graph((i-1)%6)->setPen(QPen(QColorConstants::Svg::violet));
            ui->CollectByTimePlot9->graph((i-1)%6)->setName(QString("第%1路变形数据").arg(i));
            break;
        default:
            break;
        }

        ui->CollectByTimePlot1->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot1->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot1->legend->setVisible(true);
        ui->CollectByTimePlot1->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot1->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot2->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot2->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot2->legend->setVisible(true);
        ui->CollectByTimePlot2->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot2->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot3->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot3->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot3->legend->setVisible(true);
        ui->CollectByTimePlot3->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot3->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot4->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot4->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot4->legend->setVisible(true);
        ui->CollectByTimePlot4->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot4->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot5->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot5->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot5->legend->setVisible(true);
        ui->CollectByTimePlot5->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot5->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot6->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot6->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot6->legend->setVisible(true);
        ui->CollectByTimePlot6->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot6->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot7->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot7->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot7->legend->setVisible(true);
        ui->CollectByTimePlot7->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot7->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot8->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot8->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot8->legend->setVisible(true);
        ui->CollectByTimePlot8->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot8->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

        ui->CollectByTimePlot9->xAxis->setLabel("X/数据报变形信息序号");
        ui->CollectByTimePlot9->yAxis->setLabel("Y/电压(Volt)");
        ui->CollectByTimePlot9->legend->setVisible(true);
        ui->CollectByTimePlot9->setBackground(QColorConstants::Svg::dimgray);
        ui->CollectByTimePlot9->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom|QCP::iSelectPlottables);

    }

}
