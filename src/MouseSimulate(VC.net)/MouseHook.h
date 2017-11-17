// Disable.h: interface for the CMouseHook class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DISABLE_H__C4DFF463_CE09_481B_86DD_FFCF63DD4C2D__INCLUDED_)
#define AFX_DISABLE_H__C4DFF463_CE09_481B_86DD_FFCF63DD4C2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
#define WH_KEYBOARD_LL     13
#define WH_MOUSE_LL        14

typedef struct tagKBDLLHOOKSTRUCT {
    DWORD   vkCode;
    DWORD   scanCode;
    DWORD   flags;
    DWORD   time;
    DWORD   dwExtraInfo;
} KBDLLHOOKSTRUCT, FAR *LPKBDLLHOOKSTRUCT, *PKBDLLHOOKSTRUCT;
*/

class CMouseHook  
{
public:
	CMouseHook();
	virtual ~CMouseHook();

public:
	BOOL InstallHook();
	BOOL UninstallHook();

	void StartRecord();
	void EndRecord();

	static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);	
	static LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

	static HHOOK hHookMouse;
	static HHOOK hHookKeyboard;

	static BOOL  s_bRecord;
	static CFile s_File;
	static DWORD s_dwStartTime;

	BOOL IsRecording();//是否正在记录中

protected:

};

#endif // !defined(AFX_DISABLE_H__C4DFF463_CE09_481B_86DD_FFCF63DD4C2D__INCLUDED_)
