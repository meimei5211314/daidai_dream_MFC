
// my_serial_demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cmy_serial_demoApp: 
// �йش����ʵ�֣������ my_serial_demo.cpp
//

class Cmy_serial_demoApp : public CWinApp
{
public:
	Cmy_serial_demoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cmy_serial_demoApp theApp;