#pragma once
#include "Resource.h"
#include "ResourceHelper.h"
#include "MD5Engine.h"
#include "FileCommon.h"

#include <msclr\marshal_cppstd.h>   
#using "../debug/DotNet_MD5.dll" 

using namespace DotNetMD5;
using namespace msclr::interop;
using namespace System;

class DotNetMD5Engine :public MD5Engine
{
public:
	~DotNetMD5Engine() {};
	void SetSourceStr(wstring sourceStr);
	void SetTargetStr(wstring targetStr);
	BOOL Compare();
	Engine GetEngineType();
private:
	const Engine m_engine = DotNet;
	wstring m_sourceStr;
	wstring m_targetStr;
};
