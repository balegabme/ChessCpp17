#include"Queen.h"

std::vector<Move> Queen::possible_moves(const Board& b, int x, int y) const {
	std::vector<Move> moves;
	Position pos(x, y);
	/*Bishop*/
	for (int i = 1; i < 8; i++) {
		if (pos.x + i > 7 || pos.y + i > 7)
			break;
		if (b.check_if_empty(Position(pos.x + i, pos.y + i))) {
			moves.push_back(Move{ pos, Position(pos.x + i, pos.y + i) });
		}
		else {
			if (this->color() != b.color(Position(pos.x + i, pos.y + i)))
				moves.push_back(Move{ pos, Position{pos.x + i, pos.y + i } });
			break;
		}
	}
	/* +- */
	for (int i = 1; i < 8; i++) {
		if (pos.x + i > 7 || pos.y - i < 0)
			break;
		if (b.check_if_empty(Position(pos.x + i, pos.y - i))) {
			moves.push_back(Move{ pos, Position{pos.x + i, pos.y - i} });
		}
		else {
			if (this->color() != b.color(Position(pos.x + i, pos.y - i)))
				moves.push_back(Move{ pos, Position{pos.x + i, pos.y - i} });
			break;
		}
	}
	/* -+ */
	for (int i = 1; i < 8; i++) {
		if (pos.x - i < 0 || pos.y + i > 7)
			break;
		if (b.check_if_empty(Position(pos.x - i, pos.y + i))) {
			moves.push_back(Move{ pos, Position{pos.x - i, pos.y + i} });
		}
		else {
			if (this->color() != b.color(Position(pos.x - i, pos.y + i)))
				moves.push_back(Move{ pos, Position{pos.x - i, pos.y + i} });
			break;
		}
	}
	/* -- */
	for (int i = 1; i < 8; i++) {
		if (pos.x - i < 0 || pos.y - i < 0)
			break;
		if (b.check_if_empty(Position(pos.x - i, pos.y - i))) {
			moves.push_back(Move{ pos, Position{pos.x - i, pos.y - i} });
		}
		else {
			if (this->color() != b.color(Position(pos.x - i, pos.y - i)))
				moves.push_back(Move{ pos, Position{pos.x - i, pos.y - i} });
			break;
		}
	}

	/*ROOK*/
	for (int i = 1; i < 8; i++) {
		if (pos.x + i > 7)
			break;
		if (b.check_if_empty(Position(pos.x + i, pos.y))) {
			moves.push_back(Move{ pos, Position{pos.x + i, pos.y} });
		}
		else {
			if (this->color() != b.color(Position(pos.x + i, pos.y)))
				moves.push_back(Move{ pos, Position{pos.x + i, pos.y} });
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (pos.x - i < 0)
			break;
		if (b.check_if_empty(Position(pos.x - i, pos.y))) {
			moves.push_back(Move{ pos, Position{pos.x - i, pos.y} });
		}
		else {
			if (this->color() != b.color(Position(pos.x - i, pos.y)))
				moves.push_back(Move{ pos, Position{pos.x - i, pos.y} });
			break;
		}
	}
	for (int i = 1; i < 8; i++) {
		if (pos.y + i > 7)
			break;
		if (b.check_if_empty(Position(pos.x, pos.y + i))) {
			moves.push_back(Move{ pos, Position{pos.x, pos.y + i} });
		}
		else {
			if (this->color() != b.color(Position(pos.x, pos.y + i)))
				moves.push_back(Move{ pos, Position{pos.x, pos.y + i} });
			break;
			}
		}
		for (int i = 1; i < 8; i++) {
			if (pos.y - i < 0)
				break;
			if (b.check_if_empty(Position(pos.x, pos.y - i))) {
				moves.push_back(Move{ pos, Position{pos.x, pos.y - i} });
			}
			else {
				if (this->color() != b.color(Position(pos.x, pos.y - i)))
					moves.push_back(Move{ pos, Position{pos.x, pos.y - i} });
				break;
			}
		}
	return moves;
}