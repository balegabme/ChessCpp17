#include "GameController.h"

GameController::GameController(Board& board) : board_(board) {}

void GameController::start_game(bool clear_previous, bool clear_path) {
	board_.clear_board();
	board_.next_player(true);
	if (clear_previous)
		board_.clear_previous_moves();
	if(clear_path)
		current_save_path.clear();
	/* ROOK */
	board_.add_piece(0, 0, std::make_unique<Rook>(Color::WHITE));
	board_.add_piece(7, 0, std::make_unique<Rook>(Color::WHITE));
	board_.add_piece(0, 7, std::make_unique<Rook>(Color::BLACK));
	board_.add_piece(7, 7, std::make_unique<Rook>(Color::BLACK));

	/* Knight */
	board_.add_piece(1, 0, std::make_unique<Knight>(Color::WHITE));
	board_.add_piece(6, 0, std::make_unique<Knight>(Color::WHITE));
	board_.add_piece(1, 7, std::make_unique<Knight>(Color::BLACK));
	board_.add_piece(6, 7, std::make_unique<Knight>(Color::BLACK));

	/* Bishop */
	board_.add_piece(2, 0, std::make_unique<Bishop>(Color::WHITE));
	board_.add_piece(5, 0, std::make_unique<Bishop>(Color::WHITE));
	board_.add_piece(2, 7, std::make_unique<Bishop>(Color::BLACK));
	board_.add_piece(5, 7, std::make_unique<Bishop>(Color::BLACK));

	/* King */
	board_.add_piece(4, 0, std::make_unique<King>(Color::WHITE));
	board_.add_piece(4, 7, std::make_unique<King>(Color::BLACK));

	/* Queen */
	board_.add_piece(3, 0, std::make_unique<Queen>(Color::WHITE));
	board_.add_piece(3, 7, std::make_unique<Queen>(Color::BLACK));

	/* Pawns */
	for (int i = 0; i < 8; ++i) {
		board_.add_piece(i, 1, std::make_unique<Pawn>(Color::WHITE));
		board_.add_piece(i, 6, std::make_unique<Pawn>(Color::BLACK));
	}
}

void GameController::game_loop() {
	start_game();
	std::string move_str;

	board_.show();

	while (board_.end() == Result::NOTHING) {
		if (load_flag) {
			load_flag = false;
			board_.clear_board();
			start_game(true, false);
			board_.load_moves(loaded_moves);
			loaded_moves.clear();
			board_.show();
		}

		std::cin >> move_str;
		input(move_str);

	}
}

bool GameController::save_game() {
	if (current_save_path.empty()) {
		std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::stringstream ss;
		ss << current_time;
		std::string filename = ctime(&current_time); //_CRT_SECURE_NO_WARNINGS de így szebb
		filename.erase(std::remove(filename.begin(), filename.end(), ' '), filename.end());
		filename.erase(std::remove(filename.begin(), filename.end(), ':'), filename.end());
		filename = filename.substr(0, filename.size() - 1) + ".chess";

		std::filesystem::path current_path = std::filesystem::current_path();
		std::filesystem::path directory_path = (current_path /= saves_directory);
		try {
			std::filesystem::create_directory(directory_path);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			return false;
		}
		current_save_path = (directory_path /= filename);
	}

	std::ofstream output;
	auto saved_moves = board_.save_moves();
	if (saved_moves.size() != 0) {

		try {
			output.open(current_save_path);
		}
		catch (const std::exception& e) {
			std::cout << e.what() << std::endl;
			return false;
		}

			for (auto p : saved_moves)
				output << p << ' ';
			output.close();
	}
	return true;
}

bool GameController::load_game() {
	std::filesystem::path current_path = std::filesystem::current_path();
	std::filesystem::path directory_path = (current_path /= saves_directory);
	std::vector<std::string> saves;
	loaded_moves.clear();

	for (const auto& entry : std::filesystem::directory_iterator(directory_path)) 
		saves.push_back(entry.path().string());

	int i = 1;
	std::string dest = directory_path.string() + "\\";
	for (auto p : saves) {
		p.erase(p.begin(), p.begin() + (directory_path.string() + "/").size());
		std::cout << i << ".: " << p << std::endl;
		i++;
	}
	int number;
	std::cout << "Choose what to load(Please only enter integers): ";
	std::cin >> number;
	try {
		current_save_path = saves.at(number - 1);
	}
	catch (const std::exception e) {
		std::cerr << e.what() << std::endl;
	}

	std::ifstream input;
	try {
		input.open(current_save_path);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}
	if (loaded_moves.size() != 0) {
		for (auto p : loaded_moves)
			p.pop_back();
	}
	std::string segment;
	while (input >> segment) {
		segment += " ";
		loaded_moves.push_back(segment);
	}
	load_flag = true;
	return true;
}

void GameController::show_move(std::string str) {
	switch (board_.make_move(str)) {
	case Message::Wrong_Input:
		board_.show("Wrong input !");
		break;
	case Message::Not_Possible:
		board_.show("Not possible !");
		break;
	case Message::Check:
		start_game(false, false);
		board_.move_back();
		board_.show("You are in check !");
		break;
	case Message::Stalemate:
		board_.set_result(Result::DRAW);
		board_.show("Stalemate, game ended in a draw !");
		break;
	case Message::Mate_Black:
		board_.set_result(Result::BLACKWIN);
		board_.show("Checkmate, Black is victoriuos");
		break;
	case Message::Mate_White:
		board_.set_result(Result::WHITEWIN);
		board_.show("Checkmate, White is victoriuos");
		break;
	case Message::Nothing:
		board_.show();
		break;
	}
	
}

void GameController::input(std::string& str) {
	bool move = true;
	if (str == "New" || str == "new") {
		start_game();
		board_.show();
		move = false;
	}
	else if (str == "End" || str == "end") {
		board_.set_result(Result::DRAW);
		move = false;
	}
	else if (str == "Save" || str == "save") {
		save_game();
		board_.show();
		move = false;
	}
	else if (str == "Load" || str == "load") {
		load_game();
		board_.show();
		move = false;
	}
	else if (str == "Back" || str == "back") {
		start_game(false, false);
		board_.move_back();
		board_.show();
		move = false;
	}
	if(move) {
		show_move(str);
	}
}