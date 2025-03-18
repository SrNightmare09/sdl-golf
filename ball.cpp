#include <SDL2/SDL.h>
#include <iostream>

#include "ball.hpp"
#include "util.hpp"

using namespace util;

Ball::Ball(Vector2f pos, SDL_Texture* texture) : Entity(pos, texture) {}

Vector2f Ball::getVelocity() {
    return this->velocity;
}

void Ball::setVelocity(Vector2f velocity) {
    this->velocity = velocity;
}

void Ball::moveBall(Vector2f disp) {

    constexpr float force_mult = 0.5f;

    // indicate if dx, dy were positive or negative
    float iCap = util::getSign(disp.x);
    float jCap = util::getSign(disp.y);

    // velocity of ball in direction of the mouse pointer
    float xVelocity = force_mult * abs(disp.x) * iCap;
    float yVelocity = force_mult * abs(disp.y) * jCap;

    // ball movement is directly opposite to mouse pointer direction, therefore minus sign
    this->setVelocity(Vector2f(-xVelocity, -yVelocity));
}

void Ball::updatePos(Vector2f windowDim) {

    constexpr float friction = 0.05f;

    float winWidth = windowDim.x;
    float winHeight = windowDim.y;

    // move the ball
    this->setPos(Vector2f(this->getPos().x + this->getVelocity().x, this->getPos().y + this->getVelocity().y));

    if (this->getPos().x <= 0 || this->getPos().x + this->ballSize >= winWidth) {
        this->setVelocity(Vector2f(this->getVelocity().x * -1, this->getVelocity().y));
    }
    if (this->getPos().y <= 0 || this->getPos().y + this->ballSize >= winHeight) {
        this->setVelocity(Vector2f(this->getVelocity().x, this->getVelocity().y * -1));
    }

    // calculate new velocity after friction
    float newXVel = this->getVelocity().x * (1.0f - friction);
    float newYVel = this->getVelocity().y * (1.0f - friction);
    this->setVelocity(Vector2f(newXVel, newYVel));

    // if the ball velocity is too slow, stop the ball
    if (abs(this->getVelocity().x) <= 0.01f) {
        this->setVelocity(Vector2f(0.0f, this->getVelocity().y));
    }
    if (abs(this->getVelocity().y) <= 0.01f) {
        this->setVelocity(Vector2f(this->getVelocity().x, 0.0f));
    }

}
