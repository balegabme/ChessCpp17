#pragma once
#include<memory>
#include<vector>
#include"Piece.h"
#include"Board.h"

class King;
class Board;
class Piece;
struct Move;

class King final : public Piece {

public:
	King() = default;

	King(Color color) : Piece{ color } {}

	virtual void set_flag() override {}

	virtual Type type() const override {
		return Type::KING;
	}

	virtual std::unique_ptr<Piece> clone() const override {
		return std::make_unique<King>(*this);
	}

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const override;
};