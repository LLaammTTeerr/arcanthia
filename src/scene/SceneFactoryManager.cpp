#include "SceneFactoryManager.h"
#include <mutex>
#include <iostream>

void SceneFactoryManager::registerFactory(const std::string& sceneName, 
                                         std::unique_ptr<SceneFactory> factory) {
    m_factories[sceneName] = std::move(factory);
}

// Factory Manager Implementation
SceneFactoryManager& SceneFactoryManager::getInstance() {
  static SceneFactoryManager* instance = nullptr;
  static std::mutex mutex;
  if (!instance) {
    std::lock_guard<std::mutex> lock(mutex);
    if (!instance) {
      instance = new SceneFactoryManager();
      // Register default factories
      instance->registerFactory("MenuScene", std::make_unique<MenuSceneFactory>());
      instance->registerFactory("GameplayScene", std::make_unique<GameplaySceneFactory>());
      instance->registerFactory("PauseScene", std::make_unique<PauseSceneFactory>());
      instance->registerFactory("GameOverScene", std::make_unique<GameOverSceneFactory>());
      instance->registerFactory("SettingsScene", std::make_unique<SettingsSceneFactory>());
      instance->registerFactory("WelcomeScene", std::make_unique<WelcomeSceneFactory>());
    }
  }
  return *instance;
}

std::unique_ptr<Scene> SceneFactoryManager::createScene(const std::string& sceneName) {
  SceneFactoryManager& instance = getInstance();
    if (instance.m_factories.empty()) {
        std::cerr << "No factories registered. Cannot create scene: " << sceneName << std::endl;
        return nullptr;
    }

    // Find the factory for the requested scene name
    auto it = instance.m_factories.find(sceneName);
    if (it != instance.m_factories.end()) {
        return it->second->createScene();
    }
    return nullptr;
}

bool SceneFactoryManager::hasFactory(const std::string& sceneName) const {
    SceneFactoryManager& instance = getInstance();
    return instance.m_factories.find(sceneName) != instance.m_factories.end();
}