#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include <time.h>
#include <unistd.h>
  
  
/*
	programme crée par: Khalil Mohammad et Prigent Alan
    Inspiré du jeu de Quarto © Gigamic SARL 1991 du concept de Blaise Muller.
    
    commencer le: 19/11/2021 et finis le: 04/12/2021 
    crée pour l'évaluation de la SAE 1.1 de 1ère année
    Campus 3 de l'IUT Grand Ouest Normandie
*/
     
     
// creation d'une instance de board
board game;

// variable des characteristique des pieces
enum size piece_taille;
enum shape piece_forme;
enum color piece_couleur;
enum top piece_interieur;

// variable qui servira à l'emplacement x et y de la piece 
int piece_x;
int piece_y;

// creation d'un tableau des pieces restante
int ava_piece[16][4];

// creation d'un tableau permettant l'affichage des piece sur le plateau
int played_piece[16] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 ,-1};


/* permet de remettre toute les pieces dans le tableau 
 d'affichage des pieces disponible */
void reset_available_piece()
{
	
	for (int i = 0; i < 2; i++) 
	{
		for (int y = 0; y < 2; y++) 
		{
			for (int z = 0; z < 2; z++) 
			{
				for (int t = 0; t < 2; t++) 
				{
					ava_piece[i*8 + y*4 + z*2 + t][0] = i;
					ava_piece[i*8 + y*4 + z*2 + t][1] = y;
					ava_piece[i*8 + y*4 + z*2 + t][2] = z;
					ava_piece[i*8 + y*4 + z*2 + t][3] = t;			
				 }
			}
		}
	}
	
}

// affichage du titre Principal
void titre()
{
	
	system("clear");
	for (int i = 0; i < 5; i++)
	{
		for (int y = 0; y < 40; y++)
		{
			
			if (i == 0 || i == 4) 
			{
				printf("\033[9m \033[m");
			}
			
			else 
			{
				if (y == 0 || y == 39)
				{
					printf("|");
				}
				
				else 
				{
					if (i == 2 && y == 13) 
					{	
						printf("PROJECT-QUARTO");
						y += 13;
					}
					
					else 
					{
						printf("\033[95m \033[m");
					}
				}
			}
			
		}
		printf("\n");
	}
}

// permet d'afficher les symbole representent les pieces 
void print_symbol(int a)
{
	
	switch (a)
	{
		case 0:
			printf("\033[31m□\033[m");
			break;
		case 1:
			printf("\033[31m■\033[m");
			break;
		case 2:
			printf("\033[34m□\033[m");
			break;
		case 3:
			printf("\033[34m■\033[m");
			break;
		case 4:
			printf("\033[31m◯\033[m");
			break;
		case 5:
			printf("\033[31m⬤\033[m");
			break;
		case 6:
			printf("\033[34m◯\033[m");
			break;
		case 7:
			printf("\033[34m⬤\033[m");
			break;
		case 8:
			printf("\033[31m▫\033[m");
			break;
		case 9:
			printf("\033[31m▪\033[m");
			break;
		case 10:
			printf("\033[34m▫\033[m");
			break;
		case 11:
			printf("\033[34m▪\033[m");
			break;
		case 12:
			printf("\033[31m○\033[m");
			break;
		case 13:
			printf("\033[31m●\033[m");
			break;
		case 14:
			printf("\033[34m○\033[m");
			break;
		case 15:
			printf("\033[34m●\033[m");
			break;
		default:
			printf(" ");
			break;
	}						
								
}

// fonction permettant de demander aux joueur de choisir une pièce
// en fonction de c'est characteristique, 0 ou 1
piece choose_piece(int tours)
{

	int a = 2;
	int b = 2; 
	int c = 2;
	int d = 2;
	
	// affichage du joueur qui joue en fonction de la var tours
	if (tours % 2 == 0)
	{
		printf("joueur 1 choisiser une piece");
	}
	else
	{
		printf("joueur 2 choisiser une piece");
	}
	printf("\nveuiller entrer 4 nombre de 0 ou 1:");
	
	
	// permet de n'ecrire que 4 int
	
	scanf("%1d%1d%1d%1d", &a, &b, &c, &d);
	
	while (!((a == 0 || a == 1) && (b == 0 || b == 1) && (c == 0 || c == 1) && (d == 0 || d == 1)))
	{
		scanf("%1d%1d%1d%1d", &a, &b, &c, &d);

		printf("\nveuiller reesayer avec les bonne valeur\n");
		printf("veuiller entrer 4 nombre de 0 ou 1:");
		while ((getchar()) != '\n');
	}
	
	piece_taille = a;
	piece_forme = b;
	piece_couleur = c;
	piece_interieur = d;

	return get_piece_from_characteristics(piece_taille, piece_forme, piece_couleur, piece_interieur);

}

