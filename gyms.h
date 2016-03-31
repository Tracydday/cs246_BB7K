//
//  gyms.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__gyms__
#define __bb7k__gyms__

#include <stdio.h>
#include "property.h"
#include "game.h"

class Gyms:public Property{
    
public:
    //Gyms(const int pos, const std::string nam, Game const* gam);
    Gyms(const int pos, const std::string nam, Game * const gam,const int value, const int mono1, const int mono2, const int mono3,const int mono4);
    
    virtual int todo(Player*);
    ~Gyms();
};

#endif /* defined(__bb7k__gyms__) */
