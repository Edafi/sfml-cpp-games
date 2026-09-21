#ifndef ASSET_H
#define ASSET_H

#include <SFML/Graphics.hpp>
#include <string>

#define COCONUT "../graphics/background.png"

class Asset {
private:
    std::string png_path;
    sf::Texture texture;
    sf::Sprite sprite;
public:
    Asset(std::string png_path = COCONUT);
    void loadTexture();
    void makeSprite();
    void setPos(float, float);
    sf::Sprite *getSprite();
    void spriteDel();
};

#endif
