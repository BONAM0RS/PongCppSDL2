
#pragma once

// C++ Standard Libraries
#include <unordered_map>
#include <memory>

// Class Headers
#include "Object.h"


class ObjectManager {

private:
    ObjectManager();
    ~ObjectManager();

public:
    static ObjectManager& getInstance();

    void registerObject(std::string name, LayerPriority priority);
    void removeObject(std::string name);
    void deleteAllObjects();

    void registerRenderer(SDL_Renderer* renderer);
    
    void renderAllGraphicObjects();

    SDL_Renderer* getRenderer();
    std::shared_ptr<Object> getObjectByName(std::string name);

private:
    void renderLayer(LayerPriority priority);
    
    long long m_objectCount = 0;
    SDL_Renderer* m_renderer = nullptr;
    std::unordered_map<std::string, std::shared_ptr<Object>> m_objects;
};

