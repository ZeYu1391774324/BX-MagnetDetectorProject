#ifndef FILECONVERTWORK_H
#define FILECONVERTWORK_H

#include <QObject>
#include <QDebug>
#include <fstream>
#include <QTimer>
#include <cmath>>
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
    int HexToDecimalFile(localFile file);
    void updateLocalFileList(QList<localFile>*);
    void updateSavePath(QString);
    QList<double> bxDataExtract(QString subframe);


private:
    QList<localFile> localfilelist;
    QString SavePath;
    ParaGet_hard parameters;

signals:
    void fileConvertProcess(double);
    void fileConvertedIndex(int,QString);
    void workFinished();
    void fileConvertProgress_total(int,int);

};

#endif // FILECONVERTWORK_H
