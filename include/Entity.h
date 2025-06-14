#pragma once
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include <typeindex>

using EntityID = unsigned int;

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
  std::unordered_map<EntityID, std::unordered_map<std::type_index, std::shared_ptr<Component>>> components;
public:
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