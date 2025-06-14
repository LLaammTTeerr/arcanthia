#pragma once
#include <memory>

class Scene {
public:
  virtual void update(void) = 0;
  virtual void render(void) = 0;
  virtual ~Scene(void) = default;
};