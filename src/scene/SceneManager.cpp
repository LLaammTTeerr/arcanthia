#include "SceneManager.h"
#include "SceneFactoryManager.h"
#include <iostream>
SceneManager::SceneManager() {
    pushScene("WelcomeScene"); // Default scene
}

std::unique_ptr<Scene> createScene(const std::string& name) {
    return SceneFactoryManager::getInstance().createScene(name);
}


void SceneManager::pushScene(const std::string& sceneName) {
    auto newScene = createScene(sceneName);
    std::cout << "create scene: " << sceneName << std::endl;
    if (newScene) {
        std::cout << "create scene success: " << sceneName << std::endl;
        m_sceneStack.emplace(std::move(newScene), sceneName);
        auto& entry = m_sceneStack.top();
        entry.scene->loadResources();
        entry.scene->init();
        entry.scene->onEnter();
    }
}

void SceneManager::popScene() {
    if (!m_sceneStack.empty()) {
        auto& currentEntry = m_sceneStack.top();
        currentEntry.scene->onExit();
        currentEntry.scene->cleanup();
        currentEntry.scene->unloadResources();
        m_sceneStack.pop();
    }
} 

void SceneManager::changeScene(const std::string& sceneName) {
    m_nextSceneName = sceneName;
    m_isChangeScene = true;
    m_pendingTransition = true;
}

void SceneManager::clearAllScenes() {
    while (!m_sceneStack.empty()) {
        auto& currentEntry = m_sceneStack.top();
        currentEntry.scene->onExit();
        currentEntry.scene->cleanup();
        currentEntry.scene->unloadResources();
        m_sceneStack.pop();
    }
}

void SceneManager::update(float deltaTime) {
    // if (m_pendingTransition) {
    //     processTransition();
    // } else if (!m_sceneStack.empty()) {
    //     auto& currentEntry = m_sceneStack.top();
    //     if (currentEntry.scene->isActive()) {
    //         currentEntry.scene->update(deltaTime);
    //     }
    // }
}

void SceneManager::render() {
    if (!m_sceneStack.empty()) {
        auto& currentEntry = m_sceneStack.top();
        if (!currentEntry.isPaused) {
            currentEntry.scene->render();
        }
    }
    // if (m_pendingTransition) {
    //     processTransition();
    // } else if (!m_sceneStack.empty()) {
    //     auto& currentEntry = m_sceneStack.top();
    //     if (currentEntry.scene->isActive()) {
    //         currentEntry.scene->render();
    //     }
    // }
}

Scene* SceneManager::getCurrentScene() const {
    if (!m_sceneStack.empty()) {
        return m_sceneStack.top().scene.get();
    }
    return nullptr;
}



std::unique_ptr<Scene> SceneManager::createScene(const std::string& name) {
    return SceneFactoryManager::getInstance().createScene(name);
}

// void SceneManager::processTransition() {
//     if (m_isChangeScene) {
//         // Replace current scene
//         if (!m_sceneStack.empty()) {
//             auto& currentEntry = m_sceneStack.top();
//             currentEntry.scene->onExit();
//             currentEntry.scene->cleanup();
//             currentEntry.scene->unloadResources();
//             m_sceneStack.pop();
//         }
//     } else {
//         // Push new scene, pause current one
//         if (!m_sceneStack.empty()) {
//             auto& currentEntry = m_sceneStack.top();
//             if (currentEntry.scene->isPausable()) {
//                 currentEntry.isPaused = true;
//                 currentEntry.scene->pause();
//             }
//         }
//     }
    
//     // Create new scene using factory
//     auto newScene = createScene(m_nextSceneName);
//     if (newScene) {
//         m_sceneStack.emplace(std::move(newScene), m_nextSceneName);
//         auto& newEntry = m_sceneStack.top();
//         newEntry.scene->loadResources();
//         newEntry.scene->init();
//         newEntry.scene->onEnter();
//     }
    
//     m_pendingTransition = false;
// }