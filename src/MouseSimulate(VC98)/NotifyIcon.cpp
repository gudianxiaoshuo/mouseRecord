// NotifyIcon.cpp: implementation of the CNotifyIcon class.
//
//////////////////////////////////////////////////////////////////////

/************************************
  REVISION LOG ENTRY
  Revision By: ...
  Revised on 03-11-17 14:18:50
  Comments: 
  用于处理任务条右下方的图标
 ************************************/


#include "stdafx.h"
#include "MouseSimulate.h"
#include "NotifyIcon.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNotifyIcon::CNotifyIcon()
{
	m_pWnd = NULL;
}

CNotifyIcon::~CNotifyIcon()
{

}


void CNotifyIcon::AddIconToTaskbar(LPCTSTR pszInfo)
{
	if( m_pWnd == NULL)
		return;
	m_nid.cbSize           = sizeof(NOTIFYICONDATA);
    m_nid.hWnd             = m_pWnd->GetSafeHwnd();
    m_nid.uID              = 1;
    m_nid.uFlags           = NIF_TIP|NIF_MESSAGE|NIF_ICON;
    m_nid.hIcon            = ::LoadIcon(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDR_MAINFRAME));
  
	m_nid.uCallbackMessage = (UINT)WM_MSG_NOTIFYICON;

    _tcscpy(m_nid.szTip, pszInfo);
    
    Shell_NotifyIcon(NIM_ADD, &m_nid);
}

void CNotifyIcon::DelIcon()
{
	Shell_NotifyIcon(NIM_DELETE, &m_nid);
}

void CNotifyIcon::ShowMenu(UINT nMenuID)
{
	CMenu Menu, *pPopupMenu=NULL;
	CPoint pt;
	::GetCursorPos(&pt);
	Menu.LoadMenu(nMenuID);		
	pPopupMenu = Menu.GetSubMenu(0);
	::SetForegroundWindow(m_nid.hWnd); //没有这一句，单击菜单以外
	                                   //的地方，菜单不消失
	pPopupMenu->TrackPopupMenu(TPM_RIGHTALIGN|TPM_LEFTBUTTON,
		pt.x, pt.y, AfxGetMainWnd(), NULL); 	
}