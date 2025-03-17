#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <fstream>

#include "game.hpp"

namespace util {
    inline SDL_Texture* loadTexture(const char* filepath) {
        SDL_Texture* texture;
        texture = IMG_LoadTexture(Game::renderer, filepath);
        if (texture == NULL) {
            std::cout << "Could not load texture! Err: " << SDL_GetError() << std::endl;
        }
        return texture;
    }

    inline void destroyTexture(SDL_Texture* texture) {
        SDL_DestroyTexture(texture);
    }

    inline std::string loadMapString(int level) {
        std::string filepath = "assets/levels/level_" + std::to_string(level) + ".txt";
        std::ifstream file(filepath);
        std::string data;
        std::getline(file, data);

        return data;
    }
}