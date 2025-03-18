#pragma once

#include <SDL2/SDL.h>

#include "entity.hpp"

class Ball : public Entity {

public:
    float ballSize = 16.0f;

    Ball(Vector2f pos, SDL_Texture* texture);
    Vector2f getVelocity();
    void setVelocity(Vector2f velocity);
    void moveBall(Vector2f disp);
    void updatePos(Vector2f windowDim);
private:
    Vector2f velocity;
};
