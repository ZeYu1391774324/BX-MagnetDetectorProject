#ifndef FILECONVERTWORK_H
#define FILECONVERTWORK_H

#include <QObject>
#include <QDebug>
#include <fstream>
#include "localfile.h"
#include "binddata.h"
#include "paraget_hard.h"

#define STARTPOINT 6
#define DECIMALFILEFRAMENUM_MAX 50000

using namespace std;

class FileConvertWork : public QObject
{
    Q_OBJECT
public:
    explicit FileConvertWork();

    double process;
    void initParameters(ParaGet_hard*);
    void convertFiles();
    void HexToDecimalFile(localFile file);
    void updateLocalFileList(QList<localFile>*);
    void updateSavePath(QString);
    QList<double> bxDataExtract(QString subframe);


private:
    QList<localFile>* localfilelist;
    QString SavePath;
    ParaGet_hard *parameters;

signals:
    void fileConvertProcess(double);

};

#endif // FILECONVERTWORK_H
