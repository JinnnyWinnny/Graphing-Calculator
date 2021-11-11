#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include <constants.h>
#include "../../!include/RPN/rpn.h"
#include "sidebar.h"


using namespace std;
class System
{
public:
    System();
    void Step(int command, string eqaution);
    int Size();
    void moveGraph(float x, float y);
    void resetGraph();
    void Draw(sf::RenderWindow& window, string equation, bool getInput);
    void drawGraph(sf::RenderWindow& window, string equation);
    double eval(Queue<Token*> postfix, double x);
    Queue<Token*> ShuntingYard(Queue<Token*> input);
    Queue<sf::Vector2f> getCoordinate( int numOfPts,Queue<Token*> postfix);
    Queue<sf::Vector2f> transform(Queue<sf::Vector2f> graphXY);
    Queue<Token*> strToQ(string input);
    void saveEquation(string equation);
    void drawXYaxis(sf::RenderWindow& window);

private:
    //    vector<Particle> system;
    sf::CircleShape shape;
    sf::CircleShape cir;
    sf::Vector2f vel;
    sf::Font font;
    sf::Text xmin;
    sf::Text xmax;
    sf::Text ymin;
    sf::Text ymax;
    sf::Text input;
    RPN rpn;
    double low;
    double high;
    double left;
    double right;
    float centerX;
    float centerY;
    double orgnlLow;
    double orgnlRight;
    double orgnlHigh;
    double orgnlLeft;
};

#endif // SYSTEM_H
