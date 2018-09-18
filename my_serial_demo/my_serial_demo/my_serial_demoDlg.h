
// my_serial_demoDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "mscomm1.h"
#include "stdio.h"
#include <iostream>
#include <string>
#include "afxcmn.h"
#include "LIST_CON.h"

int CommScan(CComboBox* m_pComBox);

void closeHandle(HANDLE& handle);

UINT ThreadprocA(LPVOID pParam);



#define m_Port m_Comm
// Cmy_serial_demoDlg 对话框
class Cmy_serial_demoDlg : public CDialogEx
{
// 构造
public:
	Cmy_serial_demoDlg(CWnd* pParent = NULL);	// 标准构造函数



// 对话框数据
	enum { IDD = IDD_MY_SERIAL_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现


public: 
	CString m_child;
	CEdit m_rev_edit;
	void OnCommMscomm1();
	CString m_EditReV_HEX;

protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	HCURSOR  m_hCursor;
	RECT  m_StaticRect;
	int m_nBaud;       //波特率
	int m_nCom;         //串口号
	char m_cParity;    //校验
	int m_nDatabits;    //数据位
	int m_nStopbits;    //停止位



	CComboBox m_comb1;
	CComboBox m_comb2;

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_portComBox;
	CMscomm1 m_Comm;

	DECLARE_EVENTSINK_MAP()

	// 波特率
	CComboBox m_Speed;
	// 校验位
	CComboBox m_Parity;
	// 数据位
	CComboBox m_DataBits;
	// 停止位
	CComboBox m_StopBits;
	CButton m_ctrlOpenPort;
	// 自动发送
	CButton m_ctrlAutoSend;
	CStatic m_ctrlHyperLink2;
	afx_msg void OnBnClickedSaveSer();
	CButton m_ctrlHexDisplay;
	CString m_EditReceive;
	afx_msg void OnBnClickedScPort();
	afx_msg void OnBnClickedRevempty();
	
	// 配置信息
	CListBox m_list_config;
	afx_msg void OnBnClickedReadconfig();
	CListCtrl m_list_con;
	afx_msg void OnBnClickedButClean();
	afx_msg void OnBnClickedButReadcon();
	afx_msg void OnListBox();
	virtual void PostNcDestroy();
	int String2Hex(CString str, CByteArray &senddata);
	char ConvertHexChar(char ch);
	afx_msg void OnBnClickedButton2();
	CButton m_hex_s;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit3();
};
