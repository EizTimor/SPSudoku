/*
 * solver.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor
 */

#ifndef SOLVER_STRUCT_H_
#define SOLVER_STRUCT_H_
#include "mainAux.h"

int is_finished(Cell **board);
void get_first_empty_cell(Cell **board, int *coors);
int is_value_valid(Cell **board, int row, int col, int value);

#endif /* SOLVER_STRUCT_H_ */
