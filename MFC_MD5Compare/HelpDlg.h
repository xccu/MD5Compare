#pragma once


// HelpDlg �Ի���

class CHelpDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHelpDlg)

public:
	CHelpDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHelpDlg();

// �Ի�������
	enum { IDD = IDD_HELP_DIALOG };

protected:
	HICON m_hIcon;
	CFont m_font;
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
