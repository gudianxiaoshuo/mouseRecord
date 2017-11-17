// MouseSimulateDlg.h : header file
//

#if !defined(AFX_MOUSESIMULATEDLG_H__4845A7D9_06A7_4DFA_BA2B_A8170B2822B4__INCLUDED_)
#define AFX_MOUSESIMULATEDLG_H__4845A7D9_06A7_4DFA_BA2B_A8170B2822B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "NotifyIcon.h"
#include "MouseHook.h"

/////////////////////////////////////////////////////////////////////////////
// CMouseSimulateDlg dialog

const int WM_CTL_J = WM_USER + 1001;
const int WM_CTL_T = WM_USER + 1002;

const int WM_CTL_B = WM_USER + 1003;
const int WM_CTL_E = WM_USER + 1004;

const int WM_BgSimulate=WM_USER + 1005;// 进程通信用的自定义消息，两个进程都需定义

//const int WM_CTL_F12 = WM_USER + 1005;


const UINT WM_SHOW_MAINWINDOW = WM_USER + 1010;

class CMouseEvent
{
public:
	int   EventType;
	DWORD Time;
	int   xPos;
	int   yPos;
};

class CMouseSimulateDlg : public CDialog
{
// Construction
public:
	CMouseSimulateDlg(CWnd* pParent = NULL);	// standard constructor

public:
	enum
	{
		LB_DOWN = 1,
		LB_UP,
		MOUSE_MOVE,
		RB_DOWN,
		RB_UP,
	};

protected:
	CNotifyIcon m_NotifyIcon;
	CMouseHook  m_MouseHook;
	BOOL        m_bSimulating;//是否正在进行模拟仿真

	DWORD		m_dwSimulateStartTime;
	int			m_iEventPos;
	CTypedPtrArray<CPtrArray, CMouseEvent*>m_MouseEventArray;

	int         m_iLoopCount;
	int         m_iStartTime;
	int         m_iEndTime;
	
protected:
	void RegisterMyHotkey();
	void UnRegisterMyHotkey();

	void EndSimulate();

	BOOL GetMouseEventArrayFromFile();


	CFile m_File;
// Dialog Data
	//{{AFX_DATA(CMouseSimulateDlg)
	enum { IDD = IDD_MOUSESIMULATE_DIALOG };
	CEdit	m_LoopCountCtl;
	UINT	m_iLoopDestCount;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseSimulateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMouseSimulateDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnShowMainDlg();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnQuitProgram();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStartRecord();
	afx_msg void OnStartSimulate();

	afx_msg LRESULT  OnCopyData(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnBgSimulate(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	afx_msg LRESULT OnHotKey(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsgNotifyIcon(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSESIMULATEDLG_H__4845A7D9_06A7_4DFA_BA2B_A8170B2822B4__INCLUDED_)
