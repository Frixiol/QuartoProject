#include <stdio.h>
#include <stdlib.h>
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

// variable qui servira à l'emplacement x et y de la piece 
int piece_x;
int piece_y;


// fonction permettant de demander aux joueur de choisir une pièce
// en fonction de c'est characteristique, 0 ou 1
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

// fonction permettant aux joueur de plaçer la piece qui fut choisie
void choose_emplacement(int nb_tours)
{
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
}



// fonction permettant l'affichage des pieces dans le terminal
void affiche_game(board game)
{

	// creation d'un tableau permettant affichage

	int tab[11][11] = {0};

	// remplissage du tableau, 0 == aucun element
	// 1 == premiere characteristique , 2 == seconde characteristique

	for (int i = 0; i < 11; i+=3)
	{

		for (int y = 0; y < 11; y+=3)
		{
			if (is_occupied(game, i/3, y/3))
			{
				piece p1 = get_piece(game, i/3, y/3);

				tab[i]    [y]      = (piece_size(p1)) + 1;
				tab[i]    [y + 1]  = (piece_shape(p1)) + 1;
				tab[i + 1][y]      = (piece_color(p1)) + 1;
				tab[i + 1][y + 1]  = (piece_top(p1)) + 1;
			}
		}
	}

	/* A FAIRE !!!
	 
	 faudrai afficher les piece restant sur la droite du terminal
	 y doit allez jusqua + de 30 et faire si le y et < 11 alors utilise le tab
	 sinon si le y > 25 affiche les restant:    0 1 0 1
												1 0 1 0
	*/

	// affichage du tableau
	for (int i = 0; i < 11; i++)
	{
		for (int y = 0; y < 11; y++)
		{

			if (i % 3 == 2)
			{
				printf("-");
			}
			else
			{
				if (y % 3 == 2)
				{
					printf("|");
				}
				else
				{
					if (tab[i][y] == 0)
					{
						printf(" ");
					}
					else
					{
						if (tab[i][y] - 1 > 0)
						{
							printf("1");
						}
						else
						{
							printf("0");
						}
					}
				}
			}
		}
		printf("\n");
	}
}


// fonctions permettant l'affichage du gagnant de la partie
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

	// creation d'un nouveau plateau
	board game = new_game();
	printf("Un plateau est créé.\n");

	// variable permettant de connaitre qu'elle joueur joue
	int nb_tours = 0;

	// boucle principal du jeu
	while (has_winner(game) == false)
	{
		
		nb_tours++;

		// creation d'une variable de type piece crée par un joueur
		piece p = choose_piece(nb_tours);

		// apelle de la fonction permettant de choisir emplacement de la piece
		choose_emplacement(nb_tours);

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

		// permet de clear le terminal 
		system("clear");
		
		// appel de la fonction d'affichage du plateau
		affiche_game(game);

	}

	// affichage du gagnant de la partie en fonction de qui à jouer en dernier
	is_winner(nb_tours);

	destroy_game(game);
	printf("suppression du plateau et sortie\n");
	return 0;
}
