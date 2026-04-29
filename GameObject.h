#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "raylib.h"

// Base class - the starting point for everything in our game
// Using virtual functions here because we need polymorphism for our project
class GameObject {
protected:
    float x, y;
    bool active;
public:
    GameObject(float startX, float startY) : x(startX), y(startY), active(true) {}
    virtual ~GameObject() {} 

    virtual void Update() = 0; 
    virtual void Draw(bool useTextures) const = 0; 

    void setInactive() { active = false; }
    bool isActive() const { return active; }
    float getX() const { return x; }
    float getY() const { return y; }
};

#endif