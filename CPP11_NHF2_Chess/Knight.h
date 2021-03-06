#pragma once
#include<memory>
#include<vector>
#include"Piece.h"
#include"Board.h"

class Knight;
class Board;
class Piece;
struct Move;

class Knight final : public Piece {

public:
	Knight() = default;

	Knight(Color color) : Piece{ color } {}

	virtual void set_flag() override {}

	virtual Type type() const override {
		return Type::KNIGHT;
	}

	virtual std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Knight>(*this);
	}

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const override;
};