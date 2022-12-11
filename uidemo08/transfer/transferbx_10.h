#pragma once
#include "transferbx.h"
class transferbx_10 :
	public transferbx
{
public:
    void initParameter();
	void DatTransTxt_bx(char file_name[], unsigned char Data[], FILE *fp);
	void DatTransTxt_bx_password(char file_name[], unsigned char Data[], FILE *fp);

    static void sayHello();
};

