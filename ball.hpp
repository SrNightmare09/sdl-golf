#pragma once

#include <SDL2/SDL.h>

#include "entity.hpp"
#include "game.hpp"
#include "math.hpp"

class Ball : public Entity {

public:
    float ballSize = 16.0f;
    Game* game;

    Ball(Vector2f pos, SDL_Texture* texture, Game* game);
    Vector2f getVelocity();
    void setVelocity(Vector2f velocity);
    void moveBall(Vector2f disp);
    void updatePos(Vector2f windowDim, float deltaTime);
private:
    Vector2f velocity;
};
