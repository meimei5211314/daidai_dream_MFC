#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// LIST_CON �Ի���

class LIST_CON : public CDialogEx
{
	DECLARE_DYNAMIC(LIST_CON)

public:
	LIST_CON(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~LIST_CON();
	CString str_1;

// �Ի�������
	enum { IDD = IDD_DI_LS_CON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
