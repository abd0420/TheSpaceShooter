#ifndef GAME_H
#define GAME_H

#include <vector>
#include "Entities.h"
#include "ScoreManager.h"

enum GameState { START, PLAY, OVER };

class Game {
private:
    bool useTextures; 

    RenderTexture2D target;
    Texture2D bg, shipTex, meteorTex, heartTex;
    Font titleFont, scoreFont; 
    Music music;
    Sound laser, boom, shipHit, gameOverSound;
    
    float bgY1, bgY2;
    int frames;
    
    Spaceship player;
    ScoreManager scores;
    std::vector<Bullet> bullets;
    std::vector<Meteor> meteors;
    std::vector<Explosion> effects;
    GameState state;

public:
    Game();
    ~Game();
    void Update();
    void Draw();
    void HandleCollisions();
    void Cleanup();
    void DrawCenteredText(Font fontToUse, const char* text, float y, float fontSize, Color color);
};

#endif