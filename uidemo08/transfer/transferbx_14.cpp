
#include "transferbx_14.h"

void transferbx_14::initParameter()
{
	FrameLen = 192 + 4; 	              //��֡���ݳ��ȣ��ֽڣ������أ�	  
	channelnum.mfl = 0;		          //©��ͨ����
	channelnum.deform = 0;		      //����ͨ����
	channelnum.bak = 0;			      //����ͨ���� 
	channelnum.all = 0;				  //��ͨ����     
	channelnum.motorbyte = 11;	      //��̬Ԥ���ֽ���  

	coedata.coe_voltage_24 = 0.001;	    //24v�����ѹ
	coedata.coe_current_24 = 0.001;       //24V�������
	coedata.coe_power_consum = 0.1;       //��������õ���  
	coedata.coe_time_energizing = 0.01;   //����ۼ�ͨ��ʱ�� 
	coedata.coe_power_rated = 0.1;        //���������   
	coedata.coe_temp_obient = -0.23;      //�����¶� 
	coedata.coe_temp_obient_b = 193.23;
	coedata.coe_voltage_5 = 0.0078;	    //5V�����ѹ
	coedata.coe_voltage_33 = 0.0036;	    //3.3V�����ѹ 
	coedata.coe_voltage_back = 0.0275;	//���ù����ѹ  

	coedata.coe_temp_sig = 0.0625;        //������¶�

	coedata.coe_circum_angle = 0.1;       //��̬�����
	coedata.coe_dip_angle = 0.1;	        //��̬���
	coedata.coe_accleration = 0.002;//0.0029;     //ϵͳ���ٶ�
	coedata.coe_temp_pose = 1.0;//0.0625;	    //��̬��ϵͳ�¶�    
	coedata.coe_raw_angle = 0.1;          //��̬�����

	coedata.coe_deform = 5.0 / 4096.0;    //����
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
	fwrite(data_array, sizeof(double), n, fp);
}

void transferbx_14::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
