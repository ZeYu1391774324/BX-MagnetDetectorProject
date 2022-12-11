#include <QDebug>
#include <iostream>


#include "panel_password.h"
#include "qmessagebox.h"
#include "ui_panel_password.h"

#define PASSWORD "123456"
using namespace std;

panel_password::panel_password(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::panel_password)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setWindowModality(Qt::ApplicationModal);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &panel_password::exit);
    connect(ui->pushButton,&QPushButton::clicked,this,&panel_password::checkPassword);
}

panel_password::~panel_password()
{
    delete ui;
}

void panel_password::checkPassword(){

    QString inputPwd = this->ui->textEdit->toPlainText();
    QMessageBox * pwd_message = new QMessageBox;

    if(PASSWORD==inputPwd.toStdString()){
        flag=false;
        pwd_message->information(this,"密码正确提示","密码正确！欢迎进入系统！");
        this->close();
    }
    else{
        pwd_message->warning(this,"密码错误提示","密码错误！请重新输入！（密码：123456）");
    }
    //qDebug() << inputPwd;





}

void panel_password::exit(){
    if (QMessageBox::question(this,"退出程序确认窗口","您是否想退出程序？")==QMessageBox::Yes){
        qDebug() << "Exit the application!";
        QApplication * app;
        app->exit(0);
    }
}

void panel_password::closeEvent(QCloseEvent * e){


        if(flag){
                if (QMessageBox::question(this,"退出程序确认窗口","您是否想退出程序？")==QMessageBox::Yes){
                    qDebug() << "Exit the application!";
                    QApplication * app;
                    app->exit(0);

                }
                else{
                    e->ignore();
                }


    }

}






