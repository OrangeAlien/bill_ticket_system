// CDialog_administrator.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_administrator.h"
#include "afxdialogex.h"
#include "CDialog_administrator_information.h"
#include "CDialog_search_user.h"
#include "CDialog_ticket.h"
#include "CDialog_bill.h"

// CDialog_administrator 对话框

IMPLEMENT_DYNAMIC(CDialog_administrator, CDialogEx)

CDialog_administrator::CDialog_administrator(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

}

CDialog_administrator::~CDialog_administrator()
{
}

void CDialog_administrator::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_administrator, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDialog_administrator::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CDialog_administrator::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialog_administrator::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialog_administrator::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CDialog_administrator::OnBnClickedButton7)
END_MESSAGE_MAP()


// CDialog_administrator 消息处理程序


void CDialog_administrator::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_administrator_information administrator_information0;
	administrator_information0.DoModal();
}


void CDialog_administrator::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_search_user search_user0;
	search_user0.DoModal();
}


void CDialog_administrator::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_ticket ticket0;
	ticket0.DoModal();
}


void CDialog_administrator::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CDialog_administrator::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_bill bill0;
	bill0.DoModal();
}
