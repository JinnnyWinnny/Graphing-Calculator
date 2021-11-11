#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
    void newMenu(string equation);

private:
    sf::RectangleShape reset;
    sf::RectangleShape deleteHistory;
    sf::RectangleShape menu[numOfMenus+1];
    sf::RenderWindow window;
    sf::RectangleShape xmin;
    sf::RectangleShape xmax;
    sf::RectangleShape ymin;
    sf::RectangleShape ymax;

    string equation;
    Sidebar sidebar;
    System system;
    int command;
    float mouseClickedX;
    float mouseClickedY;
    sf::Font font;
    sf::Text myTextLabel;
    bool mouseIn;
    bool getInput;
};


#endif // GAME_H
