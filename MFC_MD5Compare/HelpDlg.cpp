// HelpDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_MD5Compare.h"
#include "HelpDlg.h"
#include "afxdialogex.h"


// HelpDlg �Ի���

IMPLEMENT_DYNAMIC(CHelpDlg, CDialogEx)

CHelpDlg::CHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHelpDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CHelpDlg::~CHelpDlg()
{
}

void CHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHelpDlg, CDialogEx)
END_MESSAGE_MAP()


// HelpDlg ��Ϣ�������
BOOL CHelpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	//ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	//ASSERT(IDM_ABOUTBOX < 0xF000);

	//CMenu* pSysMenu = GetSystemMenu(FALSE);
	//if (pSysMenu != NULL)
	//{
	//	BOOL bNameValid;
	//	CString strAboutMenu;
	//	bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
	//	ASSERT(bNameValid);
	//	if (!strAboutMenu.IsEmpty())
	//	{
	//		pSysMenu->AppendMenu(MF_SEPARATOR);
	//		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	//	}
	//}
	
	//������: ����Ҫ�Ѿ�̬�ؼ�ID���Ƹ�һ��IDC_STATIC1
	//�½�ȫ�ֱ���: 
	
	//��OnInitDialog()��: 
	m_font.CreatePointFont(150, _T("Calibri"));
	GetDlgItem(IDC_STATIC)->SetFont(&m_font);
	//����ɫ:
	//��������WM_CTLCOLOR��Ϣ��Ӧ
	////��OnCtlColor()��:
	//if (pWnd == GetDlgItem(IDC_STATIC))
	//{
	//  pDC->SetTextColor(RGB(255, 0, 0));
	//}

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}