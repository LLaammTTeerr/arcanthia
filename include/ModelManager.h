#pragma once
#include <unordered_map>
#include <stdexcept>
#include <string>
#include <raylib.h>
#include <iostream>

class ModelManager {
private:
  std::unordered_map<std::string, Model> models;
public:
  bool loadModel(const std::string& name, const char* filePath) {
    if (models.find(name) != models.end()) {
      return 0;
    }
    Model model = LoadModel(filePath);
    BoundingBox box = GetModelBoundingBox(model);
    Vector3 size = {
      box.max.x - box.min.x,
      box.max.y - box.min.y,
      box.max.z - box.min.z
    };
    std::cerr << "Model: " << name << " loaded with size: "
              << size.x << ", " << size.y << ", " << size.z << std::endl;
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