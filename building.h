//
//  building.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__building__
#define __bb7k__building__

#include <stdio.h>
#include "game.h"
#include "player.h"
class Controller;

class Game;

class Player;


class Building{
protected:
    const int position;
    const std::string name;
    Game* const game;
public:
    int getPosition()const;
    Game* getGame()const;
    Controller* getController()const;
    Building(const int, const std::string, Game* const);
    ~Building();
    virtual int todo(Player*);
    virtual bool canTrade()const;
    virtual Player* getOwner()const;  // return NULL if no Owner;
    virtual bool canImprove();  // check whether building is in monopoly, for anything other than academic
    // return  false;
    virtual void setOwner(Player * player); // cs
    virtual bool mortgage();    // change status  // remember the bankrupt situation
    virtual bool unmortgage();  // cs and watch out for auction buildings
    virtual int getStatus();  // ownership(10 - no owner), level(0,1,2,3,4,5), mortgage(-1)
    virtual void setStatus(const int);
    virtual int getValue();  // get building value
    virtual int getImproveCost();
    virtual bool improve();  // remember to cs
    virtual bool deImprove();  // cs
    virtual bool isMono();
    virtual bool isAuction();
    virtual void setAuction();
    virtual void deAuction();
    std::string getName()const;
};



#endif /* defined(__bb7k__building__) */


