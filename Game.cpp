#include "Game.h"
#include "GameObject.h"
SDL_Window* Game::mWindow = nullptr;
SDL_Renderer* Game::mRenderer = nullptr;

bool Game::mIsRunning = false;
Uint32 Game::mTickCount = 0;

std::vector<class GameObject* > Game::mGameObjects;
std::unordered_set<class GameObject* > Game::mDeadGameObjects;
std::vector<class GameObject* > Game::mNewGameObjects;

bool Game::Initialize()
{
    //Initialize SDL Video System
    int sdlRes = SDL_Init(SDL_INIT_VIDEO);
    if(sdlRes!=0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "Game Engine",// window title
        100, // top left x-coordinate of window
        100, // top left y-coordinate of window
        1024,// window width
        768, // window height
        0 // window set flag
    );

    if (!mWindow) 
    {
        SDL_Log("Unable to initialize SDL Window: %s", SDL_GetError());
        return false;
    }
    
    mRenderer = SDL_CreateRenderer( //create basic 2D SDL renderer
        mWindow,
        -1, 
        SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC
    );

    if (!mRenderer) 
    {
        SDL_Log("Unable to initialize SDL Renderer: %s", SDL_GetError());
        return false;
    }
    return true;
}

void Game::Exit() 
{
    SDL_DestroyWindow(mWindow);
    SDL_Quit();

}

void Game::AddGameObject(GameObject* obj)
{
    mNewGameObjects.push_back(obj);
}

void Game::RemoveGameObject(GameObject* obj)
{
    if (mDeadGameObjects.find(obj) == mDeadGameObjects.end()) {
        obj->Destroy();
        mDeadGameObjects.insert(obj);
    }
}

void Game::GameLoop()
{
    mIsRunning = true;
    while (mIsRunning)
    {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}


void Game::ProcessInput()
{
    SDL_Event event;
    // get input from input event queue
    while (SDL_PollEvent(&event))
    {
        switch (event.type) 
        { 
        case SDL_QUIT: 
            mIsRunning = false;
            break;
        }
    }
    int keyNumber = 0;
    const Uint8* state = SDL_GetKeyboardState(&keyNumber);

}

void Game::UpdateGame()
{
    float deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));// limit max fps
    
    if (deltaTime > 0.05f) 
    {
        deltaTime = 0.05f;
        for (auto i : mGameObjects) 
        {
            if (i->GetState() == GameObject::EActive) 
            {
                i->Update(deltaTime);
            }
        }
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
        mRenderer,
        0,
        100,
        100,
        255
    );
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);

    for (auto it = mDeadGameObjects.begin(); it != mDeadGameObjects.end(); ++it) 
    {
        for (auto i = mGameObjects.begin(); i != mGameObjects.end(); ++i)
        {
            if (*i == *it)
            {
                mGameObjects.erase(i);
                break;
            }
        }
        delete (*it);
    }
    mDeadGameObjects.clear();
    for (auto i : mNewGameObjects) 
    {
        mGameObjects.push_back(i);
    }
}
