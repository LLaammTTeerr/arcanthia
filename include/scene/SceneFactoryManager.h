// Factory Manager (Registry Pattern + Factory Pattern)
#pragma once
#include "SceneFactory.h"

class SceneFactoryManager {
public:
    static SceneFactoryManager& getInstance();
    void registerFactory(const std::string& sceneName, std::unique_ptr<SceneFactory> factory);
    std::unique_ptr<Scene> createScene(const std::string& sceneName);
    bool hasFactory(const std::string& sceneName) const;
    
private:
    std::unordered_map<std::string, std::unique_ptr<SceneFactory>> m_factories;
};