#include <stdio.h>
#include "board.h"

/**
 * @file main_example.c
 * @brief a simple illustration of how to include and use board.h and board.o.
 * @author Dorbec
 */
int main(int args, char **argv){
	board game = new_game();
	printf("Un plateau est créé.\n");
        piece p = get_piece_from_characteristics(TALL, CIRCULAR, BLUE, HOLLOW);
	enum return_code res = place_piece(game, 2, 0, p);
	
	
	
	if(res == SUCCESS){
		printf("La piece a été placée avec succès.\n");
	}
	else {
		printf("Un problème a eu lieu lors du placement\n");
	}
	destroy_game(game);
	printf("suppression du plateau et sortie\n");	
	return 0;
}


