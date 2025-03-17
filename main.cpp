#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.hpp"
#include "tile.hpp"
#include "util.hpp"

using namespace util;

int main(int argc, char* args[]) {

    Game game;
    game.init("Golf!", 640, 640);

#pragma region texture loading and tile

    // load all textures
    SDL_Texture* grassTexture = util::loadTexture("assets/sprites/grass.png"); // 0
    SDL_Texture* stoneTexture = util::loadTexture("assets/sprites/stone.png"); // 1
    SDL_Texture* wallTexture = util::loadTexture("assets/sprites/wall.png"); // 2
    SDL_Texture* holeTexture = util::loadTexture("assets/sprites/hole.png"); // 3

    Tile* grass= new Tile(Vector2f(), grassTexture);
    Tile* stone = new Tile(Vector2f(), stoneTexture);
    Tile* wall = new Tile(Vector2f(), wallTexture);
    Tile* hole = new Tile(Vector2f(), holeTexture);

    game.addSprite('g', grass);
    game.addSprite('s', stone);
    game.addSprite('w', wall);
    game.addSprite('h', hole);

#pragma endregion

    bool running = true;
    SDL_Event event;

    const float deltaTime = 0.01f;
    float accumulator = 0.0f;
    float currentTime = SDL_GetTicks() * 0.001f;

    game.initMap(1);

    while (running) {

        int startTicks = SDL_GetTicks();
        float newTime = SDL_GetTicks() * 0.001f;
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_QUIT) {
                    running = false;

                }
            }
            accumulator -= deltaTime;
        }

        const float alpha = accumulator / deltaTime;
        
        game.clear();

        game.showMap();

        game.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < (1000 / game.getRefreshRate())) {
            SDL_Delay(1000 / (game.getRefreshRate() - frameTicks));
        }
    }

    game.close();
    return 0;
}
