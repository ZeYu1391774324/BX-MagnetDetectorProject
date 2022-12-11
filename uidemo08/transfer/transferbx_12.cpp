
#include "transferbx_12.h"
void transferbx_12::initParameter()
{
	FrameLen = 354;
	channelnum.mfl = 0;
	channelnum.deform = 4;
	channelnum.bak = 1;
	channelnum.all = 5;
	channelnum.motorbyte = 0;

	coedata.coe_voltage_24 = 3.3*11.032 / 4096.0;	    //24v�����ѹ
	coedata.coe_temp_obient = -0.23;      //�����¶� 
	coedata.coe_temp_obient_b = 193.23;

	coedata.coe_temp_sig = 0.0625;        //������¶�  
	coedata.coe_temp_interface = 0.0625;   //�ӿڰ��¶�   
	coedata.coe_temp_pose = 1.0;//0.0625;	    //��̬��ϵͳ�¶�
	coedata.coe_circum_angle = 0.1;   //��̬�����
	coedata.coe_dip_angle = 0.1;	  //��̬���
	coedata.coe_raw_angle = 0.1;     //��̬�����
	coedata.coe_deform = 5.0 / 4096.0;    //���� 
	coedata.coe_accleration = 0.002;//0.0029;     //ϵͳ���ٶ�
}

