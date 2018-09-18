
// my_serial_demoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "my_serial_demo.h"
#include "my_serial_demoDlg.h"
#include "afxdialogex.h"
#include "Markup.h"
#include "iostream"
#include "LIST_CON.h"

//#include "CommScan.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
using namespace std;
int k = 1;
LIST_CON *pDlg;
CString str_G;

CWinThread* g_pThreadA;
BOOL g_bRuningA;

UINT ThreadprocA(LPVOID pParam)		//线程1
{
	//Cmy_serial_demoDlg::OnCommMscomm1();
	for (int i=0;i<1000;i++)
	{
		if (!g_bRuningA) break;
		::SetDlgItemInt(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_ED_HEX, i, false);
		//::SetDlgItemText(AfxGetApp()->m_pMainWnd->m_hWnd, IDC_ED_HEX, str_G);
		Sleep(500);
	}

	g_pThreadA = NULL;
	g_bRuningA = FALSE;
	return 0;
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmy_serial_demoDlg 对话框



Cmy_serial_demoDlg::Cmy_serial_demoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cmy_serial_demoDlg::IDD, pParent)
	, m_EditReceive(_T(""))
	, m_EditReV_HEX(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	g_pThreadA = NULL;
	g_bRuningA = false;
}

void Cmy_serial_demoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_portComBox);
	DDX_Control(pDX, IDC_MSCOMM1, m_Comm);
	DDX_Control(pDX, IDC_COMBO2, m_Speed);
	DDX_Control(pDX, IDC_COMBO3, m_Parity);
	DDX_Control(pDX, IDC_COMBO4, m_DataBits);
	DDX_Control(pDX, IDC_COMBO5, m_StopBits);
	DDX_Control(pDX, IDC_BUTTON1, m_ctrlOpenPort);
	DDX_Control(pDX, IDC_CHECK1, m_ctrlAutoSend);
	DDX_Control(pDX, IDC_STATIC_1, m_ctrlHyperLink2);
	DDX_Control(pDX, IDC_CHECK2, m_ctrlHexDisplay);
	DDX_Text(pDX, IDC_ED_PT, m_EditReceive);
	DDX_Text(pDX, IDC_ED_HEX, m_EditReV_HEX);
	DDX_Control(pDX, IDC_LIST_CONFIG, m_list_config);
	DDX_Control(pDX, IDC_LIST_CON, m_list_con);
	DDX_Control(pDX, IDC_EDIT3, m_rev_edit);
	DDX_Control(pDX, IDC_CHECK3, m_hex_s);
}

