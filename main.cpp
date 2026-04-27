#include "Game.h"

// i hope this works :PP

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "TheSpaceShooter");
    InitAudioDevice();
    SetTargetFPS(60);
    
    {
        Game game;
        while (!WindowShouldClose()) {
            game.Update();
            game.Draw();
        }
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}