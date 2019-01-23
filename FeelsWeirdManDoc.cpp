
// FeelsWeirdManDoc.cpp : implementation of the CFeelsWeirdManDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FeelsWeirdMan.h"
#endif

#include "FeelsWeirdManDoc.h"
#include "COptions.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFeelsWeirdManDoc

IMPLEMENT_DYNCREATE(CFeelsWeirdManDoc, CDocument)

BEGIN_MESSAGE_MAP(CFeelsWeirdManDoc, CDocument)
	ON_COMMAND(ID_OPTIONS_BOARDSIZE32782, &CFeelsWeirdManDoc::OnOptionsBoardsize32782)
END_MESSAGE_MAP()

void CFeelsWeirdManDoc::saveSettings() {
	std::ofstream settingsStorage("settings");
	settingsStorage << " " << squareSize << " "
		<< wallWidth << " " << spacing << " " <<
		sizeOption << std::endl;
	settingsStorage.close();
}

bool CFeelsWeirdManDoc::loadSettings() {
	try {
		std::ifstream settingsStorage("settings");
		settingsStorage >> squareSize >> wallWidth >>
			spacing >> sizeOption;
		settingsStorage.close();
		return true;
	} catch (...) {
		return false;
	}
}

void CFeelsWeirdManDoc::setSizeOption(int size) {
	sizeOption = size;
}

void CFeelsWeirdManDoc::setWallWidth(int width) {
	if (width < 1)
		throw std::invalid_argument("Width must be 1 or greater.");
	wallWidth = width;
}
void CFeelsWeirdManDoc::setSquareSize(int size) {
	if (size < 1)
		throw std::invalid_argument("Size must be 1 or greater.");
	squareSize = size;
}

bool CFeelsWeirdManDoc::move(int x, int y) {
	return board.move(x, y);
}
bool CFeelsWeirdManDoc::setWall(int x, int y) {
	return board.setWall(x, y);
}
bool CFeelsWeirdManDoc::isFinished() {
	return board.isFinished();
}

int CFeelsWeirdManDoc::getBoardSize() {
	return board.getSize();
}

CellType CFeelsWeirdManDoc::getTurn() {
	return board.getTurn();
}

CellType CFeelsWeirdManDoc::getCellType(int x, int y) {
	return board.getCellType(x, y);
}

int CFeelsWeirdManDoc::getWallWidth() {
	return wallWidth;
}
int CFeelsWeirdManDoc::getSquareSize() {
	return squareSize;
}

int CFeelsWeirdManDoc::getSpacing() {
	return spacing;
}



// CFeelsWeirdManDoc construction/destruction

CFeelsWeirdManDoc::CFeelsWeirdManDoc() noexcept
{
	loadSettings();

}

CFeelsWeirdManDoc::~CFeelsWeirdManDoc()
{
}

BOOL CFeelsWeirdManDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	board.initBoard(sizeOption);
	return TRUE;
}




// CFeelsWeirdManDoc serialization

void CFeelsWeirdManDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		board.Serialize(ar);
	}
	else
	{
		board.Serialize(ar);
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CFeelsWeirdManDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CFeelsWeirdManDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFeelsWeirdManDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFeelsWeirdManDoc diagnostics

#ifdef _DEBUG
void CFeelsWeirdManDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFeelsWeirdManDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFeelsWeirdManDoc commands


void CFeelsWeirdManDoc::OnOptionsBoardsize32782()
{
	COptions optionsDlg;
	optionsDlg.m_Size = sizeOption;
	if (optionsDlg.DoModal() == IDOK) {
		sizeOption = optionsDlg.m_Size * 2 + 1;
		saveSettings();
	}
}
