#include "fileconversionpanel.h"
#include "qregexp.h"
#include "ui_fileconversionpanel.h"

#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QDateTime>
#include <QList>
#include <QTableWidget>
#include <QMessageBox>
#include <stdio.h>
#include <vector>

#include "localfile.h"
#include "transfer/transferbx_10.h"
#include "ChineseEncoding.h"
#include "transfer/transferBinary.h"

using namespace std;

FileConversionPanel::FileConversionPanel(QWidget *parent,QList<localFile>* lfList) :
    QWidget(parent),
    ui(new Ui::FileConversionPanel)
{
    ui->setupUi(this);
    // Initialization
    initFileConvertWork();
    initializingButtons();
    initializingTables();

    if(lfList!=nullptr){
        this->localFileList=*lfList;
    }
    this->refreshSelection();


}

FileConversionPanel::~FileConversionPanel()
{
    delete ui;
}


void FileConversionPanel::initializingTables(){
    // File Selecting Table
    ui->FileSelectingTable->setColumnCount(7);
    ui->FileSelectingTable->setHorizontalHeaderLabels(QStringList()<<"选择"<<"文件名"<<"路径"<<"大小"<<"修改时间"<<"状态"<<"移动文件按钮");



}


void FileConversionPanel::initializingButtons(){


    // Select new File Button
    connect(ui->SelectFileBtn,&QPushButton::clicked,[=](){
        // qDebug()<<"SelectBtn Clicked!!!";
        QStringList pathList;
        QString path;
        pathList=QFileDialog::getOpenFileNames(this,"Open File","C:\\Users\\DELL\\Desktop");
        for (int i = 0; i < pathList.length(); ++i) {
            path=pathList.at(i);

        if (path.isEmpty())
            return;
        else if(path.contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
            QMessageBox::warning(this,"提示","文件路径中请勿包含中文字符！");
            return;
        }
        QFile file(path);

        file.open(QIODevice::ReadOnly);
        QByteArray array = file.readAll();

        // new local file
        /*
            QString localFileName;
            QString localFilePath;
            QString localFileCreatedTime;
            QString localFileSize;
            QString localFileData;
            bool localFileSelectedFlag;
        */
        QFileInfo info(path);
        localFile *localfile = new localFile();
        localfile->localFileName=info.fileName();
        localfile->localFilePath=info.filePath();
        localfile->localFileCreatedTime=info.lastModified().toString("修改时间：yyyy/MM/dd hh:mm:ss");
        localfile->localFileSize=QString::number(info.size())+" Byte";
        localfile->localFileData=array;

        localFileList.append(*localfile);



        file.close();
        }
        this->updateTable();
    });

    // Refresh Button
    connect(ui->RefreshBtn,&QPushButton::clicked,[=](){
        this->refreshSelection();
    });

    // Delete Button
    connect(ui->deleteBtn,&QPushButton::clicked,[=](){
        if(QMessageBox::question(this,"确认窗口","您确定要移除所选择的文件吗？",QMessageBox::Yes|QMessageBox::No)==QMessageBox::Yes){
            this->deleteFiles();
        }
    });

    // Select All Button
    connect(ui->SelectAllBtn,&QPushButton::clicked,[=](){
        this->selectAll();
    });

    // Select Save Path Button
    connect(ui->SavePathBtn,&QPushButton::clicked,[=](){
       QString path=QFileDialog::getExistingDirectory(this,"打开文件","C:\\Users\\DELL\\Desktop");
       if(path.contains(QRegExp("[\\x4e00-\\x9fa5]+"))){
           QMessageBox::critical(this,"文件保存路径提示！","文件存储路径不可包含中文字符，请选择合适的文件存储路径！");
           return;
       }
       ui->SavePathEdit->setText(path);
       path=QDir::toNativeSeparators(path);
       SavePath=path;
       emit this->newSavePath(SavePath);
    });

    // Convert Button
    connect(ui->ConvertBtn,&QPushButton::clicked,[=](){
        if(ui->pipeTypecomboBox->currentIndex()==0){
            QMessageBox::information(this,"提示","请选择产品类型！");
            return;
        }
        else if(ui->pipeSizecomboBox->currentIndex()==0) {
            QMessageBox::information(this,"提示","请选择产品尺寸！");
            return;
        }
        else {
            this->parameters = new ParaGet_hard(ui->pipeTypecomboBox->currentText(),ui->pipeSizecomboBox->currentText(),ui->encryptStatComBox->currentIndex());
            if(!parameters->initiated){
                QMessageBox::information(this,"提示","当前型号系统暂不支持！");
                return;
            }
            else {
                emit this->newSavePath(SavePath);
                emit this->newParameters(parameters);
                emit this->newLocalFileList(&localFileList);
                this->convertSelectedFiles();
            }
        }

    });

    //自动排序按钮
    //connect(ui->autoSortBtn,&QPushButton::clicked,this,&FileConversionPanel::autoSort);

}


