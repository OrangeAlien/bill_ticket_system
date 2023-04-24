#pragma once


// CDialog_bill 对话框

class CDialog_bill : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_bill)

public:
	CDialog_bill(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_bill();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL CDialog_bill::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
