
// HappyLLKDlg.cpp : 实现文件
//

#include <Windows.h>
#include "mmsystem.h"
#include "stdafx.h"
#include "HappyLLK.h"
#include "HappyLLKDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>
#include "atlimage.h"
#include <iostream>
#pragma comment( lib, "Winmm.lib" )

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DWORD WINAPI BackMusicThread(LPVOID lpParameter);
HANDLE handle1;
bool music = false;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg(CHappyLLKDlg*);
	CHappyLLKDlg *parent;

	int poi;

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};

CAboutDlg::CAboutDlg(CHappyLLKDlg *_parent) : CDialogEx(CAboutDlg::IDD)
{
	parent = _parent;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CHappyLLKDlg 对话框
CHappyLLKDlg::CHappyLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CHappyLLKDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//进度条变量
	count=100;
}

void CHappyLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_number);
	DDX_Control(pDX, IDC_STATIC2, m_point);
	DDX_Control(pDX, IDC_STATIC3, m_time);

	DDX_Control(pDX, IDC_PROGRESS1, m_progress);
}

BEGIN_MESSAGE_MAP(CHappyLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CHappyLLKDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CHappyLLKDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CHappyLLKDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CHappyLLKDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CHappyLLKDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CHappyLLKDlg::OnBnClickedButton6)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON8, &CHappyLLKDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CHappyLLKDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON7, &CHappyLLKDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON10, &CHappyLLKDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CHappyLLKDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CHappyLLKDlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CHappyLLKDlg::OnBnClickedButton13)
END_MESSAGE_MAP()


// CHappyLLKDlg 消息处理程序

BOOL CHappyLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_ListSocket.SetDlg(this);

	//for paint
	m_bitmapOriginal.LoadBitmap(IDB_BITMAP18);
	m_bitmapPrompt.LoadBitmap(IDB_BITMAP16);
	m_bitmapSelected.LoadBitmap(IDB_BITMAP15);
	m_bitmapNumber.LoadBitmap(IDB_BITMAP20);
	m_bitmapNet.LoadBitmap(IDB_BITMAP21);

	pDC = GetDC();
	dcMemory.CreateCompatibleDC(pDC);

	newGame = true;
	//mark=true;
	num = 1; //第一关
	poi=0; //初始分数 

	pic=IDB_BITMAP1;

	firstPoint.row = 0; firstPoint.col = 0;
	secondPoint.row = 0;secondPoint.col = 0;

	//loading
	//位图按钮
	mybutton1.LoadBitmaps (IDB_BITMAP2,IDB_BITMAP3);
	mybutton1.SubclassDlgItem(IDC_BUTTON1,this);
	mybutton1.SizeToContent();

	mybutton2.LoadBitmaps (IDB_BITMAP4,IDB_BITMAP5);
	mybutton2.SubclassDlgItem(IDC_BUTTON2,this);
	mybutton2.SizeToContent();

	mybutton3.LoadBitmaps (IDB_BITMAP6,IDB_BITMAP7);
	mybutton3.SubclassDlgItem(IDC_BUTTON3,this);
	mybutton3.SizeToContent();


	mbutton_hint.LoadBitmaps (IDB_BITMAP9,IDB_BITMAP_hintdown);
	mbutton_hint.SubclassDlgItem(IDC_BUTTON4,this);
	mbutton_hint.SizeToContent();

	mbutton_pause.LoadBitmaps (IDB_BITMAP10,IDB_BITMAP_pausedown);
	mbutton_pause.SubclassDlgItem(IDC_BUTTON5,this);
	mbutton_pause.SizeToContent();

	mbutton_rank.LoadBitmaps (IDB_BITMAP11,IDB_BITMAP_rankdown);
	mbutton_rank.SubclassDlgItem(IDC_BUTTON6,this);
	mbutton_rank.SizeToContent();

	mbutton_next.LoadBitmaps (IDB_BITMAP_successon,IDB_BITMAP_successdown);
	mbutton_next.SubclassDlgItem(IDC_BUTTON7,this);
	mbutton_next.SizeToContent();

	mbutton_continue.LoadBitmaps (IDB_BITMAP_continue,IDB_BITMAP_continuedown);
	mbutton_continue.SubclassDlgItem(IDC_BUTTON8,this);
	mbutton_continue.SizeToContent();

	mbutton_again.LoadBitmaps (IDB_BITMAP_failon,IDB_BITMAP_faildown);
	mbutton_again.SubclassDlgItem(IDC_BUTTON9,this);
	mbutton_again.SizeToContent();

	mbutton_look.LoadBitmaps (IDB_BITMAP_koon,IDB_BITMAP_kodown);
	mbutton_look.SubclassDlgItem(IDC_BUTTON10,this);
	mbutton_look.SizeToContent();

	mbutton_music.LoadBitmaps (IDB_BITMAP22,IDB_BITMAP23);
	mbutton_music.SubclassDlgItem(IDC_BUTTON12,this);
	mbutton_music.SizeToContent();

	mbutton_music_OFF.LoadBitmaps (IDB_BITMAP24,IDB_BITMAP25);
	mbutton_music_OFF.SubclassDlgItem(IDC_BUTTON13,this);
	mbutton_music_OFF.SizeToContent();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CHappyLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
