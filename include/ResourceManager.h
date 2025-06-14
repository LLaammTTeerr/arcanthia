#pragma once
#include <raylib.h>
#include <iostream>
#include <string>
// singleton
class ResourceManager {
public:
  static ResourceManager& getInstance();

  void preloadTexture2D(std::string filename);
  // void preloadTexture3D(std::string filename);
  void preloadFont(std::string filename);
  void preloadImage(std::string filename);

  // void unloadTexture2D(std::string filename);
  // void unloadFont(std::string filename);
  // void unloadImage(std::string filename);

  Image getImage(std::string filename);
  Texture2D getTexture2D(std::string filename);
  Font getFont(std::string filename);

private:
  ResourceManager() = default;
  ~ResourceManager() = default;
  ResourceManager(const ResourceManager&) = delete;
  ResourceManager& operator=(const ResourceManager&) = delete;


  /// Mapping of paths to resources
  std::unordered_map<std::string, Font> Fonts;
  std::unordered_map<std::string, Texture2D> Texture2Ds;
  std::unordered_map<std::string, Image> Images;
  // std::unordered_map<std::string, Texture3D> Texture3Ds;
};