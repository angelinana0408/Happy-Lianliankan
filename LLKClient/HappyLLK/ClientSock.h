#if !defined(AFX_CLIENTSOCK_H__5B409EDC_0202_4AFC_8285_88A6358BF9A5__INCLUDED_)
#define AFX_CLIENTSOCK_H__5B409EDC_0202_4AFC_8285_88A6358BF9A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSock.h : header file
//

class CMyClientDlg;

/////////////////////////////////////////////////////////////////////////////
// CClientSock command target

class CClientSock : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CClientSock();
	virtual ~CClientSock();
	void SetDlg(CMyClientDlg* pDlg);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
private:
	CMyClientDlg* m_pDlg;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCK_H__5B409EDC_0202_4AFC_8285_88A6358BF9A5__INCLUDED_)
