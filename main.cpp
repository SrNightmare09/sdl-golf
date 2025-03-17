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

    auto grass= std::make_unique<Tile>(Vector2f(0.0f, 0.0f), grassTexture);
    auto stone = std::make_unique<Tile>(Vector2f(0.0f, 0.0f), stoneTexture);
    auto wall = std::make_unique<Tile>(Vector2f(0.0f, 0.0f), wallTexture);
    auto hole = std::make_unique<Tile>(Vector2f(0.0f, 0.0f), holeTexture);

    game.addSprite('g', std::move(grass));
    game.addSprite('s', std::move(stone));
    game.addSprite('w', std::move(wall));
    game.addSprite('h', std::move(hole));

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

        SDL_SetRenderDrawColor(Game::renderer, 36, 175, 64, 255);
        game.clear();

        // game.showMap();

        game.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < (1000 / game.getRefreshRate())) {
            SDL_Delay(1000 / (game.getRefreshRate() - frameTicks));
        }
    }

    game.close();
    return 0;
}
