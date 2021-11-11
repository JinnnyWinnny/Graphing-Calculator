#include "system.h"
#include "random.h"
#include "animate.h"
#include "sidebar.h"
#include <sstream>
#include <math.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <constants.h>
#include <string>

using namespace std;

System::System()
{
    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Graph() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    orgnlHigh = 10;
    orgnlLeft = -10;
    orgnlRight = 10;
    orgnlLow = -10;
    low = orgnlLow;
    high = orgnlHigh;
    left = orgnlLeft;
    right = orgnlRight;
    centerX = WORK_PANEL/2;
    centerY = SCREEN_HEIGHT/2;
    cout<<"Graph CTOR Exit"<<endl;
}
void System::moveGraph(float x, float y){
    centerX += x;
    centerY += y;

    float gDx = (x*(right-left))/WORK_PANEL;
    cout<<"graph dx: "<<gDx<<endl;
    left-=gDx;
    right-=gDx;

    float gDy = (y*(high-low))/WORK_PANEL;
    high+=gDy;
    low+=gDy;
}
void System::resetGraph(){
    low = orgnlLow;
    high = orgnlHigh;
    left = orgnlLeft;
    right = orgnlRight;
    centerX = WORK_PANEL/2;
    centerY = SCREEN_HEIGHT/2;
}
void System::Step(int command, string equation){
    //zooming in
    if(command == 1){
        low = low/1.5;
        high = high/1.5;
        left = left/1.5;
        right = right/1.5;
    }
    //zooming out
    else if(command == 2){
        low = low*1.5;
        high = high*1.5;
        left = left*1.5;
        right = right*1.5;
    }
}
void System::drawXYaxis(sf::RenderWindow& window){

    //drawing xaxis and yaxis
    sf::VertexArray xaxis(sf::LineStrip,2);
    sf::VertexArray yaxis(sf::LineStrip,2);

    xaxis[0].position = sf::Vector2f(0,centerY);
    xaxis[1].position = sf::Vector2f(WORK_PANEL,centerY);

    yaxis[0].position = sf::Vector2f(centerX,0);
    yaxis[1].position = sf::Vector2f(centerX,SCREEN_HEIGHT);

    window.draw(xaxis);
    window.draw(yaxis);

    //show xmin, xmax, ymin, ymax on the screen
    xmin.setFont(font);
    xmin.setString(to_string(left).substr(0,6));
    xmin.setCharacterSize(24);
    xmin.setFillColor(sf::Color::White);
    xmin.setPosition(sf::Vector2f(10,SCREEN_HEIGHT/2));
    //xmax
    xmax.setFont(font);
    xmax.setString(to_string(right).substr(0,5));
    xmax.setCharacterSize(24);
    xmax.setFillColor(sf::Color::White);
    xmax.setPosition(sf::Vector2f(WORK_PANEL-60,SCREEN_HEIGHT/2-30));
    //ymin
    ymin.setFont(font);
    ymin.setString(to_string(low).substr(0,6));
    ymin.setCharacterSize(24);
    ymin.setFillColor(sf::Color::White);
    ymin.setPosition(sf::Vector2f(WORK_PANEL/2-30,SCREEN_HEIGHT-30));
    //ymax
    ymax.setFont(font);
    ymax.setString(to_string(high).substr(0,5));
    ymax.setCharacterSize(24);
    ymax.setFillColor(sf::Color::White);
    ymax.setPosition(sf::Vector2f(WORK_PANEL/2-30,10));

    window.draw(xmin);
    window.draw(xmax);
    window.draw(ymin);
    window.draw(ymax);
}
void System::drawGraph(sf::RenderWindow& window, string equation){
    drawXYaxis(window);
    Queue<Token*> output;
    output = rpn.ShuntingYard(rpn.strToQ(equation));
    Queue<sf::Vector2f> coordinatesQ = getCoordinate(1000,output);
    while(!coordinatesQ.empty()){
        cir.setRadius(1);
        cir.setFillColor(sf::Color::Yellow);
        cir.setPosition(coordinatesQ.pop());
        window.draw(cir);
    }
}
Queue<sf::Vector2f> System:: getCoordinate(int numOfPts, Queue<Token*> postfix){
    Queue<sf::Vector2f> coordinateQ;
    double gap = (right - left)/numOfPts;
    float result;
    //get y with x
    for(double i = left; i<=right; i+=gap){
        result = rpn.eval(postfix,i);
        coordinateQ.push(sf::Vector2f(i,result));
    }
    Queue<sf::Vector2f> screenXYQ = transform(coordinateQ);
    return screenXYQ;
}
Queue<sf::Vector2f> System::transform(Queue<sf::Vector2f> graphXY){
    Queue<sf::Vector2f> screenXYQ;
    while(!graphXY.empty()){
        sf::Vector2f gXgY = graphXY.pop();
        sf::Vector2f sXsY;
        sXsY.x = ((WORK_PANEL/(right-left))*gXgY.x)+centerX;
        sXsY.y = (-1)*((SCREEN_HEIGHT/(high-low))*gXgY.y)+centerY;
        screenXYQ.push(sXsY);
    }
    return screenXYQ;
}
void System::Draw(sf::RenderWindow& window, string equation, bool getInput){
    if(!getInput){
        window.clear();
        drawGraph(window,equation);
    }
    input = sf::Text(equation,font);
    input.setFillColor(sf::Color::Yellow);
    input.setCharacterSize(50);
    input.setPosition(100,100);
    window.draw(input);
}
