/*
 * main.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#include <stdlib.h>
#include "game.h"
#include "mainAux.h"

#define DEFAULT 0
#define SIMPLE 3

int main(int argc, char *argv[]) {
	Board* board;
	int game_active = 1, fixed_amount;
	while (game_active) {
		fixed_amount = get_fixed_amount();

		if (fixed_amount == -1)
			exit(0);
		if (argc >= 2)
			srand(atoi(argv[1]));

		board = create_board(SIMPLE, SIMPLE, fixed_amount);

		game_active = start_game(board);
	}
	return 0;
}
