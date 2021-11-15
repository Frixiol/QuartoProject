#include <stdio.h>
#include "board.h"

/**
 * @file main_example.c
 * @brief a simple illustration of how to include and use board.h and board.o.
 * @author Dorbec
 */
 
enum size piece_taille;
enum shape piece_forme;
enum color piece_couleur;
enum top piece_interieur;
int piece_x;
int piece_y;
 
piece choose_piece(int nb_tours)
{
	
	if (nb_tours % 2 == 0)
		{
			printf("joueur 1 choisiser une piece:");
		}
		else
		{
			printf("joueur 2 choisiser une piece:");
			
		}
		
		scanf("%u", &piece_taille);
		scanf("%u", &piece_forme);
		scanf("%u", &piece_couleur);
		scanf("%u", &piece_interieur);
		
		return get_piece_from_characteristics(piece_taille, piece_forme, piece_couleur, piece_interieur);
		
}
 
 void affiche_game(board game)
 {
	 for (int i = 0; i < 4; i++)
		{
			for (int y = 0; y < 4; y++)
			{
				if (is_occupied(game, i, y) == true)
				{
					piece p1 = get_piece(game, i, y);
					
					if (piece_size(p1) == TALL)
					{
						if (piece_shape(p1) == SQUARE)
						{
							if (piece_color(p1) == RED)
							{
								if (piece_top(p1) == SOLID)
								{
									printf("① ");
						
								}
								else
								{
									printf("② ");
								}
						
							}
							else
							{
								if (piece_top(p1) == SOLID)
								{
									printf("③ ");
						
								}
								else
								{
									printf("④ ");
								}
							}
						}
						else
						{
							if (piece_color(p1) == RED)
							{
								if (piece_top(p1) == SOLID)
								{
									printf("⑤ ");
						
								}
								else
								{
									printf("⑥ ");
								}
						
							}
							else
							{
								if (piece_top(p1) == SOLID)
								{
									printf("⑦ ");
						
								}
								else
								{
									printf("⑧ ");
								}
							}
						}
					}
					else
					{
						if (piece_shape(p1) == SQUARE)
						{
							if (piece_color(p1) == RED)
							{
								if (piece_top(p1) == SOLID)
								{
									printf("⑨ ");
						
								}
								else
								{
									printf("⑩ ");
								}
						
							}
							else
							{
								if (piece_top(p1) == SOLID)
								{
									printf("⑪ ");
						
								}
								else
								{
									printf("⑫ ");
								}
							}
						}
						else
						{
							if (piece_color(p1) == RED)
							{
								if (piece_top(p1) == SOLID)
								{
									printf("⑬ ");
						
								}
								else
								{
									printf("⑭ ");
								}
						
							}
							else
							{
								if (piece_top(p1) == SOLID)
								{
									printf("⑮ ");
						
								}
								else
								{
									printf("⑯ ");
								}
							}
						}
						
					}
				}
				else
				{
					printf("Ⓞ ");
				}
			}
			printf("\n\n");
		}
 }
 
 void is_winner(int nb_tours)
 {
	 if(nb_tours%2==0)
	{
		printf("le joueur 2 a gagné\n");
	}
	else
	{
		printf("le joueur 1 a gagné\n");
	}
 }
 
 
int main(int args, char **argv){
	board game = new_game();
	printf("Un plateau est créé.\n");
	
	int nb_tours = 0;
	
	
	
	while (has_winner(game) == false)
	{
		nb_tours++;
	
	
		
		piece p = choose_piece(nb_tours);
		
		if (nb_tours % 2 == 0)
		{
			printf("joueur 2 choisiser l'emplacement:");
		}
		else
		{
			printf("joueur 1 choisiser l'emplacement:");
		}
		
		scanf("%d", &piece_x);
		scanf("%d", &piece_y);
		
		enum return_code res = place_piece(game, piece_x, piece_y, p);
		if(res == SUCCESS){
			printf("La piece a été placée avec succès.\n");
		}
		if(res == POSITION) {
			printf("Un problème a eu lieu lors du placement\n");
		}
		if(res == PIECE) {
			printf("Un problème a eu lieu avec la piece\n");
		}
		
		affiche_game(game);
		
	}
	
	is_winner(nb_tours);
	
	destroy_game(game);
	printf("suppression du plateau et sortie\n");	
	return 0;
}
