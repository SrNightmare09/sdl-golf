#include <SDL2/SDL.h>
#include <iostream>

#include "ball.hpp"

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
    this->dir.x = (disp.x > 0) ? 1 : -1;
    this->dir.y = (disp.y > 0) ? 1 : -1;

    this->velocity.x = abs(force_mult * this->dir.x);
    this->velocity.y = abs(force_mult * this->velocity.y);

    std::cout << disp.x << " : " << disp.y << std::endl;
    std::cout << this->getVelocity().x << " : " << this->getVelocity().y << std::endl;

}

void Ball::updatePos(Vector2f windowDim) {

    // std::cout << "hello" << std::endl;

    constexpr float friction = 0.1f;

    float xPos = this->getPos().x;
    float yPos = this->getPos().y;
    float xVel = this->getVelocity().x;
    float yVel = this->getVelocity().y;

    if (this->dir.x == 1) {
        this->setPos(Vector2f(xPos - xVel, yVel));
    }
    else {
        this->setPos(Vector2f(xPos + xVel, yVel));
    }
    if (this->dir.y == 1) {
        this->setPos(Vector2f(xPos, yPos - yVel));
    }
    else {
        this->setPos(Vector2f(xPos, yPos + yVel));
    }


    if (xPos + this->ballSize >= windowDim.x) {
        this->setVelocity(Vector2f(-xVel, yVel));
        this->setPos(Vector2f(xPos - this->ballSize, yPos));
    }
    else if (xPos - this->ballSize <= 0) {
        this->setVelocity(Vector2f(-xVel, yVel));
        this->setPos(Vector2f(xPos + this->ballSize, yPos));
    }

    if (yPos + this->ballSize >= windowDim.y) {
        this->setVelocity(Vector2f(xVel, -yVel));
        this->setPos(Vector2f(xPos, yPos - this->ballSize));
    }
    else if (yPos - this->ballSize <= 0) {
        this->setVelocity(Vector2f(xVel, -yVel));
        this->setPos(Vector2f(xPos, yPos + this->ballSize));
    }

    this->setPos(Vector2f(xPos * (1.0f - friction), yPos));
    this->setPos(Vector2f(yPos, xPos * (1.0f - friction)));

    if (abs(xVel) <= 1.0f) {
        this->setVelocity(Vector2f(0.0f, yVel));
    }

    if (abs(xVel) <= 1.0f) {
        this->setVelocity(Vector2f(xVel, 0.0f));
    }

}
