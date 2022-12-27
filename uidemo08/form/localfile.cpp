#include "localfile.h"

localFile::localFile()

{
    localFileName = "Default localFile Name";
    localFilePath = "File path not Found!";
    localFileCreatedTime = "N/A";
    localFileSize = "N/A";
    localFileSelectedFlag = true;
    convertState = "未转换";


}

void localFile::setConvertState(QString stat){
    this->convertState=stat;
}
