//
//  needleshall.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__needleshall__
#define __bb7k__needleshall__

#include <stdio.h>
#include "building.h"

class NeedlesHall: public Building{
    int pool[18];
public:
    virtual int todo(Player*);
    NeedlesHall(const int, Game* const gam);
    ~NeedlesHall();
};


#endif /* defined(__bb7k__needleshall__) */


