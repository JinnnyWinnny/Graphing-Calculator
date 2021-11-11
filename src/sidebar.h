#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include "constants.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    void read_file(char file_name[MAX_FN]);
    void saveEquation(string equation);
    void popIt();
    void deleteLast();


//    void set_item(int index, const string& s);
    string popItem();
    string at(int index);


private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text[20];         //used to draw strings on the window object
    sf::Text reset;
    sf::Text resetHistory;
    float _left;
    float _width;

    string equations[20];

};

#endif // SIDEBAR_H
