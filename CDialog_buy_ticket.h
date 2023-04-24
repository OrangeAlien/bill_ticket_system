#pragma once


// CDialog_buy_ticket 对话框

class CDialog_buy_ticket : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_buy_ticket)

public:
	CDialog_buy_ticket(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_buy_ticket();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL CDialog_buy_ticket::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CString starting_station;
	CString terminal_station;
	CString type;
	CString date;
	CString ticket_no;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClicked2();

};