BEGIN_MESSAGE_MAP(Cmy_serial_demoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cmy_serial_demoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_SAVE_SER, &Cmy_serial_demoDlg::OnBnClickedSaveSer)
	ON_BN_CLICKED(IDC_SC_PORT, &Cmy_serial_demoDlg::OnBnClickedScPort)
	ON_BN_CLICKED(IDC_Rev_empty, &Cmy_serial_demoDlg::OnBnClickedRevempty)
	ON_BN_CLICKED(IDC_READ_config, &Cmy_serial_demoDlg::OnBnClickedReadconfig)
	ON_BN_CLICKED(IDC_BUT_CLEAN, &Cmy_serial_demoDlg::OnBnClickedButClean)
	ON_BN_CLICKED(IDC_BUT_READCON, &Cmy_serial_demoDlg::OnBnClickedButReadcon)
	ON_COMMAND(ID_LIST_BOX, &Cmy_serial_demoDlg::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON2, &Cmy_serial_demoDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cmy_serial_demoDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cmy_serial_demoDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT3, &Cmy_serial_demoDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// Cmy_serial_demoDlg 消息处理程序

BOOL Cmy_serial_demoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	/****************************************************/
	//波特率选择组合框
	CString str1[] = { _T("115200"), _T("300"), _T("600"), _T("1200"), _T("2400"), _T("4800"), _T("9600"),
		_T("19200"), _T("38400"), _T("43000"), _T("56000"), _T("57600") };
	for (int i = 0; i<12; i++)
	{
		int judge_tf = m_Speed.AddString(str1[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("build baud error!"));
	}
	m_Speed.SetCurSel(0);//预置波特率为"115200"
	/****************************************************/
	//校验位选择组合框
	CString str_Parity[] = { _T("n"), _T("1"), _T("2") };
	for (int i = 0; i<3; i++)
	{
		int judge_tf = m_Parity.AddString(str_Parity[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("Parity baud error!"));
	}

	/*******************************************************/
	CString str_DataBits[] = { _T("8"), _T("6"), _T("7"), _T("5") };
	for (int i = 0; i<4; i++)
	{
		int judge_tf = m_DataBits.AddString(str_DataBits[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("DataBits baud error!"));
	}
	/******************************************************/
	CString str_StopBits[] = { _T("1"), _T("1.5"), _T("2") };
	for (int i = 0; i<3; i++)
	{
		int judge_tf = m_StopBits.AddString(str_StopBits[i]);
		if ((judge_tf == CB_ERR) || (judge_tf == CB_ERRSPACE))
			MessageBox(_T("DataBits baud error!"));
	}
	/******************************************************/

	CommScan(&m_portComBox);	
	m_Parity.SetCurSel(0);
	m_DataBits.SetCurSel(0);
	m_StopBits.SetCurSel(0);

	CRect rectTemp;
	GetDlgItem(IDC_LIST_CON)->GetWindowRect(rectTemp);
	m_list_con.InsertColumn(0, _T("属性"), LVCFMT_CENTER, rectTemp.Width() / 2, 0);
	m_list_con.InsertColumn(1, _T("数值"), LVCFMT_CENTER, rectTemp.Width() / 2, 1);
	




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cmy_serial_demoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cmy_serial_demoDlg::OnPaint()
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
HCURSOR Cmy_serial_demoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmy_serial_demoDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString str, str1, str_port, str_Speed, str_Parity, str_DataBits, str_StopBits, n;					//定义字符串

	GetDlgItemText(IDC_BUTTON1, str);
	CWnd *h1;
	h1 = GetDlgItem(IDC_BUTTON1);		//指向控件的caption

	if (!m_Comm.get_PortOpen())
	{
		m_portComBox.GetLBText(m_portComBox.GetCurSel(), str_port);//取得所选的串口，并存放在str_port里面
		m_Speed.GetLBText(m_Speed.GetCurSel(), str_Speed);//取得所选的波特率，并存放在str_Speed里面
		m_Parity.GetLBText(m_Parity.GetCurSel(), str_Parity);//取得所选的校验位，并存放在str_Parity里面
		m_DataBits.GetLBText(m_DataBits.GetCurSel(), str_DataBits);//取得所选的数据位，并存放在str_DataBits里面
		m_StopBits.GetLBText(m_StopBits.GetCurSel(), str_StopBits);//取得所选的停止位，并存放在str_StopBits里面

		str1 = str_Speed + ',' + str_Parity + ',' + str_DataBits + ',' + str_StopBits;			//这句话很关键

		m_Comm.put_CommPort((m_portComBox.GetCurSel() + 1));	//选择串口

		m_Comm.put_InputMode(1);			//设置输入方式为二进制方式
		m_Comm.put_Settings(str1);		//波特率为（波特率组Á合框）无校验，8数据位，1个停止位
		m_Comm.put_InputLen(1024);		//设置当前接收区数据长度为1024
		m_Comm.put_RThreshold(1);			//缓冲区一个字符引发事件
		m_Comm.put_RTSEnable(1);			//设置RT允许

		m_Comm.put_PortOpen(true);		//打开串口
		if (m_Comm.get_PortOpen())
		{
			str = _T("关闭串口");
			UpdateData(true);
			h1->SetWindowText(str);			//改变按钮名称为‘’关闭串口”
		}
	}
	else
	{
		m_Comm.put_PortOpen(false);
		if (str != _T("打开串口"))
		{
			str = _T("打开串口");
			UpdateData(true);
			h1->SetWindowText(str);			//改变按钮名称为打开串口
		}
	}



}

BEGIN_EVENTSINK_MAP(Cmy_serial_demoDlg, CDialogEx)
	ON_EVENT(Cmy_serial_demoDlg, IDC_MSCOMM1, 1, Cmy_serial_demoDlg::OnCommMscomm1, VTS_NONE)
END_EVENTSINK_MAP()



void closeHandle(HANDLE& handle)

{

	CloseHandle(handle);

	handle = INVALID_HANDLE_VALUE;

} 



int CommScan(CComboBox* m_pComBox)

{

	HANDLE hComm;
	CString ComName;

	m_pComBox->ResetContent();  //清空组合框内所有内容
	for (int i = 1; i < 256; i++)

	{

		if (i<10) ComName.Format(_T("COM%d"), i);//注意：COM后面不能有分号，COM9以下。直接用"COM9" _T("COM8")

		if (i >= 10) ComName.Format(_T("\\\\.\\COM%d"), i); //注意：COM10以上要用"\\\\.\\COM10"才行

		hComm = (HANDLE)CreateFile(ComName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);

		if (hComm != INVALID_HANDLE_VALUE)

		{
			CString string3;
			string3.Format(_T("%d"), i);
			m_pComBox->AddString(string3);    //添加COM组合框内容
			closeHandle(hComm);            //关闭句柄
		}
	}
	int ContentNo = m_pComBox->GetCount();     //获得当前选中内容的数目
	m_pComBox->SetCurSel(ContentNo - 1);        //设置当前选中内容显示
	return ContentNo;

}



void Cmy_serial_demoDlg::OnCommMscomm1()
{
	// TODO:  在此处添加消息处理程序代码
	VARIANT variant_inp;
	COleSafeArray safearray_inp;
	LONG len, k;
	unsigned char rxdata[2048]; //设置BYTE数组 An 8-bit integerthat is not signed.
	CString strtemp_PT, strtemp_HEX;

	CTime t = CTime::GetCurrentTime();		//保存系统当前时间
	CString str_time = t.Format("[%H-%M-%S] <-:");		//格式输出获取到的系统时间到 str变量中
	switch (m_Comm.get_CommEvent())
	{
	case 1:break;

	case 2:
	{

		variant_inp = m_Comm.get_Input(); //读缓冲区
		safearray_inp = variant_inp; //VARIANT型变量转换为ColeSafeArray型变量
		len = safearray_inp.GetOneDimSize(); //得到有效数据长度
		for (k = 0; k < len; k++)
		{
			safearray_inp.GetElement(&k, rxdata + k);//转换为BYTE型数组

			for (k = 0; k < len; k++) //将数组转换为Cstring型变量
			{
				BYTE bt = *(char*)(rxdata + k); //字符型

				strtemp_HEX.Format(_T("%02X "), bt); //将字符以十六进制方式送入临时变量strtemp存放，注意这里加入一个空隔 
				strtemp_PT.Format(_T("%c"), bt); //将字符送入临时变量strtemp存放		

				m_EditReceive += strtemp_PT; //加入接收编辑框对应字符串
				str_G += strtemp_HEX;
				pDlg->m_pop_edit.SetWindowText(str_G);
				m_EditReV_HEX += strtemp_HEX; //加入接收编辑框对应字符串
			}
			m_EditReceive += L"\r\n";
			m_EditReV_HEX += L"\r\n";
			UpdateData(FALSE); //更新编辑框内容
			GetDlgItem(IDC_ED_HEX)->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_BOTTOM, 0), 0);//滚动条自动下翻
			GetDlgItem(IDC_ED_PT)->SendMessage(WM_VSCROLL, MAKEWPARAM(SB_BOTTOM, 0), 0);//滚动条自动下翻
		}

		break;
	default:
		break;
	}

	}
}

void Cmy_serial_demoDlg::OnBnClickedSaveSer()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CString str_port, str_Speed, str_Parity, str_DataBits, str_StopBits;
	m_portComBox.GetLBText(m_portComBox.GetCurSel(), str_port);//取得所选的串口，并存放在str_port里面
	m_Speed.GetLBText(m_Speed.GetCurSel(), str_Speed);//取得所选的波特率，并存放在str_Speed里面
	m_Parity.GetLBText(m_Parity.GetCurSel(), str_Parity);//取得所选的校验位，并存放在str_Parity里面
	m_DataBits.GetLBText(m_DataBits.GetCurSel(), str_DataBits);//取得所选的数据位，并存放在str_DataBits里面
	m_StopBits.GetLBText(m_StopBits.GetCurSel(), str_StopBits);//取得所选的停止位，并存放在str_StopBits里面
	CMarkup xml;

	xml.SetDoc(_T("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n"));
	xml.AddElem((MCD_CSTR)_T("serial")); //在当前主位置元素或最后兄弟位置之后增加一个元素
	xml.IntoElem(); //进入当前主位置的下一级，当前的位置变为父位置。
	xml.AddElem((MCD_CSTR)_T("COM"), (MCD_CSTR)str_port);
	xml.AddElem((MCD_CSTR)_T("Speed"), (MCD_CSTR)str_Speed);
	xml.AddElem((MCD_CSTR)_T("Parity"), (MCD_CSTR)str_Parity);
	xml.AddElem((MCD_CSTR)_T("DataBits"), (MCD_CSTR)str_DataBits);
	xml.AddElem((MCD_CSTR)_T("StopBits"), (MCD_CSTR)str_StopBits);
	xml.OutOfElem(); //使当前父位置变成当前位置。
	xml.Save((MCD_CSTR)_T("C:\\Users\\Administrator\\Desktop\\绘图测试\\IC_test\\my_serial_demo\\config\\COM_config.xml"));     //可指定目录   将XML数据写入文件中

}


