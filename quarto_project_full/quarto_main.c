#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "board.h"
#include "external.h"


enum state { 
	MENU,
	NGAM,
	LGAM,
	HALL,
	CMTJ,
	QUIT
};

enum state launcher;

save game_save;


void menu()
{
	int menu_choice = 0;
	
	system("clear");
	affichage_menu();
	
	menu_choice = ask_number_between(1, 5, menu_choice);
	
	
	if (menu_choice == 1)
	{
		launcher = NGAM;
		game_save = new_save();
	}
	
	if (menu_choice == 2)
	{
		launcher = LGAM;
		game_save = new_save();
	}
	
	if (menu_choice == 3)
	{
		launcher = HALL;
	}
	
	if (menu_choice == 4)
	{
		launcher = CMTJ;
	}
	
	if (menu_choice == 5)
	{
		launcher = QUIT;
	}
	
}




void game()
{
		
	system("clear");
	affiche_game(game_save->game);
	
    while (!(has_winner(game_save->game)))
    {
		
		piece a_piece = ask_choose_piece(game_save);
		
		if (a_piece == NULL)
		{
			serialise_save(game_save);
			break;
		}
		
		game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
		
		ask_choose_emplacement(game_save, a_piece);
	
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

void load_game()
{
	
	game_save->game = new_game();
	load_save(game_save);
	
	game();
	
}

void hall_of_fame()
{
	system("clear");
	affichage_titre();
	
	hall_read("hall_of_fame.txt");
    
    // moyen de quitter le hall a CHANGER !!!
    int a;
	printf("entrer un nombre pour quitter:");
	scanf("%d", &a);
	
	launcher = MENU;
}


void how_to_play()
{
	system("clear");
	affichage_titre();
	
	hall_read("how_to_play.txt");
    
    // moyen de quitter le hall a CHANGER !!!
    int a;
	printf("entrer un nombre pour quitter:");
	scanf("%d", &a);
	
	launcher = MENU;
}


int main(int argc, char **argv)
{
	bool run = true;
	launcher = MENU;
	
	while (run)
	{
		if (launcher == MENU) menu();
		
		else if (launcher == NGAM) launch_game();
		
		else if (launcher == LGAM) load_game();
		
		else if (launcher == HALL) hall_of_fame();
		
		else if (launcher == CMTJ) how_to_play();
		
		else if (launcher == QUIT) run = false;
	}
	return 0;
}

