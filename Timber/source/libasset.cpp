#include <SFML/Graphics.hpp>
#include <string>
#include <stdio.h>
#include <cstdio>
#include "libasset.hpp"

#define COCONUT "../graphics/coconut.png"

Asset::Asset(std::string png_path = COCONUT) : sprite{texture} {
    this->png_path = png_path;
    fprintf(stdout, "Path is: %s\n", png_path.c_str());
    loadTexture();
    makeSprite();
}

Asset::Asset() : png_path{COCONUT}, sprite{texture} {
    fprintf(stdout, "Path is: %s\n", this->png_path.c_str());
    loadTexture();
    makeSprite();
}

void Asset::loadTexture() {
    if(! this->texture.loadFromFile(this->png_path)) {
        fprintf(stderr, "Error: couldn't load texture, path: %s", this->png_path.c_str());
        exit(-1);
    }
}

void Asset::makeSprite() {
    this->sprite.setTexture(this->texture);
}

void Asset::setPos(float x, float y) {
    this->sprite.setPosition(sf::Vector2f{x, y});
}   

sf::Sprite Asset::getSprite() {
    return sprite;
}