void FileConversionPanel::deleteFiles(){

    for (int i = 0; i < localFileList.length(); ++i) {
        if(localFileList[i].localFileSelectedFlag){
            localFileList.removeAt(i);
            i--;
        }
    }
//    if(!localFileList.isEmpty()&&localFileList[localFileList.length()-1].localFileSelectedFlag){
//        localFileList.removeAt(localFileList.length()-1);
//    }
    //QMessageBox::information(this,"提示","所选文件已移除！");

    this->updateTable();
}

void FileConversionPanel::refreshSelection(){
    for (int i = 0; i < ui->FileSelectingTable->rowCount(); ++i) {
        bool state=ui->FileSelectingTable->item(i,0)->checkState();
        localFileList[i].localFileSelectedFlag=state;
    }
    this->updateTable();
}

void FileConversionPanel::selectAll(){
    for (int i = 0; i < ui->FileSelectingTable->rowCount(); ++i) {
        ui->FileSelectingTable->item(i,0)->setCheckState(Qt::Checked);
    }

}

void FileConversionPanel::convertSelectedFiles(){
    int convertedNumber = 0;
    if(SavePath.isEmpty()){
        QMessageBox::critical(this,"文件保存路径为空！","当前文件存储路径未设置，请先选择文件存储路径！");
        return;
    }


    else {
        bool flag;
        for (int i = 0; i < this->localFileList.length(); ++i) {
            if(localFileList.at(i).localFileSelectedFlag){
                flag=true;
                break;
            }
        }
        if(!flag){
            QMessageBox::information(this,"提示","请先选择您要转换的文件！");
            return;
        }

        if(QMessageBox::question(this,"文件存储路径确认","您是否想要将转换后的文件存储至 "+SavePath+" ？")==QMessageBox::Yes){
            emit this->convertFilesCommand();
        }
        else {
            return;
        }
    }
/*
    else {
        if(QMessageBox::question(this,"文件存储路径确认","您是否想要将转换后的文件存储至 "+SavePath+" ？")==QMessageBox::Yes){
            for (int i = 0; i < localFileList.length(); ++i) {
                if(localFileList.at(i).localFileSelectedFlag){


                    try{
                        string cPath=(QDir::toNativeSeparators(localFileList.at(i).localFilePath)).toStdString();
                        transferBinary *tb = new transferBinary();
                        vector<string> v;
                        v.push_back(cPath);

                        tb->callTransfer(v,SavePath.toStdString(),10);

                    }
                    catch(...){
                        localFileList[i].convertState="转换失败";
                        break;
                    }

//                    FILE *file=fopen(cPath,"w");
//                    transferbx_10 *trans = new transferbx_10();
//                    trans->initParameter();
//                    trans->DatTransTxt_bx(cFileName,cData,file);
//                    qDebug()<<localFileList.at(i).localFileData<<cData;


                    ui->progressBar->setValue(((double)(i+1)/(double)localFileList.length())*100);
                    convertedNumber++;
                    localFileList[i].convertState="已转换";


                }
            }
        }
        else {
            return;
        }
    }

    QMessageBox::information(this,"文件转换完成","您所选的文件已转换完成！");
    this->updateTable();*/
}

