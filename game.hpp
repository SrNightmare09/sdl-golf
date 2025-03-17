#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "entity.hpp"
#include "tile.hpp"

class Game {
public:
    static SDL_Window* window;
    static SDL_Renderer* renderer;

    std::vector<Tile> map;

    ~Game() = default;
    void init(const char* title, int width, int height);
    void clear();
    void close();
    void addSprite(char tag, Tile* tile);
    void initMap(int level);
    void showMap();
    void render(Entity& entity);
    void display();
    int getRefreshRate();

private:
    std::unordered_map<char, Tile*> sprites;
};
