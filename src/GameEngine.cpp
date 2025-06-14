#include "GameEngine.h"
#include "SceneManager.h"
#include <mutex>

GameEngine& GameEngine::getInstance(void) {
  static GameEngine* instance = nullptr;
  static std::mutex mutex;
  
  if (instance == nullptr) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
      instance = new GameEngine();
    }
  }
  return *instance;
}


GameEngine::GameEngine(void) {
  sceneManager = new SceneManager();
}

void GameEngine::update(void) {
  sceneManager->update(0.016f); // Assuming a fixed delta time for simplicity
}

void GameEngine::render(void) {
  sceneManager->render();
}
