#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "board.h"



// enum de debugage afin de connaitre si des action se sont dérouler correctement
enum return_code{
                
		 SUCCESS,
         
		 POSITION,
	
		 PIECE,
};

// enum definissant la taille d'une piece
enum size {
	TALL,
	SHORT
};

// enum definissant la forme d'une piece
enum shape {
	SQUARE,
	CIRCULAR
};

// enum definissant la couleur d'une piece
enum color {
	RED,
	BLUE
};

// enum definissant l'interieur d'une piece
enum top {
	HOLLOW,
	SOLID
};


// struct piece definissant une piece avec 4 characteristique
struct piece_t {
	
	enum size p_size;
	enum shape p_shape;
	enum color p_color;
	enum top p_top;
	
};


/** struct board definissant un plateau basé sur un tableau à 2 dimension  **/
struct board_t {
	
	piece tab[DIMENSION][DIMENSION];
	
};


// fonction permettant de retourner une nouvelle struct save
save new_save()
{	
	save game_save;
	
	// permet d'allouer les data en dehors de la pile de la fonction
	game_save = malloc(sizeof(struct save_t));
	
	// retourne la struct 
	return game_save;	
}

// fonction permettant de retourner une nouvelle struct board
board new_game()
{	
	board game;
	
	// permet d'allouer les data en dehors de la pile de la fonction
	game = malloc(sizeof(struct board_t));
	
	// remplis le tableau de board avec des NULL
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			game->tab[i][y] = NULL;
		}
	}
	
	// retourne la struct 
	return game;	
}



// fonction permettent de connaitre si une position du plateau est occuper
bool is_occupied(board game, int line, int column)
{
	// si la position du plateau n'est pas vide alors la place est occuper
	if (game->tab[line][column] != NULL)
	{
		return true;
	}

	// sinon la place est vide
	return false;
}



// fonction permettent de connaitre si une piece donnée est NULL
bool piece_is_null(piece a_piece)
{
	if (a_piece == NULL)
	{
		return true;
	}
	return false;
}



// fonction qui retourne true si 2 piece donné ont les meme characteristique
bool is_same_piece(piece a_piece, piece b_piece)
{
	// si une des piece est NULL alors retourne false
	if (piece_is_null(a_piece) || piece_is_null(b_piece)) return false;
	
	// si les piece ont les meme characteristique retourne true
	if (a_piece->p_size == b_piece->p_size && a_piece->p_shape == b_piece->p_shape
		&& a_piece->p_color == b_piece->p_color && a_piece->p_top == b_piece->p_top)
	{
		return true;
	}
	
	// sinon retourne false
	return false;
}

// fonction qui retourne la characteristique size d'une piece donné
enum size piece_size(piece a_piece)
{
	return a_piece->p_size;
}


// fonction qui retourne la characteristique top d'une piece donné
enum top piece_top(piece a_piece)
{
	return a_piece->p_top;
}


// fonction qui retourne la characteristique color d'une piece donné
enum color piece_color(piece a_piece)
{
	return a_piece->p_color;
}


// fonction qui retourne la characteristique shape d'une piece donné
enum shape piece_shape(piece a_piece)
{
	return a_piece->p_shape;
}


// fonction recevant 4 piece et retourne true si elle on toute au moins un characteristique commune
bool piece_min_one_chara(piece piece_a, piece piece_b, piece piece_c, piece piece_d)
{
	// regarde d'abord si la piece est NULL pour ne pas comparer du vide
	if (piece_is_null(piece_a) || piece_is_null(piece_b) || piece_is_null(piece_c) || piece_is_null(piece_d)) return false;
	
	// compare si chaque piece on l'a meme characteristique size
	if ((piece_size(piece_a) == piece_size(piece_b)) == (piece_size(piece_c) == piece_size(piece_d)))
	{
		return true;
	}
	// compare si chaque piece on l'a meme characteristique top
	if ((piece_top(piece_a) == piece_top(piece_b)) == (piece_top(piece_c) == piece_top(piece_d)))
	{
		return true;
	}
	// compare si chaque piece on l'a meme characteristique color
	if ((piece_color(piece_a) == piece_color(piece_b)) == (piece_color(piece_c) == piece_color(piece_d)))
	{
		return true;
	}
	// compare si chaque piece on l'a meme characteristique shape
	if ((piece_shape(piece_a) == piece_shape(piece_b)) == (piece_shape(piece_c) == piece_shape(piece_d)))
	{
		return true;
	}
	// si les piece n'ont aucune characteristique commune retourne false
	return false;
}