// fonction permettant aux joueur de plaçer la piece qui fut choisie
void choose_emplacement(int tours, piece p)
{
	int a = 4;
	int b = 4; 
	
	if (tours % 2 == 0)
	{
		printf("joueur 2 choisiser l'emplacement");
	}
	else
	{
		printf("joueur 1 choisiser l'emplacement");
	}
	
	printf("\nveuiller entrer 2 nombre de 0 ou 1:");
	
	scanf("%1d%1d", &a, &b);
	
	while (!((a >= 1 && a <= 4) && (b >= 1 && b <= 4)))
	{
		scanf("%1d%1d", &a, &b);
		printf("\nveuiller reesayer avec les bonne valeur\n");
		printf("veuiller entrer 2 nombre de 0 ou 1:");
		while ((getchar()) != '\n');
	}

	piece_x = a - 1;
	piece_y = b - 1;
	
	// debuging
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

}



// fonction permettant l'affichage des pieces dans le terminal
void affiche_game(board game)
{
	int value = 0;
	// affichage du titre
	titre();
	
	
	// remplissage du tableau, 0 == aucun element
	// 1 == premiere characteristique , 2 == seconde characteristique
	for (int i = 0; i < 11; i+=3)
	{
		for (int y = 0; y < 11; y+=3)
		{
			if (is_occupied(game, i/3, y/3))
			{
				
				value = 0;
				// recupere la piece
				piece p1 = get_piece(game, i/3, y/3);

				// recupe la valeur de binaire a base 10 pour la mettre 
				// dans le tableau, sa marche vraiment
				
				value += (piece_size(p1)) * 8;
				value += (piece_shape(p1)) * 2;
				value += (piece_color(p1)) / 2;
				value += (piece_top(p1)) / 8;
				
				// met la 
				played_piece[i/3 * 4 + y/3] = value;
				ava_piece[value][0] = -1;
				ava_piece[value][1] = -1;
				ava_piece[value][2] = -1;
				ava_piece[value][3] = -1;
			}
		}
	}


	// affichage du tableau
	printf("|\n|\tPlateau\t      Piece disponible\n|\n");
	for (int i = 0; i < 20; i++)
	{
		
		for (int y = 0; y < 40; y++)
		{
			
			if (y > 2 && y < 20 && i < 17)
			{
				if (i % 4 == 0)
				{
					printf("\033[9m \033[m");
				}
				else
				{
					if (y % 4 == 3)
					{
						printf("|");
					}
					else
					{
						if (i % 4 == 2 && y % 4 == 1 && played_piece[((i - 2)) + (y - 5) / 4] != -1)
						{
							print_symbol(played_piece[((i - 2)) + (y - 5) / 4]);
						}	
						else
						{
							printf(" ");	
						}
					}
				}
			}
			
			else if (y == 0 || y == 39)
			{
				printf("|");
			}
			
			else if ((y >= 11 && y <= 19) || (i >= 11 && y <= 19))
			{
				printf(" ");
			}
		
			else if (y > 25 && y < 30 && i < 16)
			{
				if (ava_piece[i][y-26] != -1)
				{
					printf("%d", ava_piece[i][y-26]);
				}
				else
				{
					printf(" ");
				}
			}
			
			else if (y == 31 && i < 16)
			{
				print_symbol(i);
			}
			
			else 
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

// affichage du jeu + timer de debut
void timer_de_debut(board game)
{
	int timer = 4;
	while (timer > 0)
	{
		affiche_game(game);
		printf("----------Debut du jeux dans %d----------\n", timer);
		
		sleep(1);
		timer--;
		system("clear");
	}
	affiche_game(game);
}

// fonctions permettant l'affichage du gagnant de la partie
void is_winner(int tours)
{
	if(tours%2==0)
	{
		printf("le joueur 2 a gagné\n");
	}
	else
	{
		printf("le joueur 1 a gagné\n");
	}
}


int main(int args, char **argv)
{

	// Permert d'utiliser l'horloge interne pour generer de l'aleatoire
	srand(time(NULL)); 

	// creation d'un nouveau plateau
	game = new_game();
	printf("Un plateau est créé.\n");
	
	// variable permettant de connaitre qu'elle joueur joue
	int tours = rand() % 2;
	
	// permet de remplir le tableau d'affichage des pieces disponible
	reset_available_piece();
	
	// affichage du jeu
	timer_de_debut(game);
	
	
	// boucle principal du jeu
	while (has_winner(game) == false)
	{
		// incrementation de tour 
		tours++;

		// creation d'une variable de type piece crée par un joueur
		piece p = choose_piece(tours);

		// apelle de la fonction permettant de choisir emplacement de la piece
		choose_emplacement(tours, p);
		
		// permet de clear le terminal 
		system("clear");
		
		// appel de la fonction d'affichage du plateau
		affiche_game(game);

	}

	// affichage du gagnant de la partie en fonction de qui à jouer en dernier
	is_winner(tours);

	
	destroy_game(game);
	printf("suppression du plateau et sortie\n");
	return 0;
}
