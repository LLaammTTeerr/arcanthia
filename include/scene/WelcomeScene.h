#pragma once
#include "Scene.h"

class WelcomeScene : public Scene {
public:
  WelcomeScene(void) = default;
  void init(void) override;
  void update(float deltaTime) override;
  void render(void) override;
  void cleanup(void) override;
  bool isActive(void) const override;
  const char* getName(void) const override;

  void onEnter(void) override;
  void onExit(void) override;
  void pause(void) override;
  void resume(void) override;
  bool shouldTransition(void) const override;
  const std::string getNextScene(void) const override;
  bool isTransparent(void) const override { return false; } // Menu is not an overlay
  bool isPausable(void) const override { return false; } // Menu is not pausable
  void loadResources(void) override;
  void unloadResources(void) override;
};
