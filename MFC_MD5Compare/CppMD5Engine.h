#pragma once
#include "Resource.h"
#include "ResourceHelper.h"
#include "MD5Engine.h"
#include "MD5Encode.h"
#include "FileCommon.h"

class CppMD5Engine:public MD5Engine
{
public:
	~CppMD5Engine() {};
	void SetSourceStr(wstring sourceStr);
	void SetTargetStr(wstring targetStr);
	BOOL Compare();
	Engine GetEngineType();
private:
	const Engine m_engine= Cpp;
	wstring m_sourceStr;
	wstring m_targetStr;
};