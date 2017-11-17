// MouseSimulate.h : main header file for the MOUSESIMULATE application
//

#if !defined(AFX_MOUSESIMULATE_H__5C7C9235_1476_4978_B824_338E358957E7__INCLUDED_)
#define AFX_MOUSESIMULATE_H__5C7C9235_1476_4978_B824_338E358957E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMouseSimulateApp:
// See MouseSimulate.cpp for the implementation of this class
//

class CMouseSimulateApp : public CWinApp
{
public:
	CMouseSimulateApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseSimulateApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMouseSimulateApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CMouseSimulateApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOUSESIMULATE_H__5C7C9235_1476_4978_B824_338E358957E7__INCLUDED_)
