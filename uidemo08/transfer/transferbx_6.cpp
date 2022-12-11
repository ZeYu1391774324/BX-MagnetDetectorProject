
#include "transferbx_6.h"


void transferbx_6::initParameter()
{
	//新协议20201202
	FrameLen = 225; //单帧数据长度（字节）（本地）	  
	channelnum.mfl = 0;		          //漏磁通道数
	channelnum.deform = 3;		      //变形通道数
	channelnum.bak = 0;			      //备用通道数 
	channelnum.all = 0;				  //总通道数     
	channelnum.motorbyte = 11;	      //姿态预留字节数  

	coedata.coe_voltage_24 = 0.001; // 24v供电电压
	coedata.coe_current_24 = 0.001; // 24V供电电流

	coedata.coe_voltage_5 = 0.001; // 5V供电电压
	coedata.coe_current_5 = 0.001; // 5V供电电流

	coedata.coe_voltage_33 = 0.001; // 3.3V供电电压
	coedata.coe_current_33 = 0.001; // 3.3V供电电流 
	coedata.coe_temp_sig = 0.0625; // 信号处理板温度
	coedata.coe_circum_angle = 0.1; // 姿态周向角
	coedata.coe_dip_angle = 0.1; // 姿态倾角
	coedata.coe_raw_angle = 0.1; //姿态航向角 

	coedata.coe_accleration = 0.002; // 系统加速度(X轴、Y轴、Z轴)
	coedata.coe_temp_pose = 1.0; // 姿态分系统温度
	coedata.coe_power_consum = 0.1;       //电池组已用电量  
	coedata.coe_time_energizing = 0.01;   //电池累计通电时间 
	coedata.coe_power_rated = 0.1;        //电池组额定电量   
	coedata.coe_temp_obient = -0.23;      //环境温度 
	coedata.coe_temp_obient_b = 193.23;
	coedata.coe_voltage_back = 0.0275;	// 备用供电电压  
	coedata.coe_deform = 5.0 / 4096.0;    //变形
}

