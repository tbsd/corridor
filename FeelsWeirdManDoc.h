
// FeelsWeirdManDoc.h : interface of the CFeelsWeirdManDoc class
//


#pragma once
#include "Board.h"

class CFeelsWeirdManDoc : public CDocument {
private:
	Board board;
	int squareSize = 50;
	int wallWidth = 7;
	int spacing = 1;
	int sizeOption = 17;


public:
	CellType getTurn();
	CellType getCellType(int x, int y);
	bool move(int x, int y);
	bool setWall(int x, int y);
	void setSizeOption(int size);
	void setWallWidth(int width);
	void setSquareSize(int size);
	bool isFinished();
	int getBoardSize();
	int getWallWidth();
	int getSquareSize();
	int getSpacing();
	void saveSettings();
	bool loadSettings();

protected: // create from serialization only
	CFeelsWeirdManDoc() noexcept;
	DECLARE_DYNCREATE(CFeelsWeirdManDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CFeelsWeirdManDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnOptionsBoardsize32782();
};
