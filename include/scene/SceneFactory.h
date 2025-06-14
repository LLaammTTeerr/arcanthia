#pragma once

#include "Scene.h"
#include <memory>
#include <unordered_map>
#include <string>

// Abstract Factory
class SceneFactory {
public:
    virtual ~SceneFactory() = default;
    virtual std::unique_ptr<Scene> createScene() = 0;
    virtual const char* getSceneType() const = 0;
};

// Concrete Factories for each scene type
class MenuSceneFactory : public SceneFactory {
public:
    std::unique_ptr<Scene> createScene() override;
    const char* getSceneType() const override { return "MenuScene"; }
};

class GameplaySceneFactory : public SceneFactory {
public:
    std::unique_ptr<Scene> createScene() override;
    const char* getSceneType() const override { return "GameplayScene"; }
};

class PauseSceneFactory : public SceneFactory {
public:
    std::unique_ptr<Scene> createScene() override;
    const char* getSceneType() const override { return "PauseScene"; }
};

class GameOverSceneFactory : public SceneFactory {
public:
    std::unique_ptr<Scene> createScene() override;
    const char* getSceneType() const override { return "GameOverScene"; }
};

class SettingsSceneFactory : public SceneFactory {
public:
    std::unique_ptr<Scene> createScene() override;
    const char* getSceneType() const override { return "SettingsScene"; }
};

class WelcomeSceneFactory : public SceneFactory {
public:
    std::unique_ptr<Scene> createScene() override;
    const char* getSceneType() const override { return "WelcomeScene"; }
};