#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "math.hpp"

class Entity {

public:
    Entity(Vector2f pos, SDL_Texture* texture);
    void setPos(Vector2f pos);
    Vector2f getPos();
    SDL_Rect getRect();
    SDL_Texture* getTexture();
private:
    Vector2f pos;
    SDL_Texture* texture;
    SDL_Rect rect;
};
