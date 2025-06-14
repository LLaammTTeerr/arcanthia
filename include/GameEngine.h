#pragma once
#include <raylib.h>
#include <Scene.h>
#include <CameraController.h>
#include <SceneManager.h>
#include <ModelManager.h>
#include <cassert>

class GameEngine {
public:
  void run(void) {
    InitWindow(800, 600, "Game Engine Example");
    SetTargetFPS(60);

    SceneManager sceneManager;
    CameraController cameraController;
    ModelManager modelManager;

    while (!WindowShouldClose()) {
      cameraController.update();
      sceneManager.update();

      BeginDrawing();
      ClearBackground(RAYWHITE);
      BeginMode3D(cameraController.getCamera());

      sceneManager.render();
      DrawGrid(10, 1.0f);

      DrawModel(modelManager.getModel("grass"), (Vector3){ 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);

      EndMode3D();
      EndDrawing();
    }

    CloseWindow();
  }
};