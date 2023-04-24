
// bill_ticket_systemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "bill_ticket_system.h"
#include "bill_ticket_systemDlg.h"
#include "afxdialogex.h"
#include "CDialog_register.h"
#include "CDialog_user.h"
#include "CDialog_administrator.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CbillticketsystemDlg 对话框



CbillticketsystemDlg::CbillticketsystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BILL_TICKET_SYSTEM_DIALOG, pParent)
	, phone(_T(""))
	, password(_T(""))
	, status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CbillticketsystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, phone);
	DDV_MaxChars(pDX, phone, 11);
	DDX_Text(pDX, IDC_EDIT2, password);
	DDV_MaxChars(pDX, password, 16);
	DDX_CBString(pDX, IDC_COMBO1, status);
	DDV_MaxChars(pDX, status, 6);
}

BEGIN_MESSAGE_MAP(CbillticketsystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CbillticketsystemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCLOSE, &CbillticketsystemDlg::OnBnClickedClose)
	ON_BN_CLICKED(IDYES, &CbillticketsystemDlg::OnBnClickedYes)
END_MESSAGE_MAP()


// CbillticketsystemDlg 消息处理程序

BOOL CbillticketsystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CbillticketsystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbillticketsystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbillticketsystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CbillticketsystemDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT1)->GetWindowText(phone);
	GetDlgItem(IDC_EDIT2)->GetWindowText(password);
	GetDlgItem(IDC_COMBO1)->GetWindowText(status);
	CbillticketsystemApp* app = (CbillticketsystemApp*)AfxGetApp();
	app->PHONE= (char*)phone.GetBuffer();
	char* in_phone=(char*)phone.GetBuffer();
	char* in_password = (char*)password.GetBuffer();
	char* in_status = (char*)status.GetBuffer();
	char query[1000];
	if (phone.IsEmpty() || password.IsEmpty()||status.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空！"), _T("提示"));
		return;
	}
	MYSQL m_sqlCon;
	mysql_init(&m_sqlCon);
	if (mysql_real_connect(&m_sqlCon, "localhost", "root", "19991114", "bill_ticket", 3306, NULL, 0))
	{
		MYSQL_RES *res;
		MYSQL_ROW row;
		mysql_query(&m_sqlCon, "set names 'gb2312'");
		//MessageBox(_T("连接数据库成功!"), _T("提示"));
		if (status == "管理员")
		{
			sprintf_s(query, "select * from administrator where administrator_phone='%s' and administrator_password='%s'", in_phone, in_password);
			mysql_query(&m_sqlCon, query);
			res = mysql_store_result(&m_sqlCon);
			row = mysql_fetch_row(res);
			if (row != NULL)
			{
				MessageBox(_T("登录成功!"), _T("提示"));
				CDialog_administrator administrator0;
				administrator0.DoModal();
			}
			else
			{
				MessageBox(_T("用户名或密码不正确!"), _T("提示"));
				return;
			}
			mysql_free_result(res);
		}
		else
			if (status == "用户")
			{
				sprintf_s(query, "select * from user where user_phone='%s' and user_password='%s'", in_phone, in_password);
				mysql_query(&m_sqlCon, query);
				res = mysql_store_result(&m_sqlCon);
				row = mysql_fetch_row(res);
				if (row != NULL)
				{
					MessageBox(_T("登录成功!"), _T("提示"));
					CDialog_user user0;
					user0.DoModal();
				}
				else
				{
					MessageBox(_T("用户名或密码不正确!"), _T("提示"));
					return;
				}
				mysql_free_result(res);
			}
			else
			{
				MessageBox(_T("身份不正确!"), _T("提示"));
				return;
			}
		mysql_close(&m_sqlCon);
	}
	else
	{
		MessageBox(_T("连接数据库失败!"), _T("提示"));
		mysql_close(&m_sqlCon);
	}
}


void CbillticketsystemDlg::OnBnClickedClose()
{
	// TODO: 在此添加控件通知处理程序代码
	exit(0);
}


void CbillticketsystemDlg::OnBnClickedYes()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_register register0;
	register0.DoModal();
}
