#include <SDL2/SDL.h>
#include <iostream>
#include <string>

#include "game.hpp"
#include "entity.hpp"
#include "util.hpp"

using namespace util;

SDL_Window* Game::window = NULL;
SDL_Renderer* Game::renderer = NULL;

void Game::init(const char* title, int width, int height) {

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "Could not initialize SDL video! Err: " << SDL_GetError() << std::endl;
    }

    this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    if (this->window == NULL) {
        std::cout << "Could not initialize window! Err: " << SDL_GetError() << std::endl;
    }

    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
    if (this->renderer == NULL) {
        std::cout << "Could not initialize renderer! Err: " << SDL_GetError() << std::endl;
    }
}

void Game::clear() {
    SDL_RenderClear(this->renderer);
}

void Game::render(Entity &entity) {

    SDL_Rect source;

    source.x = 0;
    source.y = 0;

    int textureWidth;
    int textureHeight;
    SDL_QueryTexture(entity.getTexture(), NULL, NULL, &textureWidth, &textureHeight);

    source.w = textureWidth;
    source.h = textureHeight;

    SDL_Rect dest;
    dest.x = entity.getPos().x;
    dest.y = entity.getPos().y;
    dest.w = textureWidth;
    dest.h = textureHeight;

    SDL_RenderCopy(this->renderer, entity.getTexture(), &source, &dest);

}

void Game::initMap(int level) {

    std::string data = util::loadMapString(level);

    int xPos = 0;
    int yPos = 0;
    int tileSize = Tile::tileSize;

    for (int i = 0; i < data.length(); i++) {
        if (data[i] == '/') {
            xPos = 0;
            yPos += tileSize;
            continue;
        }

        else if (isdigit(data[i])) {

            std::string num(1, data[i]);
            int freq = std::stoi(num);

            for (int j = 0; j < freq; j++) {

                // use the character from map string to get tile texture
                char tileCode = data[i + 1];
                SDL_Texture* texture = this->sprites[tileCode]->getTexture();
                Tile tile(Vector2f(xPos, yPos), texture);

                this->map.push_back(tile);

                xPos += tileSize;
            }
        }
    }
}

void Game::showMap() {
    for (Tile &t : this->map) {
        this->render(t);
    }
}

void Game::addSprite(char tag, Tile* tile){
    this->sprites.insert({tag, tile});
}

void Game::display() {
    SDL_RenderPresent(renderer);
}

void Game::close() {
    this->window = NULL;
    SDL_DestroyWindow(this->window);

    this->renderer = NULL;
    SDL_DestroyRenderer(this->renderer);

    SDL_Quit();
}

int Game::getRefreshRate() {
    int displayIndex = SDL_GetWindowDisplayIndex(this->window);

    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}
