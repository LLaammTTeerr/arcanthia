#pragma once
#include <string>
// abstract class 
class Scene {
public:
  virtual ~Scene(void) = default;
  virtual void init(void) = 0;
  virtual void update(float deltaTime) = 0;
  virtual void render(void) = 0;
  virtual void cleanup(void) = 0;
  virtual bool isActive(void) const = 0;
  virtual const char* getName(void) const = 0;


  // Scene transition methods
  virtual void onEnter(void) = 0;
  virtual void onExit(void) = 0;
  virtual void pause(void) {}   // For pausable scenes
  virtual void resume(void) {}  // For resuming paused scenes

  // Scene management
  virtual bool shouldTransition(void) const { return false; }
  virtual const std::string getNextScene(void) const { return ""; }
  virtual bool isTransparent(void) const { return false; } // For overlay scenes
  virtual bool isPausable(void) const { return true; }
    
  // Resource management
  virtual void loadResources(void) {} // Load scene-specific resources
  virtual void unloadResources(void) {} // Unload when scene ends

protected:
  bool m_isActive = false;
  bool m_isPaused = false;
  float m_transitionTimer = 0.0f;
};




class MenuScene : public Scene {
public:
  MenuScene(void) = default;
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

class GameplayScene : public Scene {
public:
  GameplayScene(void) = default;
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

class PauseScene : public Scene {
public:
  PauseScene(void) = default;
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

class GameOverScene : public Scene {
public:
  GameOverScene(void) = default;
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

class SettingsScene : public Scene {
public:
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
