// ClientSock.cpp : implementation file
//

#include "stdafx.h"
#include "MyClient.h"
#include "ClientSock.h"
#include "MyClientDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClientSock

CClientSock::CClientSock()
{
	m_pDlg = NULL;
}

CClientSock::~CClientSock()
{
	m_pDlg = NULL;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CClientSock, CAsyncSocket)
	//{{AFX_MSG_MAP(CClientSock)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CClientSock member functions

void CClientSock::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if ( 0 == nErrorCode)
	{
		m_pDlg->OnClose();
	}
	CAsyncSocket::OnClose(nErrorCode);
}

void CClientSock::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (0 == nErrorCode)
	{
		m_pDlg->OnConnected();
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CClientSock::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (0 == nErrorCode)
	{
		m_pDlg->OnRvc();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}

void CClientSock::SetDlg(CMyClientDlg* pDlg)
{
	if (NULL != pDlg)
	{
		m_pDlg = pDlg;
	}
}