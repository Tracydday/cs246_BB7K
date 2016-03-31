//
//  needleshall.cpp
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#include "needleshall.h"
#include <ctime>
#include <stdlib.h>



using namespace std;


NeedlesHall:: NeedlesHall(const int pos, Game* const gam):Building(pos,"SLC",gam){
    pool[0]=-100;
    pool[1]=-100;
    pool[2]=100;
    pool[3]=100;
    pool[4]=50;
    pool[5]=50;
    pool[6]=50;
    pool[7]=-50;
    pool[8]=-50;
    pool[9]=-50;
    pool[10]=25;
    pool[11]=25;
    pool[12]=25;
    pool[13]=25;
    pool[14]=25;
    pool[15]=25;
    pool[16]=200;
    pool[17]=-200;
    
}

int NeedlesHall:: todo(Player* p){
    if (getController()->rareCup()){
        cout<<"Wow, you just won a Roll Up the Rim cup!  That's 1 out 100 odd!"<<endl;
        if(game->giveCup(p))return 0;
        cout<<"Oops, Roll Up the Rim cup is OUT OF STOCK, how unfortunate!"<<endl;
        return 0;
    }
    srand(time(NULL));
    int result= pool[rand()%18];
    if (result<0){
        cout<<"Unfortunately, you've lost $"<<result*-1<<endl;
        game->getController()->payDebt(p,NULL, -1*result);
        return 0;
    }
    cout<<"Congratulations, you won: $"<<result<<endl;
    p->addMoney(result);
    return 0;
}

NeedlesHall::~NeedlesHall(){
    cout<<"needleshall is deleted"<<endl;
}


