#pragma once
#include <raylib.h>

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