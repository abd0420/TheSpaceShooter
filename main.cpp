#include "Game.h"

// i hope this works :PP

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "TheSpaceShooter");
    InitAudioDevice();
    SetTargetFPS(60);
    
    {
        Game game;
        while (!WindowShouldClose()) {
            game.Update();
            game.Draw();
        }
    }s

    CloseAudioDevice();
    CloseWindow();
    return 0;
}