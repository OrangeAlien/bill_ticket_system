
// bill_ticket_system.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含 'pch.h' 以生成 PCH"
#endif

#include "resource.h"		// 主符号
#include <vector>
#include <string>
#include "stdafx.h"
//因为数据库是通过网络连接的，必须包含网络相关头文件
#include "winsock.h"
//这个没什么好说的，mysql头文件自然要包含  
#include "mysql.h"


// CbillticketsystemApp:
// 有关此类的实现，请参阅 bill_ticket_system.cpp
//

class CbillticketsystemApp : public CWinApp
{
public:
	CbillticketsystemApp();
	char* PHONE;
// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CbillticketsystemApp theApp;
