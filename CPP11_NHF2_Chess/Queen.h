#pragma once
#include<memory>
#include<vector>
#include"Piece.h"
#include"Board.h"

class Queen;
class Board;
class Piece;
struct Move;

class Queen final : public Piece {

public:
	Queen() = default;

	Queen(Color color) : Piece{ color } {}

	virtual void set_flag() override {}

	virtual Type type() const override {
		return Type::QUEEN;
	}

	virtual std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Queen>(*this);
	}

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const override;
};