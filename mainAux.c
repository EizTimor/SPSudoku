/*
 * mainAux.c
 *
 *  Created on: Dec 18, 2018
 *      Author: Timor Eizenman & Ido Lerer
 */

#include <stdio.h>
#include <stdlib.h>

#define START "Please enter the number of cells to fill [0-80]:\n"
#define AGAIN "Error: invalid number of cells to fill (should be between 0 and 80)\n"
#define EXIT "Exiting...\n"

int get_fixed_amount() {
	int fixed_amount = -1;
	printf("%s", START);
	if (scanf("%d", &fixed_amount) == EOF) {
		printf("%s", EXIT);
		return -1;
	}
	while (fixed_amount < 0 || 80 < fixed_amount) {
		printf("%s%s", AGAIN, START);
		if (scanf("%d", &fixed_amount) == EOF) {
			printf("%s", EXIT);
			return -1;
		}
	}

	return fixed_amount;
}

