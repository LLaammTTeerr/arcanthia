#include "ResourceManager.h"

ResourceManager& ResourceManager::getInstance() {
  static ResourceManager* instance = nullptr;
  static std::mutex mutex;
  if (instance == nullptr) {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
      instance = new ResourceManager();
    }
  }
  return *instance;
}

void ResourceManager::preloadTexture2D(std::string filename) {
  auto it = Texture2Ds.find(filename);
  if (it != Texture2Ds.end()) {
    std::cerr << "Texture already loaded: " << filename << std::endl;
    return;
  }

  Texture2D texture = LoadTexture(filename.c_str());
  if (texture.id == 0) {
    std::cerr << "Failed to load texture: " << filename << std::endl;
    return;
  }
  Texture2Ds[filename] = texture;
}

Texture2D ResourceManager::getTexture2D(std::string filename) {
  preloadTexture2D(filename);
  auto it = Texture2Ds.find(filename);
  if (it != Texture2Ds.end()) {
    return it->second;
  } else {
    std::cerr << "Texture not found: " << filename << std::endl;
    return Texture(); // Return an empty texture
  }
}


void ResourceManager::preloadFont(std::string filename) {
  auto it = Fonts.find(filename);
  if (it != Fonts.end()) {
    std::cerr << "Font already loaded: " << filename << std::endl;
    return;
  }

  Font font = LoadFont(filename.c_str());
  if (font.baseSize == 0) {
    std::cerr << "Failed to load font: " << filename << std::endl;
    return;
  }
  Fonts[filename] = font;
}

Font ResourceManager::getFont(std::string filename) {
  preloadFont(filename);
  auto it = Fonts.find(filename);
  if (it != Fonts.end()) {
    return it->second;
  } else {
    std::cerr << "Font not found: " << filename << std::endl;
    return Font(); // Return an empty font
  }
}

void ResourceManager::preloadImage(std::string filename) {
  auto it = Images.find(filename);
  if (it != Images.end()) {
    std::cerr << "Image already loaded: " << filename << std::endl;
    return;
  }

  Image image = LoadImage(filename.c_str());
  if (image.data == nullptr) {
    std::cerr << "Failed to load image: " << filename << std::endl;
    return;
  }
  Images[filename] = image;
}

Image ResourceManager::getImage(std::string filename) {
  preloadImage(filename);
  auto it = Images.find(filename);
  if (it != Images.end()) {
    return it->second;
  } else {
    std::cerr << "Image not found: " << filename << std::endl;
    return Image(); // Return an empty image
  }
}