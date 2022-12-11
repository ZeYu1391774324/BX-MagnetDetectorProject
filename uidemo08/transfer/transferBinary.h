#pragma once
#define MAXFILE_EVERYFRAME  4096               // 每帧数形成的文件大小  
#include <iostream>
#include <string>
#include <fstream>
#include "./transfer/transferbx_6.h"
#include "./transfer/transferbx_8.h"
#include "./transfer/transferbx_10.h"
#include "./transfer/transferbx_12.h"
#include "./transfer/transferbx_14.h"
#include "./transfer/transferbx_16.h"
#include "./transfer/transferbx_24.h"
#include "./transfer/transferbx_28.h"
#include "./transfer/transferbx_32.h"
#include "./transfer/transferbx_40.h"
#include "./transfer/transferbx_48.h"
#include <vector>

static int FileSizeNumber = 0;
class transferBinary
{
public:
	void callTransfer(std::vector<std::string> inputList, std::string outPath, int inchSize);
	void SingleFileTransfer(transferbx * tbx, unsigned long FileSizeTotle, std::string path, std::string outpath);
	size_t GetFileSize(const std::string & file_name);
};

