#include "stdafx.h" 
#include "MD5Common.h"

wstring MD5Common::getMD5Code(wstring fileStr)
{
	String^ fileCli = marshal_as<String^>(fileStr);
	MD5 ^a = gcnew MD5();
	String^ MD5Cli = a->Encrypt(fileCli, 201504);
	std::wstring MD5Str = marshal_as<std::wstring>(MD5Cli);
	return MD5Str;
}