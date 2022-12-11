#pragma once

#include <iostream>
#include "publicFunction.h"
#define ERVERYNUM  43
#define DEFORMERERY 43
#define DEFORMBLOCK  37     


class transferbx
{
public:
	coedata_t coedata;
	channelnum_t channelnum;
	int FrameLen;                  //每帧数据长度 
	virtual void initParameter() = 0;
	virtual void DatTransTxt_bx(char file_name[], unsigned char Data[], FILE *fp) = 0;
	virtual void DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE *fp) = 0;
    static void sayHello();
};

