//
//  TextDisplay.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__TextDisplay__
#define __bb7k__TextDisplay__

#include <stdio.h>
#include "player.h"
#include <iostream>
#include <sstream>
#include "building.h"


class TextDisplay{
    char **theDisplay;
    char **boardplayer;
    
public:
    TextDisplay();
    ~TextDisplay();
    void print();
    void addPlayer(Player * );
    void notify(Player* );
    void notify(Building*  b);
    void printAssets(Player*);
    
};

#endif /* defined(__bb7k__TextDisplay__) */
