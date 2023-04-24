#pragma once


// CDialog_user_ticket 对话框

class CDialog_user_ticket : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_user_ticket)

public:
	CDialog_user_ticket(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_user_ticket();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL CDialog_user_ticket::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CString old_ticket_no;
	CString new_ticket_no;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
