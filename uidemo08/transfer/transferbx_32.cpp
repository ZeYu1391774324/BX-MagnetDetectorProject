
#include "transferbx_32.h"

void transferbx_32::initParameter()
{
	FrameLen = 229 + 4; 	                  //单帧数据长度（字节）（本地）
	channelnum.mfl = 0;		          //漏磁通道数
	channelnum.deform = 0;		      //变形通道数
	channelnum.bak = 0;			      //备用通道数 
	channelnum.all = 0;				  //总通道数     
	channelnum.motorbyte = 11;	      //姿态预留字节数  

	coedata.coe_voltage_24 = 3.3*11.0 / 4096.0;	    //24v供电电压
	coedata.coe_voltage_5 = 3.3*2.0 / 4096.0;	    //5V供电电压
	coedata.coe_voltage_bat = 0.001;       //电池电压
	coedata.coe_current_bat = 0.001;       //电池电流 
	coedata.coe_power = 0.001;             //电池功率	
	coedata.coe_power_consum = 0.1;        //电池已用电量   
	coedata.coe_time_energizing = 0.01;    //电池累计通电时间	
	coedata.coe_temp_sig = 0.0625;         //处理板温度
	coedata.coe_temp_interface = 0.0625;   //接口板温度  
	coedata.coe_circum_angle = 0.1;        //姿态周向角
	coedata.coe_dip_angle = 0.1;	         //姿态倾角	
	coedata.coe_accleration = 0.002;//0.0029;      //系统加速度
	coedata.coe_temp_pose = 1.0;//0.0625;	     //姿态检测分系统温度 
	coedata.coe_raw_angle = 0.1;           //姿态航向角

	coedata.coe_deform = 5.0 / 4096.0;       //变形
}




void transferbx_32::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j, p, q;
	double data_array[1000], temp[72];
	int index[72] = { 1,3,5,7,9,11,13,15,17,19,21,23,25,27,29,31,33,35,72,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,
				   37,39,41,43,45,47,49,51,53,55,57,59,61,63,65,67,69,71,36,38,40,42,44,46,48,50,52,54,56,58,60,62,64,66,68,70 };

	//数据转换为十进制，并写入一帧   
	/**************************************第一部分解析**************************************************/
	data_array[0] = uchar_uint32(&Data[4], LSB_FIRST);	                                        //优选里程脉冲

	data_array[1] = (Data[13] * 0x10000000000 + Data[12] * 0x100000000
		+ Data[11] * 0x1000000 + (Data[10] * 0x10000) + (Data[9] * 0x100) + Data[8]) & 0xffffffffffff;  //时钟脉冲计数 

	data_array[2] = uchar_uint16(&Data[14], LSB_FIRST) * coedata.coe_voltage_24; 	                //24v供电电压
	n = 3;
	/**************************************变形数据**************************************************/
	p = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 18; j++)
		{
			q = index[p++] - 1;
			temp[q] = data_change_uint(uchar_uint16(&Data[40 + i * 37 + j * 2], LSB_FIRST))*coedata.coe_deform;
		}
	}

	for (i = 0; i < 72; i++)
	{
		data_array[n++] = temp[i];
	}

	data_array[n++] = (short int)(uchar_uint16(&Data[188], LSB_FIRST))*coedata.coe_temp_sig;   	     //信号处理板温度
	data_array[n++] = (short int)(uchar_uint16(&Data[190], LSB_FIRST))*coedata.coe_temp_interface;	 //接口板温度	
	data_array[n++] = (short int)(uchar_uint16(&Data[204], LSB_FIRST))*coedata.coe_temp_pose;        //姿态温度 
	//***********************************其他数据***************************************//

	data_array[n++] = (uchar_uint16(&Data[192], LSB_FIRST)) * coedata.coe_circum_angle;            //周向角 
	data_array[n++] = (short int)(uchar_int16(&Data[194], LSB_FIRST))*coedata.coe_dip_angle;     //倾角
	data_array[n++] = (short int)(uchar_int16(&Data[196], LSB_FIRST))*coedata.coe_raw_angle;     //航向角
	data_array[n++] = (short int)(uchar_int16(&Data[198], LSB_FIRST))*coedata.coe_accleration;   //X轴加速度
	data_array[n++] = (short int)(uchar_int16(&Data[200], LSB_FIRST))*coedata.coe_accleration;   //Y轴加速度
	data_array[n++] = (short int)(uchar_int16(&Data[202], LSB_FIRST))*coedata.coe_accleration;   //Z轴加速度																				  //接口板温度
	data_array[n++] = uchar_uint32(&Data[217], LSB_FIRST);                                        //第一路原始里程
	data_array[n++] = uchar_uint32(&Data[217 + 4], LSB_FIRST);                                      //第二路原始里程  
	data_array[n++] = uchar_uint32(&Data[217 + 8], LSB_FIRST);                                      //第三路原始里程 

	//增加采集状态标志20191230
	data_array[n++] = Data[215];       //采集状态标志
	fwrite(data_array, sizeof(double), n, fp);
}

void transferbx_32::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
