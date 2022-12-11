
#include "transferbx_12.h"
void transferbx_12::initParameter()
{
	FrameLen = 354;
	channelnum.mfl = 0;
	channelnum.deform = 4;
	channelnum.bak = 1;
	channelnum.all = 5;
	channelnum.motorbyte = 0;

	coedata.coe_voltage_24 = 3.3*11.032 / 4096.0;	    //24v供电电压
	coedata.coe_temp_obient = -0.23;      //环境温度 
	coedata.coe_temp_obient_b = 193.23;

	coedata.coe_temp_sig = 0.0625;        //处理板温度  
	coedata.coe_temp_interface = 0.0625;   //接口板温度   
	coedata.coe_temp_pose = 1.0;//0.0625;	    //姿态分系统温度
	coedata.coe_circum_angle = 0.1;   //姿态周向角
	coedata.coe_dip_angle = 0.1;	  //姿态倾角
	coedata.coe_raw_angle = 0.1;     //姿态航向角
	coedata.coe_deform = 5.0 / 4096.0;    //变形 
	coedata.coe_accleration = 0.002;//0.0029;     //系统加速度
}

void transferbx_12::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	//double data_array[1000];
	int err_flag = 0;
	int address = 0;
	double g_data_array[1000] = { 0 };//存放上一帧变形数据
	int g_err_cnt = 0;
	//int address_test[1200];
	int index_test = 0;
	//数据转换为十进制，并写入一帧   
	/**************************************第一部分解析**************************************************/
	g_data_array[0] = Data[5] * 0x1000000 + Data[4] * 0x10000 + Data[7] * 0x100 + Data[6];	                                        //优选里程脉冲
	g_data_array[1] = Data[9] * 0x10000000000 + Data[8] * 0x100000000
		+ Data[11] * 0x1000000 + (Data[10] * 0x10000) + (Data[13] * 0x100) + Data[12];  //时钟脉冲计数 
	g_data_array[2] = uchar_uint16(&Data[14], LSB_FIRST) * coedata.coe_voltage_24;

	//n=3; 
   /**************************************变形数据**************************************************/
   //判断前12路数据地址是否正确
	for (i = 0; i < 12; i++)
	{
		address = (uchar_uint16(&Data[16 + i * 2], LSB_FIRST)) >> 12;//取地址
		if (address != i)
		{
			err_flag = 1; //地址异常
			break;
		}
	}

	if (err_flag == 1)
	{
		g_err_cnt++;
		if (g_err_cnt == 2)
		{
			g_err_cnt = 0;
		}
		else
		{
			if (index_test == 0)   //第一帧数据不变
			{
				for (j = 0; j < 24; j++)
				{
					g_data_array[j + 3] = data_change_uint(uchar_uint16(&Data[16 + j * 2], LSB_FIRST))*coedata.coe_deform;
				}
				for (j = 0; j < 16; j++)
				{
					g_data_array[j + 27] = data_change_uint(uchar_uint16(&Data[88 + j * 2], LSB_FIRST))*coedata.coe_deform;
				}
				index_test = 1;
			}
			else
			{
				for (i = 0; i < 40; i++); //保持上帧数据
				{
					g_data_array[i + 3] = g_data_array[i + 3];
				}
			}
		}
	}
	else
	{
		g_err_cnt = 0;//连续异常标志清零
		for (j = 0; j < 24; j++)
		{
			g_data_array[j + 3] = data_change_uint(uchar_uint16(&Data[16 + j * 2], LSB_FIRST))*coedata.coe_deform;
		}
		for (j = 0; j < 16; j++)
		{
			g_data_array[j + 27] = data_change_uint(uchar_uint16(&Data[88 + j * 2], LSB_FIRST))*coedata.coe_deform;
		}
	}

	g_data_array[43] = data_change(uchar_uint16(&Data[308], LSB_FIRST))*coedata.coe_temp_sig; 	             //处理板温度
	g_data_array[44] = data_change(uchar_uint16(&Data[310], LSB_FIRST))*coedata.coe_temp_interface;		   //接口板温度
	g_data_array[45] = data_change(uchar_int16(&Data[322], LSB_FIRST));//*coedata.coe_temp_pose;                //姿态温度     

	//transfer_mode=DEBUG_MODE;  //默认对内模式，20200408
	g_data_array[46] = (short int)(uchar_uint16(&Data[312], LSB_FIRST))*coedata.coe_circum_angle; //周向角 
	g_data_array[47] = (short int)(uchar_int16(&Data[314], LSB_FIRST))*coedata.coe_dip_angle;     //倾角
	g_data_array[48] = (short int)(uchar_int16(&Data[324], MSB_FIRST))*coedata.coe_raw_angle;     //航向角
	g_data_array[49] = (short int)(uchar_int16(&Data[316], LSB_FIRST))*coedata.coe_accleration;   //X轴加速度
	g_data_array[50] = (short int)(uchar_int16(&Data[318], LSB_FIRST))*coedata.coe_accleration;   //Y轴加速度
	g_data_array[51] = (short int)(uchar_int16(&Data[320], LSB_FIRST))*coedata.coe_accleration;   //Z轴加速度
	g_data_array[52] = Data[339] * 0x1000000 + Data[338] * 0x10000 + Data[341] * 0x100 + Data[340];    //第一路原始里程
	g_data_array[53] = Data[343] * 0x1000000 + Data[342] * 0x10000 + Data[345] * 0x100 + Data[344];    //第二路原始里程  
	g_data_array[54] = Data[347] * 0x1000000 + Data[346] * 0x10000 + Data[349] * 0x100 + Data[348];    //第三路原始里程  

	//增加采集状态标志20200326
	g_data_array[55] = Data[334];       //采集状态标志

	n = 56;

	fwrite(g_data_array, sizeof(double), n, fp);
}

void transferbx_12::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000];
	unsigned char Data_temp[80];
	double data_yx;
	int cnt = FrameLen;
	//
	unsigned char data_test[354], data_low[354], data_high[354], data_1, data_2, data_3, data_4;

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


	//前5帧数据直接转存入文件夹dire1
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
	//transfer_mode = DEBUG_MODE;
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
		data_yx = uchar_uint32(&Data[167], LSB_FIRST);	    //时间采集模式优选里程                                 
		fwrite(data_array, sizeof(double), n, fp);
	}
