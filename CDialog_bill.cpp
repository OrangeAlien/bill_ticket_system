// CDialog_bill.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_bill.h"
#include "afxdialogex.h"


// CDialog_bill 对话框

IMPLEMENT_DYNAMIC(CDialog_bill, CDialogEx)

CDialog_bill::CDialog_bill(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10, pParent)
{

}

CDialog_bill::~CDialog_bill()
{
}

void CDialog_bill::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_list);
}


BEGIN_MESSAGE_MAP(CDialog_bill, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDialog_bill::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDialog_bill::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDialog_bill 消息处理程序
BOOL CDialog_bill::OnInitDialog()
{
	// TODO: 在此添加额外的初始化代码
	CDialogEx::OnInitDialog();
	m_list.InsertColumn(0, TEXT("订单号"), LVCFMT_LEFT, 75);
	m_list.InsertColumn(1, TEXT("价格"), LVCFMT_LEFT, 50);
	m_list.InsertColumn(2, TEXT("下单时间"), LVCFMT_LEFT, 120);
	m_list.InsertColumn(3, TEXT("用户"), LVCFMT_LEFT, 100);
	m_list.SetExtendedStyle(m_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	MYSQL m_mysql;			//数据库结构
	mysql_init(&m_mysql);//初始化数据库对象
	mysql_real_connect(&m_mysql, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0);//连接数据库
	//////////////////////////////////////////////////////
	MYSQL_RES* m_res;         //查询的返回结果集
	MYSQL_ROW m_row;          //获取每一条记录
	std::vector<std::string> m_data[100];  //存放数据库记录，最大为100条
	char query[1000];
	sprintf_s(query, "select * from bill");
	mysql_query(&m_mysql, "set names 'gb2312'");
	mysql_real_query(&m_mysql, query, strlen(query));//查询函数，语句用字符串表示
	MessageBox(_T("查询成功!"), _T("提示"));
	m_res = mysql_store_result(&m_mysql);//得到查询结果
										 //从数据库获取数据
	int i = 0;
	while (m_row = mysql_fetch_row(m_res))
	{
		m_data[i].push_back(m_row[0]);
		m_data[i].push_back(m_row[1]);
		m_data[i].push_back(m_row[2]);
		m_data[i++].push_back(m_row[3]);
	}
	m_list.DeleteAllItems();
	for (int i = 0; i < m_res->row_count; i++)
	{
		int iCount = m_list.GetItemCount();
		m_list.InsertItem(iCount, m_data[i][0].c_str());
		for (int j = 0; j < 4; j++)
			m_list.SetItemText(iCount, j, m_data[i][j].c_str());
	}
	//释放结果集
	mysql_free_result(m_res);
	//关闭数据库
	mysql_close(&m_mysql);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDialog_bill::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDialog_bill::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
