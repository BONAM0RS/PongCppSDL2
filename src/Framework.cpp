
// C++ Standard Libraries
#include <iostream>

// SDL Libraries
#include <SDL_image.h>
#include <SDL_ttf.h>

// Class Headers
#include "ObjectManager.h"

// This Class header
#include "Framework.h"


void handleEvents(Framework* app, bool &runState);
void handleUpdate(Framework* app);
void handleRender(Framework* app);


Framework::Framework(Uint32 subsystemFlags, const char* title, int xPos, int yPos, int wSize, int hSize)
    : CUSTOM_WINDOW_WIDTH { wSize },
      CUSTOM_WINDOW_HEIGHT{ hSize },
      HALF_WINDOW_WIDTH{ wSize / 2 },
      HALF_WINDOW_HEIGHT{ hSize / 2 },
      m_mousePosX { 0 },
      m_mousePosY { 0 },
      m_maxFrameRate { 16 } // 60 FPS
{
    if (SDL_Init(subsystemFlags) < 0) { std::cout << " SDL could not be initialized: " << SDL_GetError() << std::endl; }
    else                              { std::cout << " SDL video system is ready to go" << std::endl; }

    int flags = IMG_INIT_PNG;
    int initStatus = IMG_Init(flags);
    if ((initStatus & flags) != flags) { std::cout << " SDL2_Image format not available: " << SDL_GetError() << std::endl; }
    else                               { std::cout << " SDL_image system is ready to go" << std::endl; }

    if (TTF_Init() == -1) { std::cout << "Could not initailize SDL2_ttf, error: " << TTF_GetError() << std::endl; }
    else                  { std::cout << " SDL2_ttf system ready to go! " << std::endl; }

    m_window = SDL_CreateWindow(title, xPos, yPos, wSize, hSize, SDL_WINDOW_SHOWN);

    std::cout << " WINDOW CREATED \n" << std::endl;

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
    ObjectManager::getInstance().registerRenderer(m_renderer);
}


Framework::~Framework()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);

    IMG_Quit();
    SDL_Quit();
}


void Framework::setMaxFrameRate(unsigned int frameRate) 
{ 
    m_maxFrameRate = 1000 / frameRate; 
}


int Framework::getMouseX() const             
{ 
    return m_mousePosX;   
}


int Framework::getMouseY() const             
{ 
    return m_mousePosY;    
}


unsigned int Framework::getMaxFrameRate() const      
{ 
    return m_maxFrameRate; 
}


int Framework::getScreenWidth() const
{
    return CUSTOM_WINDOW_WIDTH;
}


int Framework::getScreenHeight() const
{
    return CUSTOM_WINDOW_HEIGHT;
}


int Framework::getScreenWidthHalf() const
{
    return HALF_WINDOW_WIDTH;
}


int Framework::getScreenHeightHalf() const
{
    return HALF_WINDOW_HEIGHT;
}


SDL_Window* Framework::getWindow() const     
{ 
    return m_window;      
}


SDL_Renderer* Framework::getRenderer() const 
{ 
    return m_renderer;     
}



int run(Framework* app)
{
    bool isRunning = false;

    if (app->Init() == true)
    {
        isRunning = true;

        while (isRunning == true)
        {
            Uint32 start = SDL_GetTicks();
            
            handleEvents(app, isRunning);
            
            if (isRunning == true)
            {
                handleUpdate(app);
                handleRender(app);

                Uint32 elapsedTime = SDL_GetTicks() - start;
                if (elapsedTime < app->getMaxFrameRate())
                {
                    SDL_Delay(app->getMaxFrameRate() - elapsedTime);
                }
            }
        }
    }
    else
    {
        app->Close();
        delete app;
    }

    return 0;
}


void handleEvents(Framework* app, bool &runState)
{
    int m_mouseX = app->getMouseX();
    int m_mouseY = app->getMouseY();

    Uint32 mousePos = SDL_GetMouseState(&m_mouseX, &m_mouseY);

    SDL_Event event;
    
    while (SDL_PollEvent(&event)) 
    {
        FRKey key{};

        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)  { key = FRKey::LEFT;  }
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) { key = FRKey::RIGHT; }
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)    { key = FRKey::UP;    }
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)  { key = FRKey::DOWN;  }
            if (event.key.keysym.scancode == SDL_SCANCODE_P)     { key = FRKey::P;     }
            if (event.key.keysym.scancode == SDL_SCANCODE_R)     { key = FRKey::R;     }

            app->KeyPressedEvent(key);
        }

        else if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)  { key = FRKey::LEFT;  }
            if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT) { key = FRKey::RIGHT; }
            if (event.key.keysym.scancode == SDL_SCANCODE_UP)    { key = FRKey::UP;    }
            if (event.key.keysym.scancode == SDL_SCANCODE_DOWN)  { key = FRKey::DOWN;  }
            if (event.key.keysym.scancode == SDL_SCANCODE_P)     { key = FRKey::P;     }
            if (event.key.keysym.scancode == SDL_SCANCODE_R)     { key = FRKey::R;     }

            app->KeyReleasedEvent(key);
            
            if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            {
                runState = false;
                app->Close();
                delete app;
            }
        }

        if (event.type == SDL_QUIT)
        {
            runState = false;
            app->Close();
            delete app;
        }
    }
}


void handleUpdate(Framework* app)
{
    app->Tick();
}


void handleRender(Framework* app)
{
    SDL_SetRenderDrawColor(app->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(app->getRenderer());
    
    // I can use this to draw some basic privitives later
    // SDL_SetRenderDrawColor(app->getRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);

    ObjectManager::getInstance().renderAllGraphicObjects();
    
    SDL_RenderPresent(app->getRenderer());
}


void createObject(const std::string &name, LayerPriority priority)
{
    ObjectManager::getInstance().registerObject(name, priority);
}


std::shared_ptr<Object> getObjectByName(const std::string &name)
{
    return ObjectManager::getInstance().getObjectByName(name);
}

