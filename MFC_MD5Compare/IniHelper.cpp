#include "stdafx.h"
#include "IniHelper.h"

CString IniHelper::FormatTypeString(wstring key, wstring listStr)
{
	wstring tempStr =  key + _T("(") + listStr + _T(")");
	return CString(tempStr.c_str());
}

void IniHelper::WriteTypes(wstring name, wstring listStr)
{
	CString cListStr(listStr.c_str()), cName(name.c_str()),keyStr;

	ReadStr(_T("SkipTypes"), _T("keys"), keyStr);
	keyStr.Format(_T("%s;%s"), keyStr, cName);

	WriteStr(_T("SkipTypes"), _T("keys"), keyStr);
	WriteStr(_T("SkipTypes"), name, cListStr);
}

void IniHelper::UpdateType(vector<wstring> typeStrList)
{
	CString typeStr, key, keys;
	vector<wstring> typeList;


	ReadStr(_T("SkipTypes"), _T("keys"), key);
	typeList = FileCommon::Split(key.GetString(),';');

	//remove all types
	for (const auto &item : typeList)
	{
		RemoveType(item);
	}

	//write types
	for (const auto &item : typeStrList)
	{
		typeStr = CString(item.c_str());
		ParseTypeList(typeStr, key, typeList);
		WriteStr(_T("SkipTypes"), key.GetString() , GetTypeListString(item));
		keys.Format(_T("%s;%s"), keys, key);
	}
	keys = keys.Right(keys.GetLength() - 1);
	WriteStr(_T("SkipTypes"), _T("keys"), keys);
}

void IniHelper::RemoveType(wstring key)
{
	Remove(_T("SkipTypes"), key);
}

BOOL IniHelper::ValidateTypeListString(wstring listStr)
{
	vector<wstring> list = FileCommon::Split(listStr, ';');
	std::regex rx("^([*][.])+[A-Za-z0-9]+$");//Æ¥ÅäÀ©Õ¹Ãû½áÎ²
	string str;
	for (const auto& item : list)
	{
		str = FileCommon::UnicodeToStr(item);
		//if (str.find_first_of('*') != 0)
			//return FALSE;
		if (!std::regex_match(str, rx))
			return FALSE;
	}
	return TRUE;
}

CString IniHelper::GetTypeString(wstring key)
{
	CString listStr;
	ReadStr(_T("SkipTypes"), key, listStr);
	return FormatTypeString(key, listStr.GetString());
}

CString IniHelper::GetTypeKey(wstring typeStr)
{
	int pos = typeStr.find_first_of(_T('('));
	return CString(typeStr.substr(0, pos).c_str());
}

void IniHelper::ReadThreadParameters(ThreadParameters &threadParameter)
{
	ReadStr(_T("Path"), _T("source"), threadParameter.sourcePath);
	ReadStr(_T("Path"), _T("target"), threadParameter.targetPath);

	ReadInt(_T("SkipSize"), _T("checkMaxSize"), threadParameter.skip.isCheckSize);
	ReadInt(_T("SkipSize"), _T("maxSizeIndex"), threadParameter.skip.maxSizeIndex);

	ReadInt(_T("Report"), _T("created"), threadParameter.created);
	ReadInt(_T("Report"), _T("modified"), threadParameter.modified);
	ReadInt(_T("Report"), _T("removed"), threadParameter.removed);
	ReadInt(_T("Report"), _T("failed"), threadParameter.failed);
}

CString IniHelper::GetTypeListString(wstring typeStr)
{
	int startpos = typeStr.find_first_of(_T('('));
	int endpos = typeStr.find_last_of(_T(')'));
	if (startpos > endpos)
		return _T("");
	return CString(typeStr.substr(startpos+1, endpos - startpos-1).c_str());
}

void IniHelper::ParseTypeList(CString typeStr, CString &key, vector<wstring> &typeList)
{
	key = GetTypeKey(typeStr.GetString());
	CString listStr = GetTypeListString(typeStr.GetString());

	typeList = FileCommon::Split(listStr.GetString(), ';', 1);
}
