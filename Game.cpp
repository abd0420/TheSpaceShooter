#include "Game.h"

float Meteor::baseSpeed = 10.5f;

Game::Game() : state(START), frames(0), useTextures(true) { // SET TO FALSE TO SHOW BASE RECTANGLES
    // Resource loading section
    bg = LoadTexture("pixelart_starfield.png");
    shipTex = LoadTexture("player.png");
    meteorTex = LoadTexture("debris - 3.png"); 
    heartTex = LoadTexture("heart_32x32.png"); 
    
    titleFont = LoadFontEx("madspixel.ttf", 64, 0, 250); 
    scoreFont = LoadFontEx("PixelStorm.ttf", 64, 0, 250); 
    
    player.setTexture(shipTex);
    bgY1 = 0.0f; bgY2 = -600.0f;

    music = LoadMusicStream("16_bit_space.ogg");
    laser = LoadSound("laser.ogg");
    boom = LoadSound("SE-Explosion3-F.ogg"); 
    shipHit = LoadSound("SE-Explosion3-B.ogg");
    gameOverSound = LoadSound("endscreen_exp.ogg"); 
    
    PlayMusicStream(music);
}

Game::~Game() {
    UnloadTexture(bg); UnloadTexture(shipTex); UnloadTexture(meteorTex); UnloadTexture(heartTex);
    UnloadFont(titleFont); UnloadFont(scoreFont);
    UnloadMusicStream(music); UnloadSound(laser); UnloadSound(boom);
    UnloadSound(shipHit); UnloadSound(gameOverSound);
}

void Game::Update() {
    UpdateMusicStream(music); 
    
    if (state != OVER) {
        float scrollSpeed = 10.0f; 
        bgY1 += scrollSpeed; bgY2 += scrollSpeed;
        if (bgY1 >= 600) bgY1 = bgY2 - 600;
        if (bgY2 >= 600) bgY2 = bgY1 - 600;
    }

    if (state == START && IsKeyPressed(KEY_ENTER)) state = PLAY;
    else if (state == OVER && IsKeyPressed(KEY_ENTER)) {
        state = PLAY; meteors.clear(); bullets.clear(); effects.clear(); player.reset(); 
        Meteor::resetDifficulty(); PlayMusicStream(music);
    }
    else if (state == PLAY) {
        player.Update();
        if (IsKeyPressed(KEY_SPACE)) {
            bullets.push_back(Bullet(player.getX(), player.getY() - 30));
            PlaySound(laser);
        }

        if (++frames >= 27) { 
            meteors.push_back(Meteor(GetRandomValue(30, 770), -60, (float)GetRandomValue(8, 14)/10.0f, meteorTex));
            frames = 0;
            if (scores.getScore() > 0 && scores.getScore() % 200 == 0) Meteor::increaseDifficulty();
        }

        for(size_t i = 0; i < bullets.size(); i++) bullets[i].Update();
        for(size_t i = 0; i < meteors.size(); i++) meteors[i].Update();
        for(size_t i = 0; i < effects.size(); i++) effects[i].Update();

        HandleCollisions();
        Cleanup();
    }
}

void Game::HandleCollisions() {
    for(size_t m = 0; m < meteors.size(); m++) {
        if (!meteors[m].isActive()) continue;

        if (CheckCollisionRecs(player.getRect(), meteors[m].getRect())) {
            meteors[m].setInactive(); 
            PlaySound(shipHit); 
            effects.push_back(Explosion(meteors[m].getX(), meteors[m].getY()));
            player.loseLife();
            if (player.getLives() <= 0) { 
                state = OVER; scores.finalize(); StopMusicStream(music); PlaySound(gameOverSound); 
            }
            continue;
        }
        
        for(size_t b = 0; b < bullets.size(); b++) {
            if (bullets[b].isActive() && CheckCollisionRecs(bullets[b].getRect(), meteors[m].getRect())) {
                bullets[b].setInactive(); meteors[m].setInactive(); 
                PlaySound(boom); 
                effects.push_back(Explosion(meteors[m].getX(), meteors[m].getY()));
                ++scores; break; 
            }
        }
    }
}

void Game::Cleanup() {
    for(size_t i = 0; i < bullets.size(); ) { if(!bullets[i].isActive()) bullets.erase(bullets.begin() + i); else i++; }
    for(size_t i = 0; i < meteors.size(); ) { if(!meteors[i].isActive()) meteors.erase(meteors.begin() + i); else i++; }
    for(size_t i = 0; i < effects.size(); ) { if(!effects[i].isActive()) effects.erase(effects.begin() + i); else i++; }
}

