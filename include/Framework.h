
#pragma once

// C++ Standard Libraries
#include <string>
#include <memory>

// SDL Libraries
#include <SDL.h>

// Class Headers
#include "LayerPriority.h"
#include "Object.h"


void createObject(const std::string &name, LayerPriority priority = LayerPriority::BACKGROUND);
std::shared_ptr<Object> getObjectByName(const std::string &name);


enum class FRKey {
    RIGHT,
    LEFT,
    DOWN,
    UP,
    P,
    R
};


class Framework {

public:
    Framework(Uint32 subsystemFlags, const char* title, int xPos, int yPos, int wSize, int hSize);
    virtual ~Framework();

    virtual bool Init() = 0;

    virtual void Close() = 0;

    virtual void Tick() = 0;

    virtual void KeyPressedEvent(FRKey k) = 0;

    virtual void KeyReleasedEvent(FRKey k) = 0;

    void setMaxFrameRate(unsigned int frameRate);
    
    unsigned int getMaxFrameRate() const;

    int getScreenWidth() const;
    int getScreenHeight() const;

    int getScreenWidthHalf() const;
    int getScreenHeightHalf() const;

    int getMouseX() const;
    int getMouseY() const;

    SDL_Window* getWindow() const;
    SDL_Renderer* getRenderer() const;

private:
    const int CUSTOM_WINDOW_WIDTH;
    const int CUSTOM_WINDOW_HEIGHT;

    const int HALF_WINDOW_WIDTH;
    const int HALF_WINDOW_HEIGHT;

    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;

    int m_mousePosX;
    int m_mousePosY;
    
    unsigned int m_maxFrameRate;
};


int run(Framework* app);

