
// MFC_MD5Compare.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFC_MD5CompareApp:
// �йش����ʵ�֣������ MFC_MD5Compare.cpp
//

class CMFC_MD5CompareApp : public CWinApp
{
public:
	CMFC_MD5CompareApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFC_MD5CompareApp theApp;