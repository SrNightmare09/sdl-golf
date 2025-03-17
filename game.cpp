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
    source.w = entity.getRect().w;
    source.h = entity.getRect().h;

    SDL_Rect dest;
    dest.x = entity.getPos().x;
    dest.y = entity.getPos().y;
    dest.w = entity.getRect().w;
    dest.h = entity.getRect().h;

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

            std::cout << std::endl;
            continue;
        }

        else if (isdigit(data[i])) {

            std::string num(1, data[i]);
            int freq = std::stoi(num);

            for (int j = 0; j < freq; j++) {
                std::cout << data[i + 1] << " ";

                SDL_Texture* texture = this->sprites[data[i + 1]]->getTexture();
                Tile tile(Vector2f(xPos, yPos), texture);

                this->map.push_back(tile);

                SDL_DestroyTexture(texture);

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

void Game::addSprite(char tag, std::unique_ptr<Tile> tile){
    this->sprites.insert({tag, std::move(tile)});
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
