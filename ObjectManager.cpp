
// C++ Standard Libraries
#include <iostream>

// This Class header
#include "ObjectManager.h"


ObjectManager::ObjectManager()
{
	// std::cout << " ObjectManager created \n" << std::endl;
}


ObjectManager::~ObjectManager()
{

}


ObjectManager& ObjectManager::getInstance()
{
    static ObjectManager* s_instance = new ObjectManager;
    return *s_instance;
}


void ObjectManager::registerObject(std::string name, LayerPriority priority)
{
    std::shared_ptr<Object> newObject = std::make_shared<Object>(name);
    newObject->setLayerPriority(priority);
    m_objects.insert(std::make_pair(name, newObject));

    m_objectCount++;

    if (m_objects[name] != nullptr)
    {
        std::cout << "\t The Object '" << name << "' has been registered \n" << std::endl;
    }
    else
    {
        std::cout << "\t Error! The Object '" << name << "' has not been registered!" << std::endl;
    }
}


void ObjectManager::removeObject(std::string name)
{
    auto it = m_objects.find(name);
    m_objects.erase(it);
    m_objectCount--;

    std::cout << "\t The Object '" << name << "' has been removed \n" << std::endl;
}


void ObjectManager::deleteAllObjects()
{
    m_objects.erase(m_objects.begin(), m_objects.end());
    m_objectCount = 0;

    std::cout << "\t All Objects has been removed" << std::endl;
}


void ObjectManager::registerRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}


void ObjectManager::renderAllGraphicObjects()
{
    renderLayer(LayerPriority::BACKGROUND);
    renderLayer(LayerPriority::MIDDLEGROUND);
    renderLayer(LayerPriority::FOREGROUND);
}


void ObjectManager::renderLayer(LayerPriority priority)
{
    
    for (auto it = m_objects.begin(); it != m_objects.end(); it++) {
        if (m_objects[it->first] != nullptr && 
            m_objects[it->first]->getRectComponent() != nullptr && 
            m_objects[it->first]->getGraphicState() == true &&
            priority == m_objects[it->first]->getLayerPriority())
        {
            SDL_Rect rectangle = m_objects[it->first]->getRectComponent()->getRect();
            SDL_Texture* texture = nullptr; 

            if (m_objects[it->first]->getSpriteComponent() != nullptr)
            {
                texture = m_objects[it->first]->getSpriteComponent()->getTexture();
            }

            if (m_objects[it->first]->getTextComponent() != nullptr)
            {
                texture = m_objects[it->first]->getTextComponent()->getTexture();
            }

            if (texture != nullptr)
            {
                if (SDL_RenderCopy(m_renderer, texture, NULL, &rectangle) < 0)
                {
                    std::cout << "SDL_RenderCopy: " << SDL_GetError() << std::endl;
                }
                
            }
        }
    }
}


SDL_Renderer* ObjectManager::getRenderer() 
{ 
    return m_renderer; 
}


std::shared_ptr<Object> ObjectManager::getObjectByName(std::string name)
{
    return (m_objects[name]);
}

