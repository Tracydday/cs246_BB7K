

#include "academic.h"
#include "player.h"
#include "property.h"
#include "game.h"
#include <string>
#include <iostream>


using namespace std;


Academic::Academic(const int pos, const std::string nam, Game *gam, const int value, int const mono1, const int mono2, int const mono3,const int upgradeCost,const int toll,const int toll1,const int toll2, const int toll3,const int toll4, const int toll5): Property(pos,nam,gam,value,mono1,mono2,mono3,100),toll(toll),toll1(toll1),toll2(toll2),toll3(toll3),toll4(toll4),toll5(toll5),upgradeCost(upgradeCost){}


bool Academic::isMono(){
    if(owner==NULL)return false;
    if(game->getBuilding(mono1)->getOwner()!=owner)return false;
    if(game->getBuilding(mono2)->getOwner()!=owner)return false;
    if(mono3<40){
        if(game->getBuilding(mono3)->getOwner()!=owner)return false;
    }
    return true;
}

void Academic:: setStatus(const int n){
    status=n;
    value=value+n*upgradeCost;
}

bool Academic::improve(){
    if (isMono()) { // monoploy exists.
        if(status<0||status>4){
            cout<<"This property can not have improvements at this moment."<<endl;
            return false;
        }
        if(owner->getMoney()<upgradeCost){
            cout<<"Sorry, improving this property requires $"<<upgradeCost;
            cout<<" .  You have insuffient fund to do so."<<endl;
            return false;
        }
        game->getController()->payDebt(owner,NULL,upgradeCost);
        value=value+upgradeCost;
        status++;
        game->notify(this);
        return true;
    }
    cout<<"The building is not in a monopoly, you can not improve it yet."<<endl;
    return false;
}

bool Academic::deImprove(){
    if (owner!=NULL&&status > 0) {
        owner->addMoney(upgradeCost/2);
        status--;
        cout<<"You've sold you an improvment on "<<name<<"."<<endl;
        value=value-upgradeCost;
        game->notify(this);
        return true;
    }
    cout<<"Action is invalid, either the building does not belong to you, or ";
    cout<<"it has no improvment."<<endl;
    return false;
}

bool Academic:: canTrade()const{
    if(game->getBuilding(mono1)->getStatus()>0)return false;
    if(game->getBuilding(mono2)->getStatus()>0)return false;
    if(mono3<40){
        if(game->getBuilding(mono3)->getStatus()>0)return false;
    }
    return true;
}

int Academic::todo(Player * p){
    if(owner==NULL){
        game->getController()->auction(p,this);
        return 0;
    }
    if(p==owner){
        cout<<"You've landed on your own property, nothing special happens."<<endl;
        return 0;
    }
    if(status==-1){
        cout<<"You've laned on a mortgaged property, no need to pay anything."<<endl;
        return 0;
    }
    int fee=999;
    if(status==0)fee=toll;
    if(isMono()) fee=fee*2;
    if(status==1)fee=toll1;
    if(status==2)fee=toll2;
    if(status==3)fee=toll3;
    if(status==4)fee=toll4;
    if(status==5)fee=toll5;
    cout<<"You need to pay a tuition of $"<<fee<<" to "<<owner->getName()<<"."<<endl;
    game->getController()->payDebt(p,owner,fee);
    return 0;
}

Academic::~Academic(){}


