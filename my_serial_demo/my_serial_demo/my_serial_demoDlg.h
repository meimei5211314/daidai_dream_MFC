
// my_serial_demoDlg.h : ͷ�ļ�
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
// Cmy_serial_demoDlg �Ի���
class Cmy_serial_demoDlg : public CDialogEx
{
// ����
public:
	Cmy_serial_demoDlg(CWnd* pParent = NULL);	// ��׼���캯��



// �Ի�������
	enum { IDD = IDD_MY_SERIAL_DEMO_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��


public: 
	CString m_child;
	CEdit m_rev_edit;
	void OnCommMscomm1();
	CString m_EditReV_HEX;

protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	HCURSOR  m_hCursor;
	RECT  m_StaticRect;
	int m_nBaud;       //������
	int m_nCom;         //���ں�
	char m_cParity;    //У��
	int m_nDatabits;    //����λ
	int m_nStopbits;    //ֹͣλ



	CComboBox m_comb1;
	CComboBox m_comb2;

	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CComboBox m_portComBox;
	CMscomm1 m_Comm;

	DECLARE_EVENTSINK_MAP()

	// ������
	CComboBox m_Speed;
	// У��λ
	CComboBox m_Parity;
	// ����λ
	CComboBox m_DataBits;
	// ֹͣλ
	CComboBox m_StopBits;
	CButton m_ctrlOpenPort;
	// �Զ�����
	CButton m_ctrlAutoSend;
	CStatic m_ctrlHyperLink2;
	afx_msg void OnBnClickedSaveSer();
	CButton m_ctrlHexDisplay;
	CString m_EditReceive;
	afx_msg void OnBnClickedScPort();
	afx_msg void OnBnClickedRevempty();
	
	// ������Ϣ
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
