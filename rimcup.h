//
//  rimcup.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__rimcup__
#define __bb7k__rimcup__

#include <stdio.h>
#include <string>
#include "game.h"
#include "player.h"
class Player;
class RimCup{
private:
    int quantity;
public:
    RimCup();
    bool giveCup(Player*);
    void destroyCup(const int);
    ~RimCup();
    
};

#endif /* defined(__bb7k__rimcup__) */
