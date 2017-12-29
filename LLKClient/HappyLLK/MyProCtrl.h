#pragma once


// CMyProCtrl

class CMyProCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CMyProCtrl)

public:
	CMyProCtrl();
	virtual ~CMyProCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


