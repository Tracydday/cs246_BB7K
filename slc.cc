//
//  slc.cpp
//  bb7k
//
//  Created by Tracy on 2015-07-18.
//  Copyright (c) 2015 Tracy. All rights reserved.
//

#include "slc.h"
#include <stdlib.h>
#include <ctime>
using namespace std;


SLC:: SLC(const int pos, Game* const gam):Building(pos,"SLC",gam){
    pool[0]=-3;
    pool[1]=-3;
    pool[2]=-3;
    pool[3]=1;
    pool[4]=1;
    pool[5]=1;
    pool[6]=-2;
    pool[7]=-2;
    pool[8]=-2;
    pool[9]=-2;
    pool[10]=-1;
    pool[11]=-1;
    pool[12]=-1;
    pool[13]=-1;
    pool[14]=2;
    pool[15]=2;
    pool[16]=2;
    pool[17]=2;
    pool[18]=3;
    pool[19]=3;
    pool[20]=3;
    pool[21]=3;
    pool[22]=10;
    pool[23]=-10;
    
    
}

int SLC:: todo(Player* p){
    if (game->getController()->rareCup()){
        cout<<"Wow, you just won a Roll Up the Rim cup!  That's 1 out 100 odd!"<<endl;
        if(getGame()->giveCup(p))return 0;
        cout<<"Oops, Roll Up the Rim cup is OUT OF STOCK, how unfortunate!"<<endl;
        return 0;
    }
    srand(time(NULL));
    int result= pool[rand()%24];
    if (result < 10 && result > -10){
        cout<<"You are asked to move forward "<<result<<" blocks."<<endl;
    }
    return result;
}


