#pragma once


// CDialog_administrator_information 对话框

class CDialog_administrator_information : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_administrator_information)

public:
	CDialog_administrator_information(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_administrator_information();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	//BOOL CDialog_administrator_information::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit phone_edit;
	CString phone;
	CEdit name_edit;
	CString name;
	CEdit password_edit;
	CString password;
	BOOL CDialog_administrator_information::OnInitDialog();
};
