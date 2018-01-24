
// MFC_MD5CompareDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFC_MD5Compare.h"
#include "MFC_MD5CompareDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFC_MD5CompareDlg �Ի���

//��̬��Ա������ʼ��
int CMFC_MD5CompareDlg::m_created = 0;
int CMFC_MD5CompareDlg::m_modified = 0;
int CMFC_MD5CompareDlg::m_removed = 0;
int CMFC_MD5CompareDlg::m_failed = 0;

CMFC_MD5CompareDlg::CMFC_MD5CompareDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFC_MD5CompareDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFC_MD5CompareDlg::~CMFC_MD5CompareDlg()
{
	delete m_threadPara;
	delete m_engine;
}

void CMFC_MD5CompareDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SOURCE_EDIT, m_sourceEdit);
	DDX_Control(pDX, IDC_TARGET_EDIT, m_targetEdit);
	DDX_Control(pDX, IDC_REPORT_EDIT, m_reportEdit);
	DDX_Control(pDX, IDC_COMPARE_PROGRESS, m_compareProgress);
	DDX_Control(pDX, IDC_SOURCE_BUTTON, m_sourceButton);
	DDX_Control(pDX, IDC_TARGET_BUTTON, m_targetButton);
	DDX_Control(pDX, IDC_SIZE_COMBO, m_sizeCombo);
	DDX_Control(pDX, IDC_SIZE_CHECK, m_sizeCheck);
	DDX_Control(pDX, IDC_SKIP_COMBO, m_skipCombo);
}

BEGIN_MESSAGE_MAP(CMFC_MD5CompareDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SOURCE_BUTTON, &CMFC_MD5CompareDlg::OnBrowseSource)
	ON_BN_CLICKED(IDC_TARGET_BUTTON, &CMFC_MD5CompareDlg::OnBrowseTarget)
	ON_BN_CLICKED(IDC_SIZE_CHECK, &CMFC_MD5CompareDlg::OnMaxSizeCheck)
	ON_CBN_SELCHANGE(IDC_SIZE_COMBO, &CMFC_MD5CompareDlg::OnSizeComboChanged)
	ON_CBN_SELCHANGE(IDC_SKIP_COMBO, &CMFC_MD5CompareDlg::OnSkipComboChanged)
	ON_MESSAGE(WM_USER_PROGRESS, &CMFC_MD5CompareDlg::OnProgressCtrl)
	ON_MESSAGE(WM_USER_FINISHED, &CMFC_MD5CompareDlg::OnFinished)
	ON_MESSAGE(WM_USER_STATUS, &CMFC_MD5CompareDlg::OnStatusBar)
	ON_COMMAND(ID_FILE_SAVE, &CMFC_MD5CompareDlg::OnSave)
	ON_COMMAND(ID_FILE_EXPORT, &CMFC_MD5CompareDlg::OnExport)
	ON_COMMAND(ID_FILE_OPTION, &CMFC_MD5CompareDlg::OnOption)
	ON_COMMAND(ID_FILE_HELP,&CMFC_MD5CompareDlg::OnUserHelp)
	ON_COMMAND(ID_FILE_RUN, &CMFC_MD5CompareDlg::OnRun)
	ON_COMMAND(ID_FILE_PAUSE, &CMFC_MD5CompareDlg::OnPause)
	ON_COMMAND(ID_FILE_STOP, &CMFC_MD5CompareDlg::OnStop)
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0, OnToolTipText)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CMFC_MD5CompareDlg ��Ϣ�������

