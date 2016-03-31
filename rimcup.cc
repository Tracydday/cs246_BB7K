//
//  rimcup.cpp
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#include "rimcup.h"
#include <string>


RimCup:: RimCup():quantity(0){}

bool RimCup::giveCup(Player* p){
    if (quantity==4) return false;
    quantity++;
    p->setCup(p->getCup()+1);
    std:: cout<<p->getName()<<" received 1 Roll Up the Rim cup."<<std::endl;
    return true;
}

void RimCup:: destroyCup(const int n){
    quantity= quantity-n;
}


RimCup:: ~RimCup(){
    std::cout<<"cup is deleted"<<std::endl;
}

