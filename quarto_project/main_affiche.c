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
	
	int nb_tours = 0;
	char piece_taille[];
	char piece_forme[];
	char piece_couleur[];
	char piece_interieur[];
	int piece_x;
	int piece_y;
	
	while (has_winner(game) == false)
	{
	
		if (nb_tours % 2 == 0)
		{
			printf("joueur 1 choisiser une piece:");
			scanf("%c", &piece_taille[]);
			scanf("%c", &piece_forme[]);
			scanf("%c", &piece_couleur[]);
			scanf("%c", &piece_interieur[]);
		}
		else
		{
			printf("joueur 2 choisiser une piece:");
			scanf("%c", &piece_taille);
			scanf("%c", &piece_forme);
			scanf("%c", &piece_couleur);
			scanf("%c", &piece_interieur);
			
		}
		piece p = get_piece_from_characteristics(piece_taille, piece_forme, piece_couleur, piece_interieur);
		
		if (nb_tours % 2 == 0)
		{
			printf("joueur 2 choisiser l'emplacement:");
			scanf("%d", &piece_x);
			scanf("%d", &piece_y);
		}
		else
		{
			printf("joueur 1 choisiser l'emplacement:");
			scanf("%d", &piece_x);
			scanf("%d", &piece_y);
			
		}
		
		
		enum return_code res = place_piece(game, piece_x, piece_y, p);
		if(res == SUCCESS){
			printf("La piece a été placée avec succès.\n");
		}
		else {
			printf("Un problème a eu lieu lors du placement\n");
		}
		
		for (int i = 0; i < 4; i++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (is_occupied(game, i, y) == true)
				{
					printf("x");
				}
				else
				{
					printf("o");
				}
			}
			printf("\n");
		}
	}
	destroy_game(game);
	printf("suppression du plateau et sortie\n");	
	return 0;
}
