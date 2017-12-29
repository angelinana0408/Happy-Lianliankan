
// HappyLLKDlg.h : ͷ�ļ�
//
#if !defined(AFX_HAPPYLLKDLG_H__C5583930_49B2_4A66_B0DA_1B801203D3F7__INCLUDED_)
#define AFX_HAPPYLLKDLG_H__C5583930_49B2_4A66_B0DA_1B801203D3F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif 

#include "resource.h" 
#include "afxwin.h"
#include "afxcmn.h"
#include "GameClass.h"
#include "MyProCtrl.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include "MyServer.h"

using namespace std;


// CHappyLLKDlg �Ի���
class CHappyLLKDlg : public CDialogEx
{
// ����
public:
	CHappyLLKDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_HAPPYLLK_DIALOG };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


protected:
	CBitmapButton mybutton1; 
	CBitmapButton mybutton2;
	CBitmapButton mybutton3;
	CBitmapButton mbutton_hint;
	CBitmapButton mbutton_rank;
	CBitmapButton mbutton_pause;
	CBitmapButton mbutton_next;
	CBitmapButton mbutton_continue;
	CBitmapButton mbutton_again;
	CBitmapButton mbutton_look;
	CBitmapButton mbutton_music;
	CBitmapButton mbutton_music_OFF;

	
// ʵ��
protected:
	HICON m_hIcon;


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();

	void forbid();
	void start();
	void success();
	void fail();
	void ko();

	void drawback();
	void draw();
	void draw_edge(int,int,CBitmap&);
	void draw_line(vertex, vertex, int, int);
	void time(int);
	void update_point();
	void draw_point(int,int);

	void generateMap(); //ͨ��ģʽ�͹������ɵ�ͼ 
	int* readFromFile(char *filename,int &dimension);

	void drawPlayer2Board();
	void OnRvc();
	void OnConnected();
	void ShowList();

	CStatic m_number;
	CStatic m_point;
	CStatic m_time;
	
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//CProgressCtrl
	CMyProCtrl m_progress;
	int count;
	
	//for paint
	CDC *pDC; 
	CBitmap m_bitmapOriginal,m_bitmapPrompt,m_bitmapSelected;
	CBitmap m_bitmapNumber;
	 
	int pic;

	CDC dcMemory;
	CBitmap* hOldBitMap;

	//GameClass gc;  //�����ͼ
	bool newGame; //�Ƿ��ػ�����
	int **map;
	int map_row_size;
	int map_col_size;
	int map_bmp_size;
	
	int mode,num;  //����ؿ���
	int poi;     //����

	int **map_player2;
	CBitmap m_bitmapNet;//����

	MyServer *m_mySocket,m_ListSocket;

	GameClass *gc;
	vertex firstPoint,secondPoint; //���������������
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton10();

	//bool mark;
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
};

#endif