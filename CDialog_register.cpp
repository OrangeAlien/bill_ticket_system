// CDialog_register.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_register.h"
#include "afxdialogex.h"

// CDialog_register 对话框

IMPLEMENT_DYNAMIC(CDialog_register, CDialogEx)

CDialog_register::CDialog_register(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, phone(_T(""))
	, name(_T(""))
	, password(_T(""))
	, id_(_T(""))
	, real_name(_T(""))
	, status(_T(""))
	, email(_T(""))
{

}

CDialog_register::~CDialog_register()
{
}

void CDialog_register::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, phone);
	DDV_MaxChars(pDX, phone, 11);
	DDX_Text(pDX, IDC_EDIT2, name);
	DDV_MaxChars(pDX, name, 32);
	DDX_Text(pDX, IDC_EDIT3, password);
	DDV_MaxChars(pDX, password, 16);
	DDX_Text(pDX, IDC_EDIT4, id_);
	DDV_MaxChars(pDX, id_, 18);
	DDX_Text(pDX, IDC_EDIT5, real_name);
	DDV_MaxChars(pDX, real_name, 32);
	DDX_CBString(pDX, IDC_COMBO2, status);
	DDV_MaxChars(pDX, status, 4);
	DDX_Text(pDX, IDC_EDIT6, email);
	DDV_MaxChars(pDX, email, 32);
}


BEGIN_MESSAGE_MAP(CDialog_register, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_register::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialog_register::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialog_register 消息处理程序


void CDialog_register::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(phone);
	GetDlgItem(IDC_EDIT2)->GetWindowText(name);
	GetDlgItem(IDC_EDIT3)->GetWindowText(password);
	GetDlgItem(IDC_EDIT4)->GetWindowText(id_);
	GetDlgItem(IDC_EDIT5)->GetWindowText(real_name);
	GetDlgItem(IDC_COMBO2)->GetWindowText(status);
	GetDlgItem(IDC_EDIT6)->GetWindowText(email);
	char query[1000];
	if (phone.IsEmpty() || password.IsEmpty() || id_.IsEmpty()|| real_name.IsEmpty() || (status !="军人" && status != "学生" && status != "普通"))
	{
		MessageBox(_T("注册信息不合法\n注册失败！"), _T("提示"));
		return;
	}
	char* in_phone = (char*)phone.GetBuffer();
	char* in_name = (char*)name.GetBuffer();
	char* in_password = (char*)password.GetBuffer();
	char* in_id = (char*)id_.GetBuffer();
	char* in_real_name = (char*)real_name.GetBuffer();
	char* in_status = (char*)status.GetBuffer();
	char* in_email = (char*)email.GetBuffer();
	sprintf_s(query, "call user_register('%s','%s','%s','%s','%s','%s','%s')", in_phone, in_name, in_password, in_id, in_real_name, in_status, in_email);
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (mysql_real_connect(&m_sqlCon, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0))
	{
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		//MessageBox(_T("连接数据库成功!"), _T("提示"));
		if (mysql_query(&m_sqlCon, query) == 0)
		{
			MessageBox(_T("注册成功!"), _T("提示"));
			return;
		}
		else
		{
			MessageBox(_T("已被注册\n注册失败!"), _T("提示"));
			return;
		}
		mysql_close(&m_sqlCon);
	}
	else
	{
		MessageBox(_T("连接数据库失败!"), _T("提示"));
		mysql_close(&m_sqlCon);
	}
	CDialogEx::OnOK();
}


void CDialog_register::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
