#pragma once

enum CellType {
	BG, SQUARE, WHITE, BLACK, WHITE_FIN,
	BLACK_FIN, VWALL, HWALL, NO_VWALL, NO_HWALL
};

class Board : public CObject {
private:
	CellType **board;
	int size;
	CellType turn;
	bool finished;
	int bx;
	int by;
	int wx;
	int wy;

	bool pathExists(CellType player);
	void Board::deleteBoard();
	void switchTurn();
	bool fit(int x, int y);
	bool possibleMove(CellType player, int x, int y);

public:
	Board();
	DECLARE_SERIAL(Board);
	virtual void Serialize(CArchive &ar);
	Board(int size);
	~Board();
	void initBoard(int sz);
	CellType getTurn();
	bool move(int x, int y);
	bool setWall(int x, int y);
	CellType getCellType(int x, int y); 
	bool isFinished();
	int getSize();
	int getbx();
	int getby();
	int getwx();
	int getwy();
};

