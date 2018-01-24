#pragma once
#include <string>   
#include <msclr\marshal_cppstd.h>    
#include <iostream>    
#using "../debug/MD5Service.dll" 

using namespace msclr::interop;
using namespace System;
using namespace std;


using namespace MD5Service;

class MD5Common
{
public:
	wstring getMD5Code(wstring filePath);
};
