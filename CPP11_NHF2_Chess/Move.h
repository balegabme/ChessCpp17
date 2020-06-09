#pragma once

struct Position final {
	int x;
	int y;

	Position(int x = 0, int y = 0) : x{ x }, y{ y } {}
	Position(char x, char y) : x{ (x - 'a') }, y{ (y - '0' - 1) } {}

	bool operator==(const Position other) const noexcept {
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Position other) const noexcept {
		return (x != other.x || y != other.y);
	}
};

struct Move final {
	Position from;
	Position to;

	Move(Position from, Position to) :from{ from }, to{ to } {}

	bool operator==(const Move other) const noexcept {
		return (from == other.from && to == other.to);
	}
	bool operator!=(const Move other) const noexcept {
		return (from != other.from || to != other.to);
	}


};