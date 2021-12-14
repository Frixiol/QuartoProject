#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "board.h"



enum state { 
	MENU,
	GAME,
	HALL,
	QUIT
};

enum state launcher;

save game_save;


void menu()
{
	int menu_choice = 0;
	
	
	
	affichage_menu();
	
	menu_choice = ask_number_between(1, 4, menu_choice);
	
	
	if (menu_choice == 1)
	{
		launcher = GAME;
		game_save = new_save();
	}
	
	if (menu_choice == 2)
	{
		launcher = MENU;
		//save game_save = load_save();
	}
	
	if (menu_choice == 3)
	{
		launcher = HALL;
	}
	
	if (menu_choice == 4)
	{
		launcher = QUIT;
	}
	
}

void game()
{
	
	system("clear");
	
	affichage_titre();
	
	game_save->game = new_game();
	
	printf("choisiser un nom pour joueur 1:");
	ask_name(game_save, 0);
	
	printf("choisiser un nom pour joueur 2:");
	ask_name(game_save, 1);
	
	system("clear");
	affiche_game(game_save->game);
	
    while (!(has_winner(game_save->game)))
    {
		
		piece a_piece = ask_choose_piece(game_save);
		
		game_save->joueur_tour = (game_save->joueur_tour + 1) % 2;
		
		ask_choose_emplacement(game_save, a_piece);
	
		system("clear");
		
		affiche_game(game_save->game);
		
	}
	
	// affichage du gagnant de la partie en fonction de qui à jouer en dernier
	printf("le joueur %d a gagné\n", game_save->joueur_tour);

	hall_write(game_save->joueur_name[game_save->joueur_tour]);
	
	destroy_game(game_save->game);
	destroy_save(game_save);
	
	printf("suppression du plateau et sortie\n");
	
	launcher = MENU;
}


void hall_of_fame()
{
	system("clear");
	affichage_titre();
	
	hall_read();
    
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
		
		else if (launcher == GAME) game();
		
		else if (launcher == HALL) hall_of_fame();
		
		else if (launcher == QUIT) run = false;
	}
	return 0;
}

