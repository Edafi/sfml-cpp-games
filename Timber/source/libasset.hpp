#ifndef ASSET_H
#define ASSET_H

#include <SFML/Graphics.hpp>
#include <string>

class Asset {
private:
    std::string png_path;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Asset(std::string);
    Asset();
    void loadTexture();
    void makeSprite();
    void setPos(float, float);
    sf::Sprite getSprite();
};

#endif
