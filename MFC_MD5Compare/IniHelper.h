#pragma once
#include "resource.h"
#include "ResourceHelper.h"
#include "FileCommon.h"
#include "ConfigCommon.h"

class IniHelper : public ConfigCommon
{
public:
	CString FormatTypeString(wstring key, wstring listStr);
	BOOL ValidateTypeListString(wstring listStr);
	CString GetTypeString(wstring key);
	CString GetTypeKey(wstring typeStr);
	void ReadThreadParameters(ThreadParameters &threadParameter);
	void ParseTypeList(CString typeStr, CString &key, vector<wstring> &typeList);
	void WriteTypes(wstring name, wstring listStr);
	void UpdateType(vector<wstring> typeStrList);
	

private:
	CString GetTypeListString(wstring typeStr);
	void RemoveType(wstring key);
};