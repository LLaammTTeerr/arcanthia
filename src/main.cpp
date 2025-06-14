#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <unordered_map>
#include <stdexcept>
#include <vector>
#include <typeindex>

class Scene {
public:
  virtual void update(void) = 0;
  virtual void render(void) = 0;
  virtual ~Scene(void) = default;
};

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

class CameraController {
private:
  Camera3D camera;
public:
  CameraController(void) {
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
  }

  void update(void) {
    UpdateCamera(&camera, CAMERA_ORBITAL);
  }

  Camera3D& getCamera(void) {
    return camera;
  }
};

class ModelManager {
private:
  std::unordered_map<std::string, Model> models;
public:
  bool loadModel(const std::string& name, const char* filePath) {
    if (models.find(name) != models.end()) {
      return 0;
    }
    Model model = LoadModel(filePath);
    if (model.meshCount == 0) {
      return false;
    }
    models[name] = model;
    return true;
  }

  const Model& getModel(const std::string& name) const {
    auto it = models.find(name);
    if (it != models.end()) {
      return it->second;
    }
    throw std::runtime_error("Model not found: " + name);
  }

  ModelManager(void) {
    for (auto& pair : models) {
      UnloadModel(pair.second);
    }
  }
};

using EntityID = u_int32_t;

class Entity {
private:
  static EntityID nextID;
  static EntityID generateID(void) {
    return nextID++;
  }
  EntityID id;
public:
  Entity(void) : id(generateID()) {}

  EntityID getID(void) const {
    return id;
  }
};

EntityID Entity::nextID = 0;

class Component {
public:
  virtual ~Component(void) = default;
};

class EntityManager {
private:
  std::unordered_map<EntityID, std::unordered_map<std::type_index, std::shared_ptr<Component>>> components;public:
  template<typename T, typename... Args>
  void addComponent(EntityID entityID, Args&&... args) {
    static_assert(std::is_base_of<Component, T>::value, "T must inherit from Component");
    auto& entityComponents = components[entityID];
    if (entityComponents.find(typeid(T)) != entityComponents.end()) {
      throw std::runtime_error("Component already exists for this entity");
    }
    entityComponents[typeid(T)] = std::make_shared<T>(std::forward<Args>(args)...);
  }

  template<typename T>
  std::shared_ptr<T> getComponents(EntityID entityID) {
    auto it = components.find(entityID);
    if (it != components.end()) {
      auto& entityComponents = it->second;
      auto compIt = entityComponents.find(typeid(T));
      if (compIt != entityComponents.end()) {
        return std::static_pointer_cast<T>(compIt->second);
      }
    }
    return nullptr;
  }
};

class GameEngine {
public:
  void run(void) {
    InitWindow(800, 600, "Game Engine Example");
    SetTargetFPS(60);

    SceneManager sceneManager;
    CameraController cameraController;

    while (!WindowShouldClose()) {
      cameraController.update();
      sceneManager.update();

      BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode3D(cameraController.getCamera());

      sceneManager.render();
      DrawGrid(10, 1.0f);
      DrawSphere((Vector3){ 0.0f, 1.0f, 0.0f }, 0.5f, BLUE);

      EndMode3D();
      EndDrawing();
    }

    CloseWindow();
  }
};

int main(void) {
  GameEngine engine;
  engine.run();
  return 0;
}