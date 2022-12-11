#ifndef PANEL_PASSWORD_H
#define PANEL_PASSWORD_H

#include <QWidget>
#include <QCloseEvent>

namespace Ui {
class panel_password;
}

class panel_password : public QWidget
{
    Q_OBJECT

public:
    explicit panel_password(QWidget *parent = nullptr);
    ~panel_password();

private:
    Ui::panel_password *ui;

    bool flag=true; // flag为true退出程序。

    void checkPassword();
    void exit();
    void closeEvent(QCloseEvent * e);

};

#endif // PANEL_PASSWORD_H
