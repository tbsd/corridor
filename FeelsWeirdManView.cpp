
// FeelsWeirdManView.cpp : implementation of the CFeelsWeirdManView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FeelsWeirdMan.h"
#endif

#include "FeelsWeirdManDoc.h"
#include "FeelsWeirdManView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFeelsWeirdManView

IMPLEMENT_DYNCREATE(CFeelsWeirdManView, CView)

BEGIN_MESSAGE_MAP(CFeelsWeirdManView, CView)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_HELP_RULES, &CFeelsWeirdManView::OnHelpRules)
	ON_COMMAND(ID_TILESIZE_BIG, &CFeelsWeirdManView::OnTilesizeBig)
	ON_COMMAND(ID_TILESIZE_MEDIUM, &CFeelsWeirdManView::OnTilesizeMedium)
	ON_COMMAND(ID_TILESIZE_SMALL, &CFeelsWeirdManView::OnTilesizeSmall)
END_MESSAGE_MAP()


void CFeelsWeirdManView::configWindow() {
	CFeelsWeirdManDoc* doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;
	CRect cliRect, winRect;
	GetClientRect(&cliRect);
	GetParentFrame()->GetWindowRect(&winRect);
	int length = (doc->getSpacing() * doc->getBoardSize() + 1) + 
		(doc->getBoardSize() / 2) * doc->getSquareSize() +
		(doc->getBoardSize() / 2 + 1) * doc->getWallWidth();
	winRect.right = winRect.left + length +
		winRect.Width() - cliRect.Width();
	winRect.bottom = winRect.top + length +
		winRect.Height() - cliRect.Height();
	GetParentFrame()->MoveWindow(&winRect); 
}
// CFeelsWeirdManView construction/destruction

CFeelsWeirdManView::CFeelsWeirdManView() noexcept
{
	// TODO: add construction code here

}

CFeelsWeirdManView::~CFeelsWeirdManView()
{
}

BOOL CFeelsWeirdManView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFeelsWeirdManView drawing

void CFeelsWeirdManView::OnDraw(CDC* pDC)
{
	CFeelsWeirdManDoc* doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;

	int dcSave = pDC->SaveDC();
	CRect clientRect;
	GetClientRect(&clientRect);
	pDC->FillSolidRect(&clientRect, Background);
	CBrush brush, *oldBrush;
	oldBrush = pDC->SelectObject(&brush);
	CRect cell;
	cell.top = cell.left = doc->getSpacing();
	COLORREF color;
	for (int y = 0; y < doc->getBoardSize(); ++y) {
		for (int x = 0; x < doc->getBoardSize(); ++x) {
			switch (doc->getCellType(x, y)) {
			case BG:
				color = Background;
				cell.bottom = cell.top + doc->getWallWidth();
				cell.right = cell.left + doc->getWallWidth();
				pDC->FillSolidRect(&cell, color);
				break;
			case SQUARE:
				color = Square;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				break;
			case WHITE_FIN:
				color = WhiteFin;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				break;
			case BLACK_FIN:
				color = BlackFin;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				break;
			case HWALL:
				color = Wall;
				cell.bottom = cell.top + doc->getWallWidth();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				break;
			case NO_HWALL:
				color = NoWall;
				cell.bottom = cell.top + doc->getWallWidth();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				break;
			case VWALL:
				color = Wall;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getWallWidth();
				pDC->FillSolidRect(&cell, color);
				break;
			case NO_VWALL:
				color = NoWall;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getWallWidth();
				pDC->FillSolidRect(&cell, color);
				break;
			case WHITE:
				if (y == 1)
					color = WhiteFin;
				else if (y == doc->getBoardSize() - 2)
					color = BlackFin;
				else
					color = Square;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				brush.DeleteObject();
				brush.CreateStockObject(WHITE_BRUSH);
				pDC->SelectObject(&brush);
				pDC->Ellipse(&cell);
				break;
			case BLACK:
				if (y == 1)
					color = WhiteFin;
				else if (y == doc->getBoardSize() - 2)
					color = BlackFin;
				else
					color = Square;
				cell.bottom = cell.top + doc->getSquareSize();
				cell.right = cell.left + doc->getSquareSize();
				pDC->FillSolidRect(&cell, color);
				brush.DeleteObject();
				brush.CreateStockObject(BLACK_BRUSH);
				pDC->SelectObject(&brush);
				pDC->Ellipse(&cell);
				break;
			}
			cell.left = cell.right + doc->getSpacing();
		}
		cell.left = doc->getSpacing();
		cell.top = cell.bottom + doc->getSpacing();
	}
	pDC->RestoreDC(dcSave);
	brush.DeleteObject();
	CRect cliRect;
	GetClientRect(&cliRect);
	if (cell.right != cliRect.right || cell.bottom != clientRect.bottom) {
		configWindow();
	}
}


// CFeelsWeirdManView diagnostics

#ifdef _DEBUG
void CFeelsWeirdManView::AssertValid() const
{
	CView::AssertValid();
}

void CFeelsWeirdManView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFeelsWeirdManDoc* CFeelsWeirdManView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFeelsWeirdManDoc)));
	return (CFeelsWeirdManDoc*)m_pDocument;
}
#endif //_DEBUG


// CFeelsWeirdManView message handlers


void CFeelsWeirdManView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	configWindow();
}


void CFeelsWeirdManView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CFeelsWeirdManDoc *doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;
	if (doc->isFinished())
		return;
	int boardX, boardY, fullCoef, halfCoef;
	halfCoef = doc->getSpacing() * 2 + doc->getWallWidth();
	fullCoef = halfCoef + doc->getSquareSize();
	boardX = (point.x / fullCoef) * 2;
	boardX += point.x % fullCoef > halfCoef	? 1 : 0;
	boardY = (point.y / fullCoef) * 2;
	boardY += point.y % fullCoef > halfCoef	? 1 : 0;
	if (doc->move(boardX, boardY)) {
		Invalidate();
		UpdateWindow();
		if (doc->isFinished()) {
			CString msg("");
			if (doc->getTurn() == BLACK)
				msg += "The white player won.\nCongratulations!";
			else
				msg += "The black player won.\nCongratulations!";

			MessageBox(msg, (CString)"Game Over", MB_OK);
		}
	}
	CView::OnLButtonUp(nFlags, point);
}


void CFeelsWeirdManView::OnHelpRules()
{
	CString rules("This game is for two players. Players' goal is to move their token to the other side of the board. On their turn they can set a wall or move their token. A player can't completely block other player with a wall. White player moves first.");
	MessageBox(rules, (CString)"Rules", MB_OK);
}




void CFeelsWeirdManView::OnTilesizeBig()
{
	CFeelsWeirdManDoc *doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;
	doc->setSquareSize(70);
	doc->setWallWidth(12);
	doc->saveSettings();
	configWindow();
	Invalidate();
	UpdateWindow();

}


void CFeelsWeirdManView::OnTilesizeMedium()
{
	CFeelsWeirdManDoc *doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;
	doc->setSquareSize(50);
	doc->setWallWidth(7);
	doc->saveSettings();
	configWindow();
	Invalidate();
	UpdateWindow();
}


void CFeelsWeirdManView::OnTilesizeSmall()
{
	CFeelsWeirdManDoc *doc = GetDocument();
	ASSERT_VALID(doc);
	if (!doc)
		return;
	doc->setSquareSize(30);
	doc->setWallWidth(5);
	doc->saveSettings();
	configWindow();
	Invalidate();
	UpdateWindow();
}
