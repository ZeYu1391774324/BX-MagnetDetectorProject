// transferBinary.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "transferBinary.h"

//int main()
//{
//	std::string savefiledir_bx = "D:\\bx\\32bxz\\";
//	std::string fileList_transfer = "D:\\bx\\32bxz\\20220426-144601-1_000.dat";
//	unsigned long FileSizeTotal = GetFileSize(fileList_transfer);
//	transferbx * tbx10 = new transferbx_28();
//	SingleFileTransfer(tbx10, FileSizeTotal, fileList_transfer, savefiledir_bx);
//}
void transferBinary::callTransfer(std::vector<std::string> inputList, std::string outPath,int inchSize)
{
	transferbx * tbx;
	switch (inchSize) {
	case 6 :
		tbx = new transferbx_6();
		break;
	case 8 :
		tbx = new transferbx_8();
		break;
	case 10 :
		tbx = new transferbx_10();
		break;
	case 12 :
		tbx = new transferbx_12();
		break;
	case 14 :
		tbx = new transferbx_14();
		break;
	case 16 :
		tbx = new transferbx_16();
		break;
	case 24 :
		tbx = new transferbx_24();
		break;
	case 28:
		tbx = new transferbx_28();
		break;
	case 32:
		tbx = new transferbx_32();
		break;
	case 40:
		tbx = new transferbx_40();
		break;
	case 48:
		tbx = new transferbx_48();
		break;
	default:
		tbx = new transferbx_10();
	}
	unsigned long FileSizeTotal;
    for (int i = 0; i < inputList.size(); i++) {
        FileSizeTotal = GetFileSize(inputList.at(i));
        SingleFileTransfer(tbx, FileSizeTotal, inputList.at(i), outPath);
    }


}


void transferBinary::SingleFileTransfer(transferbx * tbx, unsigned long FileSizeTotle, std::string path,std::string outpath)
{
	FILE *fp1 = NULL;						  // 异常点记录文件
	FILE *fp2 = NULL;                         // 打开数据记录文件			  
	FILE *fp3 = NULL;                         // 写十进制漏磁数据记录文件
	FILE *fp4 = NULL;                         // 写十进制变形数据记录文件
	FILE *fp5 = NULL;                         // 写优选里程文件 
	FILE *fp6 = NULL;
    //path = "E:\\Copycentre\\20201113-171849-1_000.dat";
    int pos = path.find_last_of("\\");
	outpath = outpath + path.substr(pos);
	tbx->initParameter();
	int FrameLen = tbx->FrameLen;
	// 写优选里程文件
	double FileSizeRate = 0;
	int sizenum = 0;
	unsigned long FileSize = FileSizeTotle, amounts = 0, amounts_error = 0;
	char   Drive_Name[512] = { 0 }, Directory_Name[512] = { 0 }, File_Name[512] = { 0 };
	char   Newfiledir[512] = { 0 }, savefiledir[512] = { 0 }, savefiledir_err[512] = { 0 }, buffer[MAXFILE_EVERYFRAME] = { 0 }, savefiledir_yx[512] = { 0 }, savefiledir_bx_yx[512] = { 0 };
	char   errorfiledir[512] = { 0 };
	int    i = 0, j = 0, num = 0, self_num = 1, i_str = 0, n = 0, buffer_len = 0;
	unsigned int txtfile_num = 0;      		 // 每个文件所含的帧计数  
	int hour, min, second;
	int hour1, min1, second1;
	int interval;
	int panelTransfer;
	std::string filename;
	// 每个文件所含的帧计数      											
	txtfile_num = 10000 * 5;   //转换后文件大小：50K帧

	// 获得当前文件大小
	//打开当前的二进制文件 
    fp2 = fopen((char*)path.data(), "rb+");
	if (fp2 == NULL)
	{
		//MessagePopup("err", "cannot open this file");
		exit(0);
	}
	else
	{
		// 显示新建文件的存储路径	 
		self_num = 1;
		num = FileSize / (FrameLen * txtfile_num);//按50K帧字节分文件  
		for (i = 0; i <= num; i++)   // 建立num+1个文本文件		  
		{
			// 10000*5帧新建立一个文本文件 
			/************************************建立变形文件**************************************/
			filename = outpath + "";
			filename += std::to_string(i+1);
			filename += "IN.bin";
			
			fp4 = fopen(filename.c_str(), "wb+");

			// 生成文件
			for (j = 0; j < txtfile_num; j++)
			{
				if (self_num >= (FileSize / FrameLen))	   // 文件读完，但不满FRAMESTEPNUM帧时，跳出转换，完成   	
				{
					fread(&buffer, FrameLen, 1, fp2);
					tbx->DatTransTxt_bx(new char[filename.length() + 1], reinterpret_cast<unsigned char*>(buffer), fp4);
					break;
				}
				else														   // 文件未读完
				{
					// 读二进制文件
					fread(&buffer, FrameLen, 1, fp2);  //读出FRAMESTEPNUM帧数据放入buffer中
					tbx->DatTransTxt_bx(new char[filename.length() + 1], reinterpret_cast<unsigned char*>(buffer), fp4);
					self_num++;
				}
				// 进度显示，转换1000*FRAMESTEPNUM帧计算一次进度
				if (sizenum >= 1000)
				{
					FileSizeNumber = FileSizeNumber + 1000;
					FileSizeRate = FileSizeNumber / 1024 / FileSizeTotle;
					sizenum = 0;
					sizenum++;
				}
				else
				{
					sizenum++;
				}
			}
			fclose(fp4);
		}
	}
	// 关闭源二进制文件 
	fclose(fp2);
}

size_t transferBinary::GetFileSize(const std::string & file_name) {
	std::ifstream in(file_name.c_str());
	in.seekg(0, std::ios::end);
	size_t size = in.tellg();
	in.close();
	return size; //单位是：byte
}
