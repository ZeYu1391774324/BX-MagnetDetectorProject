#ifndef LOCALFILE_H
#define LOCALFILE_H
#include <QString>

class localFile
{

public:
    explicit localFile();

    QString localFileName;
    QString localFilePath;
    QString localFileCreatedTime;
    QString localFileSize;
    QString localFileData;
    bool localFileSelectedFlag;
    QString convertState;





};

#endif // LOCALFILE_H
