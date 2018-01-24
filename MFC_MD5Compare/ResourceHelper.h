#pragma once
#include <vector>
#include <fstream>
//#include <thread>
#include "stdlib.h"
#include <windows.h>
#include <stdio.h>
#include <Regex>

using namespace std;

struct SkipInfo
{
	BOOL isCheckSize;
	int maxSizeIndex;
	vector<wstring> typeList;
};

struct ThreadParameters
{
	CString sourcePath;
	CString targetPath;
	CString exportPath;
	SkipInfo skip;
	CDialog *dlg;
	LPVOID *engine;
	BOOL created;
	BOOL modified;
	BOOL removed;
	BOOL failed;
	vector<CString> sourceList;
	vector<CString> targetList;
	vector<CString> exportList;
};

#define WM_USER_PROGRESS    (WM_USER + 1001)  
#define WM_USER_FINISHED	(WM_USER + 1002)   
#define WM_USER_STATUS		(WM_USER + 1003)   