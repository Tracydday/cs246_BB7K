

#include "building.h"
#include <string>
#include "game.h"

Building:: Building(const int pos, const std::string nam, Game* const gam):position(pos),name(nam),game(gam){}

Building:: ~Building(){}

Game* Building:: getGame()const{
    return game;
}

Controller* Building:: getController()const{
    return game->getController();
}

bool Building:: canTrade()const{
    return false;
}

std::string Building::getName()const{
    return name;
}

Player* Building:: getOwner()const{
    return NULL;
}

int Building::getStatus(){
    return -2;
}

int Building:: todo(Player* p){
    if(position==0){
        p->addMoney(200);
        std::cout<<"You collected $200 from OSAP."<<std::endl;
        return 0;
    }
    if(position==38){
        std::cout<<"You need to pay a coop fee of $150."<<std::endl;
        if(!(game->getController()->payDebt(p,NULL,150)))return -99;
        return 0;
    }
    if(position==20){
        std::cout<<"You are attacked by a flock of nesting goose.  GoooooGA~~~~~"<<std::endl;
        return 0;
    }
    if(position==4){  // at tuition
        if(!(game->getController()->tuition(p)))return -99;
        return 0;
    }
    if(position==30){ // At go to DC
        return 10;
    }
    if(position==10){  // at DC
        std::cout<<"You arrived at DC Tims Line.  Surprisingly, you are not interested in their ";
        std::cout<<"diluted coffee."<<std::endl;
        return 0;
    }
    std::cerr<<"--------------ERROR: reached end of base todo"<<std::endl;
    return -100;
}

int Building:: getPosition()const{
    return position;
}

bool Building::improve(){
    std:: cout<<"This building can not have improvments."<<std::endl;
    
    return false;
}
bool Building::deImprove(){
    std:: cout<<"This building can not have improvments."<<std::endl;
    
    return false;
}

void Building:: setStatus(const int){
    std:: cerr<<"-------------ERROR: This setStatus should not be ran!!"<<std::endl;
}

bool Building:: canImprove(){
    std:: cerr<<"-------------ERROR: This canImprove should not be ran!!"<<std::endl;
    return false;
}

void Building:: setOwner(Player * player){
    std:: cerr<<"-------------ERROR: This setOwner should not be ran!!"<<std::endl;
    return;
}

bool Building::mortgage(){
    std:: cerr<<"-------------ERROR: This mortgage should not be ran!!"<<std::endl;
    return false;
}
bool Building::unmortgage(){
    std:: cerr<<"-------------ERROR: This unmortgage should not be ran!!"<<std::endl;

    return false;
}

int Building::getValue(){
    std:: cerr<<"-------------ERROR: This getValue should not be ran!!"<<std::endl;

    return -100;
}

int Building::getImproveCost(){
    std:: cerr<<"-------------ERROR: This getImproveCost should not be ran!!"<<std::endl;

    return -100;
}

bool Building::isMono(){
    std:: cerr<<"-------------ERROR: This isMono should not be ran!!"<<std::endl;

    return false;
}
bool Building::isAuction(){
    std:: cerr<<"-------------ERROR: This isAuction should not be ran!!"<<std::endl;

    return false;
}
void Building::setAuction(){
    std:: cerr<<"-------------ERROR: This setAuction should not be ran!!"<<std::endl;
}
void Building::deAuction(){
    std:: cerr<<"-------------ERROR: This deAuction should not be ran!!"<<std::endl;
}









