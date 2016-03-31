

#include "dice.h"
#include <string>
#include <ctime>
#include <stdlib.h>
#include <sstream>
#include <iostream>


Dice:: Dice():dice1(0),dice2(0){}

Dice:: ~Dice(){
    std::cout<<"dice is deletd"<<std::endl;
}

bool Dice:: isPair(){
    if(dice1==dice2)return true;
    return false;
}


int Dice::getSum(){
    return dice1+dice2;
}

void Dice:: testRoll(const int die1, const int die2){
    dice1=die1;
    dice2=die2;
}
void Dice::roll(){
    srand(time(0));
    dice1=1+rand()%6;
    dice2 =1+rand()%6;
    
}

std::string Dice:: die(){
    std::string s;
    std::string s2;
    std::stringstream ss;
    std::stringstream sss;
    ss<<dice1;
    ss>>s;
    sss<<dice2;
    sss>>s2;
    return "You rolled: "+s+" and "+s2;
}

