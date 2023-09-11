#include "Main.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	Game* game = new Game();
	bool success = game->Initialize();
	if (success) 
	{
		game->GameLoop();
	}
	return 0;
}