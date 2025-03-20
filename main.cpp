#include <stdio.h>
#include <SDL2/SDL.h>

#include "game.hpp"
#include "tile.hpp"
#include "util.hpp"
#include "ball.hpp"
#include "math.hpp"

using namespace util;

int main(int argc, char* args[]) {

    constexpr float windowWidth = 640.0f;
    constexpr float windowHeight = 640.0f;

    Game game;
    game.init("Golf!", windowWidth, windowHeight);

#pragma region texture loading and tiles

    // load all textures
    SDL_Texture* grassTexture = util::loadTexture("assets/sprites/grass.png");
    SDL_Texture* stoneTexture = util::loadTexture("assets/sprites/stone.png");
    SDL_Texture* wallTexture = util::loadTexture("assets/sprites/wall.png");
    SDL_Texture* holeTexture = util::loadTexture("assets/sprites/hole.png");
    SDL_Texture* ballTexture = util::loadTexture("assets/sprites/ball.png");

    // assign textures to objects
    Tile* grass = new Tile(Vector2f(), grassTexture, 'g');
    Tile* stone = new Tile(Vector2f(), stoneTexture, 's');
    Tile* wall = new Tile(Vector2f(), wallTexture, 'w');
    Tile* hole = new Tile(Vector2f(), holeTexture, 'h');
    Ball* ball = new Ball(Vector2f(160.0f, 160.0f), ballTexture, &game);

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

    game.initMap(1); // level 1

    while (running) {

        int startTicks = SDL_GetTicks();
        float newTime = SDL_GetTicks() * 0.001f;
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime) {
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    constexpr float limit = 50.0f; // force limiter

                    float mPosX = event.button.x;
                    float mPosY = event.button.y;

                    // calculate distance between ball and mouse pointer on x and y
                    float dx = mPosX - ball->getPos().x;
                    float dy = mPosY - ball->getPos().y;

                    // check if the distance between ball and mouse is within limit
                    dx = (abs(dx) > limit) ? limit * util::getSign(dx) : dx;
                    dy = (abs(dy) > limit) ? limit * util::getSign(dy) : dy;

                    ball->moveBall(Vector2f(dx, dy));
                    break;
                }
            }
            accumulator -= deltaTime;
        }

        const float alpha = accumulator / deltaTime;

        game.clear();

        game.showMap();

        ball->updatePos(Vector2f(windowWidth, windowHeight), deltaTime);

        game.render(*ball);

        game.display();

        int frameTicks = SDL_GetTicks() - startTicks;
        if (frameTicks < (1000 / game.getRefreshRate())) {
            SDL_Delay(1000 / (game.getRefreshRate() - frameTicks));
        }
    }

    game.close();
    return 0;
}
