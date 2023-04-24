// CDialog_user_information.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_user_information.h"
#include "bill_ticket_systemDlg.h"
#include "afxdialogex.h"


// CDialog_user_information 对话框

IMPLEMENT_DYNAMIC(CDialog_user_information, CDialogEx)

CDialog_user_information::CDialog_user_information(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, phone(_T(""))
	, name(_T(""))
	, password(_T(""))
	, id_(_T(""))
	, real_name(_T(""))
	, status(_T(""))
	, email(_T(""))
{

}

CDialog_user_information::~CDialog_user_information()
{
}

void CDialog_user_information::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, phone_edit);
	DDX_Text(pDX, IDC_EDIT1, phone);
	DDV_MaxChars(pDX, phone, 11);
	DDX_Control(pDX, IDC_EDIT5, name_edit);
	DDX_Text(pDX, IDC_EDIT5, name);
	DDV_MaxChars(pDX, name, 32);
	DDX_Control(pDX, IDC_EDIT4, password_edit);
	DDX_Text(pDX, IDC_EDIT4, password);
	DDV_MaxChars(pDX, password, 16);
	DDX_Control(pDX, IDC_EDIT6, id_edit);
	DDX_Text(pDX, IDC_EDIT6, id_);
	DDV_MaxChars(pDX, id_, 18);
	DDX_Control(pDX, IDC_EDIT7, real_name_edit);
	DDX_Text(pDX, IDC_EDIT7, real_name);
	DDV_MaxChars(pDX, real_name, 32);
	DDX_Control(pDX, IDC_COMBO2, status_combobox);
	DDX_CBString(pDX, IDC_COMBO2, status);
	DDV_MaxChars(pDX, status, 4);
	DDX_Control(pDX, IDC_EDIT8, email_edit);
	DDX_Text(pDX, IDC_EDIT8, email);
	DDV_MaxChars(pDX, email, 32);
}


BEGIN_MESSAGE_MAP(CDialog_user_information, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_user_information::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_user_information::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDialog_user_information 消息处理程序
BOOL CDialog_user_information::OnInitDialog()
{
	// TODO: 在此添加额外的初始化代码
	CDialogEx::OnInitDialog();
	MYSQL m_mysql;			//数据库结构
	mysql_init(&m_mysql);//初始化数据库对象
	mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
	MYSQL_RES* m_res;         //查询的返回结果集
	MYSQL_ROW m_row;          //获取每一条记录
	std::vector<std::string> m_data;  //存放数据库记录
	char query[1000];
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query,"call user_show('%s', @out_user_phone, @out_user_name, @out_user_password, @out_id, @out_real_name, @out_status, @out_eamil)",app->PHONE);
	mysql_query(&m_mysql, "set names 'gb2312'");
	mysql_query(&m_mysql, query);//查询函数，语句用字符串表示
	mysql_query(&m_mysql, "select @out_user_phone, @out_user_name, @out_user_password, @out_id, @out_real_name, @out_status, @out_eamil");
	m_res = mysql_store_result(&m_mysql);//得到查询结果
	m_row = mysql_fetch_row(m_res);//从数据库获取数据
		m_data.push_back(m_row[0]);
		m_data.push_back(m_row[1]);
		m_data.push_back(m_row[2]);
		m_data.push_back(m_row[3]);
		m_data.push_back(m_row[4]);
		m_data.push_back(m_row[5]);
		m_data.push_back(m_row[6]);
		phone = m_data[0].c_str();
		name = m_data[1].c_str();
		password = m_data[2].c_str();
		id_ = m_data[3].c_str();
		real_name = m_data[4].c_str();
		status = m_data[5].c_str();
		email = m_data[6].c_str();
		phone_edit.SetWindowTextA(phone);
		name_edit.SetWindowTextA(name);
		password_edit.SetWindowTextA(password);
		id_edit.SetWindowTextA(id_);
		real_name_edit.SetWindowTextA(real_name);
		status_combobox.SetWindowTextA(status);
		email_edit.SetWindowTextA(email);
	mysql_free_result(m_res);//释放结果集
	mysql_close(&m_mysql);//关闭数据库
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



void CDialog_user_information::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDialog_user_information::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT5)->GetWindowText(name);
	GetDlgItem(IDC_EDIT4)->GetWindowText(password);
	GetDlgItem(IDC_COMBO2)->GetWindowText(status);
	GetDlgItem(IDC_EDIT8)->GetWindowText(email);
	if (password.IsEmpty() ||(status != "军人" && status != "学生" && status != "普通"))
	{
		MessageBox(_T("修改信息不合法\n注册失败！"), _T("提示"));
		return;
	}
	char query[1000];
	char* in_name = (char*)name.GetBuffer();
	char* in_password = (char*)password.GetBuffer();
	char* in_status = (char*)status.GetBuffer();
	char* in_email = (char*)email.GetBuffer();
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query, "call user_modify('%s','%s','%s','%s','%s')", app->PHONE, in_name, in_password, in_status, in_email);
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (mysql_real_connect(&m_sqlCon, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0))
	{
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		if (mysql_query(&m_sqlCon, query) == 0)
		{
			MessageBox(_T("修改成功!"), _T("提示"));
			return;
		}
		else
		{
			MessageBox(_T("修改失败!"), _T("提示"));
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

