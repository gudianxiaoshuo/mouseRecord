// MouseSimulateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MouseSimulate.h"
#include "MouseSimulateDlg.h"
#include "winuser.h"
#include "windows.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseSimulateDlg dialog

CMouseSimulateDlg::CMouseSimulateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseSimulateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMouseSimulateDlg)
	m_iLoopDestCount = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bSimulating = FALSE;
	m_iEventPos   = -1;
	m_dwSimulateStartTime = 0;
}

void CMouseSimulateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMouseSimulateDlg)
	DDX_Control(pDX, IDC_EDIT_LOOP_COUNT, m_LoopCountCtl);
	DDX_Text(pDX, IDC_EDIT_LOOP_COUNT, m_iLoopDestCount);
	DDV_MinMaxUInt(pDX, m_iLoopDestCount, 1, 4294967295);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMouseSimulateDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseSimulateDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_SHOW_MAIN_DLG, OnShowMainDlg)
	ON_COMMAND(ID_QUIT_PROGRAM, OnQuitProgram)
	ON_WM_TIMER()
	ON_BN_CLICKED(ID_START_RECORD, OnStartRecord)
	ON_BN_CLICKED(ID_START_SIMULATE, OnStartSimulate)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_HOTKEY, OnHotKey)	
	ON_MESSAGE(WM_MSG_NOTIFYICON, OnMsgNotifyIcon)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseSimulateDlg message handlers

BOOL CMouseSimulateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	m_NotifyIcon.m_pWnd = this;
	m_NotifyIcon.AddIconToTaskbar("���ģ��");
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	CString strComment = "���ģ�����ʹ�ò���: \r\n"
		"1���� Ctrl+J ��ʼ��¼��궯��;\r\n"
		"2���� Ctrl+T ֹͣ��¼��궯��;\r\n"
		"3���� Ctrl+B ��ʼ���ողż�¼����궯�������ظ�;\r\n"
		"4���� Ctrl+E ֹͣ���ģ��,���������Ի���\r\n"
		"ע���˳���Ŀǰֻ�ṩ����ƶ������������º͵����ģ��";
	CStatic *pStaticWnd = (CStatic*)GetDlgItem(IDC_STATIC_COMMENT);
	if( pStaticWnd )
	{
		pStaticWnd->SetWindowText(strComment);
	}
	pStaticWnd = (CStatic*)GetDlgItem(IDC_STATIC_DES);
	if( pStaticWnd )
	{
		pStaticWnd->SetWindowText("");
	}
	
	RegisterMyHotkey();
	m_MouseHook.InstallHook();
	::SetTimer(GetSafeHwnd(), 1, 2, NULL);
	return TRUE;  
}

void CMouseSimulateDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		//������Щ��Ϣ���ᵼ�³����ͼ����С�������������·�ȥ
		if(nID == SC_MINIMIZE || nID == SC_CLOSE )
        {
			ShowWindow(SW_HIDE);//������������
            return ;
        }        	
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMouseSimulateDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMouseSimulateDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
//�� �� : �Զ�����ȼ�
void CMouseSimulateDlg::RegisterMyHotkey()
{
	//��ʾ�����ڵ��ȼ�
    ::RegisterHotKey(GetSafeHwnd(), WM_SHOW_MAINWINDOW,
		MOD_CONTROL|MOD_ALT, _T('V'));

	::RegisterHotKey(GetSafeHwnd(), WM_CTL_J, MOD_CONTROL, 'J');
	::RegisterHotKey(GetSafeHwnd(), WM_CTL_T, MOD_CONTROL, 'T');
	::RegisterHotKey(GetSafeHwnd(), WM_CTL_B, MOD_CONTROL, 'B');
	::RegisterHotKey(GetSafeHwnd(), WM_CTL_E, MOD_CONTROL, 'E');
}

//�� �� : ����װ�ȼ�
void CMouseSimulateDlg::UnRegisterMyHotkey()
{
    ::UnregisterHotKey(GetSafeHwnd(),WM_SHOW_MAINWINDOW);
	::UnregisterHotKey(GetSafeHwnd(),WM_CTL_J);
	::UnregisterHotKey(GetSafeHwnd(),WM_CTL_T);
	::UnregisterHotKey(GetSafeHwnd(),WM_CTL_B);
	::UnregisterHotKey(GetSafeHwnd(),WM_CTL_E);
}
//�����ȼ�
LRESULT CMouseSimulateDlg::OnHotKey(WPARAM wParam, LPARAM lParam)
{	
	switch(wParam)
	{
	case WM_CTL_J: //��ʼ��¼
		OnStartRecord();
		break;
	case WM_CTL_T: //ֹͣ��¼
		m_MouseHook.EndRecord();
		ShowWindow(SW_SHOW);
		break;
	case WM_CTL_B: //��ʼģ����궯��
		OnStartSimulate();
		break;
	case WM_CTL_E: //ֹͣģ����궯��
		EndSimulate();
		break;
	}
	return 0;
}