//画背景
void CHappyLLKDlg::drawback(){
		CPaintDC   dc(this);   
        CRect   rect;   
        GetClientRect(&rect);   
        CDC   dcMem1;   
        dcMem1.CreateCompatibleDC(&dc);   
        
		CBitmap   bmpBackground; 
        bmpBackground.LoadBitmap(pic);   
                 //pic是图对应的ID   
        BITMAP   bitmap;   
        bmpBackground.GetBitmap(&bitmap);   
        CBitmap   *pbmpOld=dcMem1.SelectObject(&bmpBackground);   
        dc.StretchBlt(0,0,rect.Width(),rect.Height(),&dcMem1,0,0,   
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CHappyLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//draw bankspace
		drawback();
		CDialogEx::OnPaint();

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CHappyLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//画地图
void CHappyLLKDlg::draw(){

	CDC dcMemory;
	CBitmap* hOldBitMap;
	dcMemory.CreateCompatibleDC(pDC);
	//hOldBitMap = dcMemory.SelectObject(&m_bitmapOriginal);

	 CBitmap   bmpBackground; 
	 bmpBackground.LoadBitmap(pic);   
                 //pic是图对应的ID   
	 BITMAP   bitmap;   
	  bmpBackground.GetBitmap(&bitmap);   


	for(int row = 0;row<map_row_size;row++){
		for(int col = 0;col<map_col_size;col++){
			if(map[row][col]!=0){
				 hOldBitMap = dcMemory.SelectObject(&m_bitmapOriginal);
				 pDC->BitBlt(col*40+60,row*40+60,40,40,&dcMemory,0,map[row][col]*40,SRCCOPY);
			}
			else{
				 hOldBitMap = dcMemory.SelectObject(&bmpBackground);
				 pDC->BitBlt(col*40+60,row*40+60,40,40,&dcMemory,col*40+60,row*40+60,SRCCOPY);
				
			}
		}
	}

	
	

	dcMemory.SelectObject(hOldBitMap);
	dcMemory.DeleteDC();

	//newGame = false;
}

//画小图,550,60
void CHappyLLKDlg::drawPlayer2Board(){
	CDC dcMemory;
	CBitmap* hOldBitMap;
	dcMemory.CreateCompatibleDC(pDC);
	//hOldBitMap = dcMemory.SelectObject(&m_bitmapOriginal);

	CBitmap   bmpBackground; 
	bmpBackground.LoadBitmap(pic);   
	//pic是图对应的ID   
	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   

	if(mode==3){
		for(int row = 0;row<map_row_size;row++){
			for(int col = 0;col<map_col_size;col++){
				if(map_player2[row][col]!=0){
					hOldBitMap = dcMemory.SelectObject(&m_bitmapNet);
					pDC->BitBlt(col*20+550,row*20+60,20,20,&dcMemory,0,map_player2[row][col]*20,SRCCOPY);
				}
				else{
					hOldBitMap = dcMemory.SelectObject(&bmpBackground);
					pDC->BitBlt(col*20+550,row*20+60,20,20,&dcMemory,col*20+550,row*20+60,SRCCOPY);
				}
			}
		}
	}
	dcMemory.SelectObject(hOldBitMap);
	dcMemory.DeleteDC();
	
}

//更新分数
void CHappyLLKDlg::update_point(){
	CString point;
	point.Format(_T("%d"),poi);
	GetDlgItem( IDC_EDIT2 )->SetWindowTextW(point);
}

//开始页面start
void CHappyLLKDlg::start(){
	//隐藏模式按钮
	GetDlgItem(IDC_BUTTON1)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(FALSE);
	//static text图
	CBitmap bitmap;     
    HBITMAP hBmp;      
    bitmap.LoadBitmap(IDB_BITMAP12);   
    hBmp = (HBITMAP)bitmap.GetSafeHandle(); 
	m_number.SetBitmap(hBmp);

	CBitmap bitmap1;    
    HBITMAP hBmp1;      
    bitmap1.LoadBitmap(IDB_BITMAP13);    
    hBmp1 = (HBITMAP)bitmap1.GetSafeHandle();  
	m_point.SetBitmap(hBmp1);

	CBitmap bitmap2;    
    HBITMAP hBmp2;      
    bitmap2.LoadBitmap(IDB_BITMAP14);    
    hBmp2 = (HBITMAP)bitmap2.GetSafeHandle();  
	m_time.SetBitmap(hBmp2);

	//更新编辑框
	CString number;
	number.Format(_T("%d"),num);
	GetDlgItem( IDC_EDIT1 )->SetWindowTextW(number);

	update_point();

	//使可见
	GetDlgItem(IDC_BUTTON11)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON12)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(TRUE);
	//游戏背景
	pic=IDB_BITMAP8;

	Invalidate();
	UpdateWindow();
	draw();
}

void CHappyLLKDlg::time(int length){
	//进度条
	m_progress.SetRange (0,100);
	m_progress.SetPos(count);

	SetTimer(1,length,NULL);
}
//简单模式
void CHappyLLKDlg::OnBnClickedButton1()
{
	mode =1;
	generateMap();
	start();
	time(1000);	
}

//普通模式
void CHappyLLKDlg::OnBnClickedButton2()
{
	mode = 2;
	generateMap();
	start();
	time(1000);
}

//困难模式
void CHappyLLKDlg::OnBnClickedButton3()
{
	mode = 3;
	generateMap();
	start();
	time(1000);
}

//提示
void CHappyLLKDlg::OnBnClickedButton4()
{
	if(poi==0){
		return;
	}
	int index,direction;
	vertex v1,v2;
	gc->FindAPathInMap(v1,v2,index,direction);
	draw_edge(v1.row,v1.col,m_bitmapPrompt);
	draw_edge(v2.row,v2.col,m_bitmapPrompt);
	poi--;
	update_point();
}


//暂停
void CHappyLLKDlg::OnBnClickedButton5()
{
	KillTimer(1);
	
	GetDlgItem(IDC_BUTTON8)->ShowWindow(TRUE);

	GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);

	GetDlgItem(IDC_BUTTON12)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(FALSE);

	pic=IDB_BITMAP_pause;
	Invalidate();
	UpdateWindow();
}
//继续
void CHappyLLKDlg::OnBnClickedButton8()
{
	GetDlgItem(IDC_BUTTON8)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(FALSE);
	start();
	time(1000);
}


