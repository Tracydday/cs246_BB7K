//
//  residence.cpp
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#include "residence.h"
using namespace std;



Residence::Residence(const int pos, const std::string nam, Game * const gam,const int value, const int mono1, const int mono2, const int mono3,const int mono4): Property(pos,nam,gam,value,mono1,mono2,mono3,mono4){}



int Residence::todo(Player* p){
    if(p==owner){
        cout<<"You've landed on your own property, nothing special happens."<<endl;
        return 0;
    }
    if(status==-1){
        cout<<"You've laned on a mortgaged property, no need to pay anything."<<endl;
        return 0;
    }
    if(owner==NULL){
        game->auction(p,this);
        return 0;
    }
    int acc=0;
    if(game->getBuilding(mono1)->getOwner()==owner)acc++;
    if(game->getBuilding(mono2)->getOwner()==owner)acc++;
    if(game->getBuilding(mono3)->getOwner()==owner)acc++;
    if(game->getBuilding(mono4)->getOwner()==owner)acc++;
    if(acc==1)acc=25;
    if(acc==2)acc=50;
    if(acc==3)acc=100;
    if(acc==4)acc=200;
    cout<<"You need to pay a rent of $"<<acc<<" to "<<owner->getName()<<"."<<endl;
    game->getController()->payDebt(p,owner,acc);
    return 0;

}