void transferbx_6::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000];
	double bx_data[24]; // 六寸变形通道有24个

	int head;

	// 帧头帧尾判断
	head = uchar_uint16(&Data[0], MSB_FIRST);

	/* 数据转换为十进制，并写入一帧 */

	// 优选里程脉冲计数
	data_array[0] = uchar_uint32(&Data[6], LSB_FIRST);

	// 时钟脉冲计数
	data_array[1] = (Data[15] * 0x10000000000
		+ Data[14] * 0x100000000
		+ Data[13] * 0x1000000
		+ Data[12] * 0x10000
		+ Data[11] * 0x100
		+ Data[10]) & 0xffffffffffff;

	// 24V系统供电电压
	data_array[2] = (unsigned short)uchar_int16(&Data[16], LSB_FIRST) * coedata.coe_voltage_24;

	n = 3;

	int nPreBxByte = 40; // 变形数据之前字节总数
	int nBxDataByte = 37; // 每通道变形数据字节数（18*2+1  1:校验和 18:每通道18路 2:每路2字节）
	int bxIndex = 0;
	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 18; i++)
		{
			// 6寸变形数据 3通道，每通道18路，每路2字节         
			/*data_array[n++] = data_change_uint(uchar_int16(&Data[nPreBxByte + j*nBxDataByte + i * 2],LSB_FIRST))
							  *coedata.coe_deform;*/
			bx_data[bxIndex++] = data_change_uint(uchar_int16(&Data[nPreBxByte + j * nBxDataByte + i * 2], LSB_FIRST))
				*coedata.coe_deform;   // 先将24路变形数据按接收到的自然顺序解析到临时数组里

			if (j == 1 && i == 5)
			{
				break;  // 总共只需要24通道数据
			}
		}

		if (j == 1 && i == 5)
		{
			break;
		}
	}

	// 按照实际安装位置存放变形数据
	int indexTable[24] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23,
						   2, 4, 6, 8, 10,12, 14, 16, 18, 20, 22, 24 };

	for (int i = 0; i < 24; ++i)
	{
		double bx_value = bx_data[i];
		int real_index = indexTable[i] - 1;
		data_array[n + real_index] = bx_value;
	}
	n += 24;

	// 信号处理板温度1
	int nPreSigTemp1Byte = nPreBxByte + DEFORMBLOCK * channelnum.deform;
	data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreSigTemp1Byte],
		LSB_FIRST))*coedata.coe_temp_sig;
	// 信号处理板温度2
	data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreSigTemp1Byte + 2],
		LSB_FIRST))*coedata.coe_temp_sig;

	// 姿态分系统温度
	int nPrePoseTempByte = nPreSigTemp1Byte + 16;
	if ((Data[nPrePoseTempByte + 1] & 0x80) == 0)
	{
		data_array[n++] = ((unsigned short)uchar_int16(&Data[nPrePoseTempByte],
			LSB_FIRST))*coedata.coe_temp_pose;
	}
	else
	{
		data_array[n++] = ((unsigned short)uchar_int16(&Data[nPrePoseTempByte],
			LSB_FIRST) - 65536)*coedata.coe_temp_pose;
	}

		// 姿态周向角
		int nPreCircumByte = nPreSigTemp1Byte + 4;
		data_array[n++] = ((unsigned short)uchar_uint16(&Data[nPreCircumByte], LSB_FIRST))
			*coedata.coe_circum_angle;

		// 姿态倾角数据
		int nPreDipByte = nPreCircumByte + 2;
		if ((Data[nPreDipByte + 1] & 0x80) == 0)
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreDipByte], LSB_FIRST))
				*coedata.coe_dip_angle;
		}
		else
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreDipByte], LSB_FIRST) - 65536)
				*coedata.coe_dip_angle;
		}

		// 姿态航向角数据
		int nPreRawAngleByte = nPreDipByte + 2;
		if ((Data[nPreRawAngleByte + 1] & 0x80) == 0)
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreRawAngleByte], LSB_FIRST))
				*coedata.coe_raw_angle;
		}
		else
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreRawAngleByte], LSB_FIRST) - 65536)
				*coedata.coe_raw_angle;
		}

		// X轴向加速度
		int nPreXAccelByte = nPreRawAngleByte + 2;
		if ((Data[nPreXAccelByte + 1] & 0x80) == 0)
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreXAccelByte], LSB_FIRST))
				*coedata.coe_accleration;
		}
		else
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreXAccelByte], LSB_FIRST) - 65536)
				*coedata.coe_accleration;
		}

		// Y轴向加速度
		int nPreYAccelByte = nPreXAccelByte + 2;
		if ((Data[nPreYAccelByte + 1] & 0x80) == 0)
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreYAccelByte], LSB_FIRST))
				*coedata.coe_accleration;
		}
		else
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreYAccelByte], LSB_FIRST) - 65536)
				*coedata.coe_accleration;
		}

		// Z轴向加速度
		int nPreZAccelByte = nPreYAccelByte + 2;
		if ((Data[nPreZAccelByte + 1] & 0x80) == 0)
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreZAccelByte], LSB_FIRST))
				*coedata.coe_accleration;
		}
		else
		{
			data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreZAccelByte], LSB_FIRST) - 65536)
				*coedata.coe_accleration;
		}

		// 第1路原始里程
		int nPreFirstMileByte = nPreSigTemp1Byte + 29;
		data_array[n++] = uchar_uint32(&Data[nPreFirstMileByte], LSB_FIRST);

		// 第2路原始里程
		data_array[n++] = uchar_uint32(&Data[nPreFirstMileByte + 12], LSB_FIRST);

		// 第3路原始里程 
		data_array[n++] = uchar_uint32(&Data[nPreFirstMileByte + 24], LSB_FIRST);

		// 采集状态标志
		int nPreFlagByte = nPreZAccelByte + 13;
		data_array[n++] = Data[nPreFlagByte];
	
		fwrite(data_array, sizeof(double), n, fp);

}

void transferbx_6::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{

}
