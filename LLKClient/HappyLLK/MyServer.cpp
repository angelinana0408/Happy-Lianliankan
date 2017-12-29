#include "stdafx.h"
#include "MyServer.h"
#include "HappyLLKDlg.h"
#include "HappyLLK.h"

MyServer::MyServer(){
	m_pDlg = NULL;
}

MyServer::~MyServer(){
	m_pDlg = NULL;
}

void MyServer::OnReceive(int nErrorCode){
	
	// TODO: Add your specialized code here and/or call the base class
	if (0 == nErrorCode)
	{
		m_pDlg->OnRvc();
	}
	CAsyncSocket::OnReceive(nErrorCode);
}
void MyServer::SetDlg(CHappyLLKDlg *pDlg){
	if(pDlg!=NULL){
		m_pDlg = pDlg;
	}
}

void MyServer::OnConnect(int nErrorCode){
	if (0 == nErrorCode)
	{
		m_pDlg->OnConnected();
	}
	CAsyncSocket::OnConnect(nErrorCode);
}