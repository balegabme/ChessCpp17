#pragma once
#include<memory>
#include<vector>
#include"Piece.h"
#include"Board.h"

class Rook;
class Board;
class Piece;
struct Move;

class Rook final : public Piece {

public:
	Rook() = default;

	Rook(Color color) : Piece{ color } {}

	virtual void set_flag() override {}

	virtual Type type() const override {
		return Type::ROOK;
	}

	virtual std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Rook>(*this);
	}

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const override;
};