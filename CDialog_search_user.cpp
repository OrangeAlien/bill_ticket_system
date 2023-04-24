// CDialog_search_user.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_search_user.h"
#include "afxdialogex.h"


// CDialog_search_user 对话框

IMPLEMENT_DYNAMIC(CDialog_search_user, CDialogEx)

CDialog_search_user::CDialog_search_user(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
	, phone(_T(""))
	, name(_T(""))
	, id_(_T(""))
	, real_name(_T(""))
	, status(_T(""))
	, email(_T(""))
{

}

CDialog_search_user::~CDialog_search_user()
{
}

void CDialog_search_user::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, phone);
	DDV_MaxChars(pDX, phone, 11);
	DDX_Text(pDX, IDC_EDIT4, name);
	DDV_MaxChars(pDX, name, 32);
	DDX_Text(pDX, IDC_EDIT5, id_);
	DDV_MaxChars(pDX, id_, 18);
	DDX_Text(pDX, IDC_EDIT6, real_name);
	DDV_MaxChars(pDX, real_name, 32);
	DDX_CBString(pDX, IDC_COMBO2, status);
	DDV_MaxChars(pDX, status, 4);
	DDX_Text(pDX, IDC_EDIT7, email);
	DDV_MaxChars(pDX, email, 32);
}


BEGIN_MESSAGE_MAP(CDialog_search_user, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_search_user::OnBnClickedOk)
END_MESSAGE_MAP()


// CDialog_search_user 消息处理程序
BOOL CDialog_search_user::OnInitDialog()
{
	// TODO: 在此添加额外的初始化代码
	CDialogEx::OnInitDialog();
	m_list.InsertColumn(0, TEXT("手机号"), LVCFMT_LEFT, 90);
	m_list.InsertColumn(1, TEXT("用户名"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(2, TEXT("身份证号"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(3, TEXT("姓名"), LVCFMT_LEFT, 100);
	m_list.InsertColumn(4, TEXT("身份"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(5, TEXT("电子邮件"), LVCFMT_LEFT, 150);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	MYSQL m_mysql;			//数据库结构
	mysql_init(&m_mysql);//初始化数据库对象
	mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
	//////////////////////////////////////////////////////
	MYSQL_RES* m_res;         //查询的返回结果集
	MYSQL_ROW m_row;          //获取每一条记录
	std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条
	char query[] = "select user_phone,user_name,`id`,real_name,status,email from user";
	mysql_query(&m_mysql, "set names 'gb2312'");
	mysql_real_query(&m_mysql, query, strlen(query));//查询函数，语句用字符串表示
	m_res = mysql_store_result(&m_mysql);//得到查询结果
										 //从数据库获取数据
	int i = 0;
	while (m_row = mysql_fetch_row(m_res))
	{
		m_data[i].push_back(m_row[0]);
		m_data[i].push_back(m_row[1]);
		m_data[i].push_back(m_row[2]);
		m_data[i].push_back(m_row[3]);
		m_data[i].push_back(m_row[4]);
		m_data[i++].push_back(m_row[5]);
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < m_res->row_count; i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());
		for (int j = 0; j < 6; j++)
			m_list.SetItemText(iCount, j, m_data[i][j].c_str());
	}
	//释放结果集
	mysql_free_result(m_res);
	//关闭数据库
	mysql_close(&m_mysql);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialog_search_user::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(phone);
	GetDlgItem(IDC_EDIT4)->GetWindowText(name);
	GetDlgItem(IDC_EDIT5)->GetWindowText(id_);
	GetDlgItem(IDC_EDIT6)->GetWindowText(real_name);
	GetDlgItem(IDC_COMBO2)->GetWindowText(status);
	GetDlgItem(IDC_EDIT7)->GetWindowText(email);
	MYSQL m_mysql;			//数据库结构
	mysql_init(&m_mysql);//初始化数据库对象
	mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
	//////////////////////////////////////////////////////
	char* in_phone = (char*)phone.GetBuffer();
	char* in_name = (char*)name.GetBuffer();
	char* in_id = (char*)id_.GetBuffer();
	char* in_real_name = (char*)real_name.GetBuffer();
	char* in_status = (char*)status.GetBuffer();
	char* in_email = (char*)email.GetBuffer();
	char query[1000];
	sprintf_s(query, "select user_phone,user_name,`id`,real_name,status,email from user where user_phone like '%s%%' and user_name like '%s%%' and `id` like '%s%%' and real_name like '%s%%' and status like '%s%%' and email like '%s%%'", in_phone, in_name, in_id, in_real_name, in_status, in_email);
	mysql_query(&m_mysql, "set names 'gb2312'");
	mysql_real_query(&m_mysql, query, strlen(query));//查询函数，语句用字符串表示
	MessageBox(_T("查询成功!"), _T("提示"));
	MYSQL_RES* m_res;         //查询的返回结果集
	MYSQL_ROW m_row;          //获取每一条记录
	std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条
	m_res = mysql_store_result(&m_mysql);//得到查询结果
										 //从数据库获取数据
	int i = 0;
	while (m_row = mysql_fetch_row(m_res))
	{
		m_data[i].push_back(m_row[0]);
		m_data[i].push_back(m_row[1]);
		m_data[i].push_back(m_row[2]);
		m_data[i].push_back(m_row[3]);
		m_data[i].push_back(m_row[4]);
		m_data[i++].push_back(m_row[5]);
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < m_res->row_count; i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());
		for (int j = 0; j < 6; j++)
			m_list.SetItemText(iCount, j, m_data[i][j].c_str());
	}
	//释放结果集
	mysql_free_result(m_res);
	//关闭数据库
	mysql_close(&m_mysql);
}
