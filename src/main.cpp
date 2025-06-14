#include <bits/stdc++.h>
#include "GameEngine.h"
#include <raylib.h>

int main() {
    // Initialize the game engine
    GameEngine& engine = GameEngine::getInstance();
    // engine.render();
    // Initialize raylib
    InitWindow(800, 600, "Game Engine Example");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        // Update the game engine
        engine.update();

        // Begin drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Render the game engine
        engine.render();

        EndDrawing();
    }

    // // Cleanup and close the window
    CloseWindow();
    return 0;
}