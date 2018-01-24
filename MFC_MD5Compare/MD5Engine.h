#pragma once
#include "Resource.h"
#include "ResourceHelper.h"

enum Engine
{
	Cpp,
	DotNet
};
class MD5Engine
{
public:
	virtual ~MD5Engine() {};
	virtual void SetSourceStr(wstring spurceStr) = 0;
	virtual void SetTargetStr(wstring targetStr) = 0;
	virtual BOOL Compare() = 0;
	virtual Engine GetEngineType() = 0;
//private:
//	wstring m_sourcePath;
//	wstring m_targetPath;
};