#pragma once

#include <vector>
#include <string>

#include "entity.hpp"

class Tile : public Entity {
public:
    Tile(Vector2f pos, SDL_Texture* texture);
    void addTile(Tile* tile);
    int getTileSize();
    static int tileSize;
private:
    std::vector<Tile*> map;
    std::string mapString;
};
