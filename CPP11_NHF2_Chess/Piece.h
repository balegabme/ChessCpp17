#pragma once
#include<iostream>
#include<memory>
#include<vector>

#include "Move.h"

class Piece;
class Board;

enum class Color { WHITE, BLACK };
enum class Type : int { ROOK = 1, KNIGHT = 2, BISHOP = 3, QUEEN = 4, KING = 5, PAWN = 6, UNDEFINED = 7};

class Piece {
private:
	Color _color;
public:
	Piece() = default;

	Piece(Color color) noexcept : _color{ color } {}

	Color color() const { 
		return this->_color; 
	}

	virtual ~Piece() = default;

	virtual Type type() const = 0;

	virtual void set_flag() = 0;

	virtual std::unique_ptr<Piece> clone() const = 0;

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const = 0;
};