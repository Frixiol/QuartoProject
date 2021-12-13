#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>

/**
 * \file board.h
 *
 * \brief Quarto game engine functions.
 *
 * In this file, all the functions for having a game of quarto 
 * run are defined.
 *  
 *
 */

/**
 * \mainpage Project 2021-2022 for IUT Grand Ouest Normandie, 
 * computer science department.
 *
 * \section description Description of the project
 * This project is aimed to implement a two players board game, 
 * called quarto. 
 * The rules of the game in French can be found on various web pages: 
 * https://fr.wikipedia.org/wiki/Quarto
 * https://www.ludism.fr/regles_files/fr/upload/quarto_-_GIGAMIC_1991.pdf
 * 
 * The project is divided into various files. Mostly, the engine of the game,
 * implementing the detailed rules, is provided in the files board.c and board.h
 *
 */ 

/**
 * @brief Game dimension.
 *
 * For being general in terms of dimensions,
 * they are defined in a general parameter,
 * though the parameter is not supposed to change.
 * In the following, all indices are given from 0 to DIMENSION - 1.
 */
#define DIMENSION 4

typedef struct save_t* save;


typedef struct board_t* board;


typedef struct piece_t* piece;


struct save_t {
	
	board game;
	int joueur_tour;
	char joueur_name[2][10];
};



save new_save();

void destroy_save(save game_save);


board new_game();

void destroy_game(board game);




bool has_winner(board game);


piece ask_choose_piece(save game_save);


void ask_choose_emplacement(save game_save, piece a_piece);


save ask_name(save game_save, int joueur);


int ask_number_between(int low_value, int high_value, int number);



void affichage_menu();


void affichage_titre();


void affiche_game(board game);


#endif /*_BOARD_H_*/