BOOL CMFC_MD5CompareDlg::OnInitDialog()
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


	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitData();
	InitControls();
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFC_MD5CompareDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFC_MD5CompareDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFC_MD5CompareDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#pragma region ��Ա��������
void CMFC_MD5CompareDlg::InitControls()
{
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	// ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//����bitmapͼƬ��button
	m_openBitmap = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_OPEN_BITMAP));
	m_sourceButton.SetBitmap(m_openBitmap);
	m_targetButton.SetBitmap(m_openBitmap);

	//���tooltip
	m_toolTip.Create(this);
	m_toolTip.Activate(TRUE);
	m_toolTip.AddTool(&m_sourceButton, _T("Browse"));
	m_toolTip.AddTool(&m_targetButton, _T("Browse"));

	//��ʼ��������
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE
		| CBRS_ALIGN_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_TOOLBAR))  //ָ��������ID��
	{
		DWORD d = GetLastError();
		TRACE0("Failed to create toolbar/n");
		return;     // fail to create
	}
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	//����ͼƬ��ToolBar
	CImageList ImageList;
	ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, 2, 2);
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_SAVE));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_EXPORT));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_OPTION));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_RUN));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_PAUSE));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_STOP));
	ImageList.Add(AfxGetApp()->LoadIcon(IDI_HELP));
	m_wndToolBar.GetToolBarCtrl().SetImageList(&ImageList);
	ImageList.Detach();

	//���� pause �� stop
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_PAUSE, FALSE);
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_STOP, FALSE);

	//����statusBar
	UINT BASED_CODE indicators[] = { 1,2 };
	m_statusBar.Create(this, WS_CHILD | WS_VISIBLE | CBRS_BOTTOM, IDC_USER_STATUSBAR);
	m_statusBar.SetIndicators(indicators, 2);

	//�������1��Ϣ ,��һ�����,���Ϊ1,������ʾ,���Ϊ100
	m_statusBar.SetPaneInfo(0, 1, SBPS_NORMAL, 580);
	//�������2��Ϣ,�ڶ������,���Ϊ2,�Զ�������ʾ,�տ�ʼ���Ϊ200
	m_statusBar.SetPaneInfo(1, 2, SBPS_STRETCH, 100);

	//����״̬��λ��
	CRect rect = { 0 };
	GetClientRect(&rect);
	//rect.bottom - 20��״̬���ĸ߶�λ��,20��״̬�ĸ߶�
	m_statusBar.MoveWindow(0, rect.bottom - 20, rect.right, 20);

	m_statusBar.SetPaneText(0, _T("Ready"));
	m_statusBar.SetPaneText(1, m_engineStr);
}

void CMFC_MD5CompareDlg::InitData()
{
	 m_isPaused = FALSE;
	 m_iniHelper.SetPath(_T("config.ini"));
	

	//���������ļ������û�оʹ���һ��
	if (!FileCommon::FindFile(FileCommon::GetModulePath() + _T("config.ini")))
	{
		m_iniHelper.Create();
	}

	m_threadPara = new ThreadParameters;
	m_threadPara->dlg = this;

	m_iniHelper.ReadThreadParameters(*m_threadPara);
	m_sizeCheck.SetCheck(m_threadPara->skip.isCheckSize);
	m_sizeCombo.EnableWindow(m_threadPara->skip.isCheckSize);
	m_sourceEdit.SetWindowTextW(m_threadPara->sourcePath);
	m_targetEdit.SetWindowTextW(m_threadPara->targetPath);

	CString comboStr;
	for (int i = 1, size = 1; i < 8; i++)
	{
		comboStr.Format(_T("%d"), size);
		m_sizeCombo.AddString(comboStr);
		size = pow(2, i);
	}
	m_sizeCombo.SetCurSel(m_threadPara->skip.maxSizeIndex);

	//fill up typeList control
	InitOptionFile();
}

