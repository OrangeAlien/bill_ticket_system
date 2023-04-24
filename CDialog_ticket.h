#pragma once


// CDialog_ticket 对话框

class CDialog_ticket : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_ticket)

public:
	CDialog_ticket(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_ticket();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL CDialog_ticket::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CString ticket_no;
	CString train_no;
	CString type;
	CString carriage;
	CString sit;
	CString price;
	CString starting_station;
	CString terminal_station;
	CString leaving_time;
	CString arrival_time;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
