/*
 * game.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#ifndef GAME_H_
#define GAME_H_

/*
 * Structure: Cell
 * ------------------
 * 	A structure used to represent a cell on the board
 *
 * 	isFixed : an integer representing whether this cell is fixed in the user's board.
 * 	value : an integer representing the cell's value
 * 	options[] : an integers array storing the value options of a cell.
 * 	countOptions : an integer representing the length of options[]
 */
typedef struct one_cell{
	int isFixed;
	int value;
	int *options;
	int countOptions;
} Cell;

/*
 * Structure: Board
 * ------------------
 * 	A structure used to represent a sudoku board.
 *
 * 	block_row : an integer representing how many rows every block have.
 * 	block_col : an integer representing how many columns every block have.
 * 	board_size : an integer representing home many rows and columns the board have.
 * 	current[] : an Cells array representing the current board's state.
 * 	complete[] : an Cells array representing the board's solution.
 */
typedef struct sudoku_board{
	int block_row;
	int block_col;
	int board_size;
	Cell **current;
	Cell **complete;
} Board;

/*
 * Function: insert_option
 * ----------------------
 * 	Receives a Cell and two integers representing a value, and the board size.
 * 	It inserts that value to the Cell's options array.
 *
 * 	cell : a Cell which his options array should be changed.
 * 	value : an integer representing the value to be added to the Cell's options array.
 * 	board_size : an integer representing the board size.
 *
 * 	returns: ?
 */
int insert_option(Cell cell, int value, int board_size);

/*
 * Function: remove_option
 * ----------------------
 * 	Receives a Cell and two integers representing an index of value, and the board size.
 * 	It removes that value from the Cell's options array.
 *
 * 	cell : a Cell which his options array should be changed.
 * 	index : an integer representing the index of the value to be removed from the Cell's options array.
 * 	board_size : an integer representing the board size.
 *
 * 	returns: ?
 */
int remove_option(Cell cell, int index, int board_size);

/*
 * Function: printBoard
 * ------------------------
 * 	prints the current board state to stdout.
 *
 * 	board : the board to be printed.
 *
 */
void printBoard(Board board);

#endif /* GAME_H_ */