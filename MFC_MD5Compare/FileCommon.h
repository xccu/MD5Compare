#pragma once
#include "Resource.h"
#include "ResourceHelper.h"
#include "Md5Encode.h"
#include "MD5Engine.h"
#include "CppMD5Engine.h"


enum CodeType
{
	ANSI,
	UTF8,
	UTF8_NO_BOM,
	UTF16,
	AUTO
};
class FileCommon
{
public:
	wstring ReadFile(LPCTSTR strFile);
	void SetMd5Engine(MD5Engine *engine);
	BOOL WriteFile(LPCTSTR path, wstring value);
	BOOL Compare(wstring sourceStr, wstring targetStr);
	BOOL CreateFolder(wstring path);
	BOOL ExportFile(wstring sourceDirectory, wstring sourcefile, wstring exportDirectory);
	static wstring GetExtensionName(wstring fileName);
	static BOOL FindFile(wstring path);
	static wstring GetModulePath();
	static long GetFileSize(LPCTSTR path);
	static vector<wstring> Split(wstring str,wchar_t ch, int sub = 0);
	static wstring StrToUnicode(string str);
	static string UnicodeToStr(wstring wstr);
private:
	MD5Engine *m_engine;
};