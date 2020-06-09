#pragma once
#include"Piece.h"
#include<memory>
#include<vector>
#include"Board.h"

class Pawn;
class Board;
class Piece;
struct Move;

class Pawn final : public Piece {
private:
	bool first_move_flag = true;
public:

	Pawn() = default;

	Pawn(Color color) : Piece{ color } {}

	void set_flag() override{
		first_move_flag = false;
	}

	virtual Type type() const override {
		return Type::PAWN;
	}

	virtual std::unique_ptr<Piece> clone() const override {
		return std::make_unique<Pawn>(*this);
	}

	virtual std::vector<Move> possible_moves(const Board& b, int x, int y) const override;
};