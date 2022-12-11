
#include "transferbx_48.h"


void transferbx_48::initParameter()
{
	FrameLen = 384; 	                  //��֡���ݳ��ȣ��ֽڣ������أ�
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
	coedata.coe_circum_angle = 0.1;        //��̬�����
	coedata.coe_dip_angle = 0.1;	         //��̬���	
	coedata.coe_accleration = 0.002;//0.0029;      //ϵͳ���ٶ�
	coedata.coe_temp_pose = 1.0;//0.0625;	     //��̬����ϵͳ�¶� 
	coedata.coe_raw_angle = 0.1;           //��̬�����

	coedata.coe_deform = 5.0 / 4096.0;       //���� 
}


void transferbx_48::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
	int  n;
	int i, j;
	double data_array[1000];

	int head1, head2;

	//֡ͷ֡β�ж�
	head1 = uchar_uint32(&Data[0], MSB_FIRST);
	head2 = uchar_uint32(&Data[FrameLen - 4], MSB_FIRST);
	//if ((head1 == 0x55aa55aa)&(head2 == 0xaa55aa55))
	//{
	//	g_flag_head = 0;//����
	//}
	//else
	//{
	//	g_flag_head = 1;//�쳣
	//	g_data_err[g_tran_err_cnt] = g_tran_cnt;
	//	g_tran_err_cnt++;
	//}

	//g_tran_cnt++;
	//����ת��Ϊʮ���ƣ���д��һ֡   
	/**************************************��һ���ֽ���**************************************************/
	data_array[0] = uchar_uint32(&Data[4], LSB_FIRST);	                                        //��ѡ�������

	data_array[1] = (Data[13] * 0x10000000000 + Data[12] * 0x100000000
		+ Data[11] * 0x1000000 + (Data[10] * 0x10000) + (Data[9] * 0x100) + Data[8]) & 0xffffffffffff;  //ʱ��������� 

	data_array[2] = uchar_int16(&Data[14], LSB_FIRST)*coedata.coe_voltage_24; 	                //24v�����ѹ
	n = 3;
	/**************************************��������**************************************************/

	for (i = 0; i < 8; i++)
	{
		for (j = 0; j < 18; j++)
		{
			data_array[n++] = data_change_uint(uchar_int16(&Data[39 + i * DEFORMBLOCK + j * 2], LSB_FIRST))*coedata.coe_deform;
		}
	}

	data_array[n++] = (short int)(uchar_int16(&Data[188], LSB_FIRST))*coedata.coe_temp_sig;   	     //�źŴ�����¶�
	data_array[n++] = (short int)(uchar_int16(&Data[190], LSB_FIRST))*coedata.coe_temp_interface;	 //�ӿڰ��¶�	
	data_array[n++] = (short int)(uchar_int16(&Data[204], LSB_FIRST))*coedata.coe_temp_pose;        //��̬�¶� 
	//***********************************��������***************************************//

	data_array[n++] = (uchar_uint16(&Data[192], LSB_FIRST))*coedata.coe_circum_angle;            //����� 
	data_array[n++] = (short int)(uchar_int16(&Data[194], LSB_FIRST))*coedata.coe_dip_angle;     //���
	data_array[n++] = (short int)(uchar_int16(&Data[196], LSB_FIRST))*coedata.coe_raw_angle;     //�����
	data_array[n++] = (short int)(uchar_int16(&Data[198], LSB_FIRST))*coedata.coe_accleration;   //X����ٶ�
	data_array[n++] = (short int)(uchar_int16(&Data[200], LSB_FIRST))*coedata.coe_accleration;   //Y����ٶ�
	data_array[n++] = (short int)(uchar_int16(&Data[202], LSB_FIRST))*coedata.coe_accleration;   //Z����ٶ�																				  //�ӿڰ��¶�
	data_array[n++] = uchar_int32(&Data[217], LSB_FIRST);                                        //��һ·ԭʼ���
	data_array[n++] = uchar_int32(&Data[217 + 4], LSB_FIRST);                                      //�ڶ�·ԭʼ���  
	data_array[n++] = uchar_int32(&Data[217 + 8], LSB_FIRST);                                      //����·ԭʼ��� 

	//���Ӳɼ�״̬��־20191230
	data_array[n++] = Data[215];       //�ɼ�״̬��־

	fwrite(data_array, sizeof(double), n, fp);

}

void transferbx_48::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
