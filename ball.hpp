#pragma once

#include <SDL2/SDL.h>

#include "entity.hpp"

class Ball : public Entity {

public:
    Ball(Vector2f pos, SDL_Texture* texture);
    Vector2f getVelocity();
    void setVelocity(Vector2f velocity);
private:
    Vector2f velocity;
};
