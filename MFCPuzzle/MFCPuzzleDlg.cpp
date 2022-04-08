
// MFCPuzzleDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCPuzzle.h"
#include "MFCPuzzleDlg.h"
#include "afxdialogex.h"
#include "PuzzleLock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <thread>

#define INITTIME "02:30"

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


// CMFCPuzzleDlg 对话框



CMFCPuzzleDlg::CMFCPuzzleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCPUZZLE_DIALOG, pParent)
	, m_password(_T(""))
	, m_tip1(_T(""))
	, m_tip2(_T(""))
	, m_tip3(_T(""))
	, m_tip4(_T(""))
	, m_tip5(_T(""))
	, m_statu(_T(""))
	, m_q1(_T(""))
	, m_q2(_T(""))
	, m_q3(_T(""))
	, m_q4(_T(""))
	, m_q5(_T(""))
	, m_answer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCPuzzleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_password);
	DDX_Text(pDX, IDC_T1, m_tip1);
	DDX_Text(pDX, IDC_T2, m_tip2);
	DDX_Text(pDX, IDC_T3, m_tip3);
	DDX_Text(pDX, IDC_T4, m_tip4);
	DDX_Text(pDX, IDC_T5, m_tip5);
	DDX_Text(pDX, IDC_STATU, m_statu);
	DDX_Text(pDX, IDC_Q1, m_q1);
	DDX_Text(pDX, IDC_Q2, m_q2);
	DDX_Text(pDX, IDC_Q3, m_q3);
	DDX_Text(pDX, IDC_Q4, m_q4);
	DDX_Text(pDX, IDC_Q5, m_q5);
	DDX_Text(pDX, IDC_EDIT2, m_answer);
	DDX_Control(pDX, IDC_BUTTON1, m_btn1);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
}

BEGIN_MESSAGE_MAP(CMFCPuzzleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCPuzzleDlg::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCPuzzleDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMFCPuzzleDlg 消息处理程序

BOOL CMFCPuzzleDlg::OnInitDialog()
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
	srand((unsigned int)time(NULL));

	CWnd* pWnd = GetDlgItem(IDC_TIME);
	cfont.CreatePointFont(360, _T("黑体"), NULL);
	pWnd->SetFont(&cfont);

	edit = (CEdit*)this->GetDlgItem(IDC_EDIT1);
	CEdit* pEdit = (CEdit*)this->GetDlgItem(IDC_EDIT2);
	pEdit->SetLimitText(3);

	m_btn2.EnableWindow(false);
	pause = false;	//不暂停
	m_password = TEXT("???");
	GetDlgItem(IDC_TIME)->SetWindowTextA(TEXT(INITTIME));
	m_statu = TEXT("单击生成题目开始游戏");
	m_q1 = TEXT("条件1");
	m_q2 = TEXT("条件2");
	m_q3 = TEXT("条件3");
	m_q4 = TEXT("条件4");
	m_q5 = TEXT("条件5");
	m_tip1 = TEXT("???");
	m_tip2 = TEXT("???");
	m_tip3 = TEXT("???");
	m_tip4 = TEXT("???");
	m_tip5 = TEXT("???");
	UpdateData(false);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCPuzzleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCPuzzleDlg::OnPaint()
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
HCURSOR CMFCPuzzleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void solving(CMFCPuzzleDlg *CDlg)
{
	CDlg->GetDlgItem(IDC_TIME)->SetWindowTextA(TEXT(INITTIME));
	CDlg->m_statu = TEXT("答题中...");
	CDlg->UpdateData(false);
	int second = 30;
	for (int minute = 2; minute >= 0; minute--) {
		for (; second >= 0; second--) {
			char buffer[128];
			sprintf_s(buffer, "%02d:%02d", minute, second);
			CDlg->GetDlgItem(IDC_TIME)->SetWindowTextA(buffer);
			Sleep(960);
			if (CDlg->pause) {
				//先关闭暂停
				CDlg->pause = false;
				//检查答案
				if (CDlg->answer == PuzzleLock::getResult()) {
					CDlg->m_statu = TEXT("恭喜！你答对了\n点击生成问题按钮重新开始");
				}
				else {
					CDlg->m_statu = TEXT("差一点就猜对了，继续努力\n点击生成问题按钮重新开始");
				}
				CDlg->UpdateData(false);
				return;
			}
		}
		second = 59;
	}
	CDlg->m_btn1.EnableWindow(true);
	CDlg->m_btn2.EnableWindow(false);
	CDlg->m_statu = TEXT("抱歉，你超时了！\n点击生成问题按钮重新开始");
	CDlg->UpdateData(false);
}



void CMFCPuzzleDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	m_btn1.EnableWindow(false);
	m_btn2.EnableWindow(true);
	edit->SetPasswordChar('*');
	edit->RedrawWindow(NULL, NULL);
	std::string tip[5];
	std::vector<std::string> question = PuzzleLock::getQuestion();
	for (int i = 0; i < 5; i++) {
		tip[i] = question[i].substr(0, 3);
		question[i].erase(0, 3);
	}
	m_password = PuzzleLock::getResult().c_str();
	m_tip1 = tip[0].c_str();
	m_tip2 = tip[1].c_str();
	m_tip3 = tip[2].c_str();
	m_tip4 = tip[3].c_str();
	m_tip5 = tip[4].c_str();
	m_q1 = question[0].c_str();
	m_q2 = question[1].c_str();
	m_q3 = question[2].c_str();
	m_q4 = question[3].c_str();
	m_q5 = question[4].c_str();
	std::thread td(solving,this);
	td.detach();
}


HBRUSH CMFCPuzzleDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	if (pWnd->GetDlgCtrlID() == IDC_TIME) {
		pDC->SetTextColor(RGB(255, 0, 0));
	}
	if (pWnd->GetDlgCtrlID() == IDC_STATU) {
		pDC->SetTextColor(RGB(255, 0, 0));
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


void CMFCPuzzleDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	answer = m_answer;
	edit->SetPasswordChar(0);
	edit->RedrawWindow(NULL, NULL);
	m_btn1.EnableWindow(true);
	m_btn2.EnableWindow(false);
	pause = true;
}


void CMFCPuzzleDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}
