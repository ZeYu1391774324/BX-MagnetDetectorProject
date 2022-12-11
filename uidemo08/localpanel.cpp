#include "localpanel.h"
#include "ui_localpanel.h"
#include "fileconversionpanel.h"
#include <QDebug>

LocalPanel::LocalPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LocalPanel)
{
    ui->setupUi(this);

    // file conversion button
    connect(ui->FileConversionBtn,&QToolButton::clicked,[=](){
        // qDebug() << "conversion button clicked!!!";
        FileConversionPanel * fc_Panel = new FileConversionPanel();
        fc_Panel->show();

    });
}

LocalPanel::~LocalPanel()
{
    delete ui;
}
