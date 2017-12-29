#if !defined(AFX_MYSERVER_H__5B409EDC_0202_4AFC_8285_88A6358BF9A5__INCLUDED_)
#define AFX_MYSERVER_H__5B409EDC_0202_4AFC_8285_88A6358BF9A5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "stdafx.h"
#include <afxsock.h>

class CHappyLLKDlg;

class MyServer: public CAsyncSocket{
public:
	MyServer();
	virtual ~MyServer();
	void SetDlg(CHappyLLKDlg *pDlg);
	virtual void OnReceive(int nErrorCode);
	virtual void OnConnect(int nErrorCode);

private:
	CHappyLLKDlg *m_pDlg;;
};


#endif