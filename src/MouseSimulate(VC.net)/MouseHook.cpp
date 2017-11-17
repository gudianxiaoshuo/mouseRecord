// Disable.cpp: implementation of the CMouseHook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MouseSimulate.h"
#include "MouseHook.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

HHOOK CMouseHook::hHookMouse    = NULL;
HHOOK CMouseHook::hHookKeyboard = NULL;
CFile CMouseHook::s_File;
BOOL  CMouseHook::s_bRecord     = FALSE;
DWORD CMouseHook::s_dwStartTime = 0;
CMouseHook::CMouseHook()
{
	s_bRecord = FALSE;
}

CMouseHook::~CMouseHook()
{

}

BOOL CMouseHook::InstallHook()
{
	//最后一个参数是线程ID，如果为0，表示全局钩子函数，必须在DLL中用，
	//可是这里好像也可以
	//原来只有WH_KEYBOARD_LL和WH_MOUSE_LL可以。
//	hHookKeyboard = ::SetWindowsHookEx(WH_KEYBOARD_LL, 
//			(HOOKPROC)LowLevelKeyboardProc, theApp.m_hInstance, 0);
	
	if(hHookMouse == NULL)
	{
		hHookMouse = ::SetWindowsHookEx(WH_MOUSE_LL, (HOOKPROC)MouseProc,
			theApp.m_hInstance, 0);
	}
	return TRUE;
}

BOOL CMouseHook::UninstallHook()
{
	if(hHookKeyboard != NULL)
	{
		::UnhookWindowsHookEx(hHookKeyboard);
		hHookKeyboard = NULL;
	}

	if(hHookMouse != NULL)
	{
		::UnhookWindowsHookEx(hHookMouse);
		hHookMouse = NULL;
	}
	return TRUE;
}

LRESULT CALLBACK CMouseHook::LowLevelKeyboardProc(INT nCode, WPARAM wParam, 
												LPARAM lParam)
{
   // By returning a non-zero value from the hook procedure, the
    // message does not get passed to the target window
    KBDLLHOOKSTRUCT *pkbhs = (KBDLLHOOKSTRUCT*)lParam;
    BOOL bControlKeyDown = 0;
	BOOL bAltKeyDown     = 0;

    switch (nCode)
    {
        case HC_ACTION:
        {
            // Check to see if the CTRL key is pressed
            bControlKeyDown = GetAsyncKeyState (VK_CONTROL)&0x8000;

            // Disable CTRL+ESC
//          if (pkbhs->vkCode == VK_ESCAPE && bControlKeyDown)
//              return 1;

            break;
        }

        default:
            break;
    }
    return CallNextHookEx (hHookKeyboard, nCode, wParam, lParam);
}

LRESULT CALLBACK CMouseHook::MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(nCode == HC_ACTION)//此时消息包含鼠标信息
	{		
		DWORD dwTime;
		CString strTime;
		CString strPos;
		CPoint ptCursor;

		CString str;
		switch(wParam)
		{
		case WM_RBUTTONDOWN:
			if( !s_bRecord )
				break;
			{
				dwTime = GetTickCount();
				dwTime = dwTime - s_dwStartTime;
				
				strTime.Format(L"%d ", dwTime);
				s_File.Write(strTime, strTime.GetLength()*2);

				str = L"RB_DOWN ";
				s_File.Write(str, str.GetLength()*2);

				::GetCursorPos(&ptCursor);
				strPos.Format(L"%d %d ", ptCursor.x, ptCursor.y);
				s_File.Write(strPos, strPos.GetLength()*2);

				str = L"\r\n";
				s_File.Write(str, str.GetLength() * 2);
				
			}
		case WM_RBUTTONDBLCLK:
			break;
		case WM_RBUTTONUP:
			if( !s_bRecord )
				break;
			{
				dwTime = GetTickCount();
				dwTime = dwTime - s_dwStartTime;
				
				strTime.Format(L"%d ", dwTime);
				s_File.Write(strTime, strTime.GetLength()*2);

				str = L"RB_UP ";
				s_File.Write(str, str.GetLength() * 2);
				

				::GetCursorPos(&ptCursor);
				strPos.Format(L"%d %d ", ptCursor.x, ptCursor.y);
				s_File.Write(strPos, strPos.GetLength()*2);


				str = L"\r\n";
				s_File.Write(str, str.GetLength() * 2);
			}			
			break;
		case WM_LBUTTONDOWN:
			if( !s_bRecord )
				break;
			{				
				dwTime = GetTickCount();
				dwTime = dwTime - s_dwStartTime;
				
				strTime.Format(L"%d ", dwTime);
				s_File.Write(strTime, strTime.GetLength()*2);

				

				str = L"LB_DOWN ";
				s_File.Write(str, str.GetLength() * 2);

				::GetCursorPos(&ptCursor);
				strPos.Format(L"%d %d ", ptCursor.x, ptCursor.y);
				s_File.Write(strPos, strPos.GetLength()*2);

				str = L"\r\n";
				s_File.Write(str, str.GetLength() * 2);
			}
			break;			
		case WM_LBUTTONUP:
			if( !s_bRecord )
				break;
			{
				dwTime = GetTickCount();
				dwTime = dwTime - s_dwStartTime;
				strTime.Format(L"%d ", dwTime);
				s_File.Write(strTime, strTime.GetLength()*2);
				
				
				str = L"LB_UP ";
				s_File.Write(str, str.GetLength() * 2);
				
				::GetCursorPos(&ptCursor);
				strPos.Format(L"%d %d ", ptCursor.x, ptCursor.y);
				s_File.Write(strPos, strPos.GetLength()*2);

				str = L"\r\n";
				s_File.Write(str, str.GetLength() * 2);
			}
			break;
		case WM_MOUSEMOVE:
			if( !s_bRecord )
				break;
			{
				dwTime = GetTickCount();
				dwTime = dwTime - s_dwStartTime;
				strTime.Format(L"%d ", dwTime);
				s_File.Write(strTime, strTime.GetLength()*2);

				str = L"MOVE ";
				s_File.Write(str, str.GetLength() * 2);
				
				
				::GetCursorPos(&ptCursor);
				strPos.Format(L"%d %d ", ptCursor.x, ptCursor.y);
				s_File.Write(strPos, strPos.GetLength()*2);
				
				str = L"\r\n";
				s_File.Write(str, str.GetLength() * 2);
			}

			break;
		default:
			break;			
		}
	}
	
	return CallNextHookEx(hHookMouse, nCode, wParam, lParam);
}

void CMouseHook::StartRecord()
{
	if( s_bRecord )//已经在记录了，所以不用再设置了
		return;
		
	s_bRecord = TRUE;
	s_dwStartTime = GetTickCount(); //记录起始的时间
	try
	{
		if( !s_File.Open(L"record.txt", CFile::modeReadWrite|CFile::modeCreate))
			throw;		
	}
	catch (...)
	{

	}
}
void CMouseHook::EndRecord()
{
	if( !s_bRecord )
		return;

	s_bRecord = FALSE;

	try
	{
		s_File.Close();
	}
	catch (...)
	{
	}
}

BOOL CMouseHook::IsRecording()
{
	return s_bRecord;
}