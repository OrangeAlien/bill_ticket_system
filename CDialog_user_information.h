#pragma once


// CDialog_user_information 对话框

class CDialog_user_information : public CDialogEx
{
	DECLARE_DYNAMIC(CDialog_user_information)

public:
	CDialog_user_information(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDialog_user_information();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	DECLARE_MESSAGE_MAP()
public:
	CEdit phone_edit;
	CString phone;
	CEdit name_edit;
	CString name;
	CEdit password_edit;
	CString password;
	CEdit id_edit;
	CString id_;
	CEdit real_name_edit;
	CString real_name;
	CComboBox status_combobox;
	CString status;
	CEdit email_edit;
	CString email;
	BOOL CDialog_user_information::OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
