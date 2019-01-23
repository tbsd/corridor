#include "stdafx.h"
#include "Board.h"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <stack>
#include <utility>
#include <string>
#include <cstdio>

IMPLEMENT_SERIAL(Board, CObject, 1);
void Board::Serialize(CArchive &ar) {
	int tmpTurn;
	std::string store = "";
	char tmpStr, buf[800];
	if (ar.IsStoring()) {
		if (turn == WHITE)
			tmpTurn = 0;
		else
			tmpTurn = 1;
		ar << size << tmpTurn << finished << bx << by << wx << wy;
		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j) {
				ar << (int)board[i][j];
			}
	} else {
		ar >> size >> tmpTurn >> finished >> bx >> by >> wx >> wy;
		turn = tmpTurn == 0 ? WHITE : BLACK;
		board = new CellType*[size];
		for (int i = 0; i < size; ++i) {
			board[i] = new CellType[size];
			for (int j = 0; j < size; ++j) {
				ar >> (int&) board[i][j];
			}
		}
	}
}

Board::Board() : board(nullptr), size(17), turn(WHITE),
by(1), bx(size / 2 - 1), wy(size - 2), wx(size / 2 + 1), finished(false) {
}

Board::Board(int size) : board(nullptr), size(size), turn(WHITE),
by(1), bx(size / 2 - 1), wy(size - 2), wx(size / 2 + 1), finished(false) {
	initBoard(size);
}


Board::~Board() {
	deleteBoard();
}

void Board::deleteBoard() {
	if (board) {
		for (int i = 0; i < size; ++i) {
			delete board[i];
		}
		delete board;
	}

}


bool Board::fit(int x, int y) {
	return y >= 0 && y < size && x >= 0 && x < size;
}

void Board::initBoard(int sz) {
	if (sz < 5)
		throw std::invalid_argument("Board size must be 5 or greater.");
	if (board)
		deleteBoard();
	size = sz;
	if (((sz - 1) / 2)% 2 == 0) {
		wx = size / 2 + 1;
		bx = size / 2 - 1;
	} else {
		wx = bx = size / 2;
	}
	by = 1;
	wy = size - 2;
	finished = false;
	turn = WHITE;
	board = new CellType*[size];
	board[0] = new CellType[size];
	board[size - 1] = new CellType[size];
	for (int j = 0; j < size; ++j) 
		board[size - 1][j] = board[0][j] = j % 2 == 0 ? BG : HWALL;

	for (int i = 1; i < size - 1; ++i) {
		board[i] = new CellType[size];
		if (i % 2 == 0) {
			for (int j = 0; j < size; ++j)
				board[i][j] = j % 2 == 0 ? BG : NO_HWALL;
		} else {
			for (int j = 1; j < size - 1; ++j)
				board[i][j] = j % 2 == 0 ? NO_VWALL : SQUARE;
			board[i][0] = VWALL;
			board[i][size - 1] = VWALL;
		}
	}
	for (int i = 0; i < size; ++i) {
		if (board[1][i] == SQUARE) {
			board[1][i] = WHITE_FIN;
			board[size - 2][i] = BLACK_FIN;
		}
	}
	board[wy][wx] = WHITE;
	board[by][bx] = BLACK;
}

CellType Board::getCellType(int x, int y) {
	return fit(x, y) ? board[y][x] : BG;
}

bool Board::possibleMove(CellType player, int x, int y) {
	if (player != WHITE && player != BLACK)
		throw std::invalid_argument("CellType player must be BLACK or WHITE");
	if (!fit(x, y))
		return false;
	if (!(board[y][x] == SQUARE || board[y][x] == WHITE_FIN || board[y][x] == BLACK_FIN))
		return false;
	if (player == WHITE) {
		if (!((abs(y - wy) == 2 && abs(x - wx) == 0) ||
			(abs(y - wy) == 0 && abs(x - wx) == 2)))
			return false;
		if (board[wy + (y - wy) / 2][wx] == HWALL ||
			board[wy][wx + (x - wx) / 2] == VWALL)
			return false;
	}
	else {
		if (!((abs(y - by) == 2 && abs(x - bx) == 0) ||
			(abs(y - by) == 0 && abs(x - bx) == 2)))
			return false;
		if (board[by + (y - by) / 2][bx] == HWALL ||
			board[by][bx + (x - bx) / 2] == VWALL)
			return false;
	}
	return true;
}

