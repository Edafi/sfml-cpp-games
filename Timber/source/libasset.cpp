#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <cstdio>
#include "libasset.hpp"

sf::Texture tex(COCONUT);
sf::Sprite spt(tex);

Asset::Asset(std::string png_path) : sprite{tex} {
    this->png_path = png_path;
    fprintf(stdout, "Path is: %s\n", png_path.c_str());
    loadTexture();
    makeSprite();
}

void Asset::loadTexture() {
    if(! this->texture.loadFromFile(this->png_path)) {
        fprintf(stderr, "Error: couldn't load texture, path: %s", this->png_path.c_str());
        exit(-1);
    }
    fprintf(stdout, "Loaded: %s\n", this->png_path.c_str());
}

void Asset::makeSprite() {
     this->sprite.setTexture(this->texture);
}

void Asset::setPos(float x, float y) {
    this->sprite.setPosition(sf::Vector2f{x, y});
}   

sf::Sprite *Asset::getSprite() {
    return &(this->sprite);
}
