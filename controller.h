
#ifndef __bb7k__controller__
#define __bb7k__controller__

#include <stdio.h>
#include "game.h"
#include <iostream>
#include "textdisplay.h"
#include "building.h"

class Game;
class View;
class Player;

class TextDisplay;
class Controller{
private:
    TextDisplay* td;
    Game *game;
public:
    Controller();
    ~Controller();
    void play(const int);
    void save(std::string s,Player*);
    bool load(const std::string);
    void notify(std::string);
    int auction(Player*, Building*);
    int tuition(Player* p);
    bool trade(Player*, std::string);
    bool improve(Player*, std::string);
    bool mortgage(Player*, std::string);
    bool unmortgage(Player*, std::string);
    bool bankrupt(Player*, Player*);
    int prisonBreak(Player*, const int);
    Player* winner();
    int payDebt(Player*,Player*, const int);
    bool rareCup();
    int init();
    void notify(Player*);
    void notify(Building*);
    
    
};

#endif /* defined(__bb7k__controller__) */
