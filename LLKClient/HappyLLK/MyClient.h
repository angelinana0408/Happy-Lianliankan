// MyClient.h : main header file for the MYCLIENT application
//

#if !defined(AFX_MYCLIENT_H__3EAE1423_3AED_4E61_836B_0C451C3D1FC4__INCLUDED_)
#define AFX_MYCLIENT_H__3EAE1423_3AED_4E61_836B_0C451C3D1FC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyClientApp:
// See MyClient.cpp for the implementation of this class
//

class CMyClientApp : public CWinApp
{
public:
	CMyClientApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyClientApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyClientApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYCLIENT_H__3EAE1423_3AED_4E61_836B_0C451C3D1FC4__INCLUDED_)