// fonction permettent de savoir si une piece donné n'a pas été placé sur le plateau
bool piece_is_free(board game, piece a_piece)
{
	// parcours le tableau du board
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			// si la piece passé est sur le plateau alors retoune false
			if (is_same_piece(a_piece, game->tab[i][y]))
			{
				return false;
			}
		}
	}
	
	// si la piece n'est pas sur le plateau retourne true
	return true;
	
}



// fonction permettent de savoir si les piece sur une meme ligne
// on au moins une characteristique commmune
bool line_same_characteristic(board game, int line)
{
	// si les piece on au moins une charactéristique commune retourne true
	if (piece_min_one_chara(game->tab[line][0], game->tab[line][1], game->tab[line][2], game->tab[line][3]))
	{
		return true;
	}
	
	// sinon retourne false
	return false;
}



// fonction permettent de savoir si les piece sur une meme colonne
// on au moins une characteristique commmune
bool column_same_characteristic(board game, int column)
{
	// si les piece on au moins une charactéristique commune retourne true
	if (piece_min_one_chara(game->tab[0][column], game->tab[1][column], game->tab[2][column], game->tab[3][column]))
	{
		return true;
	}
	
	// sinon retourne false
	return false;
}



// fonction permettent de retourner une piece a une position donné
piece get_piece(board game, int line, int column)
{
	return game->tab[line][column];
}






// fonction permettent de savoir si une ligne de piece de meme characteristique a été faite
bool has_winner(board game)
{
	
	// retourne true si chaque piece des ligne horizontal et vertical ont au moins une characteristique commune
	for (int i = 0; i < DIMENSION; i++)
	{
		if (line_same_characteristic(game, i) || column_same_characteristic(game, i))
		{
			return true;
		}
	}
	
	// retourne true si les piece diagonale on au moins une characteristique commune
	if (piece_min_one_chara(game->tab[0][0], game->tab[1][1], game->tab[2][2], game->tab[3][3]))
	{
		return true;
	}
	
	if (piece_min_one_chara(game->tab[3][0], game->tab[2][1], game->tab[1][2], game->tab[0][3]))
	{
		return true;
	}
	
	// retourne false si aucune piece d'une meme ligne n'a de characteristique commune
	return false;
}



// fonction permettent de placer une piece donné sur le plateau a une position donné
enum return_code place_piece(board game, int line, int column, piece a_piece)
{
	// si la position est occupé retourne une erreur de type position
	if (is_occupied(game, line, column) )
	{
		return POSITION;
	}
	
	// si la piece a déja été joué retourne une erreur de type piece
	if (!(piece_is_free(game, a_piece)))
	{
		return PIECE;
	}
	
	// place la piece dans le tableau a la position donné
	game->tab[line][column] = a_piece;
	
	// retourne un enum SUCCESS designant que la piece a bien été placé
	return SUCCESS;
}



// fonction permettent de renvoyer une piece de caractéristique donnés si la piece est libre
piece get_piece_from_characteristics(board game, enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top)
{
	// crée une struct piece
	piece a_piece;
	
	// permet d'allouer les data en dehors de la pile de la fonction
	a_piece = malloc(sizeof(struct piece_t));
	
	// définis la piece avec les characteristique donné 
	a_piece->p_size = a_size ;
	a_piece->p_shape = a_shape;
	a_piece->p_color = a_color;
	a_piece->p_top = a_top;
	
	// renvois NULL si la piece a déja été placé sur le bord
	if (!(piece_is_free(game, a_piece)))
	{
		free(a_piece);
		return NULL;
	}
	
	// renvoie la piece crée si la piece n'a pas déja été jouer
	return a_piece;
}

// fonction permettent de demander a l'utilisateur une piece
piece ask_choose_piece(save game_save)
{

	int a = 2;
	int b = 2; 
	int c = 2;
	int d = 2;
	
	piece a_piece = NULL;
	
	// affiche le nom de l'utilisateur qui dois choisir une piece
	printf("%s choisiser une piece", game_save->joueur_name[game_save->joueur_tour]);
	printf("\nveuiller entrer 4 nombre de 0 ou 1:");
	
	// demande une piece tant que la piece choisie n'est pas correct
	while (a_piece == NULL)
	{
	
		// permet de n'ecrire que 4 int
		scanf("%1d%1d%1d%1d", &a, &b, &c, &d);
		
		while (!((a == 0 || a == 1) && (b == 0 || b == 1) && (c == 0 || c == 1) && (d == 0 || d == 1)))
		{
			printf("\nveuiller reesayer avec les bonne valeur\n");
			printf("veuiller entrer 4 nombre de 0 ou 1:");
			while ((getchar()) != '\n');
			
			scanf("%1d%1d%1d%1d", &a, &b, &c, &d);
		}
		
		a_piece = get_piece_from_characteristics(game_save->game, a, b, c, d);
		
		// si piece est null alors demande de réessayer
		if (a_piece == NULL)
		{
			printf("\npiece deja placer veuiller reesayer:");
		}
	}
	
	return a_piece;

}

