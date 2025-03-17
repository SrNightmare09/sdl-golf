#include <SDL2/SDL.h>

#include "ball.hpp"

Ball::Ball(Vector2f pos, SDL_Texture* texture) : Entity(pos, texture) {}

Vector2f Ball::getVelocity() {
    return this->velocity;
}

void Ball::setVelocity(Vector2f velocity) {
    this->velocity = velocity;
}
