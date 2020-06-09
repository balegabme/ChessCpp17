#include <iostream>

#include"Board.h"
#include"GameController.h"

int main() {
    {
        Board board;
        GameController gc(board);

        gc.game_loop();
    }
	return 0;
}