
// C++ Standard Libraries
#include <iostream>

// SDL Libraries
#include <SDL_image.h>

// Class Headers
#include "ObjectManager.h"

// This Class header
#include "AssetManager.h"


AssetManager::AssetManager()
{ 
    // std::cout << "\n AssetManager created \n" << std::endl;
}

AssetManager::AssetManager(AssetManager const&)
{ 
    
}

AssetManager AssetManager::operator=(AssetManager const& rhs)
{
    return *this;
}

AssetManager::~AssetManager()
{

}


AssetManager& AssetManager::getInstance()
{
    static AssetManager* s_instance = new AssetManager;
    return *s_instance;
}


SDL_Texture* AssetManager::loadSpriteTexture(const std::string &path)
{
    auto search = m_textures.find(path);
    if (search != m_textures.end()) 
    {
        return m_textures[path];
    }
    else 
    {
        SDL_Renderer* renderer = ObjectManager::getInstance().getRenderer();
        SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());
        if (texture == NULL)
        {
            std::cout << "Could not load image: " << path << '\n' << SDL_GetError() << std::endl;
        }
        m_textures.insert(std::make_pair(path, texture));

        return m_textures[path];
    }

    return nullptr;
}


TTF_Font* AssetManager::loadTextFont(const std::string &fontpath, int ptsize)
{
    auto search = m_fonts.find(fontpath);
    if (search != m_fonts.end())
    {
        return m_fonts[fontpath];
    }
    else
    {
        SDL_Renderer* renderer = ObjectManager::getInstance().getRenderer();
        TTF_Font* font = TTF_OpenFont(fontpath.c_str(), ptsize);
        if (font == NULL)
        {
            std::cout << "Could not load font" << fontpath << '\n' << TTF_GetError() << std::endl;
        }
        m_fonts.insert(std::make_pair(fontpath, font));

        return m_fonts[fontpath];
    }

    return nullptr;
}


Mix_Music* AssetManager::loadMusic(const std::string &path)
{
    auto search = m_music.find(path);
    if (search != m_music.end())
    {
        return m_music[path];
    }
    else
    {
        Mix_Music* music = Mix_LoadMUS(path.c_str());

        if (music == NULL)
        {
            std::cout << "Could not load music" << path << '\n' << SDL_GetError() << std::endl;
        }
        m_music.insert(std::make_pair(path, music));

        return m_music[path];
    }

    return nullptr;
}


Mix_Chunk* AssetManager::loadSound(const std::string &path)
{
    auto search = m_sounds.find(path);
    if (search != m_sounds.end())
    {
        return m_sounds[path];
    }
    else
    {
        Mix_Chunk* sound = Mix_LoadWAV(path.c_str());

        if (sound == NULL)
        {
            std::cout << "Could not load sound" << path << '\n' << SDL_GetError() << std::endl; 
        }
        m_sounds.insert(std::make_pair(path, sound));

        return m_sounds[path];
    }

    return nullptr;
}