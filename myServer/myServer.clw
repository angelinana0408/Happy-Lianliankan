; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CClientSock
LastTemplate=CAsyncSocket
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "myServer.h"

ClassCount=5
Class1=CMyServerApp
Class2=CMyServerDlg
Class3=CAboutDlg

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Class4=CMySocket
Class5=CClientSock
Resource3=IDD_MYSERVER_DIALOG

[CLS:CMyServerApp]
Type=0
HeaderFile=myServer.h
ImplementationFile=myServer.cpp
Filter=N

[CLS:CMyServerDlg]
Type=0
HeaderFile=myServerDlg.h
ImplementationFile=myServerDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_EDIT_POR

[CLS:CAboutDlg]
Type=0
HeaderFile=myServerDlg.h
ImplementationFile=myServerDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_MYSERVER_DIALOG]
Type=1
Class=CMyServerDlg
ControlCount=5
Control1=IDC_BTN_START,button,1342242816
Control2=IDC_BTN_STOP,button,1342242816
Control3=IDC_EDIT_POR,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_TREE_CLIENT,SysTreeView32,1350631424

[CLS:CMySocket]
Type=0
HeaderFile=MySocket.h
ImplementationFile=MySocket.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CMySocket

[CLS:CClientSock]
Type=0
HeaderFile=ClientSock.h
ImplementationFile=ClientSock.cpp
BaseClass=CAsyncSocket
Filter=N
VirtualFilter=q
LastObject=CClientSock