//排行榜
void CHappyLLKDlg::OnBnClickedButton6()
{
	ShowList();
}
void CHappyLLKDlg::ShowList()
{
	// 组长大大看这里，这里是排行榜显示
	// 输出
	FILE *fp;
	fp = fopen("./list.txt", "rb");
	if (fp != NULL)
	{
		record list[6];
		fread(list, sizeof(record) * 6, 1, fp);
		fclose(fp);
		// TODO: 界面
		GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON6)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
		GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
		GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON12)->ShowWindow(FALSE);
		GetDlgItem(IDC_BUTTON13)->ShowWindow(FALSE);
		pic = IDB_BITMAP_LIST;
		Invalidate();
		UpdateWindow();
		CFont font;

		VERIFY(font.CreatePointFont(300, _T("Tekton Pro"), pDC));//创建字体宋体格式  100为字高

		CFont *def_font = pDC->SelectObject(&font);  //选择该字体进入PDC



		pDC->SetBkMode(TRANSPARENT);//设置字体背景为透明
		// 输出分数
		for (int i = 0; i < 6; i++)
		{
			CString str_poi; str_poi.Format(L"%d", list[i].poi);
			pDC->TextOutW(500, 100 + i * 90, CString(list[i].name));
			pDC->TextOutW(750, 100 + i * 90, str_poi);
			/*poi = list[i].poi;
			draw_point(750, 100 + i * 90);*/
		}
		pDC->SelectObject(def_font);//恢复PDC的缺省字体



		// Done with the font.Delete the font object.

		font.DeleteObject();//释放font对象
	}
}

