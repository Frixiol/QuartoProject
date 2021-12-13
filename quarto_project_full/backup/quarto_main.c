#include <stdio.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
	run = true;
	while (run)
	{
		menu();
		
		game();
		
		menu_end();
	}
	return 0;
}

