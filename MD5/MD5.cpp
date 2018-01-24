// MD5.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MD5Encode.h"
#include <fstream>
using namespace std;

std::string ReadFile(std::string file_path)
{
	std::string  res;
	std::string  str_tmp;
	ifstream file(file_path, std::ios::binary);
	if (file.fail())
	{
		//std::string  info;
		//info.Format(_T("无法打开文件“%s”！"), file_path);
		//return _T("");
	}
	while (!file.eof())
	{
		str_tmp.push_back(file.get());
	}

	//str_tmp.pop_back();
	
	//res.Format(_T("%s"), str_tmp.c_str());
	return str_tmp;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string input = "^C:\\USERS\\XCY\\DESKTOP\\新建文件夹\\CPPDEMO\\MFC_MD5COMPARE\\MFC_MD5COMPARE\\STDAFX.CPP// c // ZI // nologo // W3 / WX - / sdl / Od / Oy - / D WIN32 / D _WINDOWS / D _DEBUG / D _UNICODE / D UNICODE / D _AFXDLL / Gm / EHsc / RTC1 / MDd / GS / fp:precise / Zc : wchar_t / Zc : forScope / Yc\"stdafx.h\" / Fp\"DEBUG\\MFC_MD5COMPARE.PCH";
	string input1 = "^C:\\USERS\\XCY\\DESKTOP\\新文件夹\\CPPDEMO\\MFC_MD5COMPARE\\MFC_MD5COMPARE\\STDAFX.CPP// c // ZI // nologo // W3 / WX - / sdl / Od / Oy - / D WIN32 / D _WINDOWS / D _DEBUG / D _UNICODE / D UNICODE / D _AFXDLL / Gm / EHsc / RTC1 / MDd / GS / fp:precise / Zc : wchar_t / Zc : forScope / Yc\"stdafx.h\" / Fp\"DEBUG\\MFC_MD5COMPARE.PCH";
	MD5Encode md5 = MD5Encode(input.c_str());
	string w= md5.outstr(32);

    return 0;
}

