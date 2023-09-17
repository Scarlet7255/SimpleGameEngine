#pragma once
#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <unordered_set>
#include <glew.h>

class Game
{
public:
	// Initialize Game Configure
	static bool Initialize();
	// Run Game Loop
	static void GameLoop();
	// Exit Game

	static void Exit();
	static void AddGameObject(class GameObject*);
	static void RemoveGameObject(class GameObject*);

	static void AddRenderer(class Renderer* renderer);
	static void RemoveRenderer(class Renderer* renderer);

private:

	static void ProcessInput();
	// Update Game Logic
	static void UpdateGame();
	static void GenerateOutput();

	static void ConfigOpenGL();
	
	static SDL_Window* mWindow;
	static SDL_GLContext mOpenGLContext;

	static bool mIsRunning;
	static Uint32 mTickCount;

	static std::vector<class GameObject* > mGameObjects;
	static std::unordered_set<class GameObject* > mDeadGameObjects;
	static std::vector<class GameObject* > mNewGameObjects;

	static std::vector<class Renderer*> mRenderers;
};

#endif // !GAME_H