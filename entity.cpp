#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "entity.hpp"
#include "tile.hpp"
#include "math.hpp"

Entity::Entity(Vector2f pos, SDL_Texture* texture) {
    int tileSize = Tile::tileSize;

    this->pos = pos;
    this->texture = texture;

    this->rect.x = pos.x;
    this->rect.y = pos.y;
    this->rect.w = tileSize;
    this->rect.h = tileSize;
}

void Entity::setPos(Vector2f pos) {
    this->pos = pos;
}

Vector2f Entity::getPos() {
    return this->pos;
}

SDL_Rect Entity::getRect() {
    return this->rect;
}

SDL_Texture* Entity::getTexture() {
    return this->texture;
}
