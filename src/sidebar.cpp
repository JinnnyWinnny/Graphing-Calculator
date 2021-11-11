#include "sidebar.h"
#include "constants.h"
#include <fstream>
#include "animate.h"

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
        items.reserve(50);
    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105,105,105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;
    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    cout<<"Sidebar CTOR: loaded font."<<endl;
    cout<<"Sidebar CTOR: Text object initialized."<<endl;
    //set reset text
    reset = sf::Text("RESET", font);
    reset.setFont(font);
    reset.setCharacterSize(50);
    reset.setStyle(sf::Text::Bold);
    reset.setFillColor(sf::Color::White);
    reset.setPosition(sf::Vector2f(WORK_PANEL+20,MENU_Y));
    //set resetHistory text
    resetHistory = sf::Text("DELETE", font);
    resetHistory.setFont(font);
    resetHistory.setCharacterSize(50);
    resetHistory.setStyle(sf::Text::Bold);
    resetHistory.setFillColor(sf::Color::White);
    resetHistory.setPosition(sf::Vector2f(WORK_PANEL+20,150 + 15*MENU_Y));
    //get all the equations from text file
    read_file("equations.txt");
    cout<<"Sidebar: CTOR: Exit."<<endl;
}
void Sidebar::read_file(char file_name[MAX_FN]){
    ifstream inFile;

    //open a file
    inFile.open(file_name);

    //check for fail
    if(!inFile){
        cout<<endl<<"*** COULD NOT OPEN FILE FOR INPUT ***"<<endl<<endl;
        exit(1);
    }
    //read size
    string size = "";
    getline(inFile,size);
    //push each equations into items
    for(int i = 0; i<stoi(size); i++){
        string line = "";
        getline(inFile,line);
        items.push_back(line);
    }

    //close a file
    inFile.close();
}
void Sidebar::saveEquation(string equation){
    items.push_back(equation);

    //declare
    ofstream outFile;

    //open a file
    outFile.open("equations.txt");

    //test for fail
    if (outFile.fail()){
        cout<<endl<<"*** COULD NOT OPEN FILE FOR OUTPUT ***"<<endl<<endl;
        exit(1);
    }

    outFile<<items.size()<<endl;
    for(int i = 0; i<items.size(); i++){
        outFile<<items[i]<<endl;
    }

    //close a file
    outFile.close();
}
void Sidebar::deleteLast(){
    //if there is an item to pop back
    if(items.size() > 0){
        items.pop_back();
    }
    else{
        return;
    }

    //declare
    ofstream outFile;

    //open a file
    outFile.open("equations.txt");

    //test for fail
    if (outFile.fail()){
        cout<<endl<<"*** COULD NOT OPEN FILE FOR OUTPUT ***"<<endl<<endl;
        exit(1);
    }

    outFile<<items.size()<<endl;
    for(int i = 0; i<items.size(); i++){
        outFile<<items[i]<<endl;
    }

    //close a file
    outFile.close();
    cout<<"end of saveEquation"<<endl;

}
string Sidebar::at (int index){
    //return item at index
    if(index < items.size()){
        return items[index];
    }
    return "";
}
void Sidebar::draw(sf::RenderWindow& window){
    window.draw(rect);
    window.draw(reset);
    window.draw(resetHistory);
    for(int i= 0; i<items.size(); i++){
        sb_text[i] = sf::Text(items[i], font);
        sb_text[i].setFont(font);
        sb_text[i].setCharacterSize(50);
        sb_text[i].setStyle(sf::Text::Bold);
        sb_text[i].setFillColor(sf::Color::Yellow);
        sb_text[i].setPosition(sf::Vector2f(WORK_PANEL+20,150+(i*MENU_Y)));
        window.draw(sb_text[i]);
    }
}













