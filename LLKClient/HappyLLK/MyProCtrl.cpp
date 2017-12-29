// MyProCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HappyLLK.h"
#include "MyProCtrl.h"


// CMyProCtrl

IMPLEMENT_DYNAMIC(CMyProCtrl, CProgressCtrl)

CMyProCtrl::CMyProCtrl()
{

}

CMyProCtrl::~CMyProCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyProCtrl, CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CMyProCtrl ��Ϣ�������




void CMyProCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CProgressCtrl::OnPaint()

	CBrush BackgroundBrush;
    BackgroundBrush.CreateSolidBrush(RGB(220,220,220));    

    CBrush ForeBrush;
    ForeBrush.CreateSolidBrush(RGB(205,150,205));    

    CRect r;
    this->GetClientRect(r);

    double With=r.Width();

    int min,max;
    this->GetRange(min,max);
    
    int pos= this->GetPos();
    double unit=(double)r.Width()/(max-min);

   // dc.FillRect(r,&BackgroundBrush);    
	CRect rr = r;
	rr.left = pos*unit+25;
    dc.FillRect(rr,&BackgroundBrush);

    r.right=pos*unit;    

    dc.FillRect(r,&ForeBrush);    

	CDC pDC;
	pDC.CreateCompatibleDC(&dc);
    HANDLE hBmpBG = ::LoadImageW(NULL,_T("res\\������.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);
	pDC.SelectObject(hBmpBG);

	dc.BitBlt(r.right,0,50,27,&pDC,0,0,SRCCOPY);
}
