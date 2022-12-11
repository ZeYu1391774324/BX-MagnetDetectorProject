
#include "transferbx_6.h"


void transferbx_6::initParameter()
{
	//��Э��20201202
	FrameLen = 225; //��֡���ݳ��ȣ��ֽڣ������أ�	  
	channelnum.mfl = 0;		          //©��ͨ����
	channelnum.deform = 3;		      //����ͨ����
	channelnum.bak = 0;			      //����ͨ���� 
	channelnum.all = 0;				  //��ͨ����     
	channelnum.motorbyte = 11;	      //��̬Ԥ���ֽ���  

	coedata.coe_voltage_24 = 0.001; // 24v�����ѹ
	coedata.coe_current_24 = 0.001; // 24V�������

	coedata.coe_voltage_5 = 0.001; // 5V�����ѹ
	coedata.coe_current_5 = 0.001; // 5V�������

	coedata.coe_voltage_33 = 0.001; // 3.3V�����ѹ
	coedata.coe_current_33 = 0.001; // 3.3V������� 
	coedata.coe_temp_sig = 0.0625; // �źŴ�����¶�
	coedata.coe_circum_angle = 0.1; // ��̬�����
	coedata.coe_dip_angle = 0.1; // ��̬���
	coedata.coe_raw_angle = 0.1; //��̬����� 

	coedata.coe_accleration = 0.002; // ϵͳ���ٶ�(X�ᡢY�ᡢZ��)
	coedata.coe_temp_pose = 1.0; // ��̬��ϵͳ�¶�
	coedata.coe_power_consum = 0.1;       //��������õ���  
	coedata.coe_time_energizing = 0.01;   //����ۼ�ͨ��ʱ�� 
	coedata.coe_power_rated = 0.1;        //���������   
	coedata.coe_temp_obient = -0.23;      //�����¶� 
	coedata.coe_temp_obient_b = 193.23;
	coedata.coe_voltage_back = 0.0275;	// ���ù����ѹ  
	coedata.coe_deform = 5.0 / 4096.0;    //����
}

void transferbx_6::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000];
	double bx_data[24]; // �������ͨ����24��

	int head;

	// ֡ͷ֡β�ж�
	head = uchar_uint16(&Data[0], MSB_FIRST);

	/* ����ת��Ϊʮ���ƣ���д��һ֡ */

	// ��ѡ����������
	data_array[0] = uchar_uint32(&Data[6], LSB_FIRST);

	// ʱ���������
	data_array[1] = (Data[15] * 0x10000000000
		+ Data[14] * 0x100000000
		+ Data[13] * 0x1000000
		+ Data[12] * 0x10000
		+ Data[11] * 0x100
		+ Data[10]) & 0xffffffffffff;

	// 24Vϵͳ�����ѹ
	data_array[2] = (unsigned short)uchar_int16(&Data[16], LSB_FIRST) * coedata.coe_voltage_24;

	n = 3;

	int nPreBxByte = 40; // ��������֮ǰ�ֽ�����
	int nBxDataByte = 37; // ÿͨ�����������ֽ�����18*2+1  1:У��� 18:ÿͨ��18· 2:ÿ·2�ֽڣ�
	int bxIndex = 0;
	for (j = 0; j < 3; j++)
	{
		for (i = 0; i < 18; i++)
		{
			// 6��������� 3ͨ����ÿͨ��18·��ÿ·2�ֽ�         
			/*data_array[n++] = data_change_uint(uchar_int16(&Data[nPreBxByte + j*nBxDataByte + i * 2],LSB_FIRST))
							  *coedata.coe_deform;*/
			bx_data[bxIndex++] = data_change_uint(uchar_int16(&Data[nPreBxByte + j * nBxDataByte + i * 2], LSB_FIRST))
				*coedata.coe_deform;   // �Ƚ�24·�������ݰ����յ�����Ȼ˳���������ʱ������

			if (j == 1 && i == 5)
			{
				break;  // �ܹ�ֻ��Ҫ24ͨ������
			}
		}

		if (j == 1 && i == 5)
		{
			break;
		}
	}

	// ����ʵ�ʰ�װλ�ô�ű�������
	int indexTable[24] = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23,
						   2, 4, 6, 8, 10,12, 14, 16, 18, 20, 22, 24 };

	for (int i = 0; i < 24; ++i)
	{
		double bx_value = bx_data[i];
		int real_index = indexTable[i] - 1;
		data_array[n + real_index] = bx_value;
	}
	n += 24;

	// �źŴ�����¶�1
	int nPreSigTemp1Byte = nPreBxByte + DEFORMBLOCK * channelnum.deform;
	data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreSigTemp1Byte],
		LSB_FIRST))*coedata.coe_temp_sig;
	// �źŴ�����¶�2
	data_array[n++] = ((unsigned short)uchar_int16(&Data[nPreSigTemp1Byte + 2],
		LSB_FIRST))*coedata.coe_temp_sig;

	// ��̬��ϵͳ�¶�
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

		// ��̬�����
		int nPreCircumByte = nPreSigTemp1Byte + 4;
		data_array[n++] = ((unsigned short)uchar_uint16(&Data[nPreCircumByte], LSB_FIRST))
			*coedata.coe_circum_angle;

		// ��̬�������
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

		// ��̬���������
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

		// X������ٶ�
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

		// Y������ٶ�
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

		// Z������ٶ�
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

		// ��1·ԭʼ���
		int nPreFirstMileByte = nPreSigTemp1Byte + 29;
		data_array[n++] = uchar_uint32(&Data[nPreFirstMileByte], LSB_FIRST);

		// ��2·ԭʼ���
		data_array[n++] = uchar_uint32(&Data[nPreFirstMileByte + 12], LSB_FIRST);

		// ��3·ԭʼ��� 
		data_array[n++] = uchar_uint32(&Data[nPreFirstMileByte + 24], LSB_FIRST);

		// �ɼ�״̬��־
		int nPreFlagByte = nPreZAccelByte + 13;
		data_array[n++] = Data[nPreFlagByte];
	
		fwrite(data_array, sizeof(double), n, fp);

}

void transferbx_6::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{

}
