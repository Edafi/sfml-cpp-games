#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <cstdlib>
#include <filesystem>
#include <stdio.h>
#include <vector>
#include <math.h>

#define WINDOW_WITDH 1920
#define WINDOW_HEIGHT 1080
#define BEE_LEVEL 880
#define CLOUD_LEVEL 480

using namespace sf;

Sprite* textureToSprite(Texture *texture, const std::filesystem::path *texturePath, RenderWindow *window, float posx, float posy){
        if(! texture->loadFromFile(*texturePath)){
        printf( "Texture of %s is not loaded", texturePath->string().c_str());
        window->close();
        exit(0);
    }
    Sprite *sprite = new Sprite(*texture);
    sprite->setPosition({posx, posy});
    return sprite; 
}

void speedRandomizer(int *speedX, int *speedY, const int minSpeed, const int maxSpeed){
    *speedX = rand()%(maxSpeed - minSpeed) + minSpeed;
    *speedY = rand()%(maxSpeed - minSpeed) + minSpeed;
}
void positionRandomizer(int *posX, int *posY){
    *posX = rand()%WINDOW_WITDH;
    *posY = rand()%(BEE_LEVEL - CLOUD_LEVEL) + CLOUD_LEVEL;
}

void beeIdle(Sprite *bee, int *frame){
    if(*frame < 25){
        bee->setPosition({bee->getPosition().x, bee->getPosition().y + 1});
    }
    else if(*frame < 50){
        bee->setPosition({bee->getPosition().x, bee->getPosition().y - 1});
    }
    else if (*frame == 50){
        *frame = 0;
    }
}

bool beeMove(Sprite *bee, int beeSpeedX, int beeSpeedY, int posX, int posY, Time deltaTime){
    float speedPerFrameX = beeSpeedX * float(deltaTime.asMilliseconds());
    float speedPerFrameY = beeSpeedY * float(deltaTime.asMilliseconds());
    //Rotation of bee sprite and speed vector of bee movement
    if (posX < bee->getPosition().x){
        bee->setScale({-1.0f, 1.0f});
        speedPerFrameX *= -1;
    }
    if(posY < bee->getPosition().y){
        speedPerFrameY *=-1;
    }

    if(abs(posX - (bee->getPosition().x + speedPerFrameX)) < speedPerFrameX)
        bee->setPosition({float(posX), bee->getPosition().y});
    else
        bee->setPosition({bee->getPosition().x + speedPerFrameX, bee->getPosition().y});
    
    if(abs(posY - (bee->getPosition().y + speedPerFrameY)) < speedPerFrameY)
        bee->setPosition({bee->getPosition().x, float(posY)});
    else
        bee->setPosition({bee->getPosition().x, bee->getPosition().y + speedPerFrameY});

    if(bee->getPosition().x == posX && bee->getPosition().y == posY)
        return true;
    else
        return false;
}

int main()
{
    int frame = 0;
    Clock clock;
    RenderWindow window(VideoMode({WINDOW_WITDH, WINDOW_HEIGHT}), "SFML works!", State::Fullscreen);
    std::vector<Sprite*> sprites;
    
    std::filesystem::path texturePath = "../graphics/background.png";
    Texture backgroundTexture;
    const uint backgroundX = 0, backgroundY = 0; 
    Sprite *backgroundSprite = textureToSprite(&backgroundTexture, &texturePath, &window, backgroundX, backgroundY);
    sprites.push_back(backgroundSprite);

    texturePath = "../graphics/tree.png";
    Texture treeTexture;
    const uint treeX = (WINDOW_WITDH * 1.0f)/2 - 150, treeY = 0; 
    Sprite *treeSprite = textureToSprite(&treeTexture, &texturePath, &window, treeX, treeY);
    sprites.push_back(treeSprite);

    texturePath = "../graphics/cloud.png";
    Texture cloudTexture;
    int cloudX = 750.0f, cloudY = 50.0f;
    Sprite *cloudSprite = textureToSprite(&cloudTexture, &texturePath, &window, cloudX, cloudY);
    sprites.push_back(cloudSprite);

    texturePath = "../graphics/bee.png";
    Texture beeTexture;
    int beeX, beeY, beeSpeedX, beeSpeedY;
    bool beeOnSpot = false;
    const int beeMinSpeed = 10, beeMaxSpeed = 50;
    srand(int(time(0)));
    speedRandomizer(&beeSpeedX, &beeSpeedY, beeMinSpeed, beeMaxSpeed);
    positionRandomizer(&beeX, &beeY);

    int destinationX, destinationY;
    positionRandomizer(&destinationX, &destinationY);

    Sprite *beeSprite = textureToSprite(&beeTexture, &texturePath, &window, beeX, beeY);
    sprites.push_back(beeSprite);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()){
            if (Keyboard::isKeyPressed(Keyboard::Key::Escape)){
                window.close();
            }
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        Time deltaTime = clock.reset();
        if (beeMove(beeSprite, beeSpeedX, beeSpeedY, destinationX, destinationY, deltaTime)){
            positionRandomizer(&destinationX, &destinationY);
            speedRandomizer(&beeSpeedX, &beeSpeedY, beeMinSpeed, beeMaxSpeed);
        }
        window.clear();
        for(Sprite *sprite : sprites){
            window.draw(*sprite);
        }
        window.display();
    }
    for(Sprite *sprite : sprites){
            delete sprite;
        }
}