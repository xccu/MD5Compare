// OptionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFC_MD5Compare.h"
#include "OptionDlg.h"
#include "afxdialogex.h"


// OptionDlg dialog

IMPLEMENT_DYNAMIC(COptionDlg, CDialogEx)

COptionDlg::COptionDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(COptionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPORT_EDIT, m_exportEdit);
	DDX_Control(pDX, IDC_EXPORT_BUTTON, m_exportButton);
	DDX_Control(pDX, IDC_REMOVE_BUTTON, m_removeButton);
	DDX_Control(pDX, IDC_EDIT_BUTTON, m_editButton);
	DDX_Control(pDX, IDC_SAVE_BUTTON, m_saveButton);
	DDX_Control(pDX, IDC_TYPE_EDIT, m_typeEdit);
	DDX_Control(pDX, IDC_TYPENAME_EDIT, m_typeNameEdit);
	DDX_Control(pDX, IDC_TYPE_LIST, m_typeList);
	DDX_Control(pDX, IDC_CREATED_CHECK, m_createdCheck);
	DDX_Control(pDX, IDC_MODIFIED_CHECK, m_modifiedCheck);
	DDX_Control(pDX, IDC_REMOVED_CHECK, m_removedCheck);
	DDX_Control(pDX, IDC_FAILED_CHECK, m_failedCheck);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EXPORT_BUTTON, &COptionDlg::OnExportBrowse)
	ON_BN_CLICKED(IDOK, &COptionDlg::OnOk)
	ON_BN_CLICKED(IDC_SAVE_BUTTON, &COptionDlg::OnSaveType)
	ON_BN_CLICKED(IDC_EDIT_BUTTON, &COptionDlg::OnEditType)
	ON_BN_CLICKED(IDC_CREATED_CHECK, &COptionDlg::OnCreatedCheck)
	ON_BN_CLICKED(IDC_MODIFIED_CHECK, &COptionDlg::OnModifiedCheck)
	ON_BN_CLICKED(IDC_REMOVED_CHECK, &COptionDlg::OnRemovedCheck)
	ON_BN_CLICKED(IDC_FAILED_CHECK, &COptionDlg::OnFailedCheck)
	ON_BN_CLICKED(IDC_REMOVE_BUTTON, &COptionDlg::OnRemoveType)
END_MESSAGE_MAP()

BOOL COptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitData();
	InitControls();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void COptionDlg::InitControls()
{
	//加载bitmap图片给button
	m_exportButton.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_OPEN_BITMAP)));
	m_saveButton.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_SAVE_BITMAP)));
	m_editButton.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_EDIT_BITMAP)));
	m_removeButton.SetBitmap(LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_REMOVE_BITMAP)));

	//添加tooltip
	m_toolTip.Create(this);
	m_toolTip.Activate(TRUE);
	m_toolTip.AddTool(&m_exportButton, _T("Browse"));
	m_toolTip.AddTool(&m_saveButton, _T("Save"));
	m_toolTip.AddTool(&m_editButton, _T("Edit"));
	m_toolTip.AddTool(&m_removeButton, _T("Remove"));

	m_createdCheck.SetCheck(m_created);
	m_modifiedCheck.SetCheck(m_modified);
	m_removedCheck.SetCheck(m_removed);
}

void COptionDlg::InitData()
{
	CString keysStr, typeStr;
	int cppRadio, dotnetRadio;

	m_iniHelper.SetPath(_T("config.ini"));
	m_iniHelper.ReadStr(_T("Path"), _T("export"), m_exportPath);
	m_iniHelper.ReadStr(_T("SkipTypes"), _T("keys"), keysStr);

	m_iniHelper.ReadInt(_T("Report"), _T("created"), m_created);
	m_iniHelper.ReadInt(_T("Report"), _T("modified"), m_modified);
	m_iniHelper.ReadInt(_T("Report"), _T("removed"), m_removed);
	m_iniHelper.ReadInt(_T("Report"), _T("failed"), m_failed);

	m_iniHelper.ReadInt(_T("MD5Engine"), _T("cppEngine"), cppRadio);
	m_iniHelper.ReadInt(_T("MD5Engine"), _T("dotNetEngine"), dotnetRadio);
	
	//fill up typeList control
	m_keyList = FileCommon::Split(keysStr.GetString(), ';');
	for (const auto& item : m_keyList)
	{
		typeStr = m_iniHelper.GetTypeString(item);
		m_typeList.AddString(typeStr);
	}

	//fill up export
	m_exportEdit.SetWindowTextW(m_exportPath);

	//fillup engine radiobutton
	((CButton *)GetDlgItem(IDC_CPP_RADIO))->SetCheck(cppRadio);
	((CButton *)GetDlgItem(IDC_DOTNET_RADIO))->SetCheck(dotnetRadio);
}

