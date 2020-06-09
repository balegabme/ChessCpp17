#pragma once

#include<iostream>
#include<memory>
#include<array>
#include<vector>
#include<ctype.h>
#include<algorithm>
#include<string>
#include<iterator>
//#include<windows.h>

#include"Piece.h"
#include"Move.h"

enum class Color;
enum class Type;
class Board;
class GameController;
class Piece;

enum class Result : int { WHITEWIN = 0, BLACKWIN = 1, DRAW = 2, NOTHING = 3 };
enum class King_State : int { CHECK = 0, MATE = 1, STALEMATE = 2, NOTHING = 3 };
enum class Message {Wrong_Input, Not_Possible, Check, Stalemate, Mate_White, Mate_Black, Nothing};

class Board final {
private:
	std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board;

	Result result_ = Result::NOTHING;
	Color current_player = Color::WHITE;
	std::vector<Move> previous_moves;

	enum class Move_Type { PAWN_MOVE, PAWN_TAKE, NON_PAWN_MOVE_SINGLE, NON_PAWN_MOVE_BOTH, WRONG_INPUT };
public:

	Board() = default;

	~Board() = default;

	Board(const Board& other) {
		if (*this != other) {
			this->current_player = other.current_player;
			for (std::size_t i = 0; i < 8; i++) {
				for (std::size_t j = 0; j < 8; j++) {
					if (other.board[j][i])
						this->board[j][i] = other.board[j][i]->clone();
				}
			}
			this->previous_moves = other.previous_moves;
		}
	}

	Board(Board&& other) noexcept {
		if (*this != other) {
			this->current_player = std::move(other.current_player);
			for (std::size_t i = 0; i < 8; i++) {
				for (std::size_t j = 0; j < 8; j++) {
					if (other.board[j][i])
						this->board[j][i] = std::move(other.board[j][i]);
				}
			}

			this->previous_moves = std::move(other.previous_moves);
		}
	}

	Board& operator=(const Board& other) {
		if (*this != other) {
			this->current_player = other.current_player;
			for (std::size_t i = 0; i < 8; i++) {
				for (std::size_t j = 0; j < 8; j++) {
					if (other.board[j][i]) {
						board[j][i] = other.board[i][j]->clone();
					}
					else {
						board[j][i].reset();
					}
				}
			}
		}
		this->previous_moves = other.previous_moves;
		return *this;
	}

	Board& operator=(Board&& other) noexcept {
		if (*this != other) {
			this->current_player = std::move(other.current_player);
			for (std::size_t i = 0; i < 8; i++) {
				for (std::size_t j = 0; j < 8; j++) {
					if (other.board[j][i]) {
						board[j][i] = std::move(other.board[i][j]->clone());
					}
					else {
						board[j][i].reset();
					}
				}
			}
		}
		this->previous_moves = std::move(other.previous_moves);
		return *this;
	}

