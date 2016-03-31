//
//  game.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__game__
#define __bb7k__game__

#include <stdio.h>
#include "player.h"
#include "controller.h"
#include "dice.h"
#include "rimcup.h"
#include "building.h"
#include <string>
#include <vector>
class RimCup;

class Building;
class Game{
private:
    const int players; // number of players
    
    Controller* controller;
    
    RimCup* cup;
    Player** player;
    Dice* dice;
    Building* buildings[40];
    
public:
    void init(Player* const, const int);
    Player* loopPlayer(const int)const;
    int getPlayerSum()const;
    Player* getPlayer(const int);
    Game(const int, Controller* const);
    ~Game();
    Building* getBuilding(const std::string)const;   // return NULL if the building is not found
    Player* getPlayer(std::string name);  // return  NULL if player not found
    bool isPair();
    int getSum();
    void roll();
    void testRoll(const int, const int);
    Player* createPlayer(const std:: string,const std::string);
    std::string die();
    Building* getBuilding(const int)const;
    bool giveCup(Player*);
    void destroyCup(const int);
    void auction(Player*,Building*);  // call auction in controller
    Controller* getController()const;
    void notify(Player*);
    void notify(Building*);
    void setPlayer(const int i, const int cup,const int money, const int status,const int pos);
    
    
};
#endif /* defined(__bb7k__game__) */