void CMFC_MD5CompareDlg::InitOptionFile()
{
	CString keysStr, typeStr, selectedType;
	vector<wstring> keyList;
	int sel = 0;
	int cppRadio, dotnetRadio;
	m_iniHelper.ReadInt(_T("MD5Engine"), _T("cppEngine"), cppRadio);
	m_iniHelper.ReadInt(_T("MD5Engine"), _T("dotNetEngine"), dotnetRadio);
	m_iniHelper.ReadStr(_T("SkipTypes"), _T("keys"), keysStr);
	m_iniHelper.ReadStr(_T("SkipTypes"), _T("selected"), selectedType);
	
	//set MD5 engine
	if (m_engine)
		delete m_engine;
	if (cppRadio)
	{
		m_engine = new CppMD5Engine;
		m_engineStr = _T("Engine: Cpp");
	}
	else if (dotnetRadio)
	{
		m_engine = new DotNetMD5Engine;
		m_engineStr = _T("Engine: .Net");
	}

	m_threadPara->engine = (LPVOID*)m_engine;

	//set Type file
	m_skipCombo.ResetContent();
	m_skipCombo.AddString(_T("None"));
	m_threadPara->skip.typeList.clear();

	keyList = FileCommon::Split(keysStr.GetString(), ';');
	for (int i = 0; i<keyList.size(); i++)
	{
		typeStr = m_iniHelper.GetTypeString(keyList[i]);
		m_skipCombo.AddString(typeStr);
		if (m_iniHelper.GetTypeKey(typeStr.GetString()) == selectedType)
		{
			sel = i + 1;
			m_iniHelper.ParseTypeList(typeStr, keysStr, m_threadPara->skip.typeList);
		}
	}
	m_skipCombo.SetCurSel(sel);

}

void CMFC_MD5CompareDlg::BrowseCurrentAllFile(vector<CString> &pathList, CString strDir)
{
	if (strDir == _T(""))
	{
		return;
	}
	else
	{
		if (strDir.Right(1) != _T("\\"))
			strDir += L"\\";
		strDir = strDir + _T("*.*");
	}

	CFileFind finder;
	CString strPath;
	BOOL bWorking = finder.FindFile(strDir);

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		strPath = finder.GetFilePath();
		if (finder.IsDirectory() && !finder.IsDots())
			BrowseCurrentAllFile(pathList, strPath); //�ݹ����  
		else if (!finder.IsDirectory() && !finder.IsDots())
		{
			//strPath������Ҫ��ȡ���ļ�·��  
			pathList.push_back(strPath);
		}
	}
}

void CMFC_MD5CompareDlg::DeleteFiles()
{
	//m_compareProgress.SetPos(0);
	m_isPaused = FALSE;
	m_created = 0;
	m_modified = 0;
	m_removed = 0;
	m_failed = 0;

	m_threadPara->sourceList.clear();
	m_threadPara->targetList.clear();
}

void CMFC_MD5CompareDlg::EnableControls(BOOL enable)
{
	m_sourceEdit.EnableWindow(enable);
	m_targetEdit.EnableWindow(enable);
	m_sourceButton.EnableWindow(enable);
	m_targetButton.EnableWindow(enable);
	m_sizeCheck.EnableWindow(enable);
	m_sizeCombo.EnableWindow((m_sizeCheck.GetCheck() && m_sizeCheck.IsWindowEnabled()) ? TRUE : FALSE);
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_RUN, enable);
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_PAUSE, !enable);
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_STOP, !enable);
}

