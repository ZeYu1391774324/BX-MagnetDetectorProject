#pragma once
#include <stdint.h>
#define LSB_FIRST 0
#define MSB_FIRST 1

typedef struct CoeDataStruct
{
	double coe_voltage_24;	    //24v供电电压
	double coe_current_24;       //24V供电电流
	double coe_voltage_bat;     //电池电压
	double coe_current_bat;     //电池电流 
	double coe_voltage_5;	    //5V供电电压
	double coe_current_5;       //5V供电电流
	double coe_voltage_33;	    //3.3V供电电压 
	double coe_current_33;       //3.3V供电电流
	double coe_voltage_back;	    //备用供电电压
	double coe_time_energizing;   //电池累计通电时间
	double coe_power_consum;      //已用电量
	double coe_power_rated;       //电池组额定电量
	double coe_temp_obient;      //环境温度 
	double coe_temp_obient_b;
	double coe_temp_sig;        //处理板温度
	double coe_temp_interface;   //接口板温度
	double coe_temp_pose;	   //姿态分系统温度
	double coe_temp_sensor;
	double coe_temp_sensor_b;
	double coe_division;
	double coe_axialdata;
	double coe_radialdata;
	double coe_circumdata;
	double coe_deform;
	double coe_circum_angle;   //姿态周向角
	double coe_dip_angle;	  //姿态倾角
	double coe_raw_angle;
	double coe_accleration;  //系统加速度
	double coe_power;        //电池功率
}coedata_t;

typedef struct ChannelNumStruct
{
	unsigned int mfl;	             //漏磁通道数
	unsigned int deform;	             //变形通道数 
	unsigned int bak;				 //备用通道数
	unsigned int all;                 //总通道数
	unsigned int motorbyte;				 //姿态预留字节数
} channelnum_t;


static uint16_t uchar_uint16(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		return (uint16_t)(buf[0] << 8 | buf[1]);
	}
	else
	{
		return (uint16_t)(buf[1] << 8 | buf[0]);
	}
}
//3字节转换为32位无符号整型    
static uint32_t uchar_uint24(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		return (buf[0] << 16 | buf[1] << 8 | buf[2]);

	}
	else
	{
		return (buf[2] << 16 | buf[1] << 8 | buf[0]);
	}
}
//4字节转换为32位无符号整型    
static uint32_t uchar_uint32(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		return (buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3]);
	}
	else
	{
		return (buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]);
	}
}
//4字节转换为48位无符号整型    
static long long uchar_uint48(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		return (((buf[0] << 40) & 0xff) | ((buf[1] << 32) & 0xff) | ((buf[2] << 24) & 0xff) | ((buf[3] << 16) & 0xff) | ((buf[4] << 8) & 0xff) | (buf[5] & 0xff));
	}
	else
	{
		return (buf[5] << 40 | buf[4] << 32 | buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]);
	}
}
//2字节转换为16位有符号整型    
static int16_t uchar_int16(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		if (buf[0] & 0x80)
		{
			return (uint16_t)(buf[0] << 8 | buf[1]);
		}
		else
		{
			return (uint16_t)(buf[0] << 8 | buf[1]);
		}
	}
	else
	{
		if (buf[1] & 0x80)
		{
			return 	(uint16_t)(buf[1] << 8 | buf[0]);
		}
		else
		{
			return (uint16_t)(buf[1] << 8 | buf[0]);
		}
	}
}
//3字节转换为32位无符号整型    
static int32_t uchar_int24(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		if (buf[0] & 0x80)
		{
			return (buf[0] << 16 | buf[1] << 8 | buf[2]) - (1 << 24);
		}
		else
		{
			return (buf[0] << 16 | buf[1] << 8 | buf[2]);
		}
	}
	else
	{
		if (buf[1] & 0x80)
		{
			return 	(buf[2] << 16 | buf[1] << 8 | buf[0]) - (1 << 24);
		}
		else
		{
			return (buf[2] << 16 | buf[1] << 8 | buf[0]);
		}
	}
}
//4字节转换为32位无符号整型    
static int32_t uchar_int32(uint8_t *buf, uint8_t dir)
{
	if (dir == MSB_FIRST)
	{
		if (buf[0] & 0x80)
		{
			return (buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3]);
		}
		else
		{
			return (buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3]);
		}
	}
	else
	{
		if (buf[3] & 0x80)
		{
			return 	(buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]);
		}
		else
		{
			return (buf[3] << 24 | buf[2] << 16 | buf[1] << 8 | buf[0]);
		}
	}
}

static int16_t data_change(uint16_t data)
{
	uint16_t temp;
	temp = data & 0x0fff;
	if ((temp & 0x0800) == 0)
	{
		return (int16_t)temp;
	}
	else
	{
		temp = 0xf000 | temp;
		return (int16_t)temp;
	}
}


static int16_t data_change_temp(uint16_t data)
{
	uint16_t temp;
	temp = data & 0x0fff;
	if ((temp & 0x0800) == 0)
	{
		temp = temp | 0xf800;
		return (int16_t)(temp | 0xf800);
	}
	else
	{
		temp = temp & 0x07ff;
		return (int16_t)temp;
	}
}

static uint16_t data_change_uint(uint16_t data)
{
	uint16_t temp;
	temp = data & 0x0fff;
	if ((temp & 0x0800) == 0)
	{
		return (uint16_t)temp;
	}
	else
	{
		return (uint16_t)temp;
	}
}

