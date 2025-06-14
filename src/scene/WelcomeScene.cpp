#include "WelcomeScene.h"
#include "ResourceManager.h"
#include "ResourcePaths.h"

void WelcomeScene::init(void) {
    // Initialize welcome scene resources
    loadResources();
}

void WelcomeScene::update(float deltaTime) {
    // Update welcome scene logic
}

void WelcomeScene::render(void) {
    // Render welcome scene
    static Image welcomeImage = ResourceManager::getInstance().getImage(ResourcePaths::WELCOME_IMAGE);
    ImageResize(&welcomeImage, GetScreenWidth(), GetScreenHeight());

    static Texture2D welcomeTexture = LoadTextureFromImage(welcomeImage);
    if (welcomeTexture.id != 0) {
        DrawTexture(welcomeTexture, 0, 0, WHITE);
    } else {
        std::cerr << "Failed to load welcome image: " << ResourcePaths::WELCOME_IMAGE << std::endl;
    }
}

void WelcomeScene::cleanup(void) {
    // Cleanup welcome scene resources
}

bool WelcomeScene::isActive(void) const {
    return m_isActive;
}

const char* WelcomeScene::getName(void) const {
    return "WelcomeScene";
}

void WelcomeScene::onEnter(void) {
    m_isActive = true;
}

void WelcomeScene::onExit(void) {
    m_isActive = false;
}

void WelcomeScene::pause(void) {
    m_isPaused = true;
}

void WelcomeScene::resume(void) {
    m_isPaused = false;
}

bool WelcomeScene::shouldTransition(void) const {
    return false;
}

const std::string WelcomeScene::getNextScene(void) const {
    return "";
}

void WelcomeScene::loadResources(void) {
    // Load welcome scene resources
    ResourceManager::getInstance().preloadImage(ResourcePaths::WELCOME_IMAGE);
}

void WelcomeScene::unloadResources(void) {
    // Unload welcome scene resources
}