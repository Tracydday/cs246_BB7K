//
//  property.cpp
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#include "property.h"
#include "building.h"
#include "academic.h"
#include "gyms.h"
#include "residence.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;



Property::Property(const int pos, const std::string nam, Game * const gam,const int value, int const mono1, const int mono2, int const mono3,const int mono4):Building(pos,nam,gam),value(value),mono1(mono1),mono2(mono2),mono3(mono3),mono4(mono4),auction(false),owner(NULL),status(0){}
                   
                   
void Property::setOwner(Player *player){
    if (owner!=NULL){
        owner->detachProperty(this);
        if(player==NULL){
            cout<<name<<" belongs to the school now."<<endl;
            owner=NULL;
        }

        else {
            player->attachProperty(this);
            cout<<name<<" belongs to "<<player->getName()<<" now."<<endl;
            owner=player;
        }
    }
    else if(owner == NULL){
        if(player==NULL){
            cout<<name<<" belongs to the school now."<<endl;
            owner=NULL;
        }
        else{
            player->attachProperty(this);
            cout<<name<<" belongs to "<<player->getName()<<" now."<<endl;
            owner = player;
        }
    }
    game->notify(this);
}

Property::~Property(){}

Player * Property::getOwner() const {
    return owner;
}

void Property:: setStatus(const int n){
    status=n;
}

bool Property::mortgage(){
    if (status == 0&&owner!=NULL) {
        owner->addMoney(value/2);
        status = -1;
        game->notify(this);
        return true;
    }
    std::cout<<"This property can not be mortagaged."<<std::endl;
    return false;
}

bool Property::unmortgage(){
    if(auction){
        game->getController()->payDebt(owner,NULL,value/2);
        status=0;
        game->notify(this);
        return true;
    }
    game->getController()->payDebt(owner,NULL,(value/20)+(value/2));
    status=0;
    game->notify(this);
    
    return true;
}

int Property::getStatus(){
    return status;
}

int Property::getValue(){
    return value;
}

bool Property:: isAuction()const{
    return auction;
}
void Property:: setAuction(){
    auction=true;
}
void Property:: deAuction(){
    auction=false;
}

bool Property:: canTrade()const{
    return true;
}

int Property:: todo(Player* p){
    cerr<<"-----------------------------This todo probably should not be ran."<<endl;
    return -100;
}

