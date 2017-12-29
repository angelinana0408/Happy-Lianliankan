// myServerDlg.h : header file
//

#if !defined(AFX_MYSERVERDLG_H__66DB4819_B938_4121_B405_A5D1D566BB38__INCLUDED_)
#define AFX_MYSERVERDLG_H__66DB4819_B938_4121_B405_A5D1D566BB38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MySocket.h"
#include "ClientSock.h"
#include <afxcoll.h>


/////////////////////////////////////////////////////////////////////////////
// CMyServerDlg dialog

class CMyServerDlg : public CDialog
{
// Construction
public:
	CMyServerDlg(CWnd* pParent = NULL);	// standard constructor
	
	HTREEITEM m_Root;
	CMySocket m_Svr;
	void OnAccept(int nErrCode);
	void OnClientClose(int nErrCode,CClientSock* pConn);
	void OnRcv(CClientSock* pConn);
	CObList m_ConnList;
	CClientSock *firstSocket,*secondSocket;
	int index;

// Dialog Data
	//{{AFX_DATA(CMyServerDlg)
	enum { IDD = IDD_MYSERVER_DIALOG };
	CTreeCtrl	m_treeClient;
	CEdit	m_edtPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMyServerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnStart();
	afx_msg void OnBtnStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYSERVERDLG_H__66DB4819_B938_4121_B405_A5D1D566BB38__INCLUDED_)
