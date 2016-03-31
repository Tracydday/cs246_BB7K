#include "game.h"
#include <vector>
#include "player.h"
#include "property.h"
#include "academic.h"
#include "gyms.h"
#include "residence.h"
#include "slc.h"
#include "needleshall.h"

class Building;

Game::Game(const int n, Controller* const c):players(n),controller(c),cup(new RimCup),player(new Player*[n]),dice(new Dice){
    for(int i=0; i < n; i++){
        player[i]=NULL;
    }
    buildings[0]=new Building(0,"Collect OSAP",this);
    buildings[1]=new Academic(1,"AL",this,40,1,3,100,50,2,10,30,90,160,250);
    buildings[2]=new SLC(2,this);
    buildings[3]=new Academic(3,"ML",this,60,1,3,100,50,4,20,60,180,320,450);
    buildings[4]=new Building(4,"Tuition",this);
    buildings[5]=new Residence(5,"MKV", this,200,5,15,25,35);
    buildings[6]=new Academic(6,"ECH",this,100,6,8,9,50,6,30,90,270,400,550);
    buildings[7]=new NeedlesHall(7,this);
    buildings[8]=new Academic(8,"PAS",this,100,6,8,9,50,6,30,90,270,400,550);
    buildings[9]=new Academic(9,"HH",this,120,6,8,9,50,8,40,100,300,450,600);
    buildings[10]=new Building(10,"DC Tims Line",this);
    buildings[11]=new Academic(11,"RCH",this,140,11,13,14,100,10,50,150,450,625,750);
    buildings[12]=new Gyms(12,"PAC",this,150,12,28,100,100);
    buildings[13]=new Academic(13,"DWE",this,140,11,13,14,100,10,50,150,450,625,750);
    buildings[14]=new Academic(14,"CPH",this,160,11,13,14,100,12,60,180,500,700,900);
    buildings[15]=new Residence(15,"UWP",this,200,5,15,25,35);
    buildings[16]=new Academic(16,"LHI",this,180,16,18,19,100,14,70,200,550,750,950);
    buildings[17]=new SLC(17,this);
    buildings[18]=new Academic(18,"BMH",this,180,16,18,19,100,14,70,200,550,750,950);
    buildings[19]=new Academic(19,"OPT",this,200,16,18,19,100,16,80,220,600,800,1000);
    buildings[20]=new Building(20,"Goose Nesting",this);
    buildings[21]=new Academic(21,"EV1",this,220,21,23,24,150,18,90,250,700,875,1050);
    buildings[22]=new NeedlesHall(22,this);
    buildings[23]=new Academic(23,"EV2",this,220,21,23,24,150,18,90,250,700,875,1050);
    buildings[24]=new Academic(24,"EV3",this,220,21,23,24,150,20,100,300,750,925,1100);
    buildings[25]=new Residence(25,"V1",this,200,5,15,25,35);
    buildings[26]=new Academic(26,"PHYS",this,260,26,27,28,150,22,110,330,800,975,1150);
    buildings[27]=new Academic(27,"B1",this,260,26,27,28,150,22,110,330,800,975,1150);
    buildings[28]=new Gyms(28,"CIF",this,150,12,28,100,100);
    buildings[29]=new Academic(29,"B2",this,280,26,27,29,150,24,120,360,850,1025,1200);
    buildings[30]=new Building(30,"Go To Tims",this);
    buildings[31]=new Academic(31,"EIT",this,300,31,32,33,200,26,130,390,900,1100,1275);
    buildings[32]=new Academic(32,"ESC",this,300,31,32,33,200,26,130,390,900,1100,1275);
    buildings[33]=new SLC(33,this);
    buildings[34]=new Academic(34,"C2",this,320,31,32,33,200,28,150,450,1000,1200,1400);
    buildings[35]=new Residence(35,"REV",this,200,5,15,25,35);
    buildings[36]=new NeedlesHall(36,this);
    buildings[37]=new Academic(37,"MC",this,350,37,39,100,200,35,175,500,1100,1300,1500);
    buildings[38]=new Building(38,"COOP FEE",this);
    buildings[39]=new Academic(39,"DC",this,400,37,39,100,200,50,200,600,1400,1700,2000);
    
}

Game:: ~Game(){
    delete dice;
    delete cup;
    for(int i=0; i<40; i++){
        delete buildings[i];
    }
    for(int i=0; i< players; i++){
        delete player[i];
    }
    std::cout<<"Game is deleted"<<std::endl;
    
}

void Game:: setPlayer(const int i, const int cup,const int money, const int status,const int pos){
    if(player[i]==NULL) std::cerr<<"NULL in setPlayer"<<std::endl;
    player[i]->setPlayer(money, status,pos);
    if(cup!=0){
        for(int n=0;n<cup;n++){
            giveCup(player[i]);
        }
    }
    
}

void Game:: init(Player* const p, const int n){
    if (player[n]!=NULL){
        std::cerr<<"---------------EROOR: init in game."<<std::endl;
        return;
    }
    player[n]=p;
}

Player* Game:: createPlayer(const std:: string s,const std::string c){
    return Player::createPlayer(s, c, this);
}

Player* Game:: getPlayer(const int n){
    return player[n];
}

Building* Game:: getBuilding(const int n)const{
    return buildings[n];
}

Player* Game:: loopPlayer(const int n)const{
    if(player[n]==NULL)return NULL;
    return player[n];
}

int Game::getPlayerSum()const{
    return players;
}

void Game:: testRoll(const int die1,const int die2){
    dice->testRoll(die1,die2);
}

Building* Game::getBuilding(const std::string s)const{
    for(int i=0; i<40; i++){
        if(buildings[i]->getName()==s)return buildings[i];
    }
    std::cout<<"No building named "<<s<<" exists."<<std::endl;
    return NULL;
}

Player* Game::getPlayer(const std::string s){
    for(int i=0; i<players; i++){
        if((player[i]->getName()==s))return player[i];
    }
    std::cout<<"No player named "<<s<<" exists."<<std::endl;
    return NULL;
}

bool Game:: isPair(){
    return dice->isPair();
}

int Game:: getSum(){
    return dice->getSum();
}

std::string Game:: die(){
    return dice->die();
}

void Game::roll(){
    dice->roll();
}

bool Game:: giveCup(Player* p){
    return cup->giveCup(p);
}

void Game:: destroyCup(const int n){
    cup->destroyCup(n);
}

void Game:: auction(Player* p,Building* b){
    controller->auction(p,b);
}

Controller* Game:: getController()const{
    return controller;
}

void Game:: notify(Player*p){
    controller->notify(p);
}
void Game:: notify(Building* b){
    controller->notify(b);
}
