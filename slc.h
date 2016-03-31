//
//  slc.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__slc__
#define __bb7k__slc__


#include <stdio.h>
#include "building.h"
class Player;
class Game;

class SLC: public Building{
    int pool[24];
public:
    virtual int todo(Player*);
    SLC(const int, Game* const);
    ~SLC();
};

#endif /* defined(__bb7k__slc__) */
