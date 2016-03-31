

#include "gyms.h"
#include <string>
#include <iostream>
#include "property.h"

using namespace std;


Gyms::Gyms(const int pos, const std::string nam, Game * const gam,const int value, const int mono1,const int mono2, const int mono3,const int mono4): Property(pos,nam,gam,value,mono1,mono2,mono3,mono4){}


int Gyms::todo(Player *p){
    if(p==owner){
        cout<<"You've landed on your own property, nothing special happens."<<endl;
        return 0;
    }
    if(status==-1){
        cout<<"You've laned on a mortgaged property, no need to pay anything."<<endl;
        return 0;
    }
    if(owner==NULL){
        game->auction(p, this);
        return 0;
    }
    int acc=0;
    if(game->getBuilding(mono1)->getOwner()==owner)acc++;
    if(game->getBuilding(mono2)->getOwner()==owner)acc++;
    if(acc==0)acc=1;
    else if(acc==1)acc=4;
    else if(acc>1)acc=10;
    game->roll();
    cout<<"You need to pay a gym membership fee of $"<<acc*game->getSum()<<" to "<<owner->getName()<<"."<<endl;
    game->getController()->payDebt(p,owner,acc*game->getSum());
    return 0;
}