void Cmy_serial_demoDlg::OnBnClickedScPort()
{
	// TODO:  在此添加控件通知处理程序代码
	CommScan(&m_portComBox);
}


void Cmy_serial_demoDlg::OnBnClickedRevempty()
{
	// TODO:  在此添加控件通知处理程序代码
	m_EditReceive.Empty();
	m_EditReV_HEX.Empty();
	UpdateData(FALSE);
}


void Cmy_serial_demoDlg::OnBnClickedReadconfig()
{
	// TODO:  在此添加控件通知处理程序代码
	CMarkup xml;
	CString str;
	int a = 0;
	printf("开始解析XML文件...\n");
	bool bLoad = false;
	bLoad = xml.Load(_T("C:\\Users\\Administrator\\Desktop\\绘图测试\\IC_test\\my_serial_demo\\config\\COM_config.xml"));
	if (!bLoad)
	{
		printf("没有找到XML文件!\n");
		return;
	}

	xml.ResetMainPos();//把xml对象指向的位置初始化，使其指向文件开始
	xml.FindElem();//查找任意元素，此处查找到的第一个元素即为根元素
	xml.IntoElem();//进入Root
	while (xml.FindElem(L"COM"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_config.AddString(strData);
		printf("%s: %s\n", strTagName, strData);
	}
	while (xml.FindElem(L"Speed"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_config.AddString(strTagName);
		printf("%s: %s\n", strTagName, strData);
	}
	while (xml.FindElem(L"Parity"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_config.AddString(strData);
		printf("%s: %s\n", strTagName, strData);
	}
	while (xml.FindElem(L"DataBits"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_config.AddString(strData);
		printf("%s: %s\n", strTagName, strData);
	}
	while (xml.FindElem(L"StopBits"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_config.AddString(strData);
		printf("%s: %s\n", strTagName, strData);
	}
		printf("解析完成！\n\n");
	UpdateData(FALSE);

}


void Cmy_serial_demoDlg::OnBnClickedButClean()
{
	// TODO:  在此添加控件通知处理程序代码
	m_list_con.DeleteAllItems();
	m_list_config.ResetContent();
}


void Cmy_serial_demoDlg::OnBnClickedButReadcon()
{
	// TODO:  在此添加控件通知处理程序代码
	CMarkup xml;
	CString str;
	int a = 0;
	printf("开始解析XML文件...\n");
	bool bLoad = false;
	bLoad = xml.Load(_T("C:\\Users\\Administrator\\Desktop\\绘图测试\\IC_test\\my_serial_demo\\config\\COM_config.xml"));
	if (!bLoad)
	{
		printf("没有找到XML文件!\n");
		return;
	}
	xml.ResetMainPos();//把xml对象指向的位置初始化，使其指向文件开始
	xml.FindElem();//查找任意元素，此处查找到的第一个元素即为根元素
	xml.IntoElem();//进入Root
	while (xml.FindElem(L"COM"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_con.InsertItem(0, strTagName);
		m_list_con.SetItemText(0, 1, strData);
	}
	while (xml.FindElem(L"Speed"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_con.InsertItem(1, strTagName);
		m_list_con.SetItemText(1, 1, strData);
	}	while (xml.FindElem(L"Parity"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_con.InsertItem(2, strTagName);
		m_list_con.SetItemText(2, 1, strData);
	}	while (xml.FindElem(L"DataBits"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_con.InsertItem(3, strTagName);
		m_list_con.SetItemText(3, 1, strData);
	}	while (xml.FindElem(L"StopBits"))//不能使用if，因为要遍历所有的Student元素
	{
		CString strTagName;//元素名称
		CString strData;//元素内容
		strTagName = xml.GetTagName();//获取元素名称
		strData = xml.GetData();////获取元素内容
		m_list_con.InsertItem(4, strTagName);
		m_list_con.SetItemText(4, 1, strData);
	}
	UpdateData(TRUE);

}


void Cmy_serial_demoDlg::OnListBox()
{
	// TODO:  在此添加命令处理程序代码
	pDlg = new LIST_CON;
	
	pDlg->Create(IDD_DI_LS_CON, this);
	pDlg->ShowWindow(SW_SHOW);

	UpdateData(FALSE);

	//CString str;
	//str = pDlg->strC;//strC是子窗口的CString变量
	//m_rev_edit.SetWindowTextW(str);
	//UpdateData(FALSE);
}




void Cmy_serial_demoDlg::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类
	delete this;

	CDialogEx::PostNcDestroy();
}


void Cmy_serial_demoDlg::OnBnClickedButton2()		//发送
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(true);							//更新控件数据
	CString str, str_t;

	m_rev_edit.GetWindowTextW(str_t);
	//str = "AA 05 11 ";				//添加数据帧头+指令
	//str = str + str_t;
	if (m_hex_s.GetCheck())
	{
		CByteArray hexdata;
		int len = String2Hex(str_t, hexdata); //此处返回的len可以用于计算发送了多少个十六进制数
		m_Comm.put_Output(COleVariant(hexdata)); //发送十六进制数据
	}
	else

		m_Comm.put_Output(COleVariant(str_t)); //发送数据
	
}


//由于这个转换函数的格式 限制，在发送框中的十六制字符应该每两个字符之间插入一个空隔
//如：A1 23 45 0B 00 29
//CByteArray是一个动态字节数组，可参看MSDN帮助
int Cmy_serial_demoDlg::String2Hex(CString str, CByteArray &senddata)
{
	int hexdata, lowhexdata;
	int hexdatalen = 0;
	int len = str.GetLength();
	senddata.SetSize(len / 2);
	for (int i = 0; i<len;)
	{
		char lstr, hstr = str[i];
		if (hstr == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		lstr = str[i];
		hexdata = ConvertHexChar(hstr);
		lowhexdata = ConvertHexChar(lstr);
		if ((hexdata == 16) || (lowhexdata == 16))
			break;
		else
			hexdata = hexdata * 16 + lowhexdata;
		i++;
		senddata[hexdatalen] = (char)hexdata;
		hexdatalen++;
	}
	senddata.SetSize(hexdatalen);
	return hexdatalen;
}



//这是一个将字符转换为相应的十六进制值的函数
//好多C语言书上都可以找到
//功能：若是在0-F之间的字符，则转换为相应的十六进制字符，否则返回-1
char Cmy_serial_demoDlg::ConvertHexChar(char ch)
{
	if ((ch >= '0') && (ch <= '9'))
		return ch - 0x30;
	else if ((ch >= 'A') && (ch <= 'F'))
		return ch - 'A' + 10;
	else if ((ch >= 'a') && (ch <= 'f'))
		return ch - 'a' + 10;
	else return (-1);
}



void Cmy_serial_demoDlg::OnBnClickedButton3()
{
	// TODO:  在此添加控件通知处理程序代码
	if (g_pThreadA == NULL)
	{
		g_pThreadA = AfxBeginThread(ThreadprocA, NULL);		//创建线程
		g_bRuningA = TRUE;
	}
	else
	{
		AfxMessageBox(_T("线程已经启动！"));
	}

}


void Cmy_serial_demoDlg::OnBnClickedButton4()
{
	// TODO:  在此添加控件通知处理程序代码
	if (g_pThreadA == NULL)
	{
		AfxMessageBox(_T("线程不存在！"));
	}
	else
		g_bRuningA = FALSE;

}


void Cmy_serial_demoDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

	pDlg->str_1 = str_G;
	m_rev_edit.GetWindowTextW(str_G);
	pDlg->m_pop_edit.SetWindowTextW(str_G);
	pDlg->UpdateData(TRUE);

}
