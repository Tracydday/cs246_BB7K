//
//  dice.h
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#ifndef __bb7k__dice__
#define __bb7k__dice__

#include <stdio.h>
#include <string>

class Dice{
private:
    int dice1;
    int dice2;
public:
    Dice();
    ~Dice();
    bool isPair();
    int getSum();
    void roll();
    std::string die();
    void testRoll(const int, const int);
    
};

#endif /* defined(__bb7k__dice__) */