void FileConversionPanel::updateTable(){


    ui->FileSelectingTable->setRowCount(this->localFileList.length());

    QStringList fileNameList;
    QStringList filePathList;
    QStringList fileCreatedTimeList;
    QStringList fileSizeList;
    QStringList fileSelectionList;
    QStringList fileConvertStateList;

    for (int i = 0; i < this->localFileList.length(); ++i) {
        fileNameList.append(QString(this->localFileList.at(i).localFileName));
        filePathList.append(QString(this->localFileList.at(i).localFilePath));
        fileCreatedTimeList.append(QString(this->localFileList.at(i).localFileCreatedTime));
        fileSizeList.append(QString(this->localFileList.at(i).localFileSize));
        if(this->localFileList.at(i).localFileSelectedFlag){
            fileSelectionList.append(QString("Selected"));
        }
        else{
            fileSelectionList.append(QString("Unselected"));
        }
        fileConvertStateList.append(QString(this->localFileList.at(i).convertState));

    }

    for (int j = 0; j < localFileList.length(); ++j) {
        int col=0;

        QTableWidgetItem *selectState = new QTableWidgetItem(fileSelectionList[j]);
        if(this->localFileList.at(j).localFileSelectedFlag){
            selectState->setCheckState(Qt::Checked);
        }
        else{
            selectState->setCheckState(Qt::Unchecked);
        }
        ui->FileSelectingTable->setItem(j,col++,selectState);
        ui->FileSelectingTable->setItem(j,col++,new QTableWidgetItem(fileNameList[j]));
        ui->FileSelectingTable->setItem(j,col++,new QTableWidgetItem(filePathList[j]));
        ui->FileSelectingTable->setItem(j,col++,new QTableWidgetItem(fileSizeList[j]));
        ui->FileSelectingTable->setItem(j,col++,new QTableWidgetItem(fileCreatedTimeList[j]));
        ui->FileSelectingTable->setItem(j,col,new QTableWidgetItem(fileConvertStateList[j]));
        if(fileConvertStateList[j]==QString("未转换")){
            ui->FileSelectingTable->item(j,col)->setTextColor(Qt::yellow);

        }
        else if(fileConvertStateList[j]==QString("已转换")){
            ui->FileSelectingTable->item(j,col)->setTextColor(Qt::cyan);

        }
        else if(fileConvertStateList[j]==QString("转换失败")){
            ui->FileSelectingTable->item(j,col)->setTextColor(Qt::red);

        }
        col++;
        QPushButton *upBtn = new QPushButton("上移");
        QPushButton *downBtn = new QPushButton("下移");
        QWidget *tmp_widget = new QWidget();
        upBtn->setParent(tmp_widget);
        downBtn->setParent(tmp_widget);
        QHBoxLayout *tmp_layout = new QHBoxLayout(tmp_widget);
        tmp_layout->addWidget(upBtn);
        tmp_layout->addWidget(downBtn);
        tmp_layout->setMargin(0);

        ui->FileSelectingTable->setCellWidget(j,col,tmp_widget);
        connect(upBtn,&QPushButton::clicked,[=](){
            int x = tmp_widget->mapToParent(QPoint(0,0)).x();
            int y = tmp_widget->mapToParent(QPoint(0,0)).y();
            QModelIndex index = ui->FileSelectingTable->indexAt(QPoint(x,y));
            int row = index.row();
            int col = index.column();
            //qDebug()<<row<<"---"<<col;
            if(row>0){
                this->moveFileTo(row,row-1);
            }
        });
        connect(downBtn,&QPushButton::clicked,[=](){
            int x = tmp_widget->mapToParent(QPoint(0,0)).x();
            int y = tmp_widget->mapToParent(QPoint(0,0)).y();
            QModelIndex index = ui->FileSelectingTable->indexAt(QPoint(x,y));
            int row = index.row();
            int col = index.column();
            //qDebug()<<row<<"---"<<col;
            if(row<localFileList.length()-1){
                this->moveFileTo(row,row+1);
            }

        });

    }

    ui->FileSelectingTable->resizeColumnsToContents(); 
    emit this->newLocalFileList(&localFileList);

}

