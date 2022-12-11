#include "connectiondlg.h"
#include "ui_connectiondlg.h"

connectionDlg::connectionDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::connectionDlg)
{
    ui->setupUi(this);
}

connectionDlg::~connectionDlg()
{
    delete ui;
}
