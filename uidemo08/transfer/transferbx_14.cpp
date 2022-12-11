
#include "transferbx_14.h"

void transferbx_14::initParameter()
{
	FrameLen = 192 + 4; 	              //单帧数据长度（字节）（本地）	  
	channelnum.mfl = 0;		          //漏磁通道数
	channelnum.deform = 0;		      //变形通道数
	channelnum.bak = 0;			      //备用通道数 
	channelnum.all = 0;				  //总通道数     
	channelnum.motorbyte = 11;	      //姿态预留字节数  

	coedata.coe_voltage_24 = 0.001;	    //24v供电电压
	coedata.coe_current_24 = 0.001;       //24V供电电流
	coedata.coe_power_consum = 0.1;       //电池组已用电量  
	coedata.coe_time_energizing = 0.01;   //电池累计通电时间 
	coedata.coe_power_rated = 0.1;        //电池组额定电量   
	coedata.coe_temp_obient = -0.23;      //环境温度 
	coedata.coe_temp_obient_b = 193.23;
	coedata.coe_voltage_5 = 0.0078;	    //5V供电电压
	coedata.coe_voltage_33 = 0.0036;	    //3.3V供电电压 
	coedata.coe_voltage_back = 0.0275;	//备用供电电压  

	coedata.coe_temp_sig = 0.0625;        //处理板温度

	coedata.coe_circum_angle = 0.1;       //姿态周向角
	coedata.coe_dip_angle = 0.1;	        //姿态倾角
	coedata.coe_accleration = 0.002;//0.0029;     //系统加速度
	coedata.coe_temp_pose = 1.0;//0.0625;	    //姿态分系统温度    
	coedata.coe_raw_angle = 0.1;          //姿态航向角

	coedata.coe_deform = 5.0 / 4096.0;    //变形
}

void transferbx_14::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000];
	unsigned char Data_temp[80];

	int cnt = FrameLen;
	//
	unsigned char data_test[196], data_low[196], data_high[196], data_1, data_2, data_3, data_4;

	for (i = 0; i < cnt; i++)	  //每字节bit0 bit7交换顺序
	{
		data_low[i] = Data[i] & 0x01; //取出bit0
		data_high[i] = (Data[i] >> 7) & 0x01;//取出bit7

		data_test[i] = ((Data[i] & 0x7E) | data_high[i] | (data_low[i] << 7)) & 0xff;
	}

	for (j = 0; j < cnt / 4; j++)
	{
		data_1 = data_test[4 * j + 0];
		data_2 = data_test[4 * j + 1];
		data_3 = data_test[4 * j + 2];
		data_4 = data_test[4 * j + 3];

		Data[4 * j + 0] = data_2;
		Data[4 * j + 1] = data_4;
		Data[4 * j + 2] = data_1;
		Data[4 * j + 3] = data_3;
	}
	////////////以上为数据加密解析

	//数据转换为十进制，并写入一帧   
	/**************************************第一部分解析**************************************************/
	data_array[0] = uchar_uint32(&Data[4], LSB_FIRST);	                                        //优选里程脉冲

	data_array[1] = (Data[13] * 0x10000000000 + Data[12] * 0x100000000
		+ Data[11] * 0x1000000 + (Data[10] * 0x10000) + (Data[9] * 0x100) + Data[8]) & 0xffffffffffff;  //时钟脉冲计数 

	data_array[2] = uchar_uint16(&Data[14], LSB_FIRST)*coedata.coe_voltage_24; 	                //24v供电电压
	n = 3;
	/**************************************变形数据**************************************************/
	//变形数据（graph1~graph3）
	   //根据协议重新分配 
	for (j = 0; j < 20; j++)
	{
		Data_temp[j] = Data[40 + j];	 //第1~10路有效数据，取传感器1~10号数据
	}
	for (j = 0; j < 12; j++)
	{
		Data_temp[j + 20] = Data[40 + 24 + j];  //第11~16路有效数据，取传感器13~18号数据
	}
	for (j = 0; j < 8; j++)
	{
		Data_temp[j + 32] = Data[40 + 37 + j];  //第17~20路有效数据，取传感器19~22号数据
	}
	for (j = 0; j < 20; j++)
	{
		Data_temp[j + 40] = Data[40 + 49 + j];  //第21~30路有效数据，取传感器25~34号数据
	}
	for (j = 0; j < 20; j++)
	{
		Data_temp[j + 60] = Data[40 + 74 + j];  //第31~40路有效数据，取传感器37~46号数据
	}

	for (i = 0; i < 40; i++)
	{
		data_array[n++] = data_change_uint(uchar_uint16(&Data_temp[i * 2], LSB_FIRST))*coedata.coe_deform;
	}

	data_array[n++] = (short int)(uchar_int16(&Data[151], LSB_FIRST))*coedata.coe_temp_sig;   	  //信号处理板温度
	data_array[n++] = uchar_uint16(&Data[30], LSB_FIRST)*coedata.coe_temp_obient + coedata.coe_temp_obient_b;//电源模块环境温度
	data_array[n++] = (short int)(uchar_int16(&Data[165], LSB_FIRST))*coedata.coe_temp_pose;     //姿态温度
	//***********************************其他数据***************************************//

	data_array[n++] = (uchar_uint16(&Data[153], LSB_FIRST))*coedata.coe_circum_angle;            //周向角 
	data_array[n++] = (short int)(uchar_int16(&Data[155], LSB_FIRST))*coedata.coe_dip_angle;     //倾角
	data_array[n++] = (short int)(uchar_int16(&Data[157], LSB_FIRST))*coedata.coe_raw_angle;     //航向角
	data_array[n++] = (short int)(uchar_int16(&Data[159], LSB_FIRST))*coedata.coe_accleration;   //X轴加速度
	data_array[n++] = (short int)(uchar_int16(&Data[161], LSB_FIRST))*coedata.coe_accleration;   //Y轴加速度
	data_array[n++] = (short int)(uchar_int16(&Data[163], LSB_FIRST))*coedata.coe_accleration;   //Z轴加速度
	//data_array[n++]=(short int)(uchar_int16(&Data[154],LSB_FIRST))*coedata.coe_temp_pose;     //姿态温度
	//data_array[n++]=(short int)(uchar_int16(&Data[140],LSB_FIRST))*coedata.coe_temp_sig;   	  //信号处理板温度

	data_array[n++] = uchar_uint32(&Data[178 + 2], LSB_FIRST);      //第一路原始里程
	data_array[n++] = uchar_uint32(&Data[178 + 4 + 2], LSB_FIRST);    //第二路原始里程  
	data_array[n++] = uchar_uint32(&Data[178 + 8 + 2], LSB_FIRST);    //第三路原始里程  

	//增加采集状态标志20191230
	data_array[n++] = Data[176];       //采集状态标志
	fwrite(data_array, sizeof(double), n, fp);
}

void transferbx_14::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
