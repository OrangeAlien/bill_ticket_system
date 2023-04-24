
// bill_ticket_systemDlg.h: 头文件
//

#pragma once


// CbillticketsystemDlg 对话框
class CbillticketsystemDlg : public CDialogEx
{
	// 构造
public:
	CbillticketsystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BILL_TICKET_SYSTEM_DIALOG };
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedYes();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	CString phone;
	CString password;
	afx_msg void OnCbnSelchangeCombo1();
	CString status;
};
