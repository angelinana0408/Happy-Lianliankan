// myServer.h : main header file for the MYSERVER application
//

#if !defined(AFX_MYSERVER_H__A4E75488_C2B0_46D7_A17D_2885FCC9E864__INCLUDED_)
#define AFX_MYSERVER_H__A4E75488_C2B0_46D7_A17D_2885FCC9E864__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyServerApp:
// See myServer.cpp for the implementation of this class
//

class CMyServerApp : public CWinApp
{
public:
	CMyServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyServerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERVER_H__A4E75488_C2B0_46D7_A17D_2885FCC9E864__INCLUDED_)
