/*
 * mainAux.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#ifndef MAINAUX_STRUCT_H_
#define MAINAUX_STRUCT_H_

typedef struct one_cell{
	int isFixed;
	int value;
	int *options;
	int countOptions;
} Cell;

int insert_option(Cell cell, int value);
int remove_option(Cell cell, int index);

#endif /* MAINAUX_STRUCT_H_ */
