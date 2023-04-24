#pragma once


// CDialog_administrator 对话框

class CDialog_administrator : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_administrator)

public:
	CDialog_administrator(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_administrator();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
};
