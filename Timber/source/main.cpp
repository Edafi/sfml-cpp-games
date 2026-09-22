#include <SFML/Graphics.hpp>
#include "libasset.hpp"
using namespace sf;

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
int main() {
    VideoMode vm(Vector2u{WINDOW_WIDTH, WINDOW_HEIGHT});
    RenderWindow window(vm, "Timber!", State::Fullscreen);
    Asset background;
    background.setPos(0, 0);
    Asset coconut("../graphics/coconut.png");
    coconut.setPos(100, 100);
    coconut.getSprite()->setScale(sf::Vector2f{0.5, 0.5});
    //Texture tex("../graphics/coconut.png");
    //Sprite sprite(tex);
    //sprite.setPosition(Vector2f{0, 0});

    while (window.isOpen()) {
        // USER INPUT HERE
        // |    |   |   |
        // V    V   V   V
        if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
            window.close();
        
        coconut.moveSprite(1, 1);
        /*
         *  UPDATING ALL OBJECTS
         */ 
        
        /*
         *  RENDERING ON SCREEN
         */

        //  Cleaning screen from previous frame
        window.clear();
        //  Rendering 
        window.draw(*(background.getSprite()));
        window.draw(*(coconut.getSprite()));
        window.display();
    }
    //delete(background);
    return 0;
}
