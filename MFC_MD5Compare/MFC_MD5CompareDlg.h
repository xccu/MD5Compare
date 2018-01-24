
// MFC_MD5CompareDlg.h : 头文件
//

#pragma once
#include "shlobj.h" 
#include <STRING>
#include "afxwin.h"
#include "ResourceHelper.h"
#include "FileCommon.h"
#include "IniHelper.h"
#include "OptionDlg.h"
#include "CppMD5Engine.h"
#include "DotNetMD5Engine.h"
#include "HelpDlg.h"
//#include "afxcmn.h"

enum compareResult
{
	same,
	different,
	skip,
	failed,
};

// CMFC_MD5CompareDlg 对话框
class CMFC_MD5CompareDlg : public CDialogEx
{
// 构造
public:
	CMFC_MD5CompareDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CMFC_MD5CompareDlg();						// 析构函数

// 对话框数据
	enum { IDD = IDD_MFC_MD5COMPARE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//控件添加变量
protected:
	HBITMAP m_openBitmap;
	CEdit m_sourceEdit;
	CEdit m_targetEdit;
	CEdit m_reportEdit;
	CButton m_sourceButton;
	CButton m_targetButton;
	CProgressCtrl m_compareProgress;
	CToolBar m_wndToolBar;
	CToolTipCtrl m_toolTip;
	CComboBox m_sizeCombo;
	CComboBox m_skipCombo;
	CButton m_sizeCheck;
	CStatusBar m_statusBar;

//成员变量
protected:
	MD5Engine *m_engine;
	HANDLE m_hThread;
	IniHelper m_iniHelper;
	BOOL m_isPaused;
	CString m_engineStr;
	ThreadParameters *m_threadPara;
public:
	static int m_created;
	static int m_modified;
	static int m_removed;
	static int m_failed;

//成员函数
protected:
	void InitControls();
	void InitData();
	void InitOptionFile();
	void BrowseCurrentAllFile(vector<CString> &pathList,CString strDir);
	void DeleteFiles();
	void EnableControls(BOOL enable);	
	static DWORD __stdcall RunThread(LPVOID lpParameter);
	static DWORD __stdcall ExportThread(LPVOID lpParameter);
	static compareResult CompareFile(CString sPath, CString tPath, MD5Engine *engine);
	static BOOL IsSkipFile(CString sPath, SkipInfo skip);
	static void SendToEdit(CString fileStr, CDialog *dlg);
	void OpenSource(CString strFilePath);
	void OpenTarget(CString strFilePath);

//消息映射函数
protected:
	afx_msg void OnBrowseSource();
	afx_msg void OnBrowseTarget();
	afx_msg void OnRun();
	afx_msg void OnPause();
	afx_msg void OnStop();
	afx_msg void OnUserHelp();
	afx_msg LRESULT OnFinished(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSave();
	afx_msg void OnOption();
	afx_msg void OnExport();
	afx_msg LRESULT OnProgressCtrl(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnStatusBar(WPARAM wParam, LPARAM lParam);
	afx_msg void OnMaxSizeCheck();
	afx_msg void OnSizeComboChanged();
	afx_msg void OnSkipComboChanged();
	afx_msg BOOL OnToolTipText(UINT, NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDropFiles(HDROP hDropInfo);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
