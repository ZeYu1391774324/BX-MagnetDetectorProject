#include "paraget.h"



ParaGet::ParaGet(QString type,QString size,int encryptFlag)
{
    if(encryptFlag==0){
        encrypted=true;
    }
    else if (encryptFlag==1) {
        encrypted=false;
    }

    QStringList typelist,sizelist;
    typelist<<"请选择产品类型"<<"变形"<<"漏磁";
    sizelist<<"请选择产品尺寸"<<"8inch"<<"10inch"<<"12inch"<<"14inch";
    pipeType=type;
    pipeSize=size;

    switch (typelist.indexOf(type)) {
    case 0:
        initiated = false;
        break;
    case 1:                     //变形
        switch (sizelist.indexOf(size)) {
        case 0:
            initiated = false;
            break;
        case 1:                 //8inch变形
            if(encrypted){
                frameLength_hard=196*2;
            }
            else if(!encrypted){
                frameLength_hard=194*2;
            }
            // 数据部分参数
            dataPara.data1_18_start=80;
            dataPara.data1_18_len=72;
            dataPara.data19_36_start=154;
            dataPara.data19_36_len=72;
            dataPara.data37_54_start=228;
            dataPara.data37_54_len=72;

            //环境温度参数,处理板温度参数,姿态温度参数
            tempData.tempEnvir_start=60;
            tempData.tempEnvir_len=4;
            tempData.tempPanel_start=302;
            tempData.tempPanel_len=4;
            tempData.tempPos_start=330;
            tempData.tempPos_len=4;
            tempData.envirPara1=193.23;
            tempData.envirPara2=0.23;
            tempData.panelPara=0.0625;
            tempData.positionPara=0.0625;

            //里程参数
            disData.opt_start=8;
            disData.opt_len=8;
            disData.dis1_start=360;
            disData.dis1_len=8;
            disData.dis2_start=368;
            disData.dis2_len=8;
            disData.dis3_start=376;
            disData.dis3_len=8;

            //姿态周向角，倾角，航向角，加速度
            posData.ZXJ_start=306;
            posData.ZXJ_len=4;
            posData.QJ_start=310;
            posData.QJ_len=4;
            posData.HXJ_start=314;
            posData.HXJ_len=4;
            posData.ZXJpara=0.1;
            posData.QJpara=0.1;
            posData.HXJpara=0.1;

            /*  额外显示数据参数

                时钟脉冲计数
                24V系统供电电压
                24V系统供电电流
                电池组已用电量
                电池累计通电次数
                电池累计通电时间
                电池组额定电量
                电池更换时间
                电池模块环境温度
                供电方式
                5V二次电源电压
                3.3V二次电源电压
            */
            addData.clock_start=16;
            addData.clock_len=12;
            addData.Volt24V_start=28;
            addData.Volt24V_len=4;
            addData.Volt_24V_para=0.001;
            addData.Current_24V_start=32;
            addData.Current_24V_len=4;
            addData.Current_24V_para=0.001;
            addData.batUsed_start=36;
            addData.batUsed_len=4;
            addData.batUsed_para=0.1;
            addData.batUsedTimes_start=40;
            addData.batUsedTimes_len=4;
            addData.batUsedTimelen_start=44;
            addData.batUsedTimelen_len=4;
            addData.batUsedTimelen_para=0.01;
            addData.batVolume_start=48;
            addData.batVolume_len=4;
            addData.batVolume_para=0.1;
            addData.timeYear_start=52;
            addData.timeYear_len=4;
            addData.timeMonth_start=56;
            addData.timeMonth_len=2;
            addData.timeDay_start=58;
            addData.timeDay_len=2;
            addData.batMode_start=66;
            addData.batMode_len=2;
            addData.Volt5V_start=68;
            addData.Volt5V_len=4;
            addData.Volt5V_para=0.0078;
            addData.Volt3V_start=72;
            addData.Volt3V_len=4;
            addData.Volt3V_para=0.0036;

            initiated=true;
            break;
        case 2:                 //10inch变形
            if(encrypted){
                frameLength_hard=196*2;
            }
            else if(!encrypted){
                frameLength_hard=194*2;
            }
            // 数据部分参数
            dataPara.data1_18_start=80;
            dataPara.data1_18_len=72;
            dataPara.data19_36_start=154;
            dataPara.data19_36_len=72;
            dataPara.data37_54_start=228;
            dataPara.data37_54_len=72;

            //环境温度参数,处理板温度参数,姿态温度参数
            tempData.tempEnvir_start=60;
            tempData.tempEnvir_len=4;
            tempData.tempPanel_start=302;
            tempData.tempPanel_len=4;
            tempData.tempPos_start=330;
            tempData.tempPos_len=4;
            tempData.envirPara1=193.23;
            tempData.envirPara2=0.23;
            tempData.panelPara=0.0625;
            tempData.positionPara=0.0625;

            //里程参数
            disData.opt_start=8;
            disData.opt_len=8;
            if(encrypted){
                disData.dis1_start=360;
                disData.dis1_len=8;
                disData.dis2_start=368;
                disData.dis2_len=8;
                disData.dis3_start=376;
                disData.dis3_len=8;
            }
            else {
                disData.dis1_start=356;
                disData.dis1_len=8;
                disData.dis2_start=364;
                disData.dis2_len=8;
                disData.dis3_start=372;
                disData.dis3_len=8;
            }

            //姿态周向角，倾角，航向角，加速度
            posData.ZXJ_start=306;
            posData.ZXJ_len=4;
            posData.QJ_start=310;
            posData.QJ_len=4;
            posData.HXJ_start=314;
            posData.HXJ_len=4;
            posData.ZXJpara=0.1;
            posData.QJpara=0.1;
            posData.HXJpara=0.1;

            /*  额外显示数据参数

                时钟脉冲计数
                24V系统供电电压
                24V系统供电电流
                电池组已用电量
                电池累计通电次数
                电池累计通电时间
                电池组额定电量
                电池更换时间
                电池模块环境温度
                供电方式
                5V二次电源电压
                3.3V二次电源电压
            */
            addData.clock_start=16;
            addData.clock_len=12;
            addData.Volt24V_start=28;
            addData.Volt24V_len=4;
            addData.Volt_24V_para=0.001;
            addData.Current_24V_start=32;
            addData.Current_24V_len=4;
            addData.Current_24V_para=0.001;
            addData.batUsed_start=36;
            addData.batUsed_len=4;
            addData.batUsed_para=0.1;
            addData.batUsedTimes_start=40;
            addData.batUsedTimes_len=4;
            addData.batUsedTimelen_start=44;
            addData.batUsedTimelen_len=4;
            addData.batUsedTimelen_para=0.01;
            addData.batVolume_start=48;
            addData.batVolume_len=4;
            addData.batVolume_para=0.1;
            addData.timeYear_start=52;
            addData.timeYear_len=4;
            addData.timeMonth_start=56;
            addData.timeMonth_len=2;
            addData.timeDay_start=58;
            addData.timeDay_len=2;
            addData.batMode_start=66;
            addData.batMode_len=2;
            addData.Volt5V_start=68;
            addData.Volt5V_len=4;
            addData.Volt5V_para=0.0078;
            addData.Volt3V_start=72;
            addData.Volt3V_len=4;
            addData.Volt3V_para=0.0036;

            initiated=true;
            break;
        case 3:                 //12inch变形
            if(encrypted){
                frameLength_hard=196*2;
            }
            else if(!encrypted){
                frameLength_hard=194*2;
            }
            // 数据部分参数
            dataPara.data1_18_start=80;
            dataPara.data1_18_len=72;
            dataPara.data19_36_start=154;
            dataPara.data19_36_len=72;
            dataPara.data37_54_start=228;
            dataPara.data37_54_len=72;

            //环境温度参数,处理板温度参数,姿态温度参数
            tempData.tempEnvir_start=60;
            tempData.tempEnvir_len=4;
            tempData.tempPanel_start=302;
            tempData.tempPanel_len=4;
            tempData.tempPos_start=330;
            tempData.tempPos_len=4;
            tempData.envirPara1=193.23;
            tempData.envirPara2=0.23;
            tempData.panelPara=0.0625;
            tempData.positionPara=0.0625;

            //里程参数
            disData.opt_start=8;
            disData.opt_len=8;
            if(encrypted){
                disData.dis1_start=360;
                disData.dis1_len=8;
                disData.dis2_start=368;
                disData.dis2_len=8;
                disData.dis3_start=376;
                disData.dis3_len=8;
            }
            else {
                disData.dis1_start=356;
                disData.dis1_len=8;
                disData.dis2_start=364;
                disData.dis2_len=8;
                disData.dis3_start=372;
                disData.dis3_len=8;
            }

            //姿态周向角，倾角，航向角，加速度
            posData.ZXJ_start=306;
            posData.ZXJ_len=4;
            posData.QJ_start=310;
            posData.QJ_len=4;
            posData.HXJ_start=314;
            posData.HXJ_len=4;
            posData.ZXJpara=0.1;
            posData.QJpara=0.1;
            posData.HXJpara=0.1;

            /*  额外显示数据参数

                时钟脉冲计数
                24V系统供电电压
                24V系统供电电流
                电池组已用电量
                电池累计通电次数
                电池累计通电时间
                电池组额定电量
                电池更换时间
                电池模块环境温度
                供电方式
                5V二次电源电压
                3.3V二次电源电压
            */
            addData.clock_start=16;
            addData.clock_len=12;
            addData.Volt24V_start=28;
            addData.Volt24V_len=4;
            addData.Volt_24V_para=0.001;
            addData.Current_24V_start=32;
            addData.Current_24V_len=4;
            addData.Current_24V_para=0.001;
            addData.batUsed_start=36;
            addData.batUsed_len=4;
            addData.batUsed_para=0.1;
            addData.batUsedTimes_start=40;
            addData.batUsedTimes_len=4;
            addData.batUsedTimelen_start=44;
            addData.batUsedTimelen_len=4;
            addData.batUsedTimelen_para=0.01;
            addData.batVolume_start=48;
            addData.batVolume_len=4;
            addData.batVolume_para=0.1;
            addData.timeYear_start=52;
            addData.timeYear_len=4;
            addData.timeMonth_start=56;
            addData.timeMonth_len=2;
            addData.timeDay_start=58;
            addData.timeDay_len=2;
            addData.batMode_start=66;
            addData.batMode_len=2;
            addData.Volt5V_start=68;
            addData.Volt5V_len=4;
            addData.Volt5V_para=0.0078;
            addData.Volt3V_start=72;
            addData.Volt3V_len=4;
            addData.Volt3V_para=0.0036;

            initiated=true;
            break;
        case 4:                 //14inch变形
            if(encrypted){
                frameLength_hard=196*2;
            }
            else if(!encrypted){
                frameLength_hard=194*2;
            }
            // 数据部分参数
            dataPara.data1_18_start=80;
            dataPara.data1_18_len=72;
            dataPara.data19_36_start=154;
            dataPara.data19_36_len=72;
            dataPara.data37_54_start=228;
            dataPara.data37_54_len=72;

            //环境温度参数,处理板温度参数,姿态温度参数
            tempData.tempEnvir_start=60;
            tempData.tempEnvir_len=4;
            tempData.tempPanel_start=302;
            tempData.tempPanel_len=4;
            tempData.tempPos_start=330;
            tempData.tempPos_len=4;
            tempData.envirPara1=193.23;
            tempData.envirPara2=0.23;
            tempData.panelPara=0.0625;
            tempData.positionPara=0.0625;

            //里程参数
            disData.opt_start=8;
            disData.opt_len=8;
            disData.dis1_start=360;
            disData.dis1_len=8;
            disData.dis2_start=368;
            disData.dis2_len=8;
            disData.dis3_start=376;
            disData.dis3_len=8;

            //姿态周向角，倾角，航向角，加速度
            posData.ZXJ_start=306;
            posData.ZXJ_len=4;
            posData.QJ_start=310;
            posData.QJ_len=4;
            posData.HXJ_start=314;
            posData.HXJ_len=4;
            posData.ZXJpara=0.1;
            posData.QJpara=0.1;
            posData.HXJpara=0.1;

            /*  额外显示数据参数

                时钟脉冲计数
                24V系统供电电压
                24V系统供电电流
                电池组已用电量
                电池累计通电次数
                电池累计通电时间
                电池组额定电量
                电池更换时间
                电池模块环境温度
                供电方式
                5V二次电源电压
                3.3V二次电源电压
            */
            addData.clock_start=16;
            addData.clock_len=12;
            addData.Volt24V_start=28;
            addData.Volt24V_len=4;
            addData.Volt_24V_para=0.001;
            addData.Current_24V_start=32;
            addData.Current_24V_len=4;
            addData.Current_24V_para=0.001;
            addData.batUsed_start=36;
            addData.batUsed_len=4;
            addData.batUsed_para=0.1;
            addData.batUsedTimes_start=40;
            addData.batUsedTimes_len=4;
            addData.batUsedTimelen_start=44;
            addData.batUsedTimelen_len=4;
            addData.batUsedTimelen_para=0.01;
            addData.batVolume_start=48;
            addData.batVolume_len=4;
            addData.batVolume_para=0.1;
            addData.timeYear_start=52;
            addData.timeYear_len=4;
            addData.timeMonth_start=56;
            addData.timeMonth_len=2;
            addData.timeDay_start=58;
            addData.timeDay_len=2;
            addData.batMode_start=66;
            addData.batMode_len=2;
            addData.Volt5V_start=68;
            addData.Volt5V_len=4;
            addData.Volt5V_para=0.0078;
            addData.Volt3V_start=72;
            addData.Volt3V_len=4;
            addData.Volt3V_para=0.0036;

            initiated=true;
            break;
        default:
            initiated=false;
            break;
        }

        break;
    case 2:                     //漏磁
        switch (sizelist.indexOf(size)){
        default:
            initiated=false;
            break;
        }
        break;
    default:
        initiated = false;
        break;
    }

}
