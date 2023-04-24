#pragma once


// CDialog_register 对话框

class CDialog_register : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_register)

public:
	CDialog_register(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_register();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString phone;
	CString name;
	CString password;
	CString id_;
	CString real_name;
	CString status;
	CString email;
};
