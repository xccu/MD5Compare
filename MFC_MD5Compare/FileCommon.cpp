#pragma once
#include "stdafx.h"
#include "FileCommon.h"

wstring FileCommon::ReadFile(LPCTSTR file_path)
{
	char ch;
	CString res;
	string str_tmp;
	ifstream file(file_path, std::ios::binary);
	if (file.fail())
	{
		CString info;
		info.Format(_T("无法打开文件“%s”！"), file_path);
		return _T("");
	}
	while (!file.eof())
	{
		ch = file.get();
		if (ch == '\0')
			continue;
		str_tmp.push_back(ch);
	}

	//str_tmp.pop_back();
	wstring result = StrToUnicode(str_tmp);
	//res.Format(_T("%s"), str_tmp);   
	return result;
}

void FileCommon::SetMd5Engine(MD5Engine *engine)
{
	m_engine = engine;
}

BOOL FileCommon::WriteFile(LPCTSTR path, wstring value)
{
	ofstream file(path, std::ios::binary);
	if (!file.good())		//如果无法保存文件，则返回false
		return false;
	string str;
	str = FileCommon::UnicodeToStr(value);
	file << str.c_str();
	return true;
}

BOOL FileCommon::Compare(wstring sourceStr, wstring targetStr)
{
	m_engine->SetSourceStr(sourceStr);
	m_engine->SetTargetStr(targetStr);
	return m_engine->Compare();
}

BOOL FileCommon::CreateFolder(wstring path)
{
	//利用dos命令创建文件夹
	//wstring cmd = _T("md ") + path;
	//system(UnicodeToStr(cmd).c_str());

	vector<wstring> dirs;
	dirs = Split(path, '\\');
	wstring dir;
	for (int i = 0; i < dirs.size(); i++)
	{
		dir += dirs[i];
		//判断文件夹是否存在
		if (GetFileAttributesA(UnicodeToStr(dir).c_str()) == INVALID_FILE_ATTRIBUTES)
		{
			if (!CreateDirectory(dir.c_str(), NULL))
				return FALSE;
		}
		dir += _T('\\');
	}
	return TRUE;

}

BOOL FileCommon::ExportFile(wstring sourceDirectory,wstring sourcefile, wstring exportDirectory)
{
	wstring tempSource = sourcefile;
	tempSource.erase(0, sourceDirectory.length());

	wstring outputfile = sourcefile.substr(0, sourcefile.find_last_of('\\'));
	outputfile.erase(0, sourceDirectory.length());
	if (CreateFolder(exportDirectory + outputfile))
	{
		exportDirectory += tempSource;
		return CopyFile(sourcefile.c_str(), exportDirectory.c_str(), TRUE);
	}
}

BOOL FileCommon::FindFile(wstring path)
{
	CFileFind finder;
	return finder.FindFile(path.c_str());
}

wstring FileCommon::GetModulePath()
{
	wchar_t path[MAX_PATH];
	GetModuleFileNameW(NULL, path, MAX_PATH);
	size_t index;
	wstring current_path{ path };
	index = current_path.find_last_of(L'\\');
	current_path = current_path.substr(0, index + 1);
	return current_path;
}

long FileCommon::GetFileSize(LPCTSTR path)
{
	CFileStatus fileStatus;
	if (CFile::GetStatus(path, fileStatus))
		return fileStatus.m_size;
	else
		return -1;
}

wstring FileCommon::StrToUnicode(string str)
{
	wstring result;
	int size;
	bool is_utf8 = FALSE;
	if (str.size() >= 3 && str[0] == -17 && str[1] == -69 && str[2] == -65)
	{
		is_utf8 = true;
		str = str.substr(3);
	}
	if (!is_utf8)
	{
		size = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
		if (size <= 0) return wstring();
		wchar_t* str_unicode = new wchar_t[size + 1];
		MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, str_unicode, size);
		result.assign(str_unicode);
		delete[] str_unicode;
	}
	else
	{
		size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
		if (size <= 0) return wstring();
		wchar_t* str_unicode = new wchar_t[size + 1];
		MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, str_unicode, size);
		result.assign(str_unicode);
		delete[] str_unicode;
	}
	return result;
}

string FileCommon::UnicodeToStr(wstring wstr)
{
	string result;
	int size{ 0 };
	size = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
	if (size <= 0) return string();
	char* str = new char[size + 1];
	WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, str, size, NULL, NULL);
	result.assign(str);
	delete[] str;
	return result;
}

wstring FileCommon::GetExtensionName(wstring fileName)
{
	return fileName.substr(fileName.find_last_of('.')); //获取文件后缀  
}

vector<wstring> FileCommon::Split(wstring str, wchar_t ch, int sub)
{
	vector<wstring> list;
	wstring tempStr;
	for (const auto& c : str)
	{
		if (c != ch)
			tempStr.push_back(c);
		else
		{
			list.push_back(tempStr.substr(sub));
			tempStr.clear();
		}
	}
	//add the last item
	if(!tempStr.empty())
		list.push_back(tempStr.substr(sub)); 
	return list;
}