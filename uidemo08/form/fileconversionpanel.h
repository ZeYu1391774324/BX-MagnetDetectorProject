#ifndef FILECONVERSIONPANEL_H
#define FILECONVERSIONPANEL_H

#include <QWidget>
#include "localfile.h"
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

    QList<localFile> localFileList;

private:
    Ui::FileConversionPanel *ui;

};

#endif // FILECONVERSIONPANEL_H
