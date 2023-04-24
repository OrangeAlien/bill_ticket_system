// CDialog_administrator_information.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_administrator_information.h"
#include "bill_ticket_systemDlg.h"
#include "afxdialogex.h"


// CDialog_administrator_information 对话框

IMPLEMENT_DYNAMIC(CDialog_administrator_information, CDialogEx)

CDialog_administrator_information::CDialog_administrator_information(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
	, phone(_T(""))
	, name(_T(""))
	, password(_T(""))
{

}

CDialog_administrator_information::~CDialog_administrator_information()
{
}

void CDialog_administrator_information::DoDataExchange(CDataExchange* pDX)
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
}


BEGIN_MESSAGE_MAP(CDialog_administrator_information, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_administrator_information::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_administrator_information::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_administrator_information::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialog_administrator_information 消息处理程序
BOOL CDialog_administrator_information::OnInitDialog()
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
	sprintf_s(query, "call administrator_show('%s', @out_administrator_phone, @out_administrator_name, @out_administrator_password)", app->PHONE);
	mysql_query(&m_mysql, "set names 'gb2312'");
	mysql_query(&m_mysql, query);//查询函数，语句用字符串表示
	mysql_query(&m_mysql, "select @out_administrator_phone, @out_administrator_name, @out_administrator_password");
	m_res = mysql_store_result(&m_mysql);//得到查询结果
	m_row = mysql_fetch_row(m_res);//从数据库获取数据
	m_data.push_back(m_row[0]);
	m_data.push_back(m_row[1]);
	m_data.push_back(m_row[2]);
	phone = m_data[0].c_str();
	name = m_data[1].c_str();
	password = m_data[2].c_str();
	phone_edit.SetWindowTextA(phone);
	name_edit.SetWindowTextA(name);
	password_edit.SetWindowTextA(password);
	mysql_free_result(m_res);//释放结果集
	mysql_close(&m_mysql);//关闭数据库
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDialog_administrator_information::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDialog_administrator_information::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT5)->GetWindowText(name);
	GetDlgItem(IDC_EDIT4)->GetWindowText(password);
	if (password.IsEmpty())
	{
		MessageBox(_T("修改信息不合法\n修改失败！"), _T("提示"));
		return;
	}
	char query[1000];
	char* in_name = (char*)name.GetBuffer();
	char* in_password = (char*)password.GetBuffer();
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query, "call administrator_modify('%s','%s','%s')", app->PHONE, in_name, in_password);
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



void CDialog_administrator_information::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
