#ifndef PARAGET_H
#define PARAGET_H

#include <QWidget>
#include <QDebug>

class ParaGet
{
public:
    //ParaGet(QString type, QString size);
    ParaGet(QString type, QString size, int encryptFlag);

    bool initiated = false;
    bool encrypted = true;
    QString pipeType;
    QString pipeSize;
    int frameLength_hard;
    struct DATAPARA
    {
        int data1_18_start;
        int data1_18_len;
        int data19_36_start;
        int data19_36_len;
        int data37_54_start;
        int data37_54_len;

    }dataPara;

    struct TEMPDATA{
        int tempEnvir_start;
        int tempEnvir_len;
        int tempPanel_start;
        int tempPanel_len;
        int tempPos_start;
        int tempPos_len;
        double envirPara1,envirPara2;
        double panelPara,positionPara;
    }tempData;

    struct DISDATA{
        int opt_start,opt_len;
        int dis1_start,dis1_len;
        int dis2_start,dis2_len;
        int dis3_start,dis3_len;

    }disData;

    struct POSDATA{
        int ZXJ_start,ZXJ_len;
        int QJ_start,QJ_len;
        int HXJ_start,HXJ_len;
        double ZXJpara,QJpara,HXJpara;
    }posData;

    struct ADDDATA
    {
        int clock_start,clock_len;
        int Volt24V_start,Volt24V_len;
        double Volt_24V_para;
        int Current_24V_start,Current_24V_len;
        double Current_24V_para;
        int batUsed_start,batUsed_len;
        double batUsed_para;
        int batUsedTimes_start,batUsedTimes_len;
        int batUsedTimelen_start,batUsedTimelen_len;
        double batUsedTimelen_para;
        int batVolume_start,batVolume_len;
        double batVolume_para;
        int timeYear_start,timeYear_len,timeMonth_start,timeMonth_len,timeDay_start,timeDay_len;
        int batMode_start,batMode_len;
        int Volt5V_start,Volt5V_len;
        double Volt5V_para;
        int Volt3V_start,Volt3V_len;
        double Volt3V_para;

    }addData;

};

#endif // PARAGET_H