void COptionDlg::WriteData()
{
	CString sFilePath,typeStr;
	vector<wstring> typeStrList;

	m_exportEdit.GetWindowTextW(sFilePath);
	m_iniHelper.WriteStr(_T("Path"), _T("export"), sFilePath);

	m_iniHelper.WriteInt(_T("Report"), _T("created"), m_created);
	m_iniHelper.WriteInt(_T("Report"), _T("modified"), m_modified);
	m_iniHelper.WriteInt(_T("Report"), _T("removed"), m_removed);
	m_iniHelper.WriteInt(_T("Report"), _T("failed"), m_failed);

	//write Types
	for (int i = 0; i < m_typeList.GetCount(); i++)
	{
		m_typeList.GetText(i, typeStr);
		typeStrList.push_back(typeStr.GetString());
	}
	m_iniHelper.UpdateType(typeStrList);

	//write engine radiobutton
	int cppRadio = ((CButton *)GetDlgItem(IDC_CPP_RADIO))->GetCheck();
	int dotnetRadio = ((CButton *)GetDlgItem(IDC_DOTNET_RADIO))->GetCheck();
	m_iniHelper.WriteInt(_T("MD5Engine"), _T("cppEngine"), cppRadio);
	m_iniHelper.WriteInt(_T("MD5Engine"), _T("dotNetEngine"), dotnetRadio);
}

void COptionDlg::OnExportBrowse()
{
	CFolderPickerDialog dlg;
	CString sFilePath;
	if (dlg.DoModal() == IDOK)
	{
		sFilePath = dlg.GetPathName();
		m_exportEdit.SetWindowTextW(sFilePath);
		UpdateData(FALSE);
	}
}



void COptionDlg::OnOk()
{
	//IniHelper helper;
	//CString type;
	//m_typeEdit.GetWindowTextW(type);
	//helper.ValidateListString(type.GetString());
	WriteData();
	CDialogEx::OnOK();
}

BOOL COptionDlg::PreTranslateMessage(MSG* pMsg)
{
	//显示tooltip
	m_toolTip.RelayEvent(pMsg);
	return CDialog::PreTranslateMessage(pMsg);
}

void COptionDlg::OnSaveType()
{
	// TODO: 在此添加控件通知处理程序代码
	CString typeName, tempStr,typeStr;
	wstring skipTypeStr;
	vector<wstring>::iterator iter;

	m_typeEdit.GetWindowTextW(tempStr);
	m_typeNameEdit.GetWindowTextW(typeName);

	if (typeName.IsEmpty())
	{
		MessageBox(_T("Typename can't be empty"), _T("Warning"), MB_ICONWARNING);
		return;
	}
	if(!m_iniHelper.ValidateTypeListString(tempStr.GetString()))
	{
		MessageBox(_T("Type format incorrect"), _T("Warning"), MB_ICONWARNING);
		return;
	}

	skipTypeStr = m_iniHelper.FormatTypeString(typeName.GetString(), tempStr.GetString());

	//filter file type
	iter = find(m_keyList.begin(), m_keyList.end(), typeName.GetString());
	if (iter != m_keyList.end())  //if key founded,update the item
	{
		
		for (int i = 0; i < m_typeList.GetCount(); i++)
		{
			m_typeList.GetText(i, typeStr);
			tempStr = m_iniHelper.GetTypeKey(typeStr.GetString());
			if (tempStr == typeName)
			{
				m_typeList.DeleteString(i);
				m_typeList.InsertString(i, skipTypeStr.c_str());
				break;
			}
		}
	}
	else //add new item if not founded
		m_typeList.AddString(skipTypeStr.c_str());

	//m_iniHelper.WriteTypes(typeName.GetString(), typelist.GetString());
	m_typeNameEdit.SetWindowTextW(_T(""));
	m_typeEdit.SetWindowTextW(_T(""));
}


void COptionDlg::OnEditType()
{
	CString keyStr,cTypeStr;
	wstring  typeStr;
	vector<wstring> typeList;
	int idx = m_typeList.GetCurSel();
	
	m_typeList.GetText(idx, cTypeStr);
	m_iniHelper.ParseTypeList(cTypeStr, keyStr, typeList);
	for (const auto& item : typeList)
	{
		typeStr += (_T('*')+item+_T(';'));
	}
	typeStr.erase(typeStr.length()-1,1);
	cTypeStr = CString(typeStr.c_str());
	
	m_typeNameEdit.SetWindowTextW(keyStr);
	m_typeEdit.SetWindowTextW(cTypeStr);
}

void COptionDlg::OnRemoveType()
{
	// TODO: 在此添加控件通知处理程序代码
	int index = m_typeList.GetCurSel();
	CString keyStr, cTypeStr;
	vector<wstring> typeList;

	m_typeList.GetText(index, cTypeStr);
	m_iniHelper.ParseTypeList(cTypeStr, keyStr, typeList);
	m_typeList.DeleteString(index);
}

void COptionDlg::OnCreatedCheck()
{
	m_created = m_createdCheck.GetCheck();
}

void COptionDlg::OnModifiedCheck()
{
	m_modified = m_modifiedCheck.GetCheck();
}

void COptionDlg::OnRemovedCheck()
{
	m_removed = m_removedCheck.GetCheck();
}

void COptionDlg::OnFailedCheck()
{
	m_failed = m_failedCheck.GetCheck();
}

