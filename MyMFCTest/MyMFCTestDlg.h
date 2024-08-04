
// MyMFCTestDlg.h: 头文件
//

#pragma once

#define MY_TESTCOM WM_USER+200

// CMyMFCTestDlg 对话框
class CMyMFCTestDlg : public CDialogEx
{
// 构造
public:
	CMyMFCTestDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYMFCTEST_DIALOG };
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
//	BOOL m_ck3;
//	BOOL m_ck6;
	afx_msg void OnBnClickedButton1();
	BOOL m_ck5;
	CButton m_ck2;
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
//	afx_msg LRESULT OnMyCommand1(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnBnClickedButton2();
protected:
	afx_msg LRESULT OnMyTestcom(WPARAM wParam, LPARAM lParam);
};
