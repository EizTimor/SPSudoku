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

int main(int argc, char *argv[]) {
	Board board;
	int fixed_amount = get_fixed_amount();

	if (fixed_amount == -1)
		exit(0);
	if (argc < 2)
		srand(0); /* not sure if 0 or something else */
	else
		srand(atoi(argv[1]));

	/* here we need to build the board */

	printBoard(board);
	start_game(&board);


	return 0;
}
