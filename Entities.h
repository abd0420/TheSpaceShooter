#ifndef ENTITIES_H
#define ENTITIES_H

#include "GameObject.h"
#include "Constants.h"

//PLAYER CLASS
class Spaceship : public GameObject {
private:
    int lives;
    float speed;
    Texture2D texture;
    float scale;
public:
    Spaceship() : GameObject(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 80.0f), 
                  lives(3), speed(14.2f), scale(1.2f) {} 
                  
    void setTexture(Texture2D tex) { texture = tex; }
    
    void Update() {
        if (IsKeyDown(KEY_RIGHT) && (x + (texture.width * scale) / 2) < SCREEN_WIDTH) x += speed;
        if (IsKeyDown(KEY_LEFT) && (x - (texture.width * scale) / 2) > 0) x -= speed;
    }
    
    void Draw(bool useTextures) const {
        if (useTextures) {
            DrawTextureEx(texture, Vector2{x - (texture.width * scale) / 2, y - (texture.height * scale) / 2}, 0.0f, scale, WHITE);
        } else {
            // Normal rectangle version for the baseline logic demo
            DrawRectangle(x - 20, y - 20, 40, 40, BLUE);
        }
    }
    
    Rectangle getRect() const { //hitbox
        float hbW = (texture.width * scale) * 0.45f;
        float hbH = (texture.height * scale) * 0.50f;
        return { x - hbW / 2.0f, y - hbH / 2.0f, hbW, hbH }; 
    }
    
    void loseLife() { lives--; }
    void reset() { x = SCREEN_WIDTH / 2.0f; lives = 3; }
    int getLives() const { return lives; }
};
class Meteor : public GameObject {
private:
    static float baseSpeed; 
    float speedMultiplier;
    Texture2D texture;
    float scale;
public:
    Meteor(float startX, float startY, float multiplier, Texture2D tex) 
        : GameObject(startX, startY), speedMultiplier(multiplier), texture(tex), scale(0.6f) {}
        
    static void increaseDifficulty() { baseSpeed += 1.0f; } 
    static void resetDifficulty() { baseSpeed = 10.5f; } 
    
    void Update() {
        y += baseSpeed * speedMultiplier;
        if (y > SCREEN_HEIGHT + 100) active = false;
    }
    
    void Draw(bool useTextures) const {
        if (useTextures) {
            DrawTextureEx(texture, Vector2{x - (texture.width * scale) / 2, y - (texture.height * scale) / 2}, 0.0f, scale, WHITE);
        } else {
            DrawCircle(x, y, 15, DARKGRAY);
        }
    }
    
    Rectangle getRect() const { 
        float hbSize = (texture.width * scale) * 0.50f;
        return { x - hbSize / 2.0f, y - hbSize / 2.0f, hbSize, hbSize }; 
    }
};

class Bullet : public GameObject {
public:
    Bullet(float startX, float startY) : GameObject(startX, startY) {}
    void Update() { y -= 14.0f; if (y < -20) active = false; }
    void Draw(bool useTextures) const { 
        // We can keep bullets as rectangles or use textures
        DrawRectangle(x - 2, y - 15, 4, 20, RED); 
    }
    Rectangle getRect() const { return { x - 2, y - 15, 4, 20 }; }
};

class Explosion : public GameObject {
private:
    float radius, alpha;
public:
    Explosion(float startX, float startY) : GameObject(startX, startY), radius(5.0f), alpha(1.0f) {}
    void Update() { radius += 3.0f; alpha -= 0.05f; if (alpha <= 0) active = false; }
    void Draw(bool useTextures) const { 
        if (useTextures) {
            DrawCircleV(Vector2{x, y}, radius, Fade(ORANGE, alpha)); 
            DrawCircleV(Vector2{x, y}, radius * 0.6f, Fade(GOLD, alpha)); 
        } else {
            DrawCircle(x, y, radius, Fade(YELLOW, alpha));
        }
    }
};

#endif