#include <stdio.h>
#include <stdlib.h>
#include "board.h"



struct piece_t {
	
	enum size p_size;
	enum shape p_shape;
	enum color p_color;
	enum top p_top;
	
};

struct board_t {
	
	piece tab[DIMENSION][DIMENSION];
	
};

board new_game()
{
	board game;
	game = malloc(sizeof(struct board_t));
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			game->tab[i][y] = NULL;
		}
	}
	return game;	
}

bool is_occupied(board game, int line, int column)
{
	if (game->tab[line][column] != NULL)
	{
		return true;
	}
	return false;
}

bool piece_is_null(piece a_piece)
{
	if (a_piece == NULL)
	{
		return true;
	}
	return false;
}

bool is_same_piece(piece a_piece, piece b_piece)
{
	if (piece_is_null(a_piece) || piece_is_null(b_piece)) return false;
	
	
	if (a_piece->p_size == b_piece->p_size && a_piece->p_shape == b_piece->p_shape
		&& a_piece->p_color == b_piece->p_color && a_piece->p_top == b_piece->p_top)
	{
		return true;
	}
	return false;
}



bool piece_min_one_chara(piece piece_a, piece piece_b, piece piece_c, piece piece_d)
{
	
	if (piece_is_null(piece_a) || piece_is_null(piece_b) || piece_is_null(piece_c) || piece_is_null(piece_d)) return false;
	
	
	if ((piece_size(piece_a) == piece_size(piece_b)) == (piece_size(piece_c) == piece_size(piece_d)))
	{
		return true;
	}
	
	if ((piece_top(piece_a) == piece_top(piece_b)) == (piece_top(piece_c) == piece_top(piece_d)))
	{
		return true;
	}
	
	if ((piece_color(piece_a) == piece_color(piece_b)) == (piece_color(piece_c) == piece_color(piece_d)))
	{
		return true;
	}
	
	if ((piece_shape(piece_a) == piece_shape(piece_b)) == (piece_shape(piece_c) == piece_shape(piece_d)))
	{
		return true;
	}
	
	return false;
}


bool piece_is_free(board game, piece a_piece)
{
	
	for (int i = 0; i < DIMENSION; i++)
	{
		for (int y = 0; y < DIMENSION; y++)
		{
			
			if (is_same_piece(a_piece, game->tab[i][y]))
			{
				return false;
			}
		}
	}
	return true;
	
}

bool line_same_characteristic(board game, int line)
{
	if (piece_min_one_chara(game->tab[line][0], game->tab[line][1], game->tab[line][2], game->tab[line][3]))
	{
		return true;
	}
	return false;
}

bool column_same_characteristic(board game, int column)
{
	if (piece_min_one_chara(game->tab[0][column], game->tab[1][column], game->tab[2][column], game->tab[3][column]))
	{
		return true;
	}
	return false;
}


piece get_piece(board game, int line, int column)
{
	return game->tab[line][column];
}

enum size piece_size(piece a_piece)
{
	return a_piece->p_size;
}

enum top piece_top(piece a_piece)
{
	return a_piece->p_top;
}

enum color piece_color(piece a_piece)
{
	return a_piece->p_color;
}

enum shape piece_shape(piece a_piece)
{
	return a_piece->p_shape;
}

bool has_winner(board game)
{
	
	for (int i = 0; i < DIMENSION; i++)
	{
		if (line_same_characteristic(game, i) || column_same_characteristic(game, i))
		{
			return true;
		}
	}
	
	if (piece_min_one_chara(game->tab[0][0], game->tab[1][1], game->tab[2][2], game->tab[3][3]))
	{
		return true;
	}
	if (piece_min_one_chara(game->tab[3][0], game->tab[2][1], game->tab[1][2], game->tab[0][3]))
	{
		return true;
	}
	
	return false;
}

enum return_code place_piece(board game, int line, int column, piece a_piece)
{
	if (is_occupied(game, line, column) )
	{
		return POSITION;
	}

	if (!(piece_is_free(game, a_piece)))
	{
		return PIECE;
	}

	game->tab[line][column] = a_piece;
	return SUCCESS;
}

piece get_piece_from_characteristics(enum size a_size, enum shape a_shape, enum color a_color,  enum top a_top)
{
	piece a_piece;
	a_piece = malloc(sizeof(struct piece_t));
	
	a_piece->p_size = a_size ;
	a_piece->p_shape = a_shape;
	a_piece->p_color = a_color;
	a_piece->p_top = a_top;
	return a_piece;
}

void destroy_game(board game)
{
	free(game);
}

