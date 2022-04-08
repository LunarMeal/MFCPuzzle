
// MFCPuzzleDlg.h: 头文件
//

#pragma once
#include <string>

// CMFCPuzzleDlg 对话框
class CMFCPuzzleDlg : public CDialogEx
{
// 友元
	friend void solving(CMFCPuzzleDlg* CDlg);

// 构造
public:
	CMFCPuzzleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCPUZZLE_DIALOG };
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
private:
	CFont cfont;
public:
	afx_msg void OnBnClickedButton1();
private:
	CString m_password;
	CEdit* edit;
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
private:
	CString m_tip1;
	CString m_tip2;
	CString m_tip3;
	CString m_tip4;
	CString m_tip5;
	CString m_statu;
	bool pause;
public:
	afx_msg void OnBnClickedButton2();
private:
	CString m_q1;
	CString m_q2;
	CString m_q3;
	CString m_q4;
	CString m_q5;
	CString m_answer;
	std::string answer;
	virtual void OnOK();
public:
	CButton m_btn1;
	CButton m_btn2;
};
