#include "stdafx.h"
#include "Mscanfcom.h"


Mscanfcom::Mscanfcom()
{
}


Mscanfcom::~Mscanfcom()
{
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

void closeHandle(HANDLE& handle)

{

	CloseHandle(handle);

	handle = INVALID_HANDLE_VALUE;

}