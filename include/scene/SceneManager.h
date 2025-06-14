#pragma once

#include "Scene.h"
#include "SceneFactory.h"
#include <memory>
#include <stack>
#include <string>

class SceneManager {
public:
    
    SceneManager();
    ~SceneManager() = default;
    
    // Scene management
    void pushScene(const std::string& sceneName);
    void popScene();
    void changeScene(const std::string& sceneName);
    void clearAllScenes();
    
    // Core update loop
    void update(float deltaTime);
    void render();
    // void handleInput(const InputManager& input);
    
    // Scene queries
    Scene* getCurrentScene() const;
    size_t getSceneCount() const { return m_sceneStack.size(); }
    bool isEmpty() const { return m_sceneStack.empty(); }
    
    // Transition management
    // void requestTransition(const std::string& sceneName);
    // bool isTransitioning() const { return m_pendingTransition; }
    
private:
    struct SceneStackEntry {
        std::unique_ptr<Scene> scene;
        std::string name;
        bool isPaused = false;

        SceneStackEntry(std::unique_ptr<Scene>&& s, const std::string& n)
            : scene(std::move(s)), name(n) {}
    };
    
    std::stack<SceneStackEntry> m_sceneStack;
    
    // Transition handling
    bool m_pendingTransition = false;
    std::string m_nextSceneName;
    bool m_isChangeScene = false;
    
    // void processTransition();
    std::unique_ptr<Scene> createScene(const std::string& name);
};