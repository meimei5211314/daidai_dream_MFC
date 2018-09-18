// LIST_CON.cpp : 实现文件
//

#include "stdafx.h"
#include "my_serial_demo.h"
#include "LIST_CON.h"
#include "my_serial_demoDlg.h"
#include "afxdialogex.h"


Cmy_serial_demoDlg *pFather ;


// LIST_CON 对话框

IMPLEMENT_DYNAMIC(LIST_CON, CDialogEx)

LIST_CON::LIST_CON(CWnd* pParent /*=NULL*/)
	: CDialogEx(LIST_CON::IDD, pParent)
	, m_pop_rev(_T(""))
{



}

LIST_CON::~LIST_CON()
{
}

void LIST_CON::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_POP_LICON, m_pop_liscon);
	DDX_Control(pDX, IDC_EDIT1, m_pop_edit);
	DDX_Text(pDX, IDC_EDIT1, m_pop_rev);
}


BEGIN_MESSAGE_MAP(LIST_CON, CDialogEx)
	ON_BN_CLICKED(IDOK, &LIST_CON::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUT_SEND, &LIST_CON::OnBnClickedButSend)
END_MESSAGE_MAP()


// LIST_CON 消息处理程序


void LIST_CON::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码

	CDialogEx::OnOK();
}

void LIST_CON::OnBnClickedButSend()
{
	// TODO:  在此添加控件通知处理程序代码
	pFather->OnBnClickedButton1();

}


BOOL LIST_CON::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	
	Cmy_serial_demoDlg *pDlg = (Cmy_serial_demoDlg*)this->GetParent();
	pFather = pDlg;


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