void transferbx_12::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	//double data_array[1000];
	int err_flag = 0;
	int address = 0;
	double g_data_array[1000] = { 0 };//�����һ֡��������
	int g_err_cnt = 0;
	//int address_test[1200];
	int index_test = 0;
	//����ת��Ϊʮ���ƣ���д��һ֡   
	/**************************************��һ���ֽ���**************************************************/
	g_data_array[0] = Data[5] * 0x1000000 + Data[4] * 0x10000 + Data[7] * 0x100 + Data[6];	                                        //��ѡ�������
	g_data_array[1] = Data[9] * 0x10000000000 + Data[8] * 0x100000000
		+ Data[11] * 0x1000000 + (Data[10] * 0x10000) + (Data[13] * 0x100) + Data[12];  //ʱ��������� 
	g_data_array[2] = uchar_uint16(&Data[14], LSB_FIRST) * coedata.coe_voltage_24;

	//n=3; 
   /**************************************��������**************************************************/
   //�ж�ǰ12·���ݵ�ַ�Ƿ���ȷ
	for (i = 0; i < 12; i++)
	{
		address = (uchar_uint16(&Data[16 + i * 2], LSB_FIRST)) >> 12;//ȡ��ַ
		if (address != i)
		{
			err_flag = 1; //��ַ�쳣
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
			if (index_test == 0)   //��һ֡���ݲ���
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
				for (i = 0; i < 40; i++); //������֡����
				{
					g_data_array[i + 3] = g_data_array[i + 3];
				}
			}
		}
	}
	else
	{
		g_err_cnt = 0;//�����쳣��־����
		for (j = 0; j < 24; j++)
		{
			g_data_array[j + 3] = data_change_uint(uchar_uint16(&Data[16 + j * 2], LSB_FIRST))*coedata.coe_deform;
		}
		for (j = 0; j < 16; j++)
		{
			g_data_array[j + 27] = data_change_uint(uchar_uint16(&Data[88 + j * 2], LSB_FIRST))*coedata.coe_deform;
		}
	}

	g_data_array[43] = data_change(uchar_uint16(&Data[308], LSB_FIRST))*coedata.coe_temp_sig; 	             //������¶�
	g_data_array[44] = data_change(uchar_uint16(&Data[310], LSB_FIRST))*coedata.coe_temp_interface;		   //�ӿڰ��¶�
	g_data_array[45] = data_change(uchar_int16(&Data[322], LSB_FIRST));//*coedata.coe_temp_pose;                //��̬�¶�     

	//transfer_mode=DEBUG_MODE;  //Ĭ�϶���ģʽ��20200408
	g_data_array[46] = (short int)(uchar_uint16(&Data[312], LSB_FIRST))*coedata.coe_circum_angle; //����� 
	g_data_array[47] = (short int)(uchar_int16(&Data[314], LSB_FIRST))*coedata.coe_dip_angle;     //���
	g_data_array[48] = (short int)(uchar_int16(&Data[324], MSB_FIRST))*coedata.coe_raw_angle;     //�����
	g_data_array[49] = (short int)(uchar_int16(&Data[316], LSB_FIRST))*coedata.coe_accleration;   //X����ٶ�
	g_data_array[50] = (short int)(uchar_int16(&Data[318], LSB_FIRST))*coedata.coe_accleration;   //Y����ٶ�
	g_data_array[51] = (short int)(uchar_int16(&Data[320], LSB_FIRST))*coedata.coe_accleration;   //Z����ٶ�
	g_data_array[52] = Data[339] * 0x1000000 + Data[338] * 0x10000 + Data[341] * 0x100 + Data[340];    //��һ·ԭʼ���
	g_data_array[53] = Data[343] * 0x1000000 + Data[342] * 0x10000 + Data[345] * 0x100 + Data[344];    //�ڶ�·ԭʼ���  
	g_data_array[54] = Data[347] * 0x1000000 + Data[346] * 0x10000 + Data[349] * 0x100 + Data[348];    //����·ԭʼ���  

	//���Ӳɼ�״̬��־20200326
	g_data_array[55] = Data[334];       //�ɼ�״̬��־

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

	for (i = 0; i < cnt; i++)	  //ÿ�ֽ�bit0 bit7����˳��
	{
		data_low[i] = Data[i] & 0x01; //ȡ��bit0
		data_high[i] = (Data[i] >> 7) & 0x01;//ȡ��bit7

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
	////////////����Ϊ���ݼ��ܽ���


	//ǰ5֡����ֱ��ת�����ļ���dire1
		//����ת��Ϊʮ���ƣ���д��һ֡   
		/**************************************��һ���ֽ���**************************************************/
		data_array[0] = uchar_uint32(&Data[4], LSB_FIRST);	                                        //��ѡ�������

		data_array[1] = (Data[13] * 0x10000000000 + Data[12] * 0x100000000
			+ Data[11] * 0x1000000 + (Data[10] * 0x10000) + (Data[9] * 0x100) + Data[8]) & 0xffffffffffff;  //ʱ��������� 

		data_array[2] = uchar_uint16(&Data[14], LSB_FIRST)*coedata.coe_voltage_24; 	                //24v�����ѹ
		n = 3;
		/**************************************��������**************************************************/
		//�������ݣ�graph1~graph3��
		   //����Э�����·��� 
		for (j = 0; j < 20; j++)
		{
			Data_temp[j] = Data[40 + j];	 //��1~10·��Ч���ݣ�ȡ������1~10������
		}
		for (j = 0; j < 12; j++)
		{
			Data_temp[j + 20] = Data[40 + 24 + j];  //��11~16·��Ч���ݣ�ȡ������13~18������
		}
		for (j = 0; j < 8; j++)
		{
			Data_temp[j + 32] = Data[40 + 37 + j];  //��17~20·��Ч���ݣ�ȡ������19~22������
		}
		for (j = 0; j < 20; j++)
		{
			Data_temp[j + 40] = Data[40 + 49 + j];  //��21~30·��Ч���ݣ�ȡ������25~34������
		}
		for (j = 0; j < 20; j++)
		{
			Data_temp[j + 60] = Data[40 + 74 + j];  //��31~40·��Ч���ݣ�ȡ������37~46������
		}


		for (i = 0; i < 40; i++)
		{
			data_array[n++] = data_change_uint(uchar_uint16(&Data_temp[i * 2], LSB_FIRST))*coedata.coe_deform;
		}


		data_array[n++] = (short int)(uchar_int16(&Data[151], LSB_FIRST))*coedata.coe_temp_sig;   	  //�źŴ�����¶�
		data_array[n++] = uchar_uint16(&Data[30], LSB_FIRST)*coedata.coe_temp_obient + coedata.coe_temp_obient_b;//��Դģ�黷���¶�
		data_array[n++] = (short int)(uchar_int16(&Data[165], LSB_FIRST))*coedata.coe_temp_pose;     //��̬�¶�
		//***********************************��������***************************************//
	//transfer_mode = DEBUG_MODE;
		data_array[n++] = (uchar_uint16(&Data[153], LSB_FIRST))*coedata.coe_circum_angle;            //����� 
		data_array[n++] = (short int)(uchar_int16(&Data[155], LSB_FIRST))*coedata.coe_dip_angle;     //���
		data_array[n++] = (short int)(uchar_int16(&Data[157], LSB_FIRST))*coedata.coe_raw_angle;     //�����
		data_array[n++] = (short int)(uchar_int16(&Data[159], LSB_FIRST))*coedata.coe_accleration;   //X����ٶ�
		data_array[n++] = (short int)(uchar_int16(&Data[161], LSB_FIRST))*coedata.coe_accleration;   //Y����ٶ�
		data_array[n++] = (short int)(uchar_int16(&Data[163], LSB_FIRST))*coedata.coe_accleration;   //Z����ٶ�
		//data_array[n++]=(short int)(uchar_int16(&Data[154],LSB_FIRST))*coedata.coe_temp_pose;     //��̬�¶�
		//data_array[n++]=(short int)(uchar_int16(&Data[140],LSB_FIRST))*coedata.coe_temp_sig;   	  //�źŴ�����¶�

		data_array[n++] = uchar_uint32(&Data[178 + 2], LSB_FIRST);      //��һ·ԭʼ���
		data_array[n++] = uchar_uint32(&Data[178 + 4 + 2], LSB_FIRST);    //�ڶ�·ԭʼ���  
		data_array[n++] = uchar_uint32(&Data[178 + 8 + 2], LSB_FIRST);    //����·ԭʼ���  

		//���Ӳɼ�״̬��־20191230
		data_array[n++] = Data[176];       //�ɼ�״̬��־
		data_yx = uchar_uint32(&Data[167], LSB_FIRST);	    //ʱ��ɼ�ģʽ��ѡ���                                 
		fwrite(data_array, sizeof(double), n, fp);
	}
