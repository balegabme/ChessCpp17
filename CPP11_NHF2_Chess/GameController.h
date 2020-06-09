#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <ctime>
#include <sstream>

#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include "Board.h"

class GameController;
class Board;
class Rook;
class Knight;
class Bishop;
class King;
class Queen;
class Pawn;

class GameController final {
private:
	Board& board_;
	std::string saves_directory = "saves";
	std::filesystem::path current_save_path;
	bool load_flag = false;
	std::vector<std::string> loaded_moves;

public:
	GameController() = default;

	GameController(Board& board);

	~GameController() = default;

	void start_game(bool clear_previous = true, bool clear_path = true);

	void game_loop();

	bool save_game();

	bool load_game();

	void show_move(std::string str);

	void input(std::string& str);
};