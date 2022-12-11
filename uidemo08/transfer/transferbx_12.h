#pragma once
#include "transferbx.h"
class transferbx_12 :
	public transferbx
{
	void initParameter();
	void DatTransTxt_bx(char file_name[], unsigned char Data[], FILE *fp);
	void DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE *fp);
};

