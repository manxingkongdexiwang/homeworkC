
// snakeDlg.h: 头文件
//

#pragma once
#include"Gsnake.h"
#include"snake.h"

// CsnakeDlg 对话框
class CsnakeDlg : public CDialogEx
{
// 构造
public:
	CsnakeDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SNAKE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	Snake snake1;//单人玩家蛇类
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawSnake();
	virtual BOOL PreTranslateMessage(MSG* pMsg);//键盘控制函数
	CPoint Food;//食物生成函数
	CPoint GenerateFood(vector<CPoint>& snakeBody, int maxX, int maxY);

	int score;//分数
	int difficulty;//难度
	CEdit m_difficulty;
	CEdit m_score;
	afx_msg void OnPause();
	afx_msg void OnContinue();
	afx_msg void OnExit();
};
