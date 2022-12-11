#ifndef CONNECTIONDLG_H
#define CONNECTIONDLG_H

#include <QDialog>

namespace Ui {
class connectionDlg;
}

class connectionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit connectionDlg(QWidget *parent = 0);
    ~connectionDlg();

private:
    Ui::connectionDlg *ui;
};

#endif // CONNECTIONDLG_H
