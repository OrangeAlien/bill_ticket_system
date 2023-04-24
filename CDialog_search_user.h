#pragma once


// CDialog_search_user 对话框

class CDialog_search_user : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_search_user)

public:
	CDialog_search_user(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_search_user();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL CDialog_search_user::OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_list;
	CString phone;
	CString name;
	CString id_;
	CString real_name;
	CString status;
	CString email;
	afx_msg void OnBnClickedOk();
};
