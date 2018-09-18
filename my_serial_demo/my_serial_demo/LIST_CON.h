#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// LIST_CON 对话框

class LIST_CON : public CDialogEx
{
	DECLARE_DYNAMIC(LIST_CON)

public:
	LIST_CON(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~LIST_CON();
	CString str_1;

// 对话框数据
	enum { IDD = IDD_DI_LS_CON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_pop_liscon;
	CEdit m_pop_edit;
	CString strC;
	afx_msg void OnBnClickedButSend();
	virtual BOOL OnInitDialog();
	CString m_pop_rev;
};