bool Board::move(int x, int y) {
	if (possibleMove(turn, x, y)) {
		int py, px;
		if (turn == WHITE) {
			py = wy;
			px = wx;
		} else {
			py = by;
			px = bx;
		}
		if (turn == WHITE && getCellType(x, y) == WHITE_FIN ||
			turn == BLACK && getCellType(x, y) == BLACK_FIN)
			finished = true;
		if (py == 1)
			board[py][px] = WHITE_FIN;
		else if (py == size - 2)
			board[py][px] = BLACK_FIN;
		else
			board[py][px] = SQUARE;
		board[y][x] = turn;
		if (turn == WHITE) {
			wx = x;
			wy = y;
		}
		else {
			bx = x;
			by = y;
		}
		switchTurn();
		return true;
	}
	return setWall(x, y);
}

void Board::switchTurn() {
	if (turn == WHITE)
		turn = BLACK;
	else
		turn = WHITE;
}

bool Board::setWall(int x, int y) {
	if (fit(x, y)) {
		if (board[y][x] == NO_HWALL) {
			board[y][x] = HWALL;
			if (pathExists(WHITE) && pathExists(BLACK)) {
				switchTurn();
				return true;
			} else {
				board[y][x] = NO_HWALL;
				return false;
			}
		}
		else if (board[y][x] == NO_VWALL) {
			board[y][x] = VWALL;
			if (pathExists(WHITE) && pathExists(BLACK)) {
				switchTurn();
				return true;
			} else {
				board[y][x] = NO_VWALL;
				return false;
			}
		}
	}
	return false;
}

bool Board::pathExists(CellType player) {
	if (player != WHITE && player != BLACK)
		throw std::invalid_argument("CellType player must be BLACK or WHITE.");
	CellType **history = new CellType*[size];
	for (int i = 0; i < size; ++i) {
		history[i] = new CellType[size];
		for (int j = 0; j < size; ++j)
			history[i][j] = board[i][j];
	}
	history[wy][wx] = history[by][bx] = SQUARE;
	for (int i = 1; i < size; i += 2) 
			history[1][i] = history[size - 2][i] = SQUARE;

	std::pair<int, int> start;
	int goalRow;
	if (player == WHITE) {
		goalRow = 1;
		start.first = wx;
		start.second = wy;
	} else {
		goalRow = size - 2;
		start.first = bx;
		start.second = by;
	}
	std::stack<std::pair<int, int>> next;
	next.push(start);
	bool result = false;
	while (!next.empty()) {
		std::pair<int, int> cur = next.top();
		next.pop();
		if (cur.second == goalRow) {
			result = true;
			break;
		}
		history[cur.second][cur.first] = BG;
		if (cur.first + 2 < size &&
			history[cur.second][cur.first + 1] != VWALL &&
			history[cur.second][cur.first + 2] == SQUARE)
			next.push(std::pair<int, int>(cur.first + 2, cur.second));
		if (cur.first - 2 >= 0 &&
			history[cur.second][cur.first - 1] != VWALL &&
			history[cur.second][cur.first - 2] == SQUARE)
			next.push(std::pair<int, int>(cur.first - 2, cur.second));
		if (cur.second + 2 < size &&
			history[cur.second + 1][cur.first] != HWALL &&
			history[cur.second + 2][cur.first] == SQUARE)
			next.push(std::pair<int, int>(cur.first, cur.second + 2));
		if (cur.second - 2 >= 0 &&
			history[cur.second - 1][cur.first] != HWALL &&
			history[cur.second - 2][cur.first] == SQUARE)
			next.push(std::pair<int, int>(cur.first, cur.second - 2));
	}
	for (int i = 0; i < size; ++i) {
		delete history[i];
	}
	delete history;

	return result;
}

bool Board::isFinished() {
	return finished;
}

int Board::getSize() {
	return size;
}

int Board::getwy() {
	return wy;
}

int Board::getwx() {
	return wx;
}

int Board::getby() {
	return by;
}

int Board::getbx() {
	return bx;
}

CellType Board::getTurn() {
	return turn;
}