LRESULT CMouseSimulateDlg::OnMsgNotifyIcon(WPARAM wParam, LPARAM lParam)
{
	UINT uMsg = lParam;
    switch(uMsg)
    {
    case WM_LBUTTONDBLCLK:
        ShowWindow(SW_SHOW);
        SetForegroundWindow();	
		break;    
	case WM_RBUTTONDOWN:
		m_NotifyIcon.ShowMenu(IDR_NOTIFYICON_POPUP);
		break;
    default:
		break;
    }		
	return 0;
}

//����  : ��ʾ���Ի���
void CMouseSimulateDlg::OnShowMainDlg() 
{
    ShowWindow(SW_SHOW);
	SetForegroundWindow();			
}
void CMouseSimulateDlg::OnQuitProgram() 
{
	OnCancel();	
}

void CMouseSimulateDlg::OnOK() 
{
	ShowWindow(SW_HIDE);
	return;
	
	CDialog::OnOK();
}

void CMouseSimulateDlg::OnCancel() 
{
	EndSimulate();

	m_NotifyIcon.DelIcon();
	UnRegisterMyHotkey();
	m_MouseHook.UninstallHook();
	while (m_MouseEventArray.GetSize() > 0)
	{
		delete m_MouseEventArray[0];
		m_MouseEventArray.RemoveAt(0);
	}
	CDialog::OnCancel();
}


//����ģ����궯��
void CMouseSimulateDlg::EndSimulate()
{
	if( !m_bSimulating )//���û��ģ�⣬�����ٽ�����
		return;
	m_bSimulating = FALSE;
	m_iEventPos   = -1;
	while (m_MouseEventArray.GetSize() > 0)
	{
		delete m_MouseEventArray[0];
		m_MouseEventArray.RemoveAt(0);
	}
	
	ShowWindow(SW_SHOW);

	CTime T1 = CTime::GetCurrentTime();
	CString strTime1 = T1.Format("����ģ��ʱ�䣺%d�� %H:%M:%S\r\n");
	CStatic *pStaticWnd = (CStatic*)GetDlgItem(IDC_STATIC_DES);
	if( pStaticWnd )
	{
		CTime T2(m_iStartTime);
		CString strTime2 = T2.Format("��ʼģ��ʱ�䣺%d�� %H:%M:%S\r\n");

		CString strLoopCount;
		strLoopCount.Format("�ܹ�ģ�������%d\r\n", m_iLoopCount);

		pStaticWnd->SetWindowText(strTime2+strTime1+strLoopCount);
	}
}

