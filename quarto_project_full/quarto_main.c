#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "board.h"
#include "external.h"

/*

programme crée par: Khalil Mohammad et Prigent Alan
Inspiré du jeu de Quarto © Gigamic SARL 1991 du concept de Blaise Muller.
    
commencer le: 19/11/2021 et finis le: 04/12/2021 
crée pour l'évaluation de la SAE 1.1 de 1ère année
Campus 3 de l'IUT Grand Ouest Normandie

*/

enum state { 
	MENU,
	NGAM,
	LGAM,
	HALL,
	CMTJ,
	QUIT
};

// variable de selection de page
enum state launcher;

// variable coontenant les donné de la partie
save game_save;

// fonction menu permettent de se deplacer dans les option du programme
void menu()
{
	int menu_choice = 0;
	
	system("clear");
	affichage_menu();
	
	// demande de choisir 
	menu_choice = ask_number_between(1, 5, menu_choice);
	
	switch (menu_choice)
	{
	
		case 1:
			launcher = NGAM;
			game_save = new_save();
			break;
			
		case 2:
			launcher = LGAM;
			game_save = new_save();
			break;
			
		case 3:
			launcher = HALL;
			break;
			
		case 4:
			launcher = CMTJ;
			break;
			
		case 5:
			launcher = QUIT;
			break;
		
		default:
			launcher = QUIT;
	
	}
	
}


// fonction de jeu
void game()
{
		
	system("clear");
	affiche_game(game_save->game);
	
	int tour = 0;
	
    while (!(has_winner(game_save->game)) && tour < 16)
    {
		
		piece a_piece = ask_choose_piece(game_save);
		
		if (a_piece == NULL)
		{
			serialise_save(game_save);
			break;
		}
		
		game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
		
		ask_choose_emplacement(game_save, a_piece);
		
		tour++;
	
		system("clear");
		affiche_game(game_save->game);
		
	}
	
	// affichage du gagnant de la partie en fonction de qui à jouer en dernier
	printf("le joueur %d a gagné\n", game_save->joueur_tour);

	hall_write(game_save->joueur_name[game_save->joueur_tour]);
	
	serialise_save(game_save);
	
	destroy_game(game_save->game);
	destroy_save(game_save);
	
	printf("suppression du plateau et sortie\n");
	
	launcher = MENU;
}


// fonction permettent de lancer une nouvelle partie
void launch_game()
{
	
	system("clear");
	affichage_titre();
	
	game_save->game = new_game();
	
	printf("choisiser un nom pour joueur 1:");
	ask_name(game_save, 0);
	
	printf("choisiser un nom pour joueur 2:");
	ask_name(game_save, 1);
	
	game();
	
}

// fonction permettent de charger et lancer une partie depuis un fichier
void load_game()
{
	
	game_save->game = new_game();
	load_save(game_save);
	
	game();
	
}

// fonction permettent d'afficher les score des joueurs
void hall_of_fame()
{
	system("clear");
	
	affichage_titre();
	
	hall_read("hall_of_fame.txt");
    
    ask_to_quit();
	
	launcher = MENU;
}

// fonction permettent d'afficher les instruction du jeu
void how_to_play()
{
	system("clear");
	affichage_titre();
	
	hall_read("how_to_play.txt");
    
    ask_to_quit();
	
	launcher = MENU;
}


int main(int argc, char **argv)
{
	// variable bool de la boucle principale
	bool run = true;
	
	// mene principale lancer 
	launcher = MENU;
	
	// boucle principale du programme
	while (run)
	{
		printf("a\n");
		
		if (launcher == MENU) menu();
		
		else if (launcher == NGAM) launch_game();
		
		else if (launcher == LGAM) load_game();
		
		else if (launcher == HALL) hall_of_fame();
		
		else if (launcher == CMTJ) how_to_play();
		
		else if (launcher == QUIT) run = false;
	}
	
	system("clear");
	return 0;
}

