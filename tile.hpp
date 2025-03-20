#pragma once

#include <vector>
#include <string>

#include "entity.hpp"
#include "math.hpp"

class Tile : public Entity {
public:
    Tile(Vector2f pos, SDL_Texture* texture, char tag);
    void addTile(Tile* tile);
    int getTileSize();
    char getTag();
    static int tileSize;
private:
    char tag;
    std::vector<Tile*> map;
    std::string mapString;
};
