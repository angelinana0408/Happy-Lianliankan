
// HappyLLK.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHappyLLKApp:
// �йش����ʵ�֣������ HappyLLK.cpp
//

class CHappyLLKApp : public CWinApp
{
public:
	CHappyLLKApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHappyLLKApp theApp;