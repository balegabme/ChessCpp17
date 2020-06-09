#pragma once
#include<memory>
#include<vector>
#include"Piece.h"
#include"Board.h"

class Board;
class Bishop;
class Piece;
struct Move;

class Bishop final : public Piece {

public:
	Bishop() = default;

	Bishop(Color color) : Piece{ color } {}

	virtual void set_flag() override {}

	virtual Type type() const override {
		return Type::BISHOP;
	}

	virtual std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Bishop>(*this);
	}

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const override;

};