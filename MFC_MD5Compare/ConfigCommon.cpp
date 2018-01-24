#include "stdafx.h"
#include "ConfigCommon.h"

void ConfigCommon::SetPath(wstring path)
{
	m_path = path;
}

void ConfigCommon::Create()
{
	//Path
	Write(_T("Path"), _T("source"), _T(""));
	Write(_T("Path"), _T("target"), _T(""));
	Write(_T("Path"), _T("export"), _T(""));

	//SkipSize
	Write(_T("SkipSize"), _T("checkMaxSize"), _T("1"));
	Write(_T("SkipSize"), _T("maxSizeIndex"), _T("0"));

	//MD5Engine
	Write(_T("MD5Engine"), _T("cppEngine"), _T("1"));
	Write(_T("MD5Engine"), _T("dotNetEngine"), _T("0"));

	//Report
	Write(_T("Report"), _T("created"), _T("1"));
	Write(_T("Report"), _T("modified"), _T("1"));
	Write(_T("Report"), _T("removed"), _T("1"));
	Write(_T("Report"), _T("failed"), _T("1"));

	//SkipType
	Write(_T("SkipTypes"), _T("keys"), _T("Text Documents;Image Files;Cpp Files"));
	Write(_T("SkipTypes"), _T("selected"), _T("None"));
	Write(_T("SkipTypes"), _T("Text Documents"), _T("*.txt"));
	Write(_T("SkipTypes"), _T("Image Files"), _T("*.gif;*.jpg;*.png"));
	Write(_T("SkipTypes"), _T("Cpp Files"), _T("*.cpp;*.h;*.rc"));
}

void ConfigCommon::WriteStr(wstring appName, wstring keyName, CString value)
{
	Write(appName, keyName, value);
}

void ConfigCommon::WriteInt(wstring appName, wstring keyName, int value)
{
	CString str;
	str.Format(_T("%d"), value);
	Write(appName, keyName, str);
}

void ConfigCommon::ReadStr(wstring appName, wstring keyName, CString &value)
{
	wstring path = FileCommon::GetModulePath() + m_path;
	BOOL res = GetPrivateProfileString(appName.c_str(), keyName.c_str(), CString("NULL"), value.GetBuffer(MAX_PATH), MAX_PATH, path.c_str());
}

void ConfigCommon::ReadInt(wstring appName, wstring keyName, int &value)
{
	wstring path = FileCommon::GetModulePath() + m_path;
	value = GetPrivateProfileInt(appName.c_str(), keyName.c_str(), 0, path.c_str());
}

void ConfigCommon::Remove(wstring appName, wstring keyName)
{
	wstring path = FileCommon::GetModulePath() + m_path;
	BOOL res = WritePrivateProfileStringW(appName.c_str(), keyName.c_str(), NULL, path.c_str());
}

void ConfigCommon::Write(wstring appName, wstring keyName, CString value)
{
	wstring path = FileCommon::GetModulePath() + m_path;
	BOOL res = WritePrivateProfileStringW(appName.c_str(), keyName.c_str(), value, path.c_str());
}