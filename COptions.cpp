// COptions.cpp : implementation file
//

#include "stdafx.h"
#include "FeelsWeirdMan.h"
#include "COptions.h"
#include "afxdialogex.h"


// COptions dialog

IMPLEMENT_DYNAMIC(COptions, CDialog)

COptions::COptions(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_OPTIONS_DLG, pParent)
{

}

COptions::~COptions()
{
}

void COptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_SIzeEdit);
}


BEGIN_MESSAGE_MAP(COptions, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &COptions::OnEnChangeBoardsize)
END_MESSAGE_MAP()


// COptions message handlers


BOOL COptions::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_SIzeEdit.LimitText(1);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void COptions::OnEnChangeBoardsize()
{
	int tmp = (int)GetDlgItemInt(IDC_EDIT1);
	if (tmp > 2 && tmp < 10) 
		m_Size = tmp;
	else
		if (m_SIzeEdit.GetWindowTextLengthW() != 0)
			MessageBox((CString)"Board size must be from 3 to 9.", (CString)"Error!", MB_OK);

}
