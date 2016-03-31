//
//  residence.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__residence__
#define __bb7k__residence__

#include <stdio.h>
#include "property.h"
#include "game.h"

class Residence:public Property{
public:
    //Residence(const int, const std::string, Game const*);
    Residence(const int pos, const std::string nam, Game * const gam,const int value, const int mono1, const int mono2, const int mono3,const int mono4);
    ~Residence();
    int todo(Player*);
    
};

#endif /* defined(__bb7k__residence__) */

