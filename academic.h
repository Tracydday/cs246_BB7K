
#ifndef __bb7k__academic__
#define __bb7k__academic__

#include <stdio.h>
#include "property.h"
#include "game.h"
class Academic:public Property{
private:
    const int toll;
    const int toll1;
    const int toll2;
    const int toll3;
    const int toll4;
    const int toll5;
    const int upgradeCost;
    
public:
    Academic(const int pos, const std::string name, Game *game,const int  value, int const mono1, const int mono2, int const mono3, const int  upgradeCost,const int toll,const int toll1,const int toll2, const int toll3,const int toll4, const int toll5);  // set mono4 as NULL
    ~Academic();  // set mono3 be >40 if does not exit
    bool improve();  // remember to cs
    bool deImprove();  // cs
    virtual void setStatus(const int);
    virtual int todo(Player*);
    virtual bool isMono();
    virtual bool canTrade()const;
    
};
#endif /* defined(__bb7k__academic__) */




