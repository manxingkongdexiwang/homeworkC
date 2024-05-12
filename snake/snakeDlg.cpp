
// snakeDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "snake.h"
#include "snakeDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CsnakeDlg 对话框



CsnakeDlg::CsnakeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SNAKE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CsnakeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CsnakeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_32771, &CsnakeDlg::OnStart)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CsnakeDlg 消息处理程序

BOOL CsnakeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	CWnd* pWnd;
	pWnd = GetDlgItem(IDC_GAMEAREA);
	pWnd->SetWindowPos(NULL, 0, 0, 800, 800, SWP_NOZORDER | SWP_NOMOVE);    //把编辑控件的大小设为(100,80)
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CsnakeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CsnakeDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CsnakeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CsnakeDlg::OnStart()
{
	// TODO: 在此添加命令处理程序代码
	snake1.Init();

	SetTimer(1, 200, NULL);//启动ID为1的定时器，定时时间为1s
	Food = GenerateFood(snake1.GetBody(), 20, 20);//生成食物
	DrawSnake();//点击开始菜单，就把蛇绘制在框中
}

void CsnakeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	snake1.Move(Food);
	if (snake1.CheckCollision())
	{
		KillTimer(1);
		MessageBox(TEXT("小蛇嘎掉了"),TEXT("提示"));
		return;
	}
	if (snake1.ateFood) {
		Food = GenerateFood(snake1.GetBody(), 20, 20);//生成食物
		snake1.ateFood = false;
	}//如果吃到食物，继续生成食物
	DrawSnake();


	CDialogEx::OnTimer(nIDEvent);
}
//定时器的响应函数,在打开菜单点击开始之后按照顺序运行的函数
void CsnakeDlg::DrawSnake()
{
	CWnd* pWnd = GetDlgItem(IDC_GAMEAREA);//对话框指针
	pWnd->Invalidate();//标记控件为无效
	pWnd->UpdateWindow();//强制刷新控件
	CDC* pDC = pWnd->GetDC();//绘图设备指针

	snake1.Draw(pDC);

	CBrush brush(RGB(100, 30, 255)); // 使用画刷绘制食物
	int left = Food.x * BodySize; // 食物的大小为BodySize*BodySize，计算绘制位置
	int top = Food.y * BodySize;
	int right = left + BodySize;
	int bottom = top + BodySize;
	pDC->SelectObject(&brush);
	pDC->Rectangle(left, top, right, bottom); // 绘制食物

	ReleaseDC(pDC);
}


BOOL CsnakeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam) {
		case VK_UP:
			snake1.SetDirection(Direction::UP);
			break;
		case VK_DOWN:
			snake1.SetDirection(Direction::DOWN);
			break;
		case VK_LEFT:
			snake1.SetDirection(Direction::LEFT);
			break;
		case VK_RIGHT:
			snake1.SetDirection(Direction::RIGHT);
			break;
		}
	}//判断按键来改变蛇的方向
	return CDialogEx::PreTranslateMessage(pMsg);
}

CPoint CsnakeDlg::GenerateFood(vector<CPoint>& snakeBody, int maxX, int maxY)
{

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> xDist(0, maxX - 1); // 食物的 x 坐标范围，0-19的随机数
	uniform_int_distribution<int> yDist(0, maxY - 1); // 食物的 y 坐标范围

	int foodX, foodY;
	do {
		// 随机生成食物坐标
		foodX = xDist(gen);
		foodY = yDist(gen);
		// 检查生成的食物是否在蛇的身体上，如果是，重新生成，保证随机数不在蛇的身体上
	} while (any_of(snakeBody.begin(), snakeBody.end(), [&](const CPoint& p) {
		return p.x == foodX && p.y == foodY;
		}));

	return CPoint(foodX, foodY);
}
