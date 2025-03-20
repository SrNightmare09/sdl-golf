#include <SDL2/SDL.h>
#include <string>

#include "tile.hpp"
#include "util.hpp"
#include "math.hpp"

using namespace util;

int Tile::tileSize = 32;

Tile::Tile(Vector2f pos, SDL_Texture* texture, char tag) : Entity(pos, texture), tag(tag) {}

void Tile::addTile(Tile* tile) {
    this->map.push_back(tile);
}

int Tile::getTileSize() {
    return this->tileSize;
}

char Tile::getTag() {
    return this->tag;
}