	bool operator==(const Board& other) const noexcept {
		if (this->current_player != other.current_player || this->result_ != other.result_ || this->previous_moves != other.previous_moves)
			return false;

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->board[j][i] != other.board[j][i])
					return false;
			}
		}
		return true;
	}

	bool operator!=(const Board& other) const noexcept {
		if (this->current_player != other.current_player || this->result_ != other.result_ || this->previous_moves != other.previous_moves)
			return true;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (this->board[j][i] != other.board[j][i])
					return true;
			}
		}
		return false;
	}

	Move last_move() const {
		if (previous_moves.empty())
			return Move{ Position {-1,-1}, Position{-1,-1} };
		return previous_moves.back();
	}

	void clear_previous_moves() noexcept {
		previous_moves.clear();
	}

	void push_to_previous_moves_back(Move move) {
		previous_moves.push_back(move);
	}

	void add_piece(std::size_t x, std::size_t y, std::unique_ptr<Piece> piece) noexcept {
		board[x][y] = std::move(piece);
	}

	bool check_if_empty(Position pos) const noexcept {
		if (board[pos.x][pos.y] == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	Color color(Position pos) const {
		return board[pos.x][pos.y]->color();
	}

	void clear_board() {
		for (std::size_t i = 0; i < 8; i++) {
			for (std::size_t j = 0; j < 8; j++) {
				this->board[j][i].reset();
			}
		}
	}

	void move_piece(Move move, bool is_back = false) {
		next_player();
		if (!is_back)
			push_to_previous_moves_back(move);
		board[move.to.x][move.to.y] = std::move(board[move.from.x][move.from.y]);
	}

	void next_player(bool is_white = false) noexcept {
		if (is_white) {
			current_player = Color::WHITE;
			return;
		}
		switch (current_player) {
		case Color::WHITE:
			current_player = Color::BLACK;
			break;
		case Color::BLACK:
			current_player = Color::WHITE;
			break;
		}
	}

	King_State is_check(Board& temp_board) const {
		std::vector<std::vector<Move>> all_enemy_moves;
		Position enemy_king_pos;
		bool stop = false;
		for (int i = 0; i < 8 && !stop; i++) {
			for (int j = 0; j < 8 && !stop; j++) {
				if (!temp_board.board[j][i])
					continue;
				if (temp_board.board[j][i]->color() != temp_board.current_player && temp_board.board[j][i]->type() == Type::KING) {
					enemy_king_pos = Position{ j, i };
					stop = true;
				}
			}
		}

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!temp_board.board[j][i])
					continue;
				if (temp_board.board[j][i]->color() == temp_board.current_player)
					all_enemy_moves.push_back(temp_board.board[j][i]->possible_moves(temp_board, j, i));
			}
		}

		for (auto vec : all_enemy_moves) {
			for (auto move : vec) {
				auto king_attack_moves = std::find(vec.begin(), vec.end(), Move{ move.from, enemy_king_pos });
				if (king_attack_moves != vec.end())
					return King_State::CHECK;
			}
		}
		return King_State::NOTHING;
	}

	King_State is_stalemate(Board& temp_board) const {
		bool check = false;
		std::vector<std::vector<Move>> all_friendly_moves;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (!temp_board.board[j][i])
					continue;
				if (temp_board.board[j][i]->color() == temp_board.current_player)
					all_friendly_moves.push_back(temp_board.board[j][i]->possible_moves(temp_board, j, i));
			}
		}
		int checks = 0;
		for (auto vec : all_friendly_moves) {
			for (auto move : vec) {
				Board b{ temp_board };
				b.move_piece(move);
				if (is_check(b) == King_State::CHECK) {
					check = true;
					checks++;
				}
			}
		}
		int vec_size = 0;
		for (auto vec : all_friendly_moves)
			vec_size += vec.size();
		if ((vec_size - checks) == 0 && check)
			return King_State::MATE;
		if ((vec_size - checks) == 0)
			return King_State::STALEMATE;

		return King_State::NOTHING;
	}

	Type type_from_char(char c) {
		switch (c) {
		case 'r':
			return Type::ROOK;
			break;
		case 'b':
			return Type::BISHOP;
			break;
		case 'n':
			return Type::KNIGHT;
			break;
		case 'k':
			return Type::KING;
			break;
		case 'q':
			return Type::QUEEN;
			break;
		default:
			std::cout << "Function type_from_char got a bad char!" << std::endl;
			return Type::UNDEFINED;
			break;
		}
	}

	Move_Type process_str(std::string& str) {
		constexpr std::array<char, 8> x_axis = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
		constexpr std::array<char, 8> y_axis = { '1', '2', '3', '4', '5', '6', '7', '8' };
		constexpr std::array<char, 5> piece_chars = { 'r', 'n', 'b', 'k', 'q' };
		bool is_pawn = false;

		str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

		switch (str.size()) {
		case 2:
			std::transform(str.begin(), str.end(), str.begin(), [](char c) { return std::tolower(c); });

			if (islower(str[0]) && !(std::find(x_axis.begin(), x_axis.end(), str[0]) == x_axis.end())) {
				if (!(std::find(y_axis.begin(), y_axis.end(), str[1]) == y_axis.end())) {
					return Move_Type::PAWN_MOVE;
				}
			}
			break;

		case 3:
			if (islower(str[0]) && !(std::find(x_axis.begin(), x_axis.end(), str[0]) == x_axis.end()))
				is_pawn = true;
			std::transform(str.begin(), str.end(), str.begin(), [](char c) { return std::tolower(c); });

			if (!(std::find(piece_chars.begin(), piece_chars.end(), str[0]) == piece_chars.end()) || !(std::find(x_axis.begin(), x_axis.end(), str[0]) == x_axis.end())) {
				if (!(std::find(x_axis.begin(), x_axis.end(), str[1]) == x_axis.end())) {
					if (!(std::find(y_axis.begin(), y_axis.end(), str[2]) == y_axis.end())) {
						if (is_pawn)
							return Move_Type::PAWN_TAKE;
						return Move_Type::NON_PAWN_MOVE_SINGLE;
					}
				}
			}

			break;

		case 4:
			if (islower(str[0]))
				break;
			std::transform(str.begin(), str.end(), str.begin(), [](char c) { return std::tolower(c); });

			if (!(std::find(piece_chars.begin(), piece_chars.end(), str[0]) == piece_chars.end())) {
				if (!(std::find(x_axis.begin(), x_axis.end(), str[1]) == x_axis.end()) || !(std::find(y_axis.begin(), y_axis.end(), str[1]) == y_axis.end())) {
					if (!(std::find(x_axis.begin(), x_axis.end(), str[2]) == x_axis.end())) {
						if (!(std::find(y_axis.begin(), y_axis.end(), str[3]) == y_axis.end())) {
							return Move_Type::NON_PAWN_MOVE_BOTH;
						}
					}
				}
			}
			break;

		default:
			break;
		}
		return Move_Type::WRONG_INPUT;
	}

	Move process_move(std::string& str, Move_Type type) {
		std::vector<Move> moves;
		Position act_move;
		int from;
		switch (type) {
		case Move_Type::PAWN_MOVE:
			act_move = Position{ str[0] - 'a' , str[1] - '0' - 1 };
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (i >= 0 && i < 8 && j >= 0 && j < 8) {
						if (board[j][i] != nullptr) {
							if (board[j][i]->type() == Type::PAWN && board[j][i]->color() == current_player) {
								moves = board[j][i]->possible_moves(*this, j, i);
								if (std::find(moves.begin(), moves.end(), Move{ Position{j, i}, act_move }) != moves.end()) {
									board[j][i]->set_flag();
									return Move{ Position{j,i}, act_move };
								}
							}
						}
					}
				}
			}
			break;

		case Move_Type::PAWN_TAKE:
			from = str[0] - 'a';
			act_move = Position{ str[1] - 'a', str[2] - '0' - 1 };
			for (int i = 0; i < 8; i++) {
				if (i >= 0 && i < 8 && from >= 0 && from < 8) {
					if (board[from][i] != nullptr) {
						if (board[from][i]->type() == Type::PAWN && board[from][i]->color() == current_player) {
							moves = board[from][i]->possible_moves(*this, from, i);
							if (std::find(moves.begin(), moves.end(), Move{ Position{from, i}, act_move }) != moves.end()) {
								return Move{ Position{from,i}, act_move };
							}
						}
					}
				}
			}
			break;
		case Move_Type::NON_PAWN_MOVE_SINGLE:
			act_move = Position{ str[1] - 'a', str[2] - '0' - 1 };
			if (type_from_char(str[0]) == Type::UNDEFINED)
				break;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (i >= 0 && i < 8 && j >= 0 && j < 8) {
						if (board[j][i] != nullptr) {
							if (board[j][i]->type() == type_from_char(str[0]) && board[j][i]->color() == current_player) {
								moves = board[j][i]->possible_moves(*this, j, i);
								if (std::find(moves.begin(), moves.end(), Move{ Position{j, i}, act_move }) != moves.end()) {
									return Move{ Position{j,i}, act_move };
								}
							}
						}
					}
				}
			}
			break;
		case Move_Type::NON_PAWN_MOVE_BOTH:
			act_move = Position{ str[2] - 'a', str[3] - '0' - 1 };
			if (type_from_char(str[0]) == Type::UNDEFINED)
				break;
			if (isdigit(str[1])) {
				from = str[1] - '0' - 1;
				for (int i = 0; i < 8; i++) {
					if (i >= 0 && i < 8 && from >= 0 && from < 8) {
						if (board[i][from] != nullptr) {
							if (board[from][i]->type() == type_from_char(str[0]) && board[i][from]->color() == current_player) {
								moves = board[i][from]->possible_moves(*this, i, from);
								if (std::find(moves.begin(), moves.end(), Move{ Position{i, from}, act_move }) != moves.end()) {
									return Move{ Position{i,from}, act_move };
								}
							}
						}
					}
				}
			}
			else {
				from = str[1] - 'a';
				for (int i = 0; i < 8; i++) {
					if (i >= 0 && i < 8 && from >= 0 && from < 8) {
						if (board[from][i] != nullptr) {
							if (board[from][i]->type() == type_from_char(str[0]) && board[from][i]->color() == current_player) {
								moves = board[from][i]->possible_moves(*this, from, i);
								if (std::find(moves.begin(), moves.end(), Move{ Position{from, i}, act_move }) != moves.end()) {
									return Move{ Position{from,i}, act_move };
								}
							}
						}
					}
				}
			}
			break;
		case Move_Type::WRONG_INPUT:
			return Move{ Position{-1,-1},Position{1,1} };
			break;
		default:
			std::cout << "Function process_move got wrong Move_Type" << std::endl;
			return Move{ Position{-1,-1},Position{1,1} };
			break;
		}
		return Move{ Position{-1,-1},Position{1,1} };
	}

	Message make_move(std::string move_str) {
		Move_Type move_type = process_str(move_str);

		if (move_type == Move_Type::WRONG_INPUT) {
			return Message::Wrong_Input;
		}

		Move move = process_move(move_str, move_type);

		if (move == Move{ Position{-1,-1},Position{1,1} }) {
			return Message::Not_Possible;
		}

		move_piece(move);

		if (is_check(*this) == King_State::CHECK)
			return Message::Check;
		if (is_stalemate(*this) == King_State::STALEMATE)
			return Message::Stalemate;
		if (is_stalemate(*this) == King_State::MATE) {
			if (current_player == Color::WHITE) {
				return Message::Mate_Black;
			}
			else {
				return Message::Mate_White;
			}
		}

		return Message::Nothing;
	}

	std::string move_to_engine_friendly_string(Move move) const noexcept {
		char str[5] = { static_cast<char>(move.from.x + 'a'), static_cast<char>(move.from.y + '0' + 1), static_cast<char>(move.to.x + 'a'), static_cast<char>(move.to.y + '0' + 1) };
		return str;
	}

	Move engine_friendly_string_to_computer_friendly_move(std::string str) const noexcept {
		return Move{ Position{str[0], str[1]}, Position{str[2], str[3]} };
	}

	std::vector<std::string> save_moves() const {
		std::vector<std::string> vec;
		if (previous_moves.size() != 0) {
			for (auto p : previous_moves)
				vec.push_back(move_to_engine_friendly_string(p));
		}
		return vec;
	}

	void load_moves(std::vector<std::string> moves_str) {
		clear_previous_moves();
		for (auto p : moves_str)
			move_piece(engine_friendly_string_to_computer_friendly_move(p));
	}

	void move_back() noexcept {
		if (previous_moves.empty())
			return;
		previous_moves.pop_back();
		next_player(true);
		for (auto p : previous_moves)
			move_piece(p, true);
	}

	Result end() const {
		return result_;
	}

	void set_result(Result result) noexcept {
		result_ = result;
	}

	void show(std::string message = "") const noexcept {
		system("cls");

		std::string last_move_string = "";
		if (Move{ Position{-1,-1}, Position{-1,-1} } != last_move())
			last_move_string = "\t\t Last move: " + move_to_engine_friendly_string(last_move());

		char piece_char;
		std::array<std::string, 8> options = { "\t\t (New) Game \t Move (Back)", "\t\t (Save) Game \t      (End)", "\t\t (Load) Game", "\t\t" + message, "" , "" , "" , last_move_string };

		std::cout << std::endl << std::endl << std::endl << "Number of Moves: " << previous_moves.size() << std::endl << std::endl;
		std::cout << "      a     b     c     d     e     f     g     h" << std::endl << std::endl;
		for (int i = 0; i < 8; i++) {
			std::cout << "   =================================================" << std::endl;
			std::cout << (i + 1) << "  ";
			for (int j = 0; j < 8; j++) {
				std::cout << "|  ";
				if (board[j][i] != nullptr) {
					switch (board[j][i]->type()) {
					case Type::ROOK:
						piece_char = 'R';
						break;
					case Type::KNIGHT:
						piece_char = 'N';
						break;
					case Type::BISHOP:
						piece_char = 'B';
						break;
					case Type::QUEEN:
						piece_char = 'Q';
						break;
					case Type::KING:
						piece_char = 'K';
						break;
					case Type::PAWN:
						piece_char = 'P';
						break;
					default:
						piece_char = ' ';
						break;
					}
					if (board[j][i]->color() == Color::BLACK) {
						//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);

						std::cout << piece_char;
					}
					else {
						std::cout << piece_char;
					}
					//SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
				else { std::cout << ' '; }
				std::cout << "  ";
			}
			std::cout << '|' << options[i] << std::endl;
		}
		std::cout << "   =================================================" << std::endl;

		std::cout << "(R)ook, (B)ishop, K(N)ight, (K)ing, (Q)ueen" << std::endl;
		std::cout << "To move the pieces mentioned above please use uppercase letters, pawn moves are : e4, e5, d5, no need to prefix" << std::endl;
		std::cout << "Make a move" << std::endl;
	}
};