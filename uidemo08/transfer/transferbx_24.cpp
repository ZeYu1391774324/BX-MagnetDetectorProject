
#include "transferbx_24.h"

void transferbx_24::initParameter()
{
	FrameLen = 228 + 4; 	              //单帧数据长度（字节）（本地）
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
	coedata.coe_circum_angle = 0.01;        //姿态周向角
	coedata.coe_dip_angle = 0.01;	         //姿态倾角	
	coedata.coe_accleration = 0.002;//0.0029;      //系统加速度
	coedata.coe_temp_pose = 1.0;//0.0625;	     //姿态检测分系统温度 
	coedata.coe_raw_angle = 0.01;           //姿态航向角

	coedata.coe_deform = 5.0 / 4096.0;       //变形 
}

void transferbx_24::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000] = { 0 };
	int cnt = FrameLen;
	//
	unsigned char data_test[232], data_low[232], data_high[232], data_1, data_2, data_3, data_4;

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
	for (j = 0; j < 16; j++)
	{
		data_array[n++] = data_change_uint(uchar_uint16(&Data[39 + 2 * DEFORMBLOCK + j * 2], LSB_FIRST))*coedata.coe_deform;
	}
	for (j = 0; j < 16; j++)
	{
		data_array[n++] = data_change_uint(uchar_uint16(&Data[39 + 3 * DEFORMBLOCK + j * 2], LSB_FIRST))*coedata.coe_deform;
	}
	for (j = 0; j < 16; j++)
	{
		data_array[n++] = data_change_uint(uchar_uint16(&Data[39 + 0 * DEFORMBLOCK + j * 2], LSB_FIRST))*coedata.coe_deform;
	}
	for (j = 0; j < 16; j++)
	{
		data_array[n++] = data_change_uint(uchar_uint16(&Data[39 + 1 * DEFORMBLOCK + j * 2], LSB_FIRST))*coedata.coe_deform;
	}

	data_array[n++] = (short int)(uchar_int16(&Data[187], LSB_FIRST))*coedata.coe_temp_sig;   	     //信号处理板温度
	data_array[n++] = (short int)(uchar_int16(&Data[189], LSB_FIRST))*coedata.coe_temp_interface;	 //接口板温度	
	data_array[n++] = (short int)(uchar_int16(&Data[203], LSB_FIRST))*coedata.coe_temp_pose;        //姿态温度	
	//***********************************其他数据***************************************//
	//轨迹测绘
	data_array[n++] = (short int)(uchar_int16(&Data[207], LSB_FIRST))*coedata.coe_circum_angle;  //周向角 
	data_array[n++] = (short int)(uchar_int16(&Data[205], LSB_FIRST))*coedata.coe_dip_angle;     //倾角
	data_array[n++] = (short int)(uchar_int16(&Data[209], LSB_FIRST))*coedata.coe_raw_angle;     //航向角

	data_array[n++] = (short int)(uchar_int16(&Data[197], LSB_FIRST))*coedata.coe_accleration;   //X轴加速度
	data_array[n++] = (short int)(uchar_int16(&Data[199], LSB_FIRST))*coedata.coe_accleration;   //Y轴加速度
	data_array[n++] = (short int)(uchar_int16(&Data[201], LSB_FIRST))*coedata.coe_accleration;   //Z轴加速度
																				  //接口板温度
	data_array[n++] = uchar_uint32(&Data[216], LSB_FIRST);                                        //第一路原始里程
	data_array[n++] = uchar_uint32(&Data[216 + 4], LSB_FIRST);                                      //第二路原始里程  
	data_array[n++] = uchar_uint32(&Data[216 + 8], LSB_FIRST);                                      //第三路原始里程  

	//增加采集状态标志20191230
	data_array[n++] = Data[214];       //采集状态标志


	fwrite(data_array, sizeof(double), n, fp);
}

void transferbx_24::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