//计时器
void CHappyLLKDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent){
	case 1:
		if(count==0){
			KillTimer(1);
			fail();
		}
		else{
			count--;
			m_progress.SetPos(count);
		}
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}

//重画，加边
void CHappyLLKDlg::draw_edge(int row,int col,CBitmap& bitmap){
	CDC dcMemory;
	CBitmap* hOldBitMap;
	dcMemory.CreateCompatibleDC(pDC);
	hOldBitMap = dcMemory.SelectObject(&bitmap);

	pDC->BitBlt(col*40+60,row*40+60,40,40,&dcMemory,0,map[row][col]*40,SRCCOPY);
	dcMemory.SelectObject(hOldBitMap);
	dcMemory.DeleteDC();
}

//画分数
void CHappyLLKDlg::draw_point(int x,int y){
	CDC dcMemory;
	CBitmap* hOldBitMap;
	dcMemory.CreateCompatibleDC(pDC);
	hOldBitMap = dcMemory.SelectObject(&m_bitmapNumber);

	int ten=10000;
	int before=0;
	int current;
	int point=poi;
	for(int i=4;i>=1;i--){
		ten=ten/10;
		current=point/ten;
		if(before==0&&current==0)
			continue;
		else{
			pDC->BitBlt(before*30+x,y,30,50,&dcMemory,0,current*50,SRCCOPY);
			before++;
			point-=(current*ten);
		}  vc
	}
}

//成功啦
void CHappyLLKDlg::success(){
	PlaySound(_T("res\\ok.wav"), NULL, SND_FILENAME | SND_ASYNC);
	KillTimer(1);//new add
	poi+=count/10;
	
	forbid();
	GetDlgItem(IDC_BUTTON7)->ShowWindow(TRUE);
	/*GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);*/
	/*@@@@GetDlgItem(IDC_BUTTON12)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(FALSE);*/
	pic=IDB_BITMAP_success;
	Invalidate();
	UpdateWindow();
	draw_point(290,240);
}
//失败啦
void CHappyLLKDlg::fail(){
	if(mode!=3)
	
	forbid();
	GetDlgItem(IDC_BUTTON9)->ShowWindow(TRUE);
	/*GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);*/
	GetDlgItem(IDC_BUTTON12)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(FALSE);

	pic=IDB_BITMAP_fail;
	Invalidate();
	UpdateWindow();
	draw_point(555,70);
}

