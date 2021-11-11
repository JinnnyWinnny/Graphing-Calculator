#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"


animate::animate():sidebar(WORK_PANEL, SIDE_BAR)

{
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Grahp");
    system = System();
    window.setFramerateLimit(60);
    //set default
    mouseIn = false;
    getInput = false;
    equation = "x";
    cout<<"Geme CTOR. preparing to load the font."<<endl;
    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    //make a reset rectangle
    reset.setSize(sf::Vector2f(MENU_X,MENU_Y));
    reset.setPosition(sf::Vector2f(WORK_PANEL+20 ,MENU_Y));
    reset.setOutlineThickness(2.0);
    //make a deleteHistory rectangle
    deleteHistory.setSize(sf::Vector2f(MENU_X,MENU_Y));
    deleteHistory.setPosition(sf::Vector2f(WORK_PANEL+20 ,150 + numOfMenus*MENU_Y));
    deleteHistory.setOutlineThickness(2.0);
    //make menu rectangles
    for(int i = 0; i<numOfMenus; i++){
        menu[i].setSize(sf::Vector2f(MENU_X,MENU_Y));
        menu[i].setPosition(sf::Vector2f(WORK_PANEL+20 ,150 + (i*MENU_Y)));
        menu[i].setOutlineThickness(2.0);
        menu[i].setOutlineColor(sf::Color::Red);
        menu[i].setFillColor(sf::Color::Transparent);
    }
    cout<<"animate instantiated successfully."<<endl;
}
void animate::update(){
    //cause changes to the data for the next frame
    system.Step(command,equation);
    command = 0;
}
void animate::render(){
    window.clear();
    Draw();
    window.display();
}
void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event))//or waitEvent
    {
        switch (event.type)
        {
        // window closed
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::TextEntered:
            if(getInput){
                if(event.text.unicode < 128){
                    cout<<"text entered"<<endl;
                    if(event.text.unicode == '\b'){
                        if(equation.size() > 0){
                            equation.pop_back();
                        }
                    }
                    else{
                        equation += event.text.unicode;
                        cout<<equation<<endl;
                    }
                }
            }
            break;
        case sf::Event::KeyPressed:
            switch(event.key.code){
            //zoom in
            case sf::Keyboard::Up:
                command = 1;
                break;
                //zoom out
            case sf::Keyboard::Down:
                command = 2;
                break;
                //get a new equation
            case sf::Keyboard::E:
                getInput = true;
                window.pollEvent(event);
                break;
            case sf::Keyboard::Return:
                getInput = false;
                //if there is enough storage in menu
                if(sidebar.at(numOfMenus -1 ) == ""){
                    sidebar.saveEquation(equation);
                }
                break;
            case sf::Keyboard::Escape:
                window.close();
                break;
            }
            break;
        case sf::Event::MouseEntered:
            mouseIn = false;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;
        case sf::Event::MouseButtonPressed:
            //get a coordinate mouse clicked
            mouseClickedX = event.mouseButton.x;
            mouseClickedY = event.mouseButton.y;
            //if mouse pressed inside of workPanel
            if(mouseClickedX < WORK_PANEL){
                mouseIn = true;
            }
            break;
        case sf::Event::MouseMoved:
            if(mouseIn){
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                system.moveGraph((mouseX-mouseClickedX)/20,(mouseY-mouseClickedY)/20);
            }
            break;
        case sf::Event::MouseButtonReleased:
            mouseIn = false;
            mouseX = event.mouseButton.x;
            mouseY = event.mouseButton.y;
            //RESET menu
            if((sf::Mouse::getPosition(window).x > reset.getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (reset.getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > reset.getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (reset.getPosition().y)+MENU_Y))
            {
                system.resetGraph();
            }
            //first menu
            if((sf::Mouse::getPosition(window).x > menu[0].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[0].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[0].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[0].getPosition().y)+MENU_Y))
            {
                // if there is an element at each index
                if(sidebar.at(0) != ""){
                    equation = sidebar.at(0);
                }
            }
            //second menu
            if((sf::Mouse::getPosition(window).x > menu[1].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[1].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[1].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[1].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(1) != ""){
                    equation = sidebar.at(1);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[2].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[2].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[2].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[2].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(2) != ""){
                    equation = sidebar.at(2);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[3].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[3].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[3].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[3].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(3) != ""){
                    equation = sidebar.at(3);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[4].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[4].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[4].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[4].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(4) != ""){
                    equation = sidebar.at(4);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[5].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[5].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[5].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[5].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(5) != ""){
                    equation = sidebar.at(5);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[6].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[6].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[6].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[6].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(6) != ""){
                    equation = sidebar.at(6);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[7].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[7].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[7].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[7].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(7) != ""){
                    equation = sidebar.at(7);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[8].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[8].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[8].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[8].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(8) != ""){
                    equation = sidebar.at(8);
                    cout<<"equation: "<<equation<<endl;
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[9].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[9].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[9].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[9].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(9) != ""){
                    equation = sidebar.at(9);
                    cout<<"equation: "<<equation<<endl;
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[10].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[10].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[10].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[10].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(10) != ""){
                    equation = sidebar.at(10);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[10].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[10].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[10].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[10].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(11) != ""){
                    equation = sidebar.at(11);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[10].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[10].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[10].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[10].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(12) != ""){
                    equation = sidebar.at(12);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[10].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[10].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[10].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[10].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(13) != ""){
                    equation = sidebar.at(13);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[10].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[10].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[10].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[10].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(14) != ""){
                    equation = sidebar.at(14);
                }
            }
            if((sf::Mouse::getPosition(window).x > menu[10].getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (menu[10].getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > menu[10].getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (menu[10].getPosition().y)+MENU_Y))
            {
                if(sidebar.at(15) != ""){
                    equation = sidebar.at(15);
                }
            }
            if((sf::Mouse::getPosition(window).x > deleteHistory.getPosition().x) &&
                    (sf::Mouse::getPosition(window).x < (deleteHistory.getPosition().x)+MENU_X) &&
                    (sf::Mouse::getPosition(window).y > deleteHistory.getPosition().y) &&
                    (sf::Mouse::getPosition(window).y < (deleteHistory.getPosition().y)+MENU_Y))
            {
                //delete the last one
                sidebar.deleteLast();
            }
            break;
        default:
            break;
        }
    }
}
void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); //clear/draw/display
    }
    cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}
void animate::Draw(){
    try {
        system.Draw(window,equation,getInput);
    } catch (InputExceptions ex) {
        cout<<"ERROR"<<endl;
    }
    sidebar.draw(window);
    for(int i = 0; i<numOfMenus; i++){
        window.draw(menu[i]);
    }
}

