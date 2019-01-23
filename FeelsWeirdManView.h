
// FeelsWeirdManView.h : interface of the CFeelsWeirdManView class
//

#pragma once


class CFeelsWeirdManView : public CView {
public:
	void configWindow();

private:
	const COLORREF Background = RGB(205, 150, 127);
	const COLORREF Square = RGB(245, 201, 157);
	const COLORREF NoWall = RGB(235, 180, 137);
	const COLORREF Wall = RGB(60, 80, 80);
	const COLORREF Black = RGB(0, 0, 0);
	const COLORREF White = RGB(255, 255, 255);
	const COLORREF WhiteFin = RGB(255, 221, 197);
	const COLORREF BlackFin = RGB(47, 30, 20);

protected: // create from serialization only
	CFeelsWeirdManView() noexcept;
	DECLARE_DYNCREATE(CFeelsWeirdManView)

// Attributes
public:
	CFeelsWeirdManDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CFeelsWeirdManView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnHelpRules();
	afx_msg void OnTilesizeBig();
	afx_msg void OnTilesizeMedium();
	afx_msg void OnTilesizeSmall();
};

#ifndef _DEBUG  // debug version in FeelsWeirdManView.cpp
inline CFeelsWeirdManDoc* CFeelsWeirdManView::GetDocument() const
   { return reinterpret_cast<CFeelsWeirdManDoc*>(m_pDocument); }
#endif

