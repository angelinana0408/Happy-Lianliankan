// myServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "myServer.h"
#include "myServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyServerDlg dialog

CMyServerDlg::CMyServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMyServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMyServerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMyServerDlg)
	DDX_Control(pDX, IDC_TREE_CLIENT, m_treeClient);
	DDX_Control(pDX, IDC_EDIT_POR, m_edtPort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMyServerDlg, CDialog)
	//{{AFX_MSG_MAP(CMyServerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStart)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStop)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyServerDlg message handlers

BOOL CMyServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	index = 0;
	firstSocket=nullptr;
	secondSocket=nullptr;
	m_Svr.SetDlg(this);
	m_edtPort.SetWindowText("6100");
	m_Root = m_treeClient.InsertItem("客户端",TVI_ROOT);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMyServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMyServerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMyServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMyServerDlg::OnBtnStart() 
{
	// TODO: Add your control notification handler code here
	CString strPort;
	m_edtPort.GetWindowText(strPort);
	if (!m_Svr.Create(atoi(strPort),SOCK_STREAM,FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE))
	{
		MessageBox("Create Socket Error!");
		return;
	}
	if (!m_Svr.Listen())
	{
		int nErrorCode = m_Svr.GetLastError();
		if (nErrorCode!=WSAEWOULDBLOCK)
		{
			AfxMessageBox("Listen Error!");
			m_Svr.Close();
			PostQuitMessage(0);
			return;
		}
	}
	GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
}

void CMyServerDlg::OnBtnStop() 
{
	// TODO: Add your control notification handler code here

	while(!m_ConnList.IsEmpty())
	{
		CClientSock* pConn = (CClientSock*)m_ConnList.RemoveHead();
		delete pConn;
	}

	HTREEITEM hCurrent = m_treeClient.GetNextItem(m_Root,TVGN_CHILD);
	while(NULL != hCurrent)
	{
		m_treeClient.DeleteItem(hCurrent);
		hCurrent = m_treeClient.GetNextItem(hCurrent,TVGN_NEXT);
	}
	
	m_Svr.Close();
	GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
}

//有新连接
void CMyServerDlg::OnAccept(int nErrCode)
{
	if (0 == nErrCode)
	{
		CClientSock* pNewConn = new CClientSock;
		pNewConn->SetDlg(this);
		m_Svr.Accept(*pNewConn);
		m_ConnList.AddTail(pNewConn);
		CString strAddr("");
		CString strip("");
		UINT nPort;
		pNewConn->GetPeerName(strip,nPort);
		strAddr.Format("%s:%d",strip,nPort);
		HTREEITEM nodeCli = m_treeClient.InsertItem(strAddr,m_Root);
		m_treeClient.SetItemData(nodeCli,(DWORD)pNewConn);
		m_treeClient.Expand(m_Root,TVE_EXPAND);

		if(index==0){
			index++;
			firstSocket = pNewConn;
		}
		else if(index==1){
			index++;
			secondSocket = pNewConn;
		}
	}
 	else
 	{
 	}
}

//有客户端断开
void CMyServerDlg::OnClientClose(int nErrCode,CClientSock* pConn)
{
	if (0 == nErrCode)
	{

		POSITION pos = NULL;
		pos = m_ConnList.Find(pConn);
		if (NULL != pos)
		{
			CClientSock* pClose = (CClientSock*)m_ConnList.GetAt(pos);
			
			HTREEITEM NodeClient = m_treeClient.GetNextItem(m_Root,TVGN_CHILD);
			for(;NULL != NodeClient;)
			{
				if (pClose == (CClientSock*)m_treeClient.GetItemData(NodeClient))
				{
					m_treeClient.DeleteItem(NodeClient);
					break;
				}
				NodeClient = m_treeClient.GetNextItem(NodeClient,TVGN_NEXT);
			}
			delete pClose;
			m_ConnList.RemoveAt(pos);
		}

/*		int nCnt = m_lstClientPtr.GetCount();
		POSITION pos = m_lstClientPtr.GetHeadPosition();
		while(NULL != pos)
		{
			CClientSock* &pCli = m_lstClientPtr.GetAt(pos);
			if (pCli == pConn)
			{
				delete pCli;
				m_lstClientPtr.RemoveAt(pos);
				
				HTREEITEM fstConn = m_treeClient.GetNextItem(m_Root,TVGN_CHILD);
				if (NULL != fstConn)
				{
					HTREEITEM nodeCli = fstConn;
					for(;NULL != nodeCli;)
					{
						if (pCli == (CClientSock*)m_treeClient.GetItemData(nodeCli))
						{
							m_treeClient.DeleteItem(nodeCli);
							break;
						}
						nodeCli = m_treeClient.GetNextItem(nodeCli,TVGN_NEXT);
					}
				}
			}
		}*/

	}
}

//收到数据原数据返回
void CMyServerDlg::OnRcv(CClientSock* pConn)
{
	if (NULL != pConn)
	{
		char rcvBuf[513] = {0};
		int nRcved = 0;
		nRcved = pConn->Receive(rcvBuf,512);
		if (SOCKET_ERROR != nRcved)
		{
			if(pConn==firstSocket&&secondSocket!=NULL)
				secondSocket->Send(rcvBuf,512);
			else if(pConn==secondSocket)
				firstSocket->Send(rcvBuf,512);
		}
	}
}