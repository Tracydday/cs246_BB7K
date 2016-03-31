
#ifndef __bb7k__player__
#define __bb7k__player__

#include <stdio.h>
#include <string>
#include <iostream>
#include "game.h"
#include "building.h"
#include <vector>
class Game;
class Building;
class Player {
private:
    int id;
    int money;
    int position;
    int cup;
    int status;  // 0: ready, 1:first round in DC and 2 and 3. -1: bankrupted
    Game *game;
    bool auction;
    std::string name;
    std::string const piece;
    
    std::vector<Building*> asset;
    
    static int playernum;
    
    Player(const std::string, const std::string, Game* const game);
    
    
public:
    std::vector<Building*>& getProperty();
    std::string getPiece()const;
    bool getAuction()const; // make sure bankrupted player return false;
    void setAuction(const bool);  // make sure bankrupted player set to false;
    int getTotal()const;  // get the total wealth of the player

    static Player* createPlayer(const std::string, const std::string, Game*);
    ~Player();
    void setPlayer(const int money, const int status,const int pos);
    std:: string getName()const;
    int getMoney() const;
    int getPosition() const;
    int getID() const;
    int  getCup() const;
    void setPosition(const int p);
    void addMoney(const int m);
    void setStatus(const int);
    void setCup(const int c);
    void attachProperty(Building* const);
    void detachProperty(Building* const);
    int getStatus ();
    void bankrupt();
    int bankrupt(Player*);
    void resetMortgage();  //reset all the mortgaged buildings received from bankrupter to normal
};

#endif /* defined(__bb7k__player__) */



