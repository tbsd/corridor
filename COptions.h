#pragma once


// COptions dialog

class COptions : public CDialog
{
	DECLARE_DYNAMIC(COptions)

public:
	COptions(CWnd* pParent = nullptr);   // standard constructor
	virtual ~COptions();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPTIONS_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_SIzeEdit;
	int m_Size;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeBoardsize();
};
