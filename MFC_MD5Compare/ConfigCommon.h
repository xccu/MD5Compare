#pragma once
#include "Resource.h"
#include "ResourceHelper.h"
#include "FileCommon.h"

class ConfigCommon
{
private:
	wstring m_path;
public:
	void SetPath(wstring path);
	void Create();
	void WriteStr(wstring appName, wstring keyName, CString value);
	void WriteInt(wstring appName, wstring keyName, int value);
	void ReadStr(wstring appName, wstring keyName, CString &value);
	void ReadInt(wstring appName, wstring keyName, int &value);
	void Remove(wstring appName, wstring keyName);
private:
	void Write(wstring appName, wstring keyName, CString value);
};