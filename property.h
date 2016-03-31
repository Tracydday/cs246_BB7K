
#ifndef __bb7k__property__
#define __bb7k__property__

#include <stdio.h>
#include "building.h"
#include "player.h"

class Property: public Building{
protected:
    int value;
    int const mono1;
    int const mono2;
    int const mono3;
    int const mono4;
    bool auction;
    
    Player *owner;
    int status;
    
public:
    virtual void setStatus(const int);
    Property();
    Property(const int pos, const std::string nam, Game * const gam,const int value, const int mono1, const int mono2, const int mono3,const int mono4);
    void setOwner(Player * player);
    virtual Player* getOwner()const;
    bool mortgage();    // change status
    bool unmortgage(); // cs
    int getStatus();  // ownership(10 - no owner), level(0,1,2,3,4,5), mortgage(-1)
    int getValue(); // get building value
    virtual int todo(Player*);
    ~Property();
    bool isAuction()const;
    void setAuction();
    void deAuction();
    
    virtual bool canTrade()const;

    };


#endif /* defined(__bb7k__property__) */


