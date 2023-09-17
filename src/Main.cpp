#include "Game.h"
#include "GameObject.h"
#include "Components/Renderer.h"
int main(int argc, char* argv[])
{
	bool success = Game::Initialize();
	GameObject* test = new GameObject("test");
	test->AddComponent(new Renderer(test));
	Game::AddGameObject(test);
	if (success) 
	{
		Game::GameLoop();
	}
	return 0;
}