DWORD __stdcall CMFC_MD5CompareDlg::RunThread(LPVOID lpParameter)
{
	ThreadParameters *threadParas;
	MD5Engine *engine;
	CString tempPath, sourcePath, targetPath, reportStr,comparingStr;
	compareResult cResult;

	threadParas = (ThreadParameters*)lpParameter;
	engine = (MD5Engine*)threadParas->engine;

	threadParas->exportList.clear();
	sourcePath = threadParas->sourcePath;
	targetPath = threadParas->targetPath;

	for (int i = 0; i< threadParas->sourceList.size(); i++)
	{
		::PostMessage(threadParas->dlg->m_hWnd, WM_USER_PROGRESS, NULL, NULL);

		tempPath = threadParas->sourceList[i];
		tempPath.Replace(sourcePath, targetPath);

		//skip file
		if (IsSkipFile(threadParas->sourceList[i], threadParas->skip)) continue;

		//show on StatusBar
		comparingStr.Format(_T("Comparing: %s"), threadParas->sourceList[i]);
		::PostMessage(threadParas->dlg->m_hWnd, WM_USER_STATUS, (LPARAM)comparingStr.GetBuffer(20), 0);

		//target file was removed
		if (threadParas->removed)
		{
			if (!FileCommon::FindFile(tempPath.GetString()))
			{
				m_removed++;
				SendToEdit(_T("Removed:\t") + tempPath + _T("\n"), threadParas->dlg);
				continue;
			}
		}

		if (threadParas->modified)
		{
			cResult = CompareFile(threadParas->sourceList[i], tempPath, engine);
			switch (cResult)
			{
				case different:	//target file was modified
					m_modified++;
					threadParas->exportList.push_back(tempPath);
					SendToEdit(_T("Modified:\t") + tempPath + _T("\n"), threadParas->dlg);
					break;
				case failed:	//compare failed
					m_failed++;
					if (threadParas->failed)
						SendToEdit(_T("Failed:\t") + tempPath + _T("\n"), threadParas->dlg);
					break;
				default: break;
			}
		}
	}

	//target file was added
	for (int i = 0; i<threadParas->targetList.size(); i++)
	{
		comparingStr.Format(_T("Comparing: %s"), threadParas->targetList[i]);
		::PostMessage(threadParas->dlg->m_hWnd, WM_USER_PROGRESS, NULL, NULL);
		::PostMessage(threadParas->dlg->m_hWnd, WM_USER_STATUS, (LPARAM)comparingStr.GetBuffer(20), 0);

		tempPath = threadParas->targetList[i];
		tempPath.Replace(targetPath, sourcePath);
		//skip file
		if (IsSkipFile(threadParas->targetList[i], threadParas->skip)) continue;
		if (threadParas->created)
		{
			if (!FileCommon::FindFile(tempPath.GetString()))
			{
				m_created++;
				threadParas->exportList.push_back(threadParas->targetList[i]);
				SendToEdit(_T("Created:\t") + threadParas->targetList[i] + _T("\n"), threadParas->dlg);
			}
		}
	}

	reportStr.Format(_T("Finished:\tcreated:%d modified:%d removed:%d"), m_created, m_modified, m_removed);
	SendToEdit(reportStr, threadParas->dlg);
	::PostMessage(threadParas->dlg->m_hWnd, WM_USER_FINISHED, NULL, NULL);
	::PostMessage(threadParas->dlg->m_hWnd, WM_USER_STATUS, NULL, 0);
	return 0;
}

DWORD CMFC_MD5CompareDlg::ExportThread(LPVOID lpParameter)
{
	ThreadParameters *threadParas;
	threadParas = (ThreadParameters*)lpParameter;
	FileCommon common;
	CString exportingStr;

	for (const auto& item : threadParas->exportList)
	{
		exportingStr.Format(_T("Exporting: %s"), item);
		::PostMessage(threadParas->dlg->m_hWnd, WM_USER_PROGRESS, NULL, NULL);
		::PostMessage(threadParas->dlg->m_hWnd, WM_USER_STATUS, (LPARAM)exportingStr.GetBuffer(20), 0);
		if (!common.ExportFile(threadParas->targetPath.GetString(), item.GetString(), threadParas->exportPath.GetString()))
		{
			::MessageBox(threadParas->dlg->m_hWnd,_T("Export Failed:\n") + item, _T("Error"), MB_ICONERROR);
			return 0;
		}
	}
	::PostMessage(threadParas->dlg->m_hWnd, WM_USER_STATUS, NULL, 0);
	::MessageBox(threadParas->dlg->m_hWnd,_T("Export Completed"), _T("Note"), MB_ICONINFORMATION);
	return 0;
}

compareResult CMFC_MD5CompareDlg::CompareFile(CString sPath, CString tPath, MD5Engine *engine)
{
	try
	{
		wstring oldStr, newStr;
		FileCommon FileCommon;

		FileCommon.SetMd5Engine(engine);

		oldStr = FileCommon.ReadFile(sPath);
		newStr = FileCommon.ReadFile(tPath);

		if (FileCommon.Compare(oldStr, newStr))
			return same;
		else
			return different;
	}
	catch (exception& e)
	{
		return failed;
	}
}

