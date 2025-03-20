#include <SDL2/SDL.h>
#include <iostream>

#include "ball.hpp"
#include "util.hpp"
#include "math.hpp"

using namespace util;

Ball::Ball(Vector2f pos, SDL_Texture* texture, Game* game) : Entity(pos, texture), game(game) {}

Vector2f Ball::getVelocity() {
    return this->velocity;
}

void Ball::setVelocity(Vector2f velocity) {
    this->velocity = velocity;
}

void Ball::moveBall(Vector2f disp) {

    constexpr float force_mult = 0.25f;

    // indicate if dx, dy were positive or negative
    float iCap = util::getSign(disp.x);
    float jCap = util::getSign(disp.y);

    // velocity of ball in direction of the mouse pointer
    float xVelocity = force_mult * abs(disp.x) * iCap;
    float yVelocity = force_mult * abs(disp.y) * jCap;

    // ball movement is directly opposite to mouse pointer direction, therefore minus sign
    this->setVelocity(Vector2f(-xVelocity, -yVelocity));
}

void Ball::updatePos(Vector2f windowDim, float deltaTime) {
    constexpr float friction = 0.05f;
    constexpr float minVelocity = 0.01f;

    Vector2f predictedPos = Vector2f(this->getPos().x + this->getVelocity().x, this->getPos().y + this->getVelocity().y);

    for (Tile& t : game->map) {
        if (t.getTag() == 'g') {
            continue;
        }

        SDL_Rect ballRect = {
            static_cast<int>(predictedPos.x),
            static_cast<int>(predictedPos.y),
            static_cast<int>(ballSize),
            static_cast<int>(ballSize)
        };

        SDL_Rect tileRect = t.getRect();

        // obstacle collision
        if (SDL_HasIntersection(&ballRect, &tileRect)) {
            if (t.getTag() == 'w' || t.getTag() == 's') {

                // Calculate overlap on both axes
                float overlapX = std::min(ballRect.x + ballRect.w, tileRect.x + tileRect.w) - std::max(ballRect.x, tileRect.x);
                float overlapY = std::min(ballRect.y + ballRect.h, tileRect.y + tileRect.h) - std::max(ballRect.y, tileRect.y);

                // resolve based on the smaller overlap (indicating the side of impact)
                if (overlapX < overlapY) {
                    predictedPos.x = this->getPos().x;  // step back on X
                    this->setVelocity(Vector2f(-this->getVelocity().x * 0.5f, this->getVelocity().y));
                }
                else {
                    predictedPos.y = this->getPos().y;  // step back on Y
                    this->setVelocity(Vector2f(this->getVelocity().x, -this->getVelocity().y * 0.5f));
                }
            }

            // win condition
            else if (t.getTag() == 'h') {
                this->setVelocity(Vector2f(0.0f, 0.0f));
                std::cout << "hole" << std::endl;
                return;
            }
        }
    }

    this->setPos(predictedPos);

    // apply friction
    float newXVel = this->getVelocity().x * (1.0f - friction);
    float newYVel = this->getVelocity().y * (1.0f - friction);
    this->setVelocity(Vector2f(newXVel, newYVel));

    // if velocity is less than minVelocity in an axis, stop the ball in that axis
    if (abs(this->getVelocity().x) <= minVelocity) {
        this->setVelocity(Vector2f(0.0f, this->getVelocity().y));
    }
    if (abs(this->getVelocity().y) <= minVelocity) {
        this->setVelocity(Vector2f(this->getVelocity().x, 0.0f));
    }
}
