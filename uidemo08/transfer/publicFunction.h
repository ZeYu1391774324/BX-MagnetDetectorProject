#pragma once
#include <stdint.h>
#define LSB_FIRST 0
#define MSB_FIRST 1

typedef struct CoeDataStruct
{
	double coe_voltage_24;	    //24v�����ѹ
	double coe_current_24;       //24V�������
	double coe_voltage_bat;     //��ص�ѹ
	double coe_current_bat;     //��ص��� 
	double coe_voltage_5;	    //5V�����ѹ
	double coe_current_5;       //5V�������
	double coe_voltage_33;	    //3.3V�����ѹ 
	double coe_current_33;       //3.3V�������
	double coe_voltage_back;	    //���ù����ѹ
	double coe_time_energizing;   //����ۼ�ͨ��ʱ��
	double coe_power_consum;      //���õ���
	double coe_power_rated;       //���������
	double coe_temp_obient;      //�����¶� 
	double coe_temp_obient_b;
	double coe_temp_sig;        //������¶�
	double coe_temp_interface;   //�ӿڰ��¶�
	double coe_temp_pose;	   //��̬��ϵͳ�¶�
	double coe_temp_sensor;
	double coe_temp_sensor_b;
	double coe_division;
	double coe_axialdata;
	double coe_radialdata;
	double coe_circumdata;
	double coe_deform;
	double coe_circum_angle;   //��̬�����
	double coe_dip_angle;	  //��̬���
	double coe_raw_angle;
	double coe_accleration;  //ϵͳ���ٶ�
	double coe_power;        //��ع���
}coedata_t;

typedef struct ChannelNumStruct
{
	unsigned int mfl;	             //©��ͨ����
	unsigned int deform;	             //����ͨ���� 
	unsigned int bak;				 //����ͨ����
	unsigned int all;                 //��ͨ����
	unsigned int motorbyte;				 //��̬Ԥ���ֽ���
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
//3�ֽ�ת��Ϊ32λ�޷�������    
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
//4�ֽ�ת��Ϊ32λ�޷�������    
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
//4�ֽ�ת��Ϊ48λ�޷�������    
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
//2�ֽ�ת��Ϊ16λ�з�������    
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
//3�ֽ�ת��Ϊ32λ�޷�������    
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
//4�ֽ�ת��Ϊ32λ�޷�������    
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

