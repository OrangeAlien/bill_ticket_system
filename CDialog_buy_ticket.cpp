// CDialog_buy_ticket.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_buy_ticket.h"
#include "CDialog_user_ticket.h"
#include "afxdialogex.h"

// CDialog_buy_ticket 对话框

IMPLEMENT_DYNAMIC(CDialog_buy_ticket, CDialogEx)

CDialog_buy_ticket::CDialog_buy_ticket(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
	, starting_station(_T(""))
	, terminal_station(_T(""))
	, type(_T(""))
	, date(_T(""))
	, ticket_no(_T(""))
{

}

CDialog_buy_ticket::~CDialog_buy_ticket()
{
}

void CDialog_buy_ticket::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
	DDX_Text(pDX, IDC_EDIT1, starting_station);
	DDV_MaxChars(pDX, starting_station, 16);
	DDX_Text(pDX, IDC_EDIT4, terminal_station);
	DDV_MaxChars(pDX, terminal_station, 16);
	DDX_CBString(pDX, IDC_COMBO3, type);
	DDV_MaxChars(pDX, type, 4);
	DDX_Text(pDX, IDC_EDIT5, date);
	DDX_Text(pDX, IDC_EDIT2, ticket_no);
	DDV_MaxChars(pDX, ticket_no, 10);
}


BEGIN_MESSAGE_MAP(CDialog_buy_ticket, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_buy_ticket::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CDialog_buy_ticket::OnBnClickedOk)
	ON_BN_CLICKED(2, &CDialog_buy_ticket::OnBnClicked2)
END_MESSAGE_MAP()


// CDialog_buy_ticket 消息处理程序
BOOL CDialog_buy_ticket::OnInitDialog()
{
	// TODO: 在此添加额外的初始化代码
	CDialogEx::OnInitDialog();
	m_list.InsertColumn(0, TEXT("车票号"), LVCFMT_LEFT, 60);
	m_list.InsertColumn(1, TEXT("车次"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(2, TEXT("类型"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(3, TEXT("车厢号"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(4, TEXT("座位号"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(5, TEXT("价格"), LVCFMT_LEFT, 40);
	m_list.InsertColumn(6, TEXT("起点站"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(7, TEXT("终点站"), LVCFMT_LEFT, 80);
	m_list.InsertColumn(8, TEXT("发车时间"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(9, TEXT("到达时间"), LVCFMT_LEFT, 120);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	OnBnClickedButton1();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialog_buy_ticket::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(starting_station);
	GetDlgItem(IDC_EDIT4)->GetWindowText(terminal_station);
	GetDlgItem(IDC_EDIT5)->GetWindowText(date);
	GetDlgItem(IDC_COMBO3)->GetWindowText(type);
	MYSQL m_mysql;			//数据库结构
	mysql_init(&m_mysql);//初始化数据库对象
	mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
	//MessageBox(_T("连接数据库成功!"), _T("提示"));
	//////////////////////////////////////////////////////
	char* in_starting_station = (char*)starting_station.GetBuffer();
	char* in_terminal_station = (char*)terminal_station.GetBuffer();
	char* in_date = (char*)date.GetBuffer();
	char* in_type = (char*)type.GetBuffer();
	char query[1000];
	sprintf_s(query, "select * from ticket_ where starting_station like '%s%%' and terminal_station like '%s%%' and leaving_time like '%s%%'and type like '%s%%'", in_starting_station, in_terminal_station, in_date, in_type);
	mysql_query(&m_mysql, "set names 'gb2312'");
	mysql_real_query(&m_mysql, query, strlen(query));//查询函数，语句用字符串表示
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
		m_data[i].push_back(m_row[5]);
		m_data[i].push_back(m_row[6]);
		m_data[i].push_back(m_row[7]);
		m_data[i].push_back(m_row[8]);
		m_data[i++].push_back(m_row[9]);
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < m_res->row_count; i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());
		for (int j = 0; j < 10; j++)
			m_list.SetItemText(iCount, j, m_data[i][j].c_str());
	}
	//释放结果集
	mysql_free_result(m_res);
	//关闭数据库
	mysql_close(&m_mysql);
}


void CDialog_buy_ticket::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT2)->GetWindowText(ticket_no);
	char query[1000];
	if (ticket_no.IsEmpty())
	{
		MessageBox(_T("车票号为空\n购买失败!"), _T("提示"));
		return;
	}
	char* in_ticket_no = (char*)ticket_no.GetBuffer();
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	sprintf_s(query, "call ticket_buy('%s','%s')",app->PHONE,in_ticket_no);
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (mysql_real_connect(&m_sqlCon, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0))
	{
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		//MessageBox(_T("连接数据库成功!"), _T("提示"));
		if (mysql_query(&m_sqlCon, query) == 0)
		{
			OnInitDialog();
			MessageBox(_T("购票成功!"), _T("提示"));
			CDialog_user_ticket user_ticket0;
			user_ticket0.DoModal();
			return;
		}
		else
		{
			MessageBox(_T("车票不存在或已售出\n购票失败!"), _T("提示"));
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


void CDialog_buy_ticket::OnBnClicked2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
