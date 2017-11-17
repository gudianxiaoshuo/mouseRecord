// NotifyIcon.h: interface for the CNotifyIcon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NOTIFYICON_H__CAE2F7C1_1906_11D8_B76B_00508BFB92C3__INCLUDED_)
#define AFX_NOTIFYICON_H__CAE2F7C1_1906_11D8_B76B_00508BFB92C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const int WM_MSG_NOTIFYICON = WM_USER + 609;

class CNotifyIcon  
{
public:
	CNotifyIcon();
	virtual ~CNotifyIcon();

public:
	CWnd          *m_pWnd;//Ö÷´°¿Ú
	NOTIFYICONDATA m_nid;

public:
	void AddIconToTaskbar(LPCTSTR pszInfo);
	void DelIcon();

	void ShowMenu(UINT nMenuID);

protected:

protected:


};

#endif // !defined(AFX_NOTIFYICON_H__CAE2F7C1_1906_11D8_B76B_00508BFB92C3__INCLUDED_)
