// CDialog_user_ticket.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_user_ticket.h"
#include "CDialog_buy_ticket.h"
#include "afxdialogex.h"


// CDialog_user_ticket 对话框

IMPLEMENT_DYNAMIC(CDialog_user_ticket, CDialogEx)

CDialog_user_ticket::CDialog_user_ticket(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
	, old_ticket_no(_T(""))
	, new_ticket_no(_T(""))
{

}

CDialog_user_ticket::~CDialog_user_ticket()
{
}

void CDialog_user_ticket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST3, m_list);
	DDX_Text(pDX, IDC_EDIT1, old_ticket_no);
	DDV_MaxChars(pDX, old_ticket_no, 10);
	DDX_Text(pDX, IDC_EDIT4, new_ticket_no);
	DDV_MaxChars(pDX, new_ticket_no, 10);
}


BEGIN_MESSAGE_MAP(CDialog_user_ticket, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_user_ticket::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_user_ticket::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_user_ticket::OnBnClickedButton2)
END_MESSAGE_MAP()


// CDialog_user_ticket 消息处理程序
BOOL CDialog_user_ticket::OnInitDialog()
{
	// TODO: 在此添加额外的初始化代码
	CDialogEx::OnInitDialog();
	m_list.InsertColumn(0, TEXT("身份证号"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(1, TEXT("姓名"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(2, TEXT("车票号"), LVCFMT_LEFT, 60);
	m_list.InsertColumn(3, TEXT("车次"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(4, TEXT("类型"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(5, TEXT("车厢号"), LVCFMT_LEFT, 50); 
	m_list.InsertColumn(6, TEXT("座位号"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(7, TEXT("价格"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(8, TEXT("起点站"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(9, TEXT("终点站"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(10, TEXT("发车时间"), LVCFMT_LEFT, 120); 
	m_list.InsertColumn(11, TEXT("到达时间"), LVCFMT_LEFT, 120);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	MYSQL m_mysql;			//数据库结构
	mysql_init(&m_mysql);//初始化数据库对象
	mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
	//MessageBox(_T("连接数据库成功!"), _T("提示"));
	//////////////////////////////////////////////////////
	MYSQL_RES* m_res;         //查询的返回结果集
	MYSQL_ROW m_row;          //获取每一条记录
	std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条
	char query[1000];
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query, "select user.`id`,user.real_name,ticket_no,train_no,type,carriage,sit,ticket_price,starting_station,terminal_station,leaving_time,arrival_time from user,passenger_ticket where user_phone='%s' and user.`id`=passenger_ticket.`id`",app->PHONE);
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
		m_data[i].push_back(m_row[5]);
		m_data[i].push_back(m_row[6]);
		m_data[i].push_back(m_row[7]);
		m_data[i].push_back(m_row[8]);
		m_data[i].push_back(m_row[9]);
		m_data[i].push_back(m_row[10]);
		m_data[i++].push_back(m_row[11]);
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < m_res->row_count; i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());
		for (int j = 0; j < 12; j++)
			m_list.SetItemText(iCount, j, m_data[i][j].c_str());
	}
	//释放结果集
	mysql_free_result(m_res);
	//关闭数据库
	mysql_close(&m_mysql);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialog_user_ticket::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDialog_user_ticket::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(old_ticket_no);
	char query[1000];
	if (old_ticket_no.IsEmpty())
	{
		MessageBox(_T("车票号为空\n退票失败!"), _T("提示"));
		return;
	}
	char* in_old_ticket_no = (char*)old_ticket_no.GetBuffer();
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query, "call ticket_refund('%s','%s')", app->PHONE, in_old_ticket_no);
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (mysql_real_connect(&m_sqlCon, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0))
	{
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		//MessageBox(_T("连接数据库成功!"), _T("提示"));
		mysql_query(&m_sqlCon, query);
		MYSQL m_mysql;			//数据库结构
		mysql_init(&m_mysql);//初始化数据库对象
		mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
		//MessageBox(_T("连接数据库成功!"), _T("提示"));
		//////////////////////////////////////////////////////
		MYSQL_RES* m_res;         //查询的返回结果集
		MYSQL_ROW m_row;          //获取每一条记录
		std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条
		char query[1000];
		CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
		sprintf_s(query, "select user.`id`,user.real_name,ticket_no,train_no,type,carriage,sit,ticket_price,starting_station,terminal_station,leaving_time,arrival_time from user,passenger_ticket where user_phone='%s' and user.`id`=passenger_ticket.`id`", app->PHONE);
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
			m_data[i].push_back(m_row[5]);
			m_data[i].push_back(m_row[6]);
			m_data[i].push_back(m_row[7]);
			m_data[i].push_back(m_row[8]);
			m_data[i].push_back(m_row[9]);
			m_data[i].push_back(m_row[10]);
			m_data[i++].push_back(m_row[11]);
		}
		m_list.DeleteAllItems();
		for (int i = 0; i < m_res->row_count; i++)
		{
			int iCount = m_list.GetItemCount();
			m_list.InsertItem(iCount, m_data[i][0].c_str());
			for (int j = 0; j < 12; j++)
				m_list.SetItemText(iCount, j, m_data[i][j].c_str());
		}
		mysql_free_result(m_res);
		mysql_close(&m_mysql);
		mysql_close(&m_sqlCon);
		return;
	}
	else
	{
		MessageBox(_T("连接数据库失败!"), _T("提示"));
		mysql_close(&m_sqlCon);
	}
	CDialogEx::OnOK();
}


void CDialog_user_ticket::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(old_ticket_no);
	GetDlgItem(IDC_EDIT4)->GetWindowText(new_ticket_no);
	char query[1000];
	if (old_ticket_no.IsEmpty()|| new_ticket_no.IsEmpty())
	{
		MessageBox(_T("车票号为空\n改签失败!"), _T("提示"));
		return;
	}
	char* in_old_ticket_no = (char*)old_ticket_no.GetBuffer();
	char* in_new_ticket_no = (char*)new_ticket_no.GetBuffer();
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query, "call ticket_change('%s','%s','%s')", app->PHONE, in_old_ticket_no, in_new_ticket_no);
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (mysql_real_connect(&m_sqlCon, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0))
	{
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		if (mysql_query(&m_sqlCon, query)==0)
		{
			MYSQL m_mysql;			//数据库结构
			mysql_init(&m_mysql);//初始化数据库对象
			mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
			//MessageBox(_T("连接数据库成功!"), _T("提示"));
			//////////////////////////////////////////////////////
			MYSQL_RES* m_res;         //查询的返回结果集
			MYSQL_ROW m_row;          //获取每一条记录
			std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条
			char query[1000];
			CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
			sprintf_s(query, "select user.`id`,user.real_name,ticket_no,train_no,type,carriage,sit,ticket_price,starting_station,terminal_station,leaving_time,arrival_time from user,passenger_ticket where user_phone='%s' and user.`id`=passenger_ticket.`id`", app->PHONE);
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
				m_data[i].push_back(m_row[5]);
				m_data[i].push_back(m_row[6]);
				m_data[i].push_back(m_row[7]);
				m_data[i].push_back(m_row[8]);
				m_data[i].push_back(m_row[9]);
				m_data[i].push_back(m_row[10]);
				m_data[i++].push_back(m_row[11]);
			}
			m_list.DeleteAllItems();
			for (int i = 0; i < m_res->row_count; i++)
			{
				int iCount = m_list.GetItemCount();
				m_list.InsertItem(iCount, m_data[i][0].c_str());
				for (int j = 0; j < 12; j++)
					m_list.SetItemText(iCount, j, m_data[i][j].c_str());
			}
			mysql_free_result(m_res);
			mysql_close(&m_mysql);
			mysql_close(&m_sqlCon);
			return;
		}
		else
		{
			MessageBox(_T("车票不存在或已售出\n改签失败!"), _T("提示"));
			return;
		}
	}
	else
	{
		MessageBox(_T("连接数据库失败!"), _T("提示"));
		mysql_close(&m_sqlCon);
	}
	CDialogEx::OnOK();
}