// fonction permettant aux joueur de plaçer la piece qui fut choisie
void ask_choose_emplacement(save game_save, piece a_piece)
{
	int a = 5;
	int b = 5; 
	enum return_code valid;
	
	printf("%s choisiser un emplacement", game_save->joueur_name[game_save->joueur_tour]);
	printf("\nveuiller entrer 2 nombre de 1 a 4:");
	
	while (valid != SUCCESS)
	{
		scanf("%1d%1d", &a, &b);
		
		while (!((a >= 1 && a <= 4) && (b >= 1 && b <= 4)))
		{
			printf("\nveuiller reesayer avec les bonne valeur\n");
			printf("veuiller entrer 2 nombre de 1 a 4:");
			while ((getchar()) != '\n');
			
			scanf("%1d%1d", &a, &b);
		}

		// debuging
		valid = place_piece(game_save->game, a-1, b-1, a_piece);
		
		if (valid != SUCCESS)
		{
			printf("\nemplacement pris veuiller reesayer:");
		}
		
	 }
}

// demande a l'utilisateur un nom
save ask_name(save game_save, int joueur)
{
	char name[10];
	scanf("%s", name);
	strcpy(game_save->joueur_name[joueur], name);
	return game_save;
}

int ask_number_between(int low_value, int high_value, int number)
{
	scanf("%1d", &number);
	
	while (!(number >= low_value && number <= high_value))
	{
		scanf("%1d", &number);
		printf("\reesayer avec les bonne valeur\n");
		printf("veuiller entrer 1 nombre de %d a %d:", low_value, high_value);
		while ((getchar()) != '\n');
	}
	
	return number;
}

// fonction permettent de désallouer la memoire de l'instance de la fonction de board
void destroy_game(board game)
{
	free(game);
}

void destroy_save(save game_save)
{
	free(game_save);
}

/** 
 * 
 * 
 * 
 *           affichage 
 * 
 * 
 * 
 *
**/


void affichage_titre()
{
	for (int i = 0; i < 5; i++)
	{
		for (int y = 0; y < 40; y++)
		{
			if (i == 0 || i == 4) printf("\033[9m \033[m");
		
			else if (y == 0 || y == 39) printf("|");
			
			else if (i == 2 && y == 13) {
				printf("PROJECT-QUARTO");
				y += 13;
			}
			
			else printf("\033[95m \033[m");
		}
		printf("\n");
	}
	printf("\n");
}

void affichage_menu()
{
	affichage_titre();
	
	printf("Bienvenue sur Quarto project\n\n");
	printf("1: Lancer une partie\n");
	printf("2: Charger une partie\n");
	printf("3: Regarder le Hall of Fame\n\n");
}

void print_symbol(int a_piece)
{
	
	
	switch (a_piece)
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
			printf("error");
			break;
	}													
}


void print_symbol_by_piece(piece a_piece)
{
	int val;
	
	val = a_piece->p_size * 8;
	val += a_piece->p_shape * 4;
	val += a_piece->p_color * 2;
	val += a_piece->p_top;
	

	print_symbol(val);
	
}

void print_board(board game, int i, int y)
{
	if ((y + 1) % 4 == 0)
	{
		printf("|");
	}
	else
	{
		if ((i + 1) % 4 == 0)
		{
			printf("-");	
		}
		else
		{
			if ((i - 1) % 4 == 0 && (y - 1) % 4 == 0 && is_occupied(game, (i - 1) / 4, (y - 1) / 4))
			{
				print_symbol_by_piece(game->tab[(i - 1) / 4][(y - 1) / 4]);
			}
			else
			{
				printf(" ");
			}
		}
	}
}


void print_all_piece(int i, int y)
{
	
	if (y == 31)
	{
		print_symbol(i);
	}
	
	
}


void affiche_game(board game)
{
	
	// affichage du titre
	affichage_titre();
	
	
	// affichage du jeu
	for (int i = 0; i < 16; i++)
	{
		
		for (int y = 0; y < 40; y++)
		{
			
			if (y < 15 && i < 15)
			{
				print_board(game, i, y);
			}
			else 
			{
				if (y > 19)
				{
					print_all_piece(i, y);
				}
				else
				{
					printf(" ");		
				}
			}
			
		}
		printf("\n");
	}
	printf("\n");
}