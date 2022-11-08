
#pragma once

// C++ Standard Libraries
#include <string>
#include <unordered_map>

// SDL Libraries
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


class AssetManager {

private:
    AssetManager();
    AssetManager(AssetManager const&);
    AssetManager operator=(AssetManager const&);
    ~AssetManager();

public:
    static AssetManager& getInstance();

    SDL_Texture* loadSpriteTexture(std::string path);
    TTF_Font* loadTextFont(std::string fontpath, int ptsize);
    Mix_Music* loadMusic(std::string path);
    Mix_Chunk* loadSound(std::string path);

private:
    std::unordered_map<std::string, SDL_Texture*> m_textures;
    std::unordered_map<std::string, TTF_Font*> m_fonts;
    std::unordered_map<std::string, Mix_Music*> m_music;
    std::unordered_map<std::string, Mix_Chunk*> m_sounds;
};