//�Ӽ�¼�ļ��ж�����궯����������ӵ�һ��������ȥ���������˳��ִ������
BOOL CMouseSimulateDlg::GetMouseEventArrayFromFile()
{
	try
	{
		CFile file;
		if( !file.Open("record.txt", CFile::modeRead) )
			return FALSE;

		CMouseEvent *pEvent = NULL;

		CString strBuf;
		int iLen = (int)file.GetLength();
		file.Read(strBuf.GetBuffer(iLen), iLen);
		strBuf.ReleaseBuffer(iLen);
		
		int iPos = 0;
		int iLast= 0;
		int iLinePos = 0;
		int iLineLast= 0;
		CString strLine;
		CString strTmp;
		while( iPos < (iLen-1) )
		{
			iLinePos = 0;
			iLast = iPos;
			iPos = strBuf.Find("\n", iLast);
			if( iPos==-1)
			{
				if( iPos < (iLen-1) )
				{
					strLine = strBuf.Mid(iLast, iLen-iLast);
					iPos = iLen;
				}
				else
					break;
			}
			iPos++;
			strLine = strBuf.Mid(iLast, iPos-iLast);
			strLine.TrimLeft();strLine.TrimRight();

			int iLineLen = strLine.GetLength();
			
			iLineLast = iLinePos;
			iLinePos = strLine.Find(' ', iLineLast);
			if( iLinePos == -1)
				throw;
			pEvent = new CMouseEvent();
			strTmp = strLine.Mid(iLineLast, iLinePos-iLineLast);//������ʱ��
			pEvent->Time = atoi((LPCTSTR)strTmp);
			
			iLinePos++;
			iLineLast = iLinePos;
			iLinePos = strLine.Find(' ', iLineLast);
			if( iLinePos == -1)
				throw;
			strTmp = strLine.Mid(iLineLast, iLinePos-iLineLast);//��������궯������
			if( strTmp=="LBUTTON_DOWN" || strTmp=="LB_DOWN")
				pEvent->EventType = LB_DOWN;
			if( strTmp=="LBUTTON_UP" || strTmp=="LB_UP")
				pEvent->EventType = LB_UP;
			if( strTmp=="MOUSE_MOVE" || strTmp=="MOVE")
				pEvent->EventType = MOUSE_MOVE;
			if( strTmp=="RB_DOWN")
				pEvent->EventType = RB_DOWN;
			if (strTmp=="RB_UP")
				pEvent->EventType = RB_UP;

			iLinePos++;
			iLineLast = iLinePos;
			iLinePos = strLine.Find(' ', iLineLast);
			if( iLinePos == -1)
				throw;
			strTmp = strLine.Mid(iLineLast, iLinePos-iLineLast);//��������굱ʱ�ĺ�����
			pEvent->xPos = atoi((LPCTSTR)strTmp);	
			
			iLinePos++;
			iLineLast = iLinePos;
			strTmp = strLine.Mid(iLineLast, iLineLen-iLineLast);//��������굱ʱ��������
			pEvent->yPos = atoi((LPCTSTR)strTmp);
			
			m_MouseEventArray.Add(pEvent);
		}		
	}
	catch (...)
	{
		while (m_MouseEventArray.GetSize() > 0)
		{
			delete m_MouseEventArray[0];
			m_MouseEventArray.RemoveAt(0);
		}
		return FALSE;
	}	
	return TRUE;
}

void CMouseSimulateDlg::OnTimer(UINT nIDEvent) 
{
	CDialog::OnTimer(nIDEvent);
	if( m_bSimulating )//����ģ��֮��
	{
		int iSize = m_MouseEventArray.GetSize();
		if( iSize == 0)
			return;
		if( m_iEventPos < 0 )
			m_iEventPos = 0;
		if( m_iEventPos >= iSize)
		{
			m_dwSimulateStartTime = GetTickCount();
			m_iEventPos = 0;
			m_iLoopCount++;
			if( (UINT)m_iLoopCount >= m_iLoopDestCount )
				EndSimulate();
			return ;
		}
		
		DWORD dwTime = GetTickCount();
		CMouseEvent *pEvent = m_MouseEventArray[m_iEventPos];
		if( (dwTime - m_dwSimulateStartTime) >= pEvent->Time )//ʱ����������������¼��ʱ��
		{
			if( pEvent->EventType == MOUSE_MOVE)
			{
				::SetCursorPos(pEvent->xPos, pEvent->yPos);
				m_iEventPos++;
				return;
			}
			
			INPUT Input = {0};
			Input.type = INPUT_MOUSE;
			
			if( pEvent->EventType == LB_DOWN)//LBUTTON_DOWN
				Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTDOWN;
			if( pEvent->EventType == LB_UP)//LBUTTON_UP
				Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_LEFTUP;
			if( pEvent->EventType== RB_DOWN)
				Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTDOWN;
			if( pEvent->EventType== RB_UP)
				Input.mi.dwFlags = MOUSEEVENTF_ABSOLUTE|MOUSEEVENTF_RIGHTUP;

			Input.mi.dx = pEvent->xPos;
			Input.mi.dy = pEvent->yPos;
			
			::SetCursorPos(pEvent->xPos, pEvent->yPos);

			::SendInput(1, &Input, sizeof(INPUT));

			m_iEventPos++; //ָ����һ��Ҫִ�еļ�¼
		}
	}
}

void CMouseSimulateDlg::OnStartRecord() 
{
	if( m_bSimulating )//����ģ��֮���ǲ��ܼ�¼��
		return;
	ShowWindow(SW_HIDE);
	m_MouseHook.StartRecord();	
}

void CMouseSimulateDlg::OnStartSimulate() 
{
	if (!UpdateData(TRUE))
		return;
	
	//����Ѿ���ʼģ����,�����ٿ�ʼ��
	//������ڼ�¼������ģ��
	if( m_bSimulating || m_MouseHook.IsRecording())
		return;
	if( !GetMouseEventArrayFromFile() )
		return;
	ShowWindow(SW_HIDE);
	m_bSimulating = TRUE;
	m_dwSimulateStartTime = GetTickCount();
	
	m_iLoopCount = 0;
	CTime T = CTime::GetCurrentTime();
	m_iStartTime = (int)T.GetTime();
}
