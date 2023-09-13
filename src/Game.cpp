#include "Game.h"
#include "GameObject.h"

SDL_Window* Game::mWindow = nullptr;
SDL_GLContext Game::mOpenGLContext = NULL;

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
   
    ConfigOpenGL();
    mWindow = SDL_CreateWindow(
        "Game Engine",// window title
        100, // top left x-coordinate of window
        100, // top left y-coordinate of window
        1024,// window width
        768, // window height
        SDL_WINDOW_OPENGL// window set flag
    );

    if (!mWindow) 
    {
        SDL_Log("Unable to initialize SDL Window: %s", SDL_GetError());
        return false;
    }
    mOpenGLContext = SDL_GL_CreateContext(mWindow);
    
    glewExperimental = true;
    if (glewInit() != GLEW_OK) 
    {
        SDL_Log("Failed to initialize GLEW");
        return false;
    }
    glGetError();
    return true;
}

void Game::Exit() 
{
    SDL_GL_DeleteContext(mOpenGLContext);
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

    // delay removev and create GameObjects
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

void Game::GenerateOutput()
{
    // set color to gray
    glClearColor(0.0f, 0.5f, 0.86f,1.0f);
    // clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(mWindow);
}

void Game::ConfigOpenGL()
{
    //Use core core OpenGL profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    // Choose OpenGL version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    // Request 8-bits color buffer pre RGB channel
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    // Enable double buffering
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    //  Force Open_GL use hardware acceleration
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
}
