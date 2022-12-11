
#include "transferbx_16.h"

void transferbx_16::initParameter()
{
    FrameLen = 1504;
    channelnum.mfl = 30;
    channelnum.deform = 3;
    channelnum.bak = 0;
    channelnum.all = 33;
    channelnum.motorbyte = 0;


    coedata.coe_voltage_24 = 3.3*11.0 / 4096.0;	    //24v
    coedata.coe_voltage_5 = 3.3*2.0 / 4096.0;	    //5V
    coedata.coe_voltage_bat = 0.001;      //
    coedata.coe_current_bat = 0.001;      //
    coedata.coe_power = 0.001;            //
    coedata.coe_power_consum = 0.1;       //
    coedata.coe_time_energizing = 0.01;   //

    coedata.coe_axialdata = 1.0 / 4.0;	  //
    coedata.coe_radialdata = 1.0 / 4.0;    //
    coedata.coe_circumdata = 1.0 / 4.0;    //
    coedata.coe_temp_sensor = 302.0 / 4096.0;	 //
    coedata.coe_temp_sensor_b = -1708.0;
    coedata.coe_division = 3.3 / 4096.0;   //
    coedata.coe_deform = 5.0 / 4096.0;    //

    coedata.coe_temp_sig = 0.0625;        //
    coedata.coe_temp_interface = 0.0625;   //
    coedata.coe_circum_angle = 0.1;   //
    coedata.coe_dip_angle = 0.1;	  //
    coedata.coe_raw_angle = 0.1;     //
    coedata.coe_accleration = 0.002;//0.0029;  //
    coedata.coe_temp_pose = 1.0;//0.0625;	//
}

void transferbx_16::DatTransTxt_bx(char file_name[], unsigned char Data[], FILE * fp)
{
    int  n;
    int i, j;
    double data_array[1000];
    //§Õ
    /****************************************************************************************/
    data_array[0] = uchar_uint32(&Data[4], MSB_FIRST);	                                        //
    data_array[1] = (Data[8] * 0x10000000000 + Data[9] * 0x100000000
        + Data[10] * 0x1000000 + (Data[11] * 0x10000) + (Data[12] * 0x100) + Data[13]) & 0xffffffffffff;  //
    data_array[2] = uchar_int16(&Data[14], MSB_FIRST)*coedata.coe_voltage_24;
    n = 3;
    /****************************************************************************************/
    for (i = 0; i < (channelnum.deform - 1); i++)
    {
        for (j = 0; j < 16; j++)
        {
            data_array[n++] = data_change_uint(uchar_int16(&Data[1330 + i * DEFORMERERY + j * 2], LSB_FIRST))*coedata.coe_deform;
        }
    }
    for (j = 0; j < 4; j++)
    {
        data_array[n++] = data_change_uint(uchar_int16(&Data[1330 + 2 * DEFORMERERY + j * 2], LSB_FIRST))*coedata.coe_deform;
    }
    //data_array[n++]=(data_change_uint(uchar_uint16(&Data[0*ERVERYNUM+76],MSB_FIRST))+coedata.coe_temp_sensor_b)*coedata.coe_temp_sensor;
    //data_array[n++]=(data_change_uint(uchar_uint16(&Data[14*ERVERYNUM+76],MSB_FIRST))+coedata.coe_temp_sensor_b)*coedata.coe_temp_sensor;
    data_array[n++] = (short int)(uchar_int16(&Data[40 + ERVERYNUM * (channelnum.mfl + channelnum.deform)], MSB_FIRST))*coedata.coe_temp_sig;   	     //
    data_array[n++] = (short int)(uchar_int16(&Data[42 + ERVERYNUM * (channelnum.mfl + channelnum.deform)], MSB_FIRST))*coedata.coe_temp_interface;   //
    data_array[n++] = (short int)(uchar_int16(&Data[54 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_temp_pose;                            //

    data_array[n++] = (uchar_uint16(&Data[44 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_circum_angle; //
    data_array[n++] = (short int)(uchar_int16(&Data[46 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_dip_angle;     //
    data_array[n++] = (short int)(uchar_int16(&Data[56 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_raw_angle;     //
    data_array[n++] = (short int)(uchar_int16(&Data[48 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_accleration;   //X
    data_array[n++] = (short int)(uchar_int16(&Data[50 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_accleration;   //Y
    data_array[n++] = (short int)(uchar_int16(&Data[52 + ERVERYNUM * channelnum.all], LSB_FIRST))*coedata.coe_accleration;   //Z
    //data_array[n++]=(short int)(uchar_int16(&Data[54+ERVERYNUM*channelnum.all],LSB_FIRST))*coedata.coe_temp_pose;     //
    //data_array[n++]=(short int)(uchar_int16(&Data[40+ERVERYNUM*(channelnum.mfl+channelnum.deform)],MSB_FIRST))*coedata.coe_temp_sig;   	   //
    //data_array[n++]=(short int)(uchar_int16(&Data[42+ERVERYNUM*(channelnum.mfl+channelnum.deform)],MSB_FIRST))*coedata.coe_temp_interface;   //
    data_array[n++] = uchar_uint32(&Data[69 + ERVERYNUM * channelnum.all], MSB_FIRST);    //¡¤
    data_array[n++] = uchar_uint32(&Data[73 + ERVERYNUM * channelnum.all], MSB_FIRST);    //¡¤
    data_array[n++] = uchar_uint32(&Data[77 + ERVERYNUM * channelnum.all], MSB_FIRST);    //¡¤

    fwrite(data_array, sizeof(double), n, fp);
}

void transferbx_16::DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE * fp)
{
}
