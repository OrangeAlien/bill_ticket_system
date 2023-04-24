// CDialog_user.cpp: 实现文件
//

#include "pch.h"
#include "bill_ticket_system.h"
#include "CDialog_user.h"
#include "afxdialogex.h"
#include "CDialog_user_information.h"
#include "CDialog_user_ticket.h"
#include "CDialog_buy_ticket.h"




// CDialog_user 对话框

IMPLEMENT_DYNAMIC(CDialog_user, CDialogEx)

CDialog_user::CDialog_user(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

CDialog_user::~CDialog_user()
{
}

void CDialog_user::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog_user, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON3, &CDialog_user::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CDialog_user::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CDialog_user::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CDialog_user::OnBnClickedButton6)
END_MESSAGE_MAP()


// CDialog_user 消息处理程序


void CDialog_user::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_user_information user_information0;
	user_information0.DoModal();
}


void CDialog_user::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_buy_ticket buy_ticket0;
	buy_ticket0.DoModal();
}


void CDialog_user::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog_user_ticket user_ticket0;
	user_ticket0.DoModal();
}


void CDialog_user::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
