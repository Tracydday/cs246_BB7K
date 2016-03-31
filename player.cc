//
//  player.cpp
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#include "player.h"
#include "game.h"
#include <string>
#include <vector>

using namespace std;

int Player::playernum=0;
Player:: Player(const string nam, const string c, Game* const game):id(playernum++),money(1500),position(0),cup(0),status(0),game(game),auction(false),name(nam),piece(c){}

Player* Player::createPlayer(const string nam, const string c, Game* game){
    if (game->getPlayerSum()<playernum){
        cerr<<"Can't not create more than "<<game->getPlayerSum()<<" players"<<endl;
        return NULL;
    }
    Player* p=new Player(nam,c,game);
    return p;
    
}

void Player::setPlayer(const int m, const int stat,const int pos){
    money=m;
    status=stat;
    position=pos;
    game->notify(this);
}
void Player:: setStatus(const int n){
    status=n;
    game->notify(this);
}

bool Player:: getAuction()const{
    if(status==-1)return false;
    return auction;
}

void Player:: setAuction(const bool set){
    auction=set;
    if (status==-1)auction=false;
}

int Player:: getMoney()const{
    return money;
}

std::string Player:: getPiece()const{
    return piece;
}

int Player:: getPosition()const{
    return position;
}

int Player::getID()const{
    return id;
}

int Player::getCup()const{
    return cup;
}

std::vector<Building*>& Player:: getProperty(){
    return asset;
}

std::string Player:: getName()const{
    return name;
}
void Player::setPosition(const int p){
    position=p;
    game->notify(this);
}

void Player::addMoney(const int m){
    if(m==0);
    else if(m>0){
        cout<<name<<" received: $"<<m<<endl;
    }
    else{
        cout<<name<<" lost: $"<<m<<endl;
    }
    money= money + m;
}

void Player::setCup(const int c){
    if(c<cup){
        game->destroyCup(cup-c);
    }
    cup=c;
}

int Player:: getStatus (){
    return status;
}

void Player:: attachProperty(Building* const b){
    asset.push_back(b);
}

void Player:: detachProperty(Building* const b){
    int acc=0;
    for(std::vector<Building*>::size_type i=0;  i != asset.size();i++){
        if(asset[i]==b)break;
        acc++;
    }
    asset.erase(asset.begin()+acc-1);
}


void Player:: resetMortgage(){
    
}


int Player:: getTotal()const{
    int acc=0;
    for(std::vector<Building*>::size_type i=0;  i != asset.size();i++){
        acc=acc+asset[i]->getValue();
    }
    return acc+money;
}

void Player::bankrupt(){
    status=-1;
    game->destroyCup(cup);
    auction=false;
    setCup(0);
    std::vector<Building*>::size_type i=0;
    while(asset.size()!=0){
        Building* tmp = asset[i];
        tmp->setOwner(NULL);
        if(tmp->getStatus()==-1)tmp->setStatus(0);
        game->notify(tmp);
        game->auction(NULL,tmp);
        i++;
    }
    
    game->notify(this);
    cout<<name<<" has bankrupted."<<endl;
}

int Player:: bankrupt(Player* p){
    status=-1;
    auction=false;
    p->addMoney(money);
    p->setCup(p->getCup()+cup);
    cup=0;
    int acc=0;
    while(asset.size()!=0){
        Building* tmp = asset[0];
        if (tmp->getStatus()==-1){
            acc=acc+tmp->getValue();
            tmp->setAuction();
        }
        tmp->setOwner(p);
    }
    game->notify(this);
    cout<<name<<" has bankrupted."<<endl;
    return acc/20;
  
}

Player:: ~Player(){
    while(asset.size()!=0){
        asset.erase(asset.begin());
    }
    cout<<"player is deleted"<<endl;
}

