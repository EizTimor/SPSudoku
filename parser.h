/*
 * parser.h
 *
 *  Created on: 20 Dec 2018
 *      Authors: Ido Lerer, Timor Eizenman
 */

/*
 * Structure: Command
 * ------------------
 * 	A structure used to represent a command
 *
 * 	id : an integer representing the command type. List of all command types:
 * 			SET: 0, HINT: 1, VALIDATE: 2, RESTART: 3, EXIT: 4
 * 	params[]: an integer array storing command parameters.
 * 			For commands with less than 3 parameters excess integers are 0.
 */
typedef struct command_t{
	int id;
	int params[3];
} Command;

/*
 * Function: parseCommand
 * ----------------------
 * 	Receives a string and returns a command variable with the interpreted command.
 *
 * 	str[] : a character array with the string to be interpreted.
 *
 * 	returns: if the string represents a valid command, returns a command variable with
 * 			 the interpreted command. Otherwise returns null.
 */
Command* parseCommand(char str[]);

/*
 * Function: destroyCommand
 * ------------------------
 * 	Used to destroy a command structure and free the memory allocated to it.
 *
 * 	cmd : a pointer to the command structure.
 *
 */
void destroyCommand(Command* cmd);

/*
 * Function: printCommand
 * ------------------------
 * 	prints the string corresponding to the command.
 *
 * 	cmd : a pointer to the command structure.
 *
 */
void printCommand(Command* cmd);