//当前模式通关啦
void CHappyLLKDlg::ko(){
	KillTimer(1);//new add
	poi+=count/10;
	
	forbid();
	GetDlgItem(IDC_BUTTON10)->ShowWindow(TRUE);
	/*GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);*/
	GetDlgItem(IDC_BUTTON12)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(TRUE);
	pic=IDB_BITMAP_ko;
	Invalidate();
	UpdateWindow();
}
//点击图片时获取坐标并获取图片
void CHappyLLKDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//success();
	int index,direction;
	
	int row=(point.y-60)/40;
	int col=(point.x-60)/40 ;
	if(col >0 && col < map_col_size-1 && row >0 && row < map_row_size-1 && map[row][col]!=0){ 
		PlaySound(_T("res\\suc.wav"), NULL, SND_FILENAME | SND_ASYNC);
		draw_edge(row,col,m_bitmapSelected);
		if(firstPoint.col==0&&firstPoint.row==0){
			firstPoint.row = row;
			firstPoint.col = col;
		}
		else{
			if(firstPoint.col!=(point.x-60)/40 || firstPoint.row!=(point.y-60)/40){
				secondPoint.row = (point.y-60)/40;
				secondPoint.col = (point.x-60)/40;
				if(gc->Remove(firstPoint,secondPoint,index,direction))   //如果找到路径 连线 消牌 重绘
				{
					
					if(mode==3){//网络模式
						//mark=false;
						char SendBuf[512] = {0};
						int index = 0;
						for(int i = 0;i<map_row_size;i++){
							for(int j = 0;j<map_col_size;j++){
								SendBuf[index++] = (char)map[i][j];
							}
						}
						m_ListSocket.Send(SendBuf,map_col_size*map_row_size);
					}
					PlaySound(_T("res\\bubble.wav"), NULL, SND_FILENAME | SND_ASYNC);
					draw_line(firstPoint, secondPoint, index, direction);
					Sleep(500);
					poi++;
					update_point();
				}
				draw();

				firstPoint.row = 0;firstPoint.col = 0;
				secondPoint.row = 0;secondPoint.col = 0;

				//成功啦
				if(gc->IsEmptyMap()){
					if((mode==1&&num==1)||(mode==2&&num==7)||(mode==3&&num==4))
					{
						ko();
						PlaySound(_T("res\\ok.wav"), NULL, SND_FILENAME | SND_ASYNC);
					}
					else{
						success();
						PlaySound(_T("res\\ok.wav"), NULL, SND_FILENAME | SND_ASYNC);
					}
					
				};

			}
		}
	}
		
	CDialogEx::OnLButtonDown(nFlags, point);
}
//画连线
void CHappyLLKDlg::draw_line(vertex firstPoint, vertex secondPoint, int index, int direction)
{
	CPen newPen;
	CPen *oldPen = nullptr;
	newPen.CreatePen(PS_SOLID, 5, RGB(205,150,205));
	oldPen = pDC->SelectObject(&newPen);

	CBitmap bitmap;
	////加载位图资源
	bitmap.LoadBitmap(IDB_BITMAP26);
	////创建位图画刷
	CBrush brush(&bitmap);
	//创建并获得设备描述符
	//利用位图画刷填充鼠标拖拽过程中形成的矩形区域

	//闪电图标
	CBitmap thC,thBW;
	thC.LoadBitmap(IDB_BITMAP27);
	thBW.LoadBitmap(IDB_BITMAP28);
	// device context for painting
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pbmpOld;
	////////////////////////////////

	if (direction == gc->direction_horizontal)
	{
		// 从fp x,y -> fp x,index y -> sp x,index y -> sp x,y
		pDC->FillRect(CRect(CPoint(60 + 40 * firstPoint.col + 16, 60 + 40 * firstPoint.row + 20),CPoint(60 + 40 * firstPoint.col + 24, 60 + 40 * index + 20)),&brush);
		pDC->FillRect(CRect(CPoint(60 + 40 * firstPoint.col + 20, 60 + 40 * index + 16),CPoint(60 + 40 * secondPoint.col + 20, 60 + 40 * index + 24)),&brush);
		pDC->FillRect(CRect(CPoint(60 + 40 * secondPoint.col + 16, 60 + 40 * index + 20),CPoint(60 + 40 * secondPoint.col + 24, 60 + 40 * secondPoint.row + 20)),&brush);
		//黑白图
		pbmpOld = memDC.SelectObject(&thBW);
		pDC->BitBlt(60 + 40 * firstPoint.col - 15, 60 + 40 * firstPoint.row - 15, 70, 70, &memDC, 0, 0, SRCPAINT); 
		//彩色图
		memDC.SelectObject(&thC);
		pDC->BitBlt(60 + 40 * firstPoint.col - 15, 60 + 40 * firstPoint.row - 15, 70, 70, &memDC, 0, 0, SRCAND); 
		//黑白图
		pbmpOld = memDC.SelectObject(&thBW);
		pDC->BitBlt(60 + 40 * secondPoint.col - 15, 60 + 40 * secondPoint.row - 15, 70, 70, &memDC, 0, 0, SRCPAINT); 
		//彩色图
		memDC.SelectObject(&thC);
		pDC->BitBlt(60 + 40 * secondPoint.col - 15, 60 + 40 * secondPoint.row - 15, 70, 70, &memDC, 0, 0, SRCAND); 
	}
	else if (direction == gc->direction_vertical)
	{
		// 从fp x,y -> index x,fp y -> index x,sp y -> sp x,y
		pDC->FillRect(CRect(CPoint(60 + 40 * firstPoint.col + 20, 60 + 40 * firstPoint.row + 16),CPoint(60 + 40 * index + 20, 60 + 40 * firstPoint.row + 24)),&brush);
		pDC->FillRect(CRect(CPoint(60 + 40 * index + 16, 60 + 40 * firstPoint.row + 20),CPoint(60 + 40 * index + 24, 60 + 40 * secondPoint.row + 20)),&brush);
		pDC->FillRect(CRect(CPoint(60 + 40 * index + 20, 60 + 40 * secondPoint.row + 16),CPoint(60 + 40 * secondPoint.col + 20, 60 + 40 * secondPoint.row + 24)),&brush);
		//黑白图
		pbmpOld = memDC.SelectObject(&thBW);
		pDC->BitBlt(60 + 40 * firstPoint.col - 15, 60 + 40 * firstPoint.row - 15, 70, 70, &memDC, 0, 0, SRCPAINT); 
		//彩色图
		memDC.SelectObject(&thC);
		pDC->BitBlt(60 + 40 * firstPoint.col - 15, 60 + 40 * firstPoint.row - 15, 70, 70, &memDC, 0, 0, SRCAND); 
		//黑白图
		pbmpOld = memDC.SelectObject(&thBW);
		pDC->BitBlt(60 + 40 * secondPoint.col - 15, 60 + 40 * secondPoint.row - 15, 70, 70, &memDC, 0, 0, SRCPAINT); 
		//彩色图
		memDC.SelectObject(&thC);
		pDC->BitBlt(60 + 40 * secondPoint.col - 15, 60 + 40 * secondPoint.row - 15, 70, 70, &memDC, 0, 0, SRCAND); 
	}
	newPen.DeleteObject();
	if (oldPen != nullptr)
	{
		oldPen->DeleteObject();
	}

}


