#include"King.h"

std::vector<Move> King::possible_moves(const Board& b, int x, int y) const {
	std::vector<Move> moves;
	Position pos(x, y);
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i == 0 && j == 0)
				continue;
			if (pos.x + i > 7 || pos.y + j > 7 || pos.x + i < 0 || pos.y + j < 0)
				continue;
			if (b.check_if_empty(Position(pos.x + i, pos.y + j))) {
				moves.push_back(Move{ pos, Position{pos.x + i, pos.y + j} });
			}
			else {
				if (this->color() != b.color(Position(pos.x + i, pos.y + j)))
					moves.push_back(Move{ pos, Position{pos.x + i, pos.y + j} });
				continue;
			}
		}
	}
	return moves;
}