BOOL CMFC_MD5CompareDlg::IsSkipFile(CString sPath, SkipInfo skip)
{
	long size = FileCommon::GetFileSize(sPath);
	wstring extension = FileCommon::GetExtensionName(sPath.GetString());
	vector<wstring>::iterator iter;

	//filter file type
	iter = find(skip.typeList.begin(), skip.typeList.end(), extension);
	if (iter != skip.typeList.end())
		return TRUE;
	
	//filter file size
	if (!skip.isCheckSize) return FALSE;
	long maxSize = pow(2, skip.maxSizeIndex) * 1024 * 1024;
	if (size > maxSize)
		return TRUE;
	
	return FALSE;
}

void CMFC_MD5CompareDlg::SendToEdit(CString fileStr,CDialog *dlg)
{
	HWND hWnd = dlg->m_hWnd; //��ȡ��ǰ���ھ��
	HWND hEdit = ::GetDlgItem(hWnd, IDC_REPORT_EDIT); //��ȡEdit�ؼ����

	//LPTSTR lpszProgress = new TCHAR[fileStr.GetLength() + 1];
	//_tcscpy_s(lpszProgress, fileStr.GetLength() + 1, fileStr);
	//::PostMessage(hEdit, WM_SETTEXT, (LPARAM)lpszProgress,0);
	//
	//delete[] lpszProgress;
													  
	for (int i = 0; i<fileStr.GetLength(); )	//������Ϣ�� IDC_REPORT_EDIT
	{
		if (fileStr[i]< 128)
		{
			::SendMessage(hEdit, WM_CHAR, fileStr[i], 0);
			
		}
		else
		{
			::SendMessage(hEdit, WM_CHAR, fileStr[i], 0);
			::SendMessage(hEdit, WM_CHAR, fileStr[i + 1], 0);
			i++;
		}
		i++;
	}
}
void CMFC_MD5CompareDlg::OpenSource(CString strFilePath)
{
		m_sourceEdit.SetWindowTextW(strFilePath);
		m_iniHelper.WriteStr(_T("Path"), _T("source"), strFilePath);
		UpdateData(FALSE);
}
void CMFC_MD5CompareDlg::OpenTarget(CString strFilePath)
{
		m_targetEdit.SetWindowTextW(strFilePath);
		m_iniHelper.WriteStr(_T("Path"), _T("target"), strFilePath);
		UpdateData(FALSE);
}
#pragma endregion

#pragma region ��Ϣӳ�亯������
void CMFC_MD5CompareDlg::OnBrowseSource()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		OpenSource(dlg.GetPathName());
	} 
}

void CMFC_MD5CompareDlg::OnBrowseTarget()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFolderPickerDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		OpenTarget(dlg.GetPathName());
	} 
}

void CMFC_MD5CompareDlg::OnRun()
{
	//std::thread t1(&CMFC_MD5CompareDlg::RunThread, this);
	//t1.detach();

	//reset ProgressCtrl
	m_compareProgress.SetPos(0);

	if (m_isPaused)
	{
		m_isPaused = FALSE;
		EnableControls(FALSE);
		ResumeThread(m_hThread);
		SendToEdit(_T("Resume\n"), this);
		return;
	}

	m_sourceEdit.GetWindowTextW(m_threadPara->sourcePath);
	m_targetEdit.GetWindowTextW(m_threadPara->targetPath);

	//whether path is empty
	if (m_threadPara->sourcePath.IsEmpty() || m_threadPara->targetPath.IsEmpty())
	{
		MessageBox(_T("You must select a source folder and a target folder"), _T("Warning"), MB_ICONWARNING);
		return;
	}
	//whether path is exist
	if (!FileCommon::FindFile(m_threadPara->sourcePath.GetString()) || !FileCommon::FindFile(m_threadPara->targetPath.GetString()))
	{
		MessageBox(_T("The path you choosen doesn't exist.Please choose the right one"), _T("Warning"), MB_ICONWARNING);
		return;
	}

	BrowseCurrentAllFile(m_threadPara->sourceList, m_threadPara->sourcePath);
	BrowseCurrentAllFile(m_threadPara->targetList, m_threadPara->targetPath);

	m_reportEdit.SetWindowTextW(_T(""));
	m_compareProgress.SetRange(0, m_threadPara->sourceList.size() + m_threadPara->targetList.size());
	m_compareProgress.SetStep(1);

	EnableControls(FALSE);
	m_hThread = CreateThread(NULL, 0, RunThread, m_threadPara, 0, NULL);
}

void CMFC_MD5CompareDlg::OnPause()
{
	SuspendThread(m_hThread);
	m_isPaused = TRUE;
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_RUN, TRUE);
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_PAUSE, FALSE);
	m_wndToolBar.GetToolBarCtrl().EnableButton(ID_FILE_STOP, TRUE);

	//SendToEdit(_T("Paused\n"), this);

	::PostMessage(this->m_hWnd, WM_USER_STATUS, NULL, 1);
}

void CMFC_MD5CompareDlg::OnStop()
{
	TerminateThread(m_hThread,NULL);
	CString report;
	m_compareProgress.SetPos(0);
	//m_compareProgress.SetRange(0, m_sourceList.size() + m_targetList.size());
	report.Format(_T("Stoped:\t created:%d modified:%d removed:%d"), m_created, m_modified, m_removed);
	SendToEdit(report,this);

	//CString stopStr = _T("Stoped");
	::PostMessage(this->m_hWnd, WM_USER_STATUS, NULL, 2);
	
	DeleteFiles();
	EnableControls(TRUE);
}

void CMFC_MD5CompareDlg::OnUserHelp()
{
	CHelpDlg dlg;
	dlg.DoModal();
}

LRESULT CMFC_MD5CompareDlg::OnFinished(WPARAM wParam, LPARAM lParam)
{
	DeleteFiles();
	EnableControls(TRUE);
	return 0;
}

void CMFC_MD5CompareDlg::OnSave()
{
	// TODO: Add your control notification handler code here
	CString path,saveStr;
	FileCommon fileCommon;
	m_reportEdit.GetWindowTextW(saveStr);
	//set Filter
	const wchar_t* filter = _T("Text Documents(*.txt)|*.txt|Log Files(*.log)|*.log||");
	CFileDialog fileDlg(FALSE, _T("txt"), L"NoTitle", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, this);
	//show  fileDialog
	if (IDOK == fileDlg.DoModal())
	{
		path = fileDlg.GetPathName();
		fileCommon.WriteFile(path, saveStr.GetString());
	}
}

void CMFC_MD5CompareDlg::OnOption()
{
	COptionDlg dlg;
	dlg.DoModal();

	m_iniHelper.ReadThreadParameters(*m_threadPara);
	InitOptionFile();
	m_statusBar.SetPaneText(1, m_engineStr);
}

void CMFC_MD5CompareDlg::OnExport()
{
	//reset ProgressCtrl
	m_compareProgress.SetPos(0);

	m_iniHelper.ReadStr(_T("Path"), _T("target"), m_threadPara->targetPath);
	m_iniHelper.ReadStr(_T("Path"), _T("export"), m_threadPara->exportPath);

	m_reportEdit.SetWindowTextW(_T(""));
	m_compareProgress.SetRange(0, m_threadPara->exportList.size());
	m_compareProgress.SetStep(1);

	m_hThread = CreateThread(NULL, 0, ExportThread, m_threadPara, 0, NULL);
}

LRESULT CMFC_MD5CompareDlg::OnProgressCtrl(WPARAM wParam, LPARAM lParam)
{
	//for (int i = 0; i<100; i++)
	//{
		//m_compareProgress.SetStep(1);
		//m_compareProgress.StepIt();
		//Sleep(100);
	//}
	//m_compareProgress.SetStep(0);
	//m_compareProgress.SetPos(wParam);
	m_compareProgress.StepIt();
	return LRESULT();
}

LRESULT CMFC_MD5CompareDlg::OnStatusBar(WPARAM wParam, LPARAM lParam)
{
	CString str((wchar_t*)wParam);

	if(wParam!=NULL)
		m_statusBar.SetPaneText(0, str);
	else
	{
		switch (lParam)
		{
		case 0:
			m_statusBar.SetPaneText(0, _T("Completed")); break;
		case 1:
			m_statusBar.SetPaneText(0, _T("Paused")); break;
		case 2:
			m_statusBar.SetPaneText(0, _T("Stoped")); break;
		default:
			break;
		}	
	}
	return LRESULT();
}

void CMFC_MD5CompareDlg::OnMaxSizeCheck()
{
	m_threadPara->skip.isCheckSize = m_sizeCheck.GetCheck();
	m_sizeCombo.EnableWindow(m_threadPara->skip.isCheckSize);
	m_iniHelper.WriteInt(_T("SkipSize"), _T("checkMaxSize"), m_threadPara->skip.isCheckSize);
}

void CMFC_MD5CompareDlg::OnSizeComboChanged()
{
	m_threadPara->skip.maxSizeIndex = m_sizeCombo.GetCurSel();
	m_iniHelper.WriteInt(_T("SkipSize"), _T("maxSizeIndex"), m_threadPara->skip.maxSizeIndex);
}

void CMFC_MD5CompareDlg::OnSkipComboChanged()
{
	CString typeStr,keyStr,listStr;
	//int index = m_skipCombo.GetCurSel();
	m_skipCombo.GetWindowTextW(typeStr);
	m_iniHelper.ParseTypeList(typeStr, keyStr, m_threadPara->skip.typeList);
	m_iniHelper.WriteStr(_T("SkipTypes"), _T("selected"), keyStr);
}

BOOL CMFC_MD5CompareDlg::OnToolTipText(UINT, NMHDR * pNMHDR, LRESULT * pResult)
{
	//���ù�����������ʾ
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
	CString str;
	UINT nID = pNMHDR->idFrom; //��ȡ��������ťID  
	if (nID)
	{
		//nID = m_wndToolBar.CommandToIndex(nID); //����ID��ȡ��ť����  
		if (nID != -1)
		{
			switch (nID)
			{
				case ID_FILE_EXPORT:
					pTTT->lpszText = L"Export modified files";	break;
				case ID_FILE_SAVE:
					pTTT->lpszText = L"Save report";			break;
				case ID_FILE_OPTION:
					pTTT->lpszText = L"Option";					break;
				case ID_FILE_RUN:
					pTTT->lpszText = L"Run";					break;
				case ID_FILE_PAUSE:
					pTTT->lpszText = L"Pause";					break;
				case ID_FILE_STOP:
					pTTT->lpszText = L"Stop";					break;
				case ID_FILE_HELP:
					pTTT->lpszText = L"Help";					break;
				default:
					pTTT->lpszText = L" ";						break;

			}
			//��ȡ�������ı�             
			pTTT->hinst = AfxGetResourceHandle();
			return(TRUE);
		}
	}
	return(FALSE);
}

void CMFC_MD5CompareDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TCHAR file_path[MAX_PATH];
	int drop_count = DragQueryFile(hDropInfo, -1, NULL, 0);		//ȡ�ñ��϶��ļ�����Ŀ
	if (drop_count <= 1)		//����϶��������ļ�ֻ��1��
	{
		DragQueryFile(hDropInfo, 0, file_path, MAX_PATH);		//��ȡ���ļ�
		OpenSource(file_path);		//�򿪵�1���ļ�
	}
	else		//����϶��������ļ�Ϊ1������
	{
		DragQueryFile(hDropInfo, 0, file_path, MAX_PATH);		//��ȡ��1���ļ�
		OpenSource(file_path);		//�򿪵�1���ļ�

		DragQueryFile(hDropInfo, 1, file_path, MAX_PATH);		//��ȡ��2���ļ�
		OpenTarget(file_path);		//�򿪵�2���ļ�
	}
	DragFinish(hDropInfo); //�ϷŽ�����,�ͷ��ڴ�

	CDialogEx::OnDropFiles(hDropInfo);
}

BOOL CMFC_MD5CompareDlg::PreTranslateMessage(MSG* pMsg)
{
	//��ʾtooltip
	m_toolTip.RelayEvent(pMsg);
	//���μ�����Ϣ
	if (pMsg->message == WM_KEYDOWN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
#pragma endregion
