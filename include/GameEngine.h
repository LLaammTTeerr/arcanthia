#pragma once
// #include "SceneManager.h"
class SceneManager;

class GameEngine {
private:
  SceneManager* sceneManager;
public:
  GameEngine(void);
  ~GameEngine(void) = default;

  void update(void);
  void render(void);
  static GameEngine& getInstance(void);
  GameEngine(const GameEngine&) = delete;
  GameEngine& operator=(const GameEngine&) = delete;
  GameEngine(GameEngine&&) = delete;
  GameEngine& operator=(GameEngine&&) = delete;

};