void FileConversionPanel::initFileConvertWork(){
    QThread * fileConvertThread = new QThread;
    FileConvertWork *fileconvertWork = new FileConvertWork;
    fileconvertWork->moveToThread(fileConvertThread);
    fileConvertThread->start();
    connect(this,&FileConversionPanel::newParameters,fileconvertWork,&FileConvertWork::initParameters);                 //更新产品参数
    connect(this,&FileConversionPanel::newSavePath,fileconvertWork,&FileConvertWork::updateSavePath);                   //更新存储路径
    connect(this,&FileConversionPanel::newLocalFileList,fileconvertWork,&FileConvertWork::updateLocalFileList);         //更新文件列表
    connect(this,&FileConversionPanel::convertFilesCommand,fileconvertWork,&FileConvertWork::convertFiles);             //开始文件转换指令
    connect(fileconvertWork,&FileConvertWork::fileConvertProgress_total,this,&FileConversionPanel::returnedProgress_total);
    connect(fileconvertWork,&FileConvertWork::fileConvertProcess,this,&FileConversionPanel::returnedProgress);
    connect(fileconvertWork,&FileConvertWork::fileConvertedIndex,this,&FileConversionPanel::returnedFileConvertedIndex);
    connect(fileconvertWork,&FileConvertWork::workFinished,this,&FileConversionPanel::returnedFinishedInfo);
    connect(fileconvertWork,&FileConvertWork::newInfo,this,&FileConversionPanel::newCovertingInfo);

    connect(this,&FileConversionPanel::returnedProgress_total,[=](int currentIndex,int total){                //返回总体进度
        ui->convertProgressLabel->setText(QString("当前进度：%1/%2").arg(currentIndex).arg(total));
    });
    connect(this,&FileConversionPanel::returnedProgress,[=](int progress){                                                 //返回当前文件转换进度
        this->ui->progressBar->setValue(progress);
    });
    connect(this,&FileConversionPanel::returnedFileConvertedIndex,[=](int index,QString stat){                           //更新文件转换状态
        this->localFileList[index].setConvertState(stat);
        this->updateTable();
    });
    connect(this,&FileConversionPanel::returnedFinishedInfo,[=](){                                                       //转换完成提示
        QMessageBox::information(this,"提示","文件转换完成！");
        ui->convertProgressLabel->setText("文件转换完成！");
        ui->progressBar->setValue(100);
    });
    connect(this,&FileConversionPanel::newCovertingInfo,[=](QString info){
        QString str = ui->convertProgressLabel->text();
        str+="; ";
        str+=info;
        ui->convertProgressLabel->setText(str);
    });

}

void FileConversionPanel::moveFileTo(int currentIndex, int targetIndex){
    if((targetIndex>=0)&&(targetIndex<this->localFileList.length())){
//        localFile temp = localFileList.at(currentIndex);
//        localFileList[currentIndex]=localFileList[targetIndex];
//        localFileList[targetIndex]=temp;
        localFileList.swap(currentIndex,targetIndex);
        this->updateTable();

    }
}

void FileConversionPanel::autoSort(){
    QList<localFile> tempList;
    for (int i = 0; i < localFileList.length(); ++i) {
        int min=tempList.at(i).localFileName.toInt();
        int flag;
        for (int j = 0; j < localFileList.length(); ++j) {
            int value = localFileList.at(j).localFileName.toInt();
            if(value<min){
                flag=j;
                min=value;
            }
        }
        tempList.append(localFileList.at(flag));
        localFileList.removeAt(flag);
        i--;
    }
    localFileList=tempList;
    tempList.clear();
    this->updateTable();
}
