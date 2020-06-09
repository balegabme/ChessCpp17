#include"Knight.h"

std::vector<Move> Knight::possible_moves(const Board& b, int x, int y) const {
	std::vector<Move> moves;
	Position pos(x,y);
	/* ++ */
	if (pos.x + 2 <= 7 && pos.y + 1 <= 7) {
		if (b.check_if_empty(Position{ pos.x + 2, pos.y + 1 })) {
			moves.push_back(Move{ pos, Position{ pos.x + 2, pos.y + 1 } });
		}
		else if (b.color(Position{ pos.x + 2, pos.y + 1 }) != this->color())
			moves.push_back(Move{ pos, Position{ pos.x + 2, pos.y + 1 } });
	}
	if (pos.x + 1 <= 7 && pos.y + 2 <= 7) {
		if (b.check_if_empty(Position{pos.x + 1, pos.y + 2})) {
			moves.push_back(Move{ pos, Position{ pos.x + 1, pos.y + 2 } });
		}
		else if (b.color(Position{ pos.x + 1, pos.y + 2 }) != this->color())
			moves.push_back(Move{ pos, Position{ pos.x + 1, pos.y + 2 } });
	}
	/* +- */
	if (pos.x + 2 <= 7 && pos.y - 1 >= 0) {
		if (b.check_if_empty(Position{pos.x + 2, pos.y - 1})) {
			moves.push_back(Move{ pos, Position{ pos.x + 2, pos.y - 1 } });
		}
		else if (b.color(Position{ pos.x + 2, pos.y - 1 }) != this->color())
			moves.push_back(Move{ pos, Position{ pos.x + 2, pos.y - 1 } });
	}
	if (pos.x + 1 <= 7 && pos.y - 2 >= 0) {
		if (b.check_if_empty(Position{pos.x + 1, pos.y - 2})) {
			moves.push_back(Move{ pos, Position{ pos.x + 1, pos.y - 2 } });
		}
		else if (b.color(Position{ pos.x + 1, pos.y - 2 }) != this->color())
			moves.push_back(Move{ pos, Position{ pos.x + 1, pos.y - 2 } });
	}
	
	/*-+*/
	if (pos.x - 1 >= 0 && pos.y + 2 <= 7) {
		if (b.check_if_empty(Position{ pos.x - 1, pos.y + 2 })) {
			moves.push_back(Move{ pos, Position{ pos.x - 1, pos.y + 2 } });
		}
		else if (b.color(Position{ pos.x - 1, pos.y + 2 }) != this->color())
			moves.push_back(Move{ pos, Position{ pos.x - 1, pos.y + 2 } });
	}	
	if (pos.x - 2 >= 0 && pos.y + 1 <= 7) {
		if (b.check_if_empty(Position{ pos.x - 2, pos.y + 1 })) {
			moves.push_back(Move{ pos, Position{ pos.x - 2, pos.y + 1 } });
		}
		else if (b.color(Position{ pos.x - 2, pos.y + 1 }) != this->color())
			moves.push_back(Move{ pos, Position{pos.x - 2, pos.y + 1} });
	}
	/*--*/
	if (pos.x - 2 >= 0 && pos.y - 1 >= 0) {
		if (b.check_if_empty(Position{ pos.x - 2, pos.y - 1 })) {
			moves.push_back(Move{ pos, Position{ pos.x - 2, pos.y - 1 } });
		}
		else if (b.color(Position{ pos.x - 2, pos.y - 1 }) != this->color())
			moves.push_back(Move{ pos, Position{pos.x - 2, pos.y - 1} });
	}
	if (pos.x - 1 >= 0 && pos.y - 2 >= 0) {
		if (b.check_if_empty(Position{ pos.x - 1, pos.y - 2 })) {
			moves.push_back(Move{ pos, Position{ pos.x - 1, pos.y - 2 } });
		}
		else if (b.color(Position{ pos.x - 1, pos.y - 2 }) != this->color())
			moves.push_back(Move{ pos, Position{ pos.x - 1, pos.y - 2 } });
	}

	return moves;
}