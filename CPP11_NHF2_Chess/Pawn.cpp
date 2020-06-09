#include"Pawn.h"

std::vector<Move> Pawn::possible_moves(const Board& b, int x, int y) const {
	std::vector<Move> moves;
	Position pos(x, y);
	if (this->color() == Color::WHITE) {
		if (pos.y + 2 <= 7 && pos.y + 1 <= 7) {
			if (first_move_flag && b.check_if_empty(Position(pos.x, (pos.y + 1))) && b.check_if_empty(Position(pos.x, (pos.y + 2))))
				moves.push_back(Move{ pos, Position{pos.x, pos.y + 2} });
		}
		if (pos.y + 1 <= 7) {
			if (b.check_if_empty(Position(pos.x, pos.y + 1)))
				moves.push_back(Move{ pos, Position{pos.x, pos.y + 1 }});
		}
		if (pos.x + 1 <= 7 && pos.y + 1 <= 7) {
			if (!b.check_if_empty(Position(pos.x + 1, pos.y + 1)) && b.color(Position(pos.x + 1, pos.y + 1)) != this->color())
				moves.push_back(Move{ pos, Position{pos.x + 1, pos.y + 1} });
		}
		if (pos.x - 1 >= 0 && pos.y + 1 <= 7) {
			if (!b.check_if_empty(Position(pos.x - 1, pos.y + 1)) && b.color(Position(pos.x - 1, pos.y + 1)) != this->color())
				moves.push_back(Move{ pos, Position{pos.x - 1, pos.y + 1} });
		}
	}

	if (this->color() == Color::BLACK) {
		if (pos.y - 1 >= 0 && pos.y - 2 >= 0) {
			if (first_move_flag && b.check_if_empty(Position(pos.x, pos.y - 1)) && b.check_if_empty(Position(pos.x, pos.y - 2)))
				moves.push_back(Move{ pos, Position{pos.x, pos.y - 2} });
		}
		if (pos.y - 1 >= 0) {
			if (b.check_if_empty(Position(pos.x, pos.y - 1)))
				moves.push_back(Move{ pos, Position{pos.x, pos.y - 1} });
		}
		if (pos.x + 1 <= 7 && pos.y - 1 >= 0) {
			if (!b.check_if_empty(Position(pos.x + 1, pos.y - 1)) && b.color(Position(pos.x + 1, pos.y - 1)) != this->color())
				moves.push_back(Move{ pos, Position{pos.x + 1, pos.y - 1} });
		}
		if (pos.x - 1 >= 0 && pos.y - 1 >= 0) {
			if (!b.check_if_empty(Position(pos.x - 1, pos.y - 1)) && b.color(Position(pos.x - 1, pos.y - 1)) != this->color())
				moves.push_back(Move{ pos, Position{pos.x - 1, pos.y - 1} });
		}
	}

	/* En-passant TODO */

	return moves;
}