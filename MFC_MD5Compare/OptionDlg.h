#pragma once
#include "Resource.h"
#include "ResourceHelper.h"
#include "IniHelper.h"
#include "afxwin.h"

// OptionDlg dialog

class COptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COptionDlg();

// Dialog Data
	enum { IDD = IDD_OPTION_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

//�ؼ���ӱ���
protected:
	HICON m_hIcon;
	CToolTipCtrl m_toolTip;
	CButton m_exportButton;
	CButton m_saveButton;
	CButton m_editButton;
	CButton m_removeButton;
	CEdit m_exportEdit;
	CEdit m_typeEdit;
	CEdit m_typeNameEdit;
	CListBox m_typeList;
	CButton m_createdCheck;
	CButton m_modifiedCheck;
	CButton m_removedCheck;
	CButton m_failedCheck;

//��Ա����
protected:
	IniHelper m_iniHelper;
	CString m_exportPath;
	vector<wstring> m_keyList;
	BOOL m_created;
	BOOL m_modified;
	BOOL m_removed;
	BOOL m_failed;

//��Ա����
protected:
	void InitControls();
	void InitData();
	void WriteData();

//��Ϣӳ�亯��
protected:
	afx_msg void OnExportBrowse();
	afx_msg void OnSaveType();
	afx_msg void OnEditType();
	afx_msg void OnRemoveType();
	afx_msg void OnCreatedCheck();
	afx_msg void OnModifiedCheck();
	afx_msg void OnRemovedCheck();
	afx_msg void OnFailedCheck();
	afx_msg void OnOk();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
