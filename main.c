/*
 * main.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#include <stdio.h>
#include <stdlib.h>
#include "game.h"
#include "solver.h"
#include "mainAux.h"
#include "parser.h"

#define DEFAULT 0
#define SIMPLE 3
#define SUCCESS "Puzzle solved successfully"

int main(int argc, char *argv[]) {
	Board* board;
	int fixed_amount = get_fixed_amount();

	if (fixed_amount == -1)
		exit(0);
	if (argc >= 2)
		srand(atoi(argv[1]));

	board = create_board(SIMPLE, SIMPLE, fixed_amount);

	if (start_game(&board) == -1)
		exit(0);

	printBoard(&board);
	printf("%s", SUCCESS);

	return 0;
}
