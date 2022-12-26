#ifndef FILECONVERSIONPANEL_H
#define FILECONVERSIONPANEL_H

#include <QWidget>
#include <QThread>
#include "localfile.h"
#include "workers/fileconvertwork.h"
#include "paraget_hard.h"

namespace Ui {
class FileConversionPanel;
}

class FileConversionPanel : public QWidget
{
    Q_OBJECT

public:
    explicit FileConversionPanel(QWidget *parent = nullptr);
    ~FileConversionPanel();

    QString SavePath;

    void initializingTables();
    void initializingButtons();
    void updateTable();
    void refreshSelection();
    void deleteFiles();
    void selectAll();
    void convertSelectedFiles();
    void initFileConvertWork();

    QList<localFile> localFileList;
    ParaGet_hard *parameters;

private:
    Ui::FileConversionPanel *ui;

signals:
    void newLocalFileList(QList<localFile>*);
    void newSavePath(QString);
    void newParameters(ParaGet_hard*);
    void convertFilesCommand();

};

#endif // FILECONVERSIONPANEL_H
