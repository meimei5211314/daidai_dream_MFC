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

	m_pComBox->ResetContent();  //�����Ͽ�����������

	for (int i = 1; i < 256; i++)

	{

		if (i<10) ComName.Format(_T("COM%d"), i);//ע�⣺COM���治���зֺţ�COM9���¡�ֱ����"COM9" _T("COM8")

		if (i >= 10) ComName.Format(_T("\\\\.\\COM%d"), i); //ע�⣺COM10����Ҫ��"\\\\.\\COM10"����

		hComm = (HANDLE)CreateFile(ComName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);



		if (hComm != INVALID_HANDLE_VALUE)

		{

			CString string3;

			string3.Format(_T("%d"), i);

			m_pComBox->AddString(string3);    //���COM��Ͽ�����

			closeHandle(hComm);            //�رվ��

		}

	}

	int ContentNo = m_pComBox->GetCount();     //��õ�ǰѡ�����ݵ���Ŀ

	m_pComBox->SetCurSel(ContentNo - 1);        //���õ�ǰѡ��������ʾ

	return ContentNo;

}

void closeHandle(HANDLE& handle)

{

	CloseHandle(handle);

	handle = INVALID_HANDLE_VALUE;

}