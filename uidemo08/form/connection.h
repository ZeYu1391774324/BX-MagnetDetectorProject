#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>

class Connection
{
public:
    Connection();

    QStringList *baudList;          //波特率
    QStringList *parityList;        //校验位
    QStringList *dataBitsList;       //数据位
    QStringList *stopBitsList;       //停止位
    QStringList *flowControlList;    //控制流

};

#endif // CONNECTION_H
