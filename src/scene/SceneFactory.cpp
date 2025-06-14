#include "SceneFactory.h"
#include "WelcomeScene.h"

// Concrete Factory Implementations
std::unique_ptr<Scene> MenuSceneFactory::createScene() {
    return std::make_unique<MenuScene>();
}

std::unique_ptr<Scene> GameplaySceneFactory::createScene() {
    return std::make_unique<GameplayScene>();
}

std::unique_ptr<Scene> PauseSceneFactory::createScene() {
    return std::make_unique<PauseScene>();
}

std::unique_ptr<Scene> GameOverSceneFactory::createScene() {
    return std::make_unique<GameOverScene>();
}

std::unique_ptr<Scene> SettingsSceneFactory::createScene() {
    return std::make_unique<SettingsScene>();
}

std::unique_ptr<Scene> WelcomeSceneFactory::createScene() {
    return std::make_unique<WelcomeScene>();
}