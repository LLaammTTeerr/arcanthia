#pragma once
#include <memory>
#include "Scene.h"

class SceneManager {
private:
  std::shared_ptr<Scene> currentScene;
public:
  void changeScene(std::shared_ptr<Scene> newScene) {
    currentScene = std::move(newScene);
  }

  void update(void) {
    if (currentScene) {
      currentScene->update();
    }
  }

  void render(void) {
    if (currentScene) {
      currentScene->render();
    }
  }
};