//本关失败，重新开始此关
void CHappyLLKDlg::OnBnClickedButton9()
{
	GetDlgItem(IDC_BUTTON9)->ShowWindow(FALSE);
	generateMap();
	
	start();
	count=100;
	time(1000);
	poi=0;
}

//本关成功，继续游戏下一关
void CHappyLLKDlg::OnBnClickedButton7()
{
	PlaySound(_T("res\\ok.wav"), NULL, SND_FILENAME | SND_ASYNC);
	num++;
	generateMap();
	start();
	count=100;
	time(1000);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(FALSE);

}

//此模式通关→_→弹个框 请玩家输入名字 然后显示排行榜 balabalabala
void CHappyLLKDlg::OnBnClickedButton10()
{
	// 组长大大看这里，这里是用户名获取
	GetDlgItem(IDC_BUTTON10)->ShowWindow(FALSE);
	// 你是何方神圣？
	CAboutDlg *pDlg = new CAboutDlg(this);
	pDlg->poi = poi;
	pDlg->Create(IDD_ABOUTBOX, this);
	pDlg->ShowWindow(SW_SHOW);
	ShowList();
}

void CHappyLLKDlg::generateMap(){
	switch(mode){                                    //关数超过之后要怎么办呢 0.0
	case 1:
		int *map_would;
		char *filename;
		int dimension;
		switch(num){
		case 1:
			filename = "1.txt";
			break;
		case 2:
			filename = "2.txt";
			break;
		case 3:
			filename = "3.txt";
			break;
		case 4:
			filename = "4.txt";
			break;
		}
		map_would = readFromFile(filename,dimension);
		gc = new GameClass(dimension, dimension, 20, map_would);
		break;
	case 2:
		switch(num){
		case 1:
			gc = new GameClass(8,10,20);
			break;
		case 2:
			gc = new GameClass_Up(8,10,20);
			break;
		case 3:
			gc = new GameClass_Down(8,10,20);
			break;
		case 4:
			gc = new GameClass_Left(8,10,20);
			break;
		case 5:
			gc = new GameClass_Right(8,10,20);
			break;
		case 6:
			gc = new GameClass_Up_Down(8,10,20);
			break;
		case 7:
			gc = new GameClass_Left_Right(8,10,20);
			break;
		}
		break;
	case 3:  //双人对战模式
		switch(num){
		case 1:
			filename = "1.txt";
			break;
		case 2:
			filename = "2.txt";
			break;
		case 3:
			filename = "3.txt";
			break;
		case 4:
			filename = "4.txt";
			break;
		}


		map_would = readFromFile(filename,dimension);
		gc = new GameClass(dimension, dimension, 20, map_would);
		//gc->GetMap(map_player2,map_row_size,map_col_size,map_bmp_size);
		
	}
	gc->GetMap(map,map_row_size,map_col_size,map_bmp_size);
	
	//mark==true
	if(mode==3&&num==1){
		if (!m_ListSocket.Create())
		{
			MessageBox(_T("Socket Error!"));
			m_ListSocket.Close();
			PostQuitMessage(0);
			return;
		}
		// TODO: Add your control notification handler code here
		if (!m_ListSocket.Connect(_T("192.168.191.3"),6100))
		{
			int nErrorCode = m_ListSocket.GetLastError();
			if (nErrorCode!=WSAEWOULDBLOCK)
			{
				MessageBox(_T("Listen Error!"));
				m_ListSocket.Close();
				PostQuitMessage(0);
				return;
			}
		}

		map_player2 = new int *[map_row_size];
		for(int i =0;i<map_row_size;i++){
			map_player2[i] = new int [map_col_size];
			memset(map_player2[i],0,map_row_size*sizeof(int));
		}
		
	}
	
	//draw();
}

int* CHappyLLKDlg::readFromFile(char *filename,int& dimension){
	//FILE fin;
	ifstream readfile(filename);
	readfile>>dimension;
	//readfile.get(dimension);
	int *map_would = new int[dimension*dimension];
	for (int row = 0; row < dimension; row++)
		for (int column = 0; column < dimension; column++)
			readfile>>map_would[row*dimension+column];
			
	
	readfile.close();
	return map_would;
}

void CHappyLLKDlg::OnRvc(){
	char Rcv[513] = {0};
	m_ListSocket.Receive(Rcv,512);
	int index = 0;

	map_player2 = new int*[map_row_size];
	for (int i = 0; i < map_row_size; i++)
	{
		map_player2[i] = new int[map_col_size];
	}

	for(int i = 0;i<map_row_size;i++){
		for(int j = 0;j<map_col_size;j++){
			map_player2[i][j] = (int)Rcv[index++];
		}
	}
	drawPlayer2Board();
}

void CHappyLLKDlg::OnConnected(){
	MessageBox(_T("连接成功"));

	char SendBuf[512] = {0};
	int index = 0;
	for(int i = 0;i<map_row_size;i++){
		for(int j = 0;j<map_col_size;j++){
			SendBuf[index++] = (char)map[i][j];
		}
	}
	m_ListSocket.Send(SendBuf,map_col_size*map_row_size);
	
}

void CAboutDlg::OnBnClickedOk()
{
	// 排行榜修改
	// 更新排行榜然后关闭对话框
	CString name;
	GetDlgItemText(IDC_EDIT_NAME, name);
	// 如果排行榜文件不存在，创建新文件写入空白排行榜。
	FILE *fp = fopen("./list.txt", "rb");
	if (fp == NULL)
	{
		fp = fopen("./list.txt", "wb");
		record list[6];
		for (int i = 0; i < 6; i++)
		{
			strcpy(list[i].name, "NOBODY");
			list[i].poi = 0;
		}
		fwrite(list, sizeof(record) * 6, 1, fp);
		fflush(fp);
		fclose(fp);
		fp = fopen("./list.txt", "rb");
	}
	// 读取排行榜并进行更新。
	
	if (fp != NULL)
	{
		// 读取排行榜
		record list[6];
		fread(list, sizeof(record) * 6, 1, fp);
		fclose(fp);
		// 修改排行榜
		int i;
		for (i = 0; i < name.GetLength(); i++)
		{
			list[5].name[i] = name.GetAt(i);
			TRACE("Out> %c ", name.GetAt(i));
		}
		if (i < 12) list[5].name[i] = '\0';
		list[5].name[11] = '\0';
		list[5].poi = poi;
		for (int i = 0; i < 6; i++)	// 简单选择排序
		{
			int max_index = i;
			for (int j = i; j < 6; j++)
			{
				if (list[j].poi > list[max_index].poi)
				{
					max_index = j;
				}
			}
			// 交换list[i]和list[max_index]
			record record_temp;
			strcpy(record_temp.name, list[i].name);			record_temp.poi = list[i].poi;
			strcpy(list[i].name, list[max_index].name);		list[i].poi = list[max_index].poi;
			strcpy(list[max_index].name, record_temp.name);	list[max_index].poi = record_temp.poi;
		}
		// 写入排行榜
		fp = fopen("./list.txt", "wb");
		if (fp != NULL)
		{
			fwrite(list, sizeof(record) * 6, 1, fp);
			fflush(fp);
			fclose(fp);
		}
	}
	parent->ShowList();
	CDialogEx::OnOK();
}
void CHappyLLKDlg::forbid(){

	GetDlgItem(IDC_BUTTON4)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON5)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON6)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON9)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON10)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROGRESS1)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON12)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON13)->ShowWindow(FALSE);
}
//back home
void CHappyLLKDlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	KillTimer(1);
	GetDlgItem(IDC_BUTTON11)->ShowWindow(FALSE);
	pic=IDB_BITMAP1;

	GetDlgItem(IDC_BUTTON1)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(TRUE);

	forbid();
	Invalidate();
	UpdateWindow();
}


void CHappyLLKDlg::OnBnClickedButton12()
{
	// TODO: 在此添加控件通知处理程序代码
	music = true;
	handle1 = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)BackMusicThread,NULL,0,NULL);     
	CloseHandle(handle1);
}


void CHappyLLKDlg::OnBnClickedButton13()
{
	// TODO: 在此添加控件通知处理程序代码
	music = false;
}

DWORD WINAPI BackMusicThread(LPVOID lpParameter)
{
	mciSendString(_T("open res\\music.wav alias aa"),NULL,0,NULL); 
	mciSendString(_T("play aa"),NULL,0,NULL);

	while(music){}
	mciSendString(_T("stop aa"),NULL,0,NULL);

	return 0;
}