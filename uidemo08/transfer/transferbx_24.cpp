
#include "transferbx_24.h"

void transferbx_24::initParameter()
{
	FrameLen = 228 + 4; 	              //��֡���ݳ��ȣ��ֽڣ������أ�
	channelnum.mfl = 0;		          //©��ͨ����
	channelnum.deform = 0;		      //����ͨ����
	channelnum.bak = 0;			      //����ͨ���� 
	channelnum.all = 0;				  //��ͨ����     
	channelnum.motorbyte = 11;	      //��̬Ԥ���ֽ���  

	coedata.coe_voltage_24 = 3.3*11.0 / 4096.0;	    //24v�����ѹ
	coedata.coe_voltage_5 = 3.3*2.0 / 4096.0;	    //5V�����ѹ
	coedata.coe_voltage_bat = 0.001;       //��ص�ѹ
	coedata.coe_current_bat = 0.001;       //��ص��� 
	coedata.coe_power = 0.001;             //��ع���	
	coedata.coe_power_consum = 0.1;        //������õ���   
	coedata.coe_time_energizing = 0.01;    //����ۼ�ͨ��ʱ��	
	coedata.coe_temp_sig = 0.0625;         //������¶�
	coedata.coe_temp_interface = 0.0625;   //�ӿڰ��¶�  
	coedata.coe_circum_angle = 0.01;        //��̬�����
	coedata.coe_dip_angle = 0.01;	         //��̬���	
	coedata.coe_accleration = 0.002;//0.0029;      //ϵͳ���ٶ�
	coedata.coe_temp_pose = 1.0;//0.0625;	     //��̬����ϵͳ�¶� 
	coedata.coe_raw_angle = 0.01;           //��̬�����

	coedata.coe_deform = 5.0 / 4096.0;       //���� 
}

void transferbx_24::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000] = { 0 };
	int cnt = FrameLen;
	//
	unsigned char data_test[232], data_low[232], data_high[232], data_1, data_2, data_3, data_4;

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

	data_array[n++] = (short int)(uchar_int16(&Data[187], LSB_FIRST))*coedata.coe_temp_sig;   	     //�źŴ�����¶�
	data_array[n++] = (short int)(uchar_int16(&Data[189], LSB_FIRST))*coedata.coe_temp_interface;	 //�ӿڰ��¶�	
	data_array[n++] = (short int)(uchar_int16(&Data[203], LSB_FIRST))*coedata.coe_temp_pose;        //��̬�¶�	
	//***********************************��������***************************************//
	//�켣���
	data_array[n++] = (short int)(uchar_int16(&Data[207], LSB_FIRST))*coedata.coe_circum_angle;  //����� 
	data_array[n++] = (short int)(uchar_int16(&Data[205], LSB_FIRST))*coedata.coe_dip_angle;     //���
	data_array[n++] = (short int)(uchar_int16(&Data[209], LSB_FIRST))*coedata.coe_raw_angle;     //�����

	data_array[n++] = (short int)(uchar_int16(&Data[197], LSB_FIRST))*coedata.coe_accleration;   //X����ٶ�
	data_array[n++] = (short int)(uchar_int16(&Data[199], LSB_FIRST))*coedata.coe_accleration;   //Y����ٶ�
	data_array[n++] = (short int)(uchar_int16(&Data[201], LSB_FIRST))*coedata.coe_accleration;   //Z����ٶ�
																				  //�ӿڰ��¶�
	data_array[n++] = uchar_uint32(&Data[216], LSB_FIRST);                                        //��һ·ԭʼ���
	data_array[n++] = uchar_uint32(&Data[216 + 4], LSB_FIRST);                                      //�ڶ�·ԭʼ���  
	data_array[n++] = uchar_uint32(&Data[216 + 8], LSB_FIRST);                                      //����·ԭʼ���  

	//���Ӳɼ�״̬��־20191230
	data_array[n++] = Data[214];       //�ɼ�״̬��־


	fwrite(data_array, sizeof(double), n, fp);
}

void transferbx_24::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
