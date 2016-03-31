
#include "controller.h"

#include "game.h"
#include "textdisplay.h"
#include <iostream>
#include <sstream>
#include "property.h"
#include <ctime>
#include <stdlib.h>
#include <fstream>
#include <cstring>

using namespace std;


// --------------------------------

Controller:: Controller(){
    td=new TextDisplay;
    game=NULL;
}

Controller:: ~Controller(){
    delete td;
    delete game;
    cout<<"controller is deleted"<<endl;
} 

// --------------------------------

void Controller:: notify(Player* p){
    td->notify(p);
}
void Controller:: notify(Building* b){
    td->notify(b);
}
//-----------------------------------

void Controller:: save(string input,Player* pp){
    string s;
    stringstream ss(input);
    ss>>s;
    if(!(ss>>s)){  // pre-condition check
        cout<<"Invalid file name to be save at."<<endl;
        return;
    }
    ofstream file;
    file.open (s.c_str());
    file<<game->getPlayerSum()<<endl;
    int acc=0;
    Player* p=NULL;
    while(1){
        if(acc==game->getPlayerSum())break;
        else if(acc==0){
            p=pp;
        }
        else{
            if(acc+pp->getID()==game->getPlayerSum()){
                p=game->loopPlayer(acc+pp->getID()-game->getPlayerSum());
            }
            else p=game->loopPlayer(p->getID()+acc);
        }
        if(p->getStatus()==-1)continue;
        file<<p->getName()<<" ";
        file<<p->getPiece()<<" ";
        file<<p->getCup()<<" ";
        file<<p->getMoney()<<" ";
        file<<p->getPosition()<<" ";
        if(p->getPosition()==10){                       // possible proble 1 or num?  ?????????????????????
            if(p->getStatus()>0) file<<"1 "<<p->getStatus()-1;
            else file<<"0";
        }
        else file<<"0";
        file<<endl;
        acc++;
    }
    for(int i=0; i<40;i++){
        Building*b=game->getBuilding(i);
        if(b->getStatus()==-2)continue;
        file<<b->getName()<<" ";
        if(b->getOwner()==NULL){
            file<<"BANK"<<" ";
        }
        else{
            file<<b->getOwner()->getName()<<" ";
        }
        file<<b->getStatus()<<endl;
    }
    file.close();
    cout<<"Save complete."<<endl;
    return;

}

// ----------------------------------

bool Controller::load(const string input){
    
    ifstream load;
    load.open(input.c_str());
    int playerSum=0;
    string s;
    getline(load,s);
    stringstream ss(s);
    ss>>playerSum;
    string name;
    string piece;
    string owner;
    int totalCup=0;
    int cup;
    int money;
    int pos;
    int status;
    game=new Game(playerSum, this);
    for(int i=0; i<playerSum;i++){
        ss.str("");
        ss.clear();
        getline(load,s);
        ss<<s;
        ss>>name;
        ss>>piece;
        ss>>cup;
        ss>>money;
        ss>>pos;
        ss>>status;

        if(status==1){
            
            ss>>status;
            if(status<0||status>2){
                load.close();
                return false;
            }
            
            if(piece=="G"||piece=="B"||piece=="D"||piece=="P"||piece=="S"||piece=="$"||piece=="L"||piece=="T"){
                for(int n=0;n< i;n++){
                    if(name==game->loopPlayer(n)->getName()){
                        cout<<"Invalid input, "<<name<<" already exists."<<endl;
                        return false;
                    }
                    if(piece==game->loopPlayer(n)->getPiece()){
                        cout<<"Invalid input, "<<piece<<" already exists."<<endl;
                        return false;
                    }
                }
                game->init(game->createPlayer(name, piece),i);
                td->addPlayer(game->loopPlayer(i));
                if(cup!=0){
                    totalCup+=cup;
                    if(totalCup>4||totalCup<0){
                        cout<<"Wrong number of RimCups in load file.  Loading failed."<<endl;
                        return false;
                    }
                }
               
                game->setPlayer(i,cup,money,status+1,pos);
                cout<<piece<<" is created."<<endl;
                td->notify(game->loopPlayer(i));
                continue;
            }
            load.close();
            
            return false;
        }
        else if(status==0){
            
            if(piece=="G"||piece=="B"||piece=="D"||piece=="P"||piece=="S"||piece=="$"||piece=="L"||piece=="T"){
                for(int n=0;n< i;n++){
                    if(name==game->loopPlayer(n)->getName()){
                        cout<<"Invalid input, "<<name<<" already exists."<<endl;
                        return false;
                    }
                    if(piece==game->loopPlayer(n)->getPiece()){
                        cout<<"Invalid input, "<<piece<<" already exists."<<endl;
                        return false;
                    }
                }
                game->init(game->createPlayer(name, piece),i);
                td->addPlayer(game->loopPlayer(i));
                if(cup!=0){
                    totalCup+=cup;
                    if(totalCup>4||totalCup<0){
                        cout<<"Wrong number of RimCups in load file.  Loading failed."<<endl;
                        return false;
                    }
                }
                
                game->setPlayer(i,cup,money,status,pos);
                td->notify(game->loopPlayer(i));
                cout<<piece<<" is created."<<endl;
                continue;
            }
            load.close();
            return false;
        }
        load.close();
        return false;
    }
    for(int i=0; i<28;i++){
        getline(load,s);
        ss.clear();
        ss.str(s);
        ss>>name;
        ss>>owner;
        ss>>status;
        Building* b=game->getBuilding(name);
        if(owner=="BANK"){
            b->setStatus(status);
        }
        else{
            b->setOwner(game->getPlayer(owner));
            b->setStatus(status);
        }
       td->notify(b);          //     a building can have no owner and improvements
    }
    cout<<"Game has been loaded."<<endl;
    load.close();
    return true;
}






// ----------------------------------

int Controller:: init(){
    int num=0;
    cout<<"Please enter the number of players."<<endl;
    string s;
    string tmp;
    while(1){
        getline(cin,s);
        stringstream ss(s);
        if(ss>>num){
            if (num>1&&num<=8)break;
            cout<<"Invalid number of players.  Please enter a number between 2 and 8."<<endl;
            continue;
        }
        cout<<"Inavlid input."<<endl;
        continue;
    }
    game=new Game(num,this);
    cout<<"Please enter your name and the corresponding piece you want to use to ";
    cout<<"represent you."<<endl;
    cout<<"G for Goose."<<endl;
    cout<<"B for GRT BUS."<<endl;
    cout<<"D for Tim Hortons Doughnut."<<endl;
    cout<<"P for Professor."<<endl;
    cout<<"S for Student."<<endl;
    cout<<"$ for Money."<<endl;
    cout<<"L for Laptop."<<endl;
    cout<<"T for Pink tie."<<endl;
    cout<<"The format of the input should be 'name pieceSymbol' followed by enter."<<endl;
    int acc=0;
    while(1){
        if (acc==num){
            cout<<"Game Starts."<<endl;
            return num;
        }
        getline(cin,s);
        stringstream ss(s);
        string name;
        ss>>name;
        bool error=false;
        if(ss>>tmp){
           if(tmp=="G"||tmp=="B"||tmp=="D"||tmp=="P"||tmp=="S"||tmp=="$"||tmp=="L"||tmp=="T"){
               for(int i=0;game->loopPlayer(i)!=NULL;i++){
                   if(name==game->loopPlayer(i)->getName()){
                       cout<<"Invalid input, "<<name<<" already exists."<<endl;
                       error=true;
                       break;
                   }
                   if(tmp==game->loopPlayer(i)->getPiece()){
                       cout<<"Invalid input, "<<tmp<<" already exists."<<endl;
                       error=true;
                       break;
                   }
               }
               if(error) continue;    // duplicate name or piece occured
               acc++;
               game->init(game->createPlayer(name, tmp),acc-1);
               td->addPlayer(game->loopPlayer(acc-1));
               cout<<tmp<<" is created."<<endl;
               
               continue;
            }
        }
        cout<<"Invalid input."<<endl;
        cout<<"The format of the input should be 'name pieceSymbol' followed by enter."<<endl;
        continue;
        }
}



// ----------------------------------

bool Controller::improve(Player* p, string s){
    string building;
    string action;
    stringstream ss(s);
    ss>>s;
    if(!(ss>>building)||!(ss>>action)||(action!="buy"&&action!="sell")){  // pre-condition check
        cout<<"Invalid input."<<endl;
        cout<<"Tips: to buy or sell improvements, enter 'improve <building> buy/sell'."<<endl;
        return false;
    }
    Building* b=game->getBuilding(building);
    if(b==NULL){
        cout<<"invalid input.  "<<building<<" is not a building"<<endl;
        return false;
    }
    if(b->getOwner()!=p){
        cout<<"Can not improve a building that does not belong to you."<<endl;
        return false;
    }
    if(action=="buy"){    // buying improvement
        return b->improve();
    }
    if(action=="sell"){   // sell improvement
        return b->deImprove();
    }
    cerr<<"an error has occured, reached end of improve!"<<endl;
    return false;
}

//////////////////////

bool Controller::mortgage(Player* p, string s){
    string building;
    stringstream ss(s);
    ss>>s;
    if(!(ss>>building)){  // pre-condition check
        cout<<"Invalid input."<<endl;
        cout<<"Hint: to mortgage, enter 'mortgage <building>'."<<endl;
        return false;
    }
    Building* b=game->getBuilding(building);
    if(b==NULL){
        cout<<"Invalid input.  "<<building<<" is not a building"<<endl;
        return false;
    }
    if(b->getOwner()!=p){
        cout<<"Invalid input.  Can not mortgage a building that does not belong to you."<<endl;
        return false;
    }
    return b->mortgage();
}


////////////////////////

bool Controller::unmortgage(Player* p, string s){
    string building;
    stringstream ss(s);
    ss>>s;
    if(!(ss>>building)){  // pre-condition check
        cout<<"Invalid input."<<endl;
        cout<<"Hint: to unmortgage, enter 'unmortgage <building>'."<<endl;
        return false;
    }
    Building* b=game->getBuilding(building);
    if(b==NULL){
        cout<<"Invalid input.  "<<building<<" is not a building"<<endl;
        return false;
    }
    if(b->getOwner()!=p){
        cout<<"Invalid input.  Can not unmortgage a building that does not belong to you."<<endl;
        return false;
    }
    return b->unmortgage();
}

//---------------------------------

bool Controller::bankrupt(Player* p, Player* debtor){
    
    if(debtor==NULL){               // owe bank
        p->bankrupt();
        td->print();
        return true;
    }
    int payment=p->bankrupt(debtor);       // owe debtor
    td->print();
    if(winner()!=NULL) return true;   // the debtor won the game
    if(payment==0)return true;
    string s;
    stringstream ss;
    string tmp;
    while(debtor->getMoney()<payment){
        cout<<"A message for "<<debtor->getName()<<": You need to pay a total of $"<<payment;
        cout<<" for the unmortgaged building(s) you received from "<<p->getName()<<endl;
        cout<<"You currently have $"<<debtor->getMoney()<<" cash on you."<<endl;
        getline(cin,s);
        stringstream ss(s);
        ss>>tmp;
        if(tmp=="trade"){
            trade(debtor,s);
            continue;
        }
        if(tmp=="mortgage"){
            mortgage(p,s);
            continue;
        }
        if(tmp=="improve"){
            if(!(ss>>tmp)||!(ss>>tmp)){
                cout<<"Invalid input."<<endl;
                cout<<"Tips: to sell improvements, enter 'improve <building> sell'."<<endl;
                continue;
            }
            if(tmp=="buy"){
                cout<<"NO NO NO, you can not buy improvements now, pay your debt first."<<endl;
                continue;
            }
            improve(debtor, s);
        }
        if(tmp=="bankrupt"&&debtor->getMoney()<payment){
            debtor->bankrupt();
            td->print();
            return true;
        }
        if(tmp=="assets"){
            td->printAssets(debtor);
            continue;
        }
        else{
            cout<<"I don't know what you just entered, but I say it is not allowed."<<endl;
        }
    }
    
    debtor->addMoney(payment*-1);
    cout<<"A message for "<<debtor->getName()<<": You've paid a total of $"<<payment;
    cout<<" for the unmortgaged building(s) you received from "<<p->getName()<<endl;
    cout<<"If you choose to unmortaged these buildings now you don't pay the extra 10%."<<endl;
    
    while(1){
        cout<<"If you are ready to proceed, enter 'next'."<<endl;
        getline(cin,s);
        stringstream ss(s);
        ss>>tmp;
        if(tmp=="unmortgage"){
            unmortgage(debtor,s);
            continue;
        }
        if(tmp=="trade"){
            trade(debtor,s);
            continue;
        }
        if(tmp=="mortgage"){
            mortgage(p,s);
            continue;
        }
        if(tmp=="improve"){
            if(!(ss>>tmp)||!(ss>>tmp)){
                cout<<"Invalid input."<<endl;
                cout<<"Tips: to sell improvements, enter 'improve <building> sell'."<<endl;
                continue;
            }
            if(tmp=="buy"){
                cout<<"NO, you can not buy improvements now, pay your debt first.  Nice try!"<<endl;
                continue;
            }
            improve(debtor, s);
        }
        if(tmp=="assets"){
            td->printAssets(debtor);
            continue;
        }
        if(tmp=="next"){
            debtor->resetMortgage();
            return true;
        }
        else{
            cout<<"Invalid inputs."<<endl;
        }
    }
}

// --------------------------------------

bool Controller::trade(Player* p, string s){
    stringstream ss(s);
    ss>>s;
    string name;
    string give;
    string receive;
    int money;

    if(!(ss>>name)||!(ss>>give)||!(ss>>receive)){     // check for valid input startd here
        cout<<"Invalid input"<<endl;
        cout<<"Hint: to trade, enter 'trade <name> <give> <receive>'."<<endl;

        return false;
    }
    if(game->getPlayer(name)==NULL){
        cout<<"Trade is rejected.  "<<name<<" is not a valid player."<<endl;
        return false;
    }
    if(p->getName()==name){
        cout<<"Trade is rejected.  You can't trade with yourself."<<endl;
        return false;
    }                                             //check for valid input ends here
  
    
    
    ///////////////////////
    ss.str("");
    ss.clear();
    ss<<give;
    if(ss>>money){                              // give is money
        ss.str("");
        ss.clear();
        ss<<receive;
        int i;
        if(ss>>i){
            cout<<"Trade is rejected.  Cannot trade money for money."<<endl;
            return false;
        }
        if(game->getBuilding(receive)==NULL){
            cout<<"Invalid input, "<<receive<<" is not a building."<<endl;
            return false;
            
        }
        Building* b=game->getBuilding(receive);
        if((b->getOwner()->getName())!=name){
            cout<<"Trade is rejected. "<<receive<<" does not belong to "<<name<<"."<<endl;
            return false;
        }
        if(!(game->getBuilding(receive)->canTrade())){
            cout<<"Trade is rejected.  "<<receive<<" is not valid for trading."<<endl;
            return false;
        }
        if(money<0){
            cout<<"Can not trade with negtive amount of money."<<endl;
            return false;
        }
        if(p->getMoney()<money){
            cout<<"Trade is rejected.  You don't have as much money as you offer."<<endl;
            return false;
        }
        cout<<"A message for "<<name<<": "<<p->getName();
        cout<<" wants to give you "<<give<<" for "<<receive<<"."<<endl;
        cout<<"Press Y to accept this offer, or press N to deny."<<endl;
        while(getline(cin,s)){
            if(s!="Y" && s!="y" && s!="n" && s!="N"){
                cout<<"Invalid input.  Please try again."<<endl;
                cout<<"Press Y to accept this offer, or press N to deny."<<endl;
                continue;
            }
            if(s=="n"||s=="N"){
                cout<<name<<" has rejected the trade"<<endl;
                return false;
            }
            else{
                p->addMoney(money*-1);
                b->setOwner(p);
                game->getPlayer(name)->addMoney(money);
                td->print();
                cout<<"Trade accepted by "<<name<<"."<<endl;
                return true;
            }
        }
        cerr<<"-------------ERROR: reached end of trade give money"<<endl;
    }
    
    
    //////////////////
    ss.str("");
    ss.clear();
    ss<<receive;
        if(ss>>money){                        // give is property, receive is money
            if(game->getBuilding(give)==NULL){
                cout<<"Invalid input, "<<give<<" is not a building."<<endl;
                return false;
                
            }
            Building* b=game->getBuilding(give);
            if((b->getOwner())!=p){
                cout<<"Trade is rejected. "<<give<<" does not belong to "<<name<<"."<<endl;
                return false;
            }
            if(!(game->getBuilding(give)->canTrade())){
                cout<<"Trade is rejected.  "<<give<<" is not valid for trading."<<endl;
                return false;
            }
            if(game->getPlayer(name)->getMoney()<money){
                cout<<"Trade is rejected.  "<<name<<" don't have as much money as you ask."<<endl;
                return false;
            }
            if(money<0){
                cout<<"Can not trade with negtive amount of money."<<endl;
                return false;
            }
            cout<<"A message for "<<name<<": "<<p->getName();
            cout<<" wants to give you "<<give<<" for "<<receive<<"."<<endl;
            cout<<"Press Y to accept this offer, or press N to deny."<<endl;
            string s;
            while(getline(cin,s)){
                if(s!="Y" && s!="y"&&s!="n"&&s!="N"){
                    cout<<"Invalid input.  Please try again."<<endl;
                    cout<<"Press Y to accept this offer, or press N to deny."<<endl;
                    continue;
                }
                if(s=="n"||s=="N"){
                    cout<<name<<" has rejected the trade"<<endl;
                    return false;
                }
                else{
                    game->getPlayer(name)->addMoney(money*-1);
                    b->setOwner(game->getPlayer(name));
                    p->addMoney(money);
                    td->print();
                    cout<<"Trade accepted by "<<name<<"."<<endl;
                    return true;
                }
            }
            cerr<<"-------------ERROR: reached end of trade receive money"<<endl;
        }
    
    /////////////////////
    
        if(true){                                   // both give and receive are properties
            if(game->getBuilding(give)==NULL){
                cout<<"Invalid input, "<<give<<" is not a building."<<endl;
                return false;
                
            }
            Building* b=game->getBuilding(give);
            if((b->getOwner())!=p){
                cout<<"Trade is rejected. "<<give<<" does not belong to you."<<endl;
                return false;
            }
            if(!(game->getBuilding(give)->canTrade())){
                cout<<"Trade is rejected.  "<<give<<" is not valid for trading."<<endl;
                return false;
            
            }
            if(game->getBuilding(receive)==NULL){
                cout<<"Invalid input, "<<receive<<" is not a building."<<endl;
                return false;
                
            }
            Building* bb=game->getBuilding(receive);
            if((bb->getOwner()->getName())!=name){
                cout<<"Trade is rejected. "<<receive<<" does not belong to "<<name<<"."<<endl;
                return false;
            }
            if(!(game->getBuilding(receive)->canTrade())){
                cout<<"Trade is rejected.  "<<receive<<" is not valid for trading."<<endl;
                return false;
            }
            cout<<"A message for "<<name<<": "<<p->getName();
            cout<<" wants to give you "<<give<<" for "<<receive<<"."<<endl;
            cout<<"Press Y to accept this offer, or press N to deny."<<endl;
            string s;
            while(getline(cin,s)){
                if(s!="Y" && s!="y"&&s!="n"&&s!="N"){
                    cout<<"Invalid input.  Please try again."<<endl;
                    cout<<"Press Y to accept this offer, or press N to deny."<<endl;
                    continue;
                }
                if(s=="n"||s=="N"){
                    cout<<name<<" has rejected the trade"<<endl;
                    return false;
                }
                else{
                    
                    b->setOwner(game->getPlayer(name));
                    bb->setOwner(p);
                    cout<<"Trade accepted by "<<name<<"."<<endl;
                    return true;
                }
            }
        }

                                                // falls in hell, error occured
        cerr<<"SYSTEM ERROR: trade error has occured, reached end of line."<<endl;
        return false;
    
}

// ----------------------------------

int Controller:: tuition(Player* p){
    cout<<"It's time to pay your tuition, you can either pay $300 or 10% or your ";
    cout<<"total wealth, which is: "<<p->getTotal()/10<<endl;
    
    string s;
    stringstream ss;
    string tmp;
    bool noMoney=false;
    bool no300=false;
    while(1){
        cout<<"Enter 1 for the first option, 2 for the second."<<endl;
        cout<<"If you are short on cash, you can trade, sell improvemnts, or mortagage ";
        cout<<"your buildings."<<endl;
        getline(cin,s);
        stringstream ss(s);
        ss>>tmp;
        if(p->getMoney()<300)noMoney=true;   // this is so cool, you can cheat in here!!!
        if(p->getMoney()<(p->getTotal()/10))no300=true;
        if(tmp=="1"||tmp=="2"){
            if(tmp=="2"&&noMoney){
                cout<<"Invalid option, you don't have enough money."<<endl;
                continue;
            }
            if(tmp=="1"&&no300){
                cout<<"Invalid option, you don't have enough money."<<endl;
                continue;
            }
            if(tmp=="1")p->addMoney(-300);
            if(tmp=="2")p->addMoney(p->getTotal()/10);
            cout<<"Good, you've paid your tuition.  Enjor your next semaster."<<endl;
            return 1;
        }
        if(tmp=="bankrupt"){
            if(noMoney&&no300){
                bankrupt(p, NULL);
                return 0;
            }
            cout<<"You can't do that since you do have enough to pay your tuition."<<endl;
            continue;
        }
        if(tmp=="trade"){
            if(noMoney&&no300){
                trade(p,s);
                continue;
            }
            cout<<"You can't do that since you do have enough to pay your tuition."<<endl;
            continue;
        }
        if(tmp=="mortgage"){
            if(noMoney&&no300){
                mortgage(p,s);
                continue;
            }
            cout<<"You can't do that since you do have enough to pay your tuition."<<endl;
            continue;
        }
        if(tmp=="improve"){
            if(!(ss>>tmp)||!(ss>>tmp)){
                cout<<"Invalid input."<<endl;
                cout<<"Tips: to sell improvements, enter 'improve <building> sell'."<<endl;
                continue;
            }
            if(tmp=="buy"){
                cout<<"NO, you can not buy improvements now, pay your debt first.  Nice try!"<<endl;
                continue;
            }
            if(noMoney&&no300){
                improve(p, s);
                continue;
            }
            cout<<"You can't do that since you do have enough to pay your tuition."<<endl;
            continue;
        }
        if(tmp=="assets"){
            td->printAssets(p);
            continue;
        }
        else{
            cout<<"Invalid input."<<endl;
            continue;
        }
    }
}

// -------------------------

int Controller::payDebt(Player* p, Player* debtor, const int debt){
    if(debtor==NULL){
        cout<<"You need to pay $"<<debt<<" to the school."<<endl;
    }
    else{
        cout<<"You need to pay $"<<debt<<" to "<<debtor->getName()<<"."<<endl;
    }
    string s;
    stringstream ss;
    string tmp;
    bool noMoney=false;
    while(1){
        cout<<"Enter 'pay' to pay your debt: $ "<<debt<<endl;
        getline(cin,s);
        stringstream ss(s);
        ss>>tmp;
        if(p->getMoney()<debt)noMoney=true;
        if(tmp=="pay"){
            if(noMoney){
                cout<<"Sorry, you don't have enough money."<<endl;
                continue;
            }
            p->addMoney(debt*-1);
            if(debtor!=NULL)debtor->addMoney(debt);
            cout<<"Thank you for your payment."<<endl;
            return 1;
        }
        if(tmp=="bankrupt"){
            if(noMoney){
                bankrupt(p, debtor);
                return 0;
            }
            cout<<"You can't do that since you do have enough to pay your debt."<<endl;
            continue;
        }
        if(tmp=="trade"){
            if(noMoney){
                trade(p,s);
                continue;
            }
            cout<<"You can't do that since you do have enough to pay your debt."<<endl;
            continue;
        }
        if(tmp=="mortgage"){
            if(noMoney){
                mortgage(p,s);
                continue;
            }
            cout<<"You can't do that since you do have enough to pay your debt."<<endl;
            continue;
        }
        if(tmp=="improve"){
            if(!(ss>>tmp)||!(ss>>tmp)){
                cout<<"Invalid input."<<endl;
                cout<<"Tips: to sell improvements, enter 'improve <building> sell'."<<endl;
                continue;
            }
            if(tmp=="buy"){
                cout<<"NO, you can not buy improvements now, pay your debt first."<<endl;
                continue;
            }
            if(noMoney){
                improve(p, s);
                continue;
            }
            cout<<"You can't do that since you do have enough to pay your debt."<<endl;
            continue;
        }
        if(tmp=="assets"||tmp=="asset"){
            td->printAssets(p);
            continue;
        }
        else{
            cout<<"Invalid input."<<endl;
            continue;
        }
    }
}

// -------------------------

int Controller:: auction(Player* p, Building* b){
    int bid=b->getValue();
    string s;
    stringstream ss;
    string tmp;
    if(p!=NULL){
        cout<<b->getName()<<" has no owner, you can purchase it for: $"<<b->getValue()<<endl;
        bool noMoney=false;
        while(1){
            cout<<"Enter 'buy' to purchase or enter 'pass' to continue."<<endl;
            getline(cin,s);
            stringstream ss(s);
            ss>>tmp;
            if(p->getMoney()<bid)noMoney=true;
            if(tmp=="pass")break;
            if(tmp=="buy"){
                if(noMoney){
                    cout<<"Sorry, you don't have enough money."<<endl;
                    continue;
                }
                p->addMoney(bid*-1);
                b->setOwner(p);
                cout<<"Congratulations, "<<b->getName()<<" is yours!"<<endl;
                return 1;
            }
            if(tmp=="bankrupt"){
                cout<<"Don't be a chicken, there is no need to bankrupt!"<<endl;
                continue;
            }
            if(tmp=="trade"){
                if(noMoney){
                    trade(p,s);
                    continue;
                }
                cout<<"You can't do that since you do have enough to buy it."<<endl;
                continue;
            }
            if(tmp=="mortgage"){
                if(noMoney){
                    mortgage(p,s);
                    continue;
                }
                cout<<"You can't do that now."<<endl;
                continue;
            }
            if(tmp=="improve"){
                if(!(ss>>tmp)||!(ss>>tmp)){
                    cout<<"Invalid input."<<endl;
                    cout<<"Tips: to sell improvements, enter 'improve <building> sell'."<<endl;
                    continue;
                }
                if(tmp=="buy"){
                    cout<<"NO, you can not do that now."<<endl;
                    continue;
                }
                if(noMoney){
                    improve(p, s);
                    continue;
                }
                cout<<"You can't do that now."<<endl;
                continue;
            }
            if(tmp=="assets"){
                td->printAssets(p);
                continue;
            }
            else{
                cout<<"Hey, quit fooling around, other players are waiting."<<endl;
                continue;
            }
        }
        cout<<"Since you choose to pass, "<<b->getName()<<" will be auctioned."<<endl;
    }
    cout<<"Auction of "<<b->getName()<<" begins!"<<endl;
    string bidder="None";
    for(int i=0; i<game->getPlayerSum();i++){
        game->loopPlayer(i)->setAuction(true);
    }
    Player* currentTurn=NULL;
    while(1){
        if(currentTurn==NULL){
            currentTurn=game->loopPlayer(0);
        }
        else if(currentTurn->getID()==(game->getPlayerSum()-1)){
            currentTurn=game->loopPlayer(0);
        }
        else {
            currentTurn=game->loopPlayer(currentTurn->getID()+1);
        }
        for(int i=0; i<game->getPlayerSum();i++){  // whether none wants it
            if(game->loopPlayer(i)->getAuction()==true)break;
            if(i+1==game->getPlayerSum()){
                cout<<"It seems none wants "<<b->getName()<<".  ";
                cout<<" It remains a property of UW."<<endl;
                return 0;
            }
        }
        if(currentTurn->getAuction()==false)continue;  // whether the currentTurn is valid Player
        if(bidder==currentTurn->getName()){
            cout<<"The winner of this auction is "<<bidder<<" ."<<endl;
            cout<<"A message for "<<bidder<<": "<<"Please pay: $"<<bid<<endl;
            payDebt(currentTurn, NULL, bid);
            if(currentTurn->getStatus()!=-1){
                currentTurn->addMoney(bid*-1);
                b->setOwner(currentTurn);
            }
            return 1;
        }
        cout<<"The current bid is: $"<<bid<<endl;
        cout<<"Highest bidder: "<<bidder<<endl;
        cout<<currentTurn->getName()<<"'s turn.  Either enter 'raise #' ";
        cout<<"where '#' is the amount you wish to raise,";
        cout<<" or enter 'pass' to withdraw for this auction."<<endl;
        while(1){
            getline(cin,s);
            stringstream ss(s);
            ss>>tmp;
            if(tmp=="pass"){
                currentTurn->setAuction(false);
                break;
            }
            if(tmp=="raise"){
                int i;
                if(ss>>i&&i>0){
                    bid=i+bid;
                    bidder=currentTurn->getName();
                    break;
                }
                cout<<"Invalid amount to raise."<<endl;
            }
            else cout<<"Invalid input, please be serious."<<endl;
        }
    }
}

// -------------------------

int Controller:: prisonBreak(Player* p,const int test=0){ // return 0 if fail, return 1 for ready to roll, >1 if
                                         // already rolled
    int turn=p->getStatus();
    stringstream ss;
    string s;
    string tmp;
    if (turn==1||turn==2){
        if(turn==1){
            cout<<"This is you first turn in DC Tims Line.  "<<endl;
        }
        else{
            cout<<"This is you second turn in DC Tims Line.  "<<endl;
        }
        cout<<"You can choose to roll a double, pay $50, ";
        cout<<"or use a Roll Up the Rim cup to move On."<<endl;
        cout<<"Please make you decision by entering: 'roll', 'pay', or use."<<endl;
        while(1){
            getline(cin,s);
            ss.clear();
            ss.str(s);
            ss>>tmp;
            if(tmp=="pay"){
                if(p->getMoney()>=50){
                    p->addMoney(-50);
                    p->setStatus(0);
                    cout<<"Congratulations, by spending 50 on diluted coffee, ";
                    cout<<"you are FREE.  Please continue your turn."<<endl;
                    return 1;
                }
                cout<<"Sorry, You don't even have $50 to buy your own freedom.  ";
                cout<<"Try something else."<<endl;
                continue;
            }
            if(tmp=="use"){
                if(p->getCup()>0){
                    p->setCup(p->getCup()-1);   // possible error regarding cups
                    cout<<"You consumed a Roll Up the Rim cup."<<endl;
                    cout<<"Congratulations, you are FREE.  Please continue your turn."<<endl;
                    p->setStatus(0);
                    return 1;
                }
                cout<<"Unfortunately, you don't even have a cup.  Try something else."<<endl;
                continue;
                
            }
            if(tmp=="roll"){
                
                int die1=0;
                int die2=0;
                ss.clear();
                ss.str(s);
                ss>>tmp;
                if(test==1&&ss>>die1&&ss>>die2){
                    if(die1<1||die1>6||die2<1||die2>6){
                        cout<<"Even in test mode you can't roll those numbers."<<endl;
                        continue;
                    }
                    
                    game->testRoll(die1,die2);
                }
                else{
                    ss.clear();
                    ss.str(s);
                    ss>>tmp;
                    if(ss>>tmp){
                        cout<<"Invalid input, please try again."<<endl;
                        continue;
                    }
                    else game->roll();
                }
                cout<<game->die()<<endl;
                if(game->isPair()){
                    p->setStatus(0);
                    cout<<"Wow, you just rolled a doulbe!  You are FREE."<<endl;
                    return game->getSum();
                }
                cout<<"Since you didn't roll a double, you have to stay at";
                cout<<" DC Tims Line for one more turn."<<endl;
                p->setStatus(turn+1);
                return 0;
            }
            else{
                cout<<"Face the reality pal, you are not going anywhere until you "<<endl;
                cout<<"roll a double, pay $50, or use a Roll Up the Rim cup."<<endl;
                continue;
            }
        }
    }
    bool rolled=false;
    if(turn==3){
        cout<<"This is you third turn in DC Tims Line.  "<<endl;
        cout<<"You can choose to roll a double, pay $50, ";
        cout<<"or use a Roll Up the Rim cup to move On."<<endl;
        cout<<"Please make you decision by entering: 'roll', 'pay', or use."<<endl;
        bool noMoney=false;
        bool noCup=false;
        if(p->getCup()==0)noCup=true;
        if(p->getMoney()<50)noMoney=true;
        while(1){
            getline(cin,s);
            ss.clear();
            ss.str(s);
            ss>>tmp;
            if(tmp=="pay"){
                if(p->getMoney()>=50){
                    p->addMoney(-50);
                    p->setStatus(0);
                    cout<<"Congratulations, by spending 50 on diluted coffee, ";
                    cout<<"you are FREE.  Please continue your turn."<<endl;
                    if(rolled)return game->getSum();
                    return 1;
                }
                cout<<"Sorry, You don't even have $50 to buy your own freedom.  ";
                cout<<"Try something else."<<endl;
                continue;
                }
                if(tmp=="use"){
                if(p->getCup()>0){
                    p->setCup(p->getCup()-1);   // possible error regarding cups
                    cout<<"You consumed a Roll Up the Rim cup."<<endl;
                    cout<<"Congratulations, you are FREE.  Please continue your turn."<<endl;
                    p->setStatus(0);
                    if(rolled)return game->getSum();
                    return 1;
                }
                cout<<"Unfortunately, you don't even have a cup.  Try something else."<<endl;
                continue;
                
            }
            if(tmp=="roll"){
                if(rolled==true){
                    cout<<"You've already failed to roll a double three times, either pay $50, use ";
                    cout<<"a Roll Up the Rim cup, or declare bankruptcy."<<endl;
                    continue;
                }
                string tmp;
                int die1=0;
                int die2=0;
                ss.clear();
                ss.str(s);
                ss>>tmp;
                if(test==1&&ss>>die1&&ss>>die2){
                    if(die1<1||die1>6||die2<1||die2>6){
                        cout<<"Even in test mode you can't roll those numbers."<<endl;
                        continue;
                    }
                    
                    game->testRoll(die1,die2);
                }
                else{
                    ss.clear();
                    ss.str(s);
                    ss>>tmp;
                    if(ss>>tmp){
                        cout<<"Invalid input, please try again."<<endl;
                        continue;
                    }
                    else game->roll();
                }
                rolled=true;
                cout<<game->die()<<endl;
                if(game->isPair()){
                    p->setStatus(0);
                    cout<<"Wow, you just rolled a doulbe!  You are FREE."<<endl;
                    return game->getSum();
                }
                cout<<"Since you didn't roll a double for the third time you are doomed."<<endl;
                continue;
            }
            
            if(tmp=="trade"&&noMoney&&noCup&&rolled){
                trade(p,s);
                continue;
            }
            if(tmp=="mortgage"&&noMoney&&noCup&&rolled){
                mortgage(p,s);
                continue;
            }
            if(tmp=="improve"&&noMoney&&noCup&&rolled){
                if(!(ss>>tmp)||!(ss>>tmp)){
                    cout<<"Invalid input."<<endl;
                    cout<<"Tips: to sell improvements, enter 'improve <building> sell'."<<endl;
                    continue;
                }
                if(tmp=="buy"){
                    cout<<"NO, you can not buy improvements now, pay your debt first.  Nice try!"<<endl;
                    continue;
                }
                improve(p, s);
            }
            if(tmp=="assets"&&noMoney&&noCup&&rolled){
                td->printAssets(p);
                continue;
            }
            
            if(tmp=="bankrupt"){
            if(noMoney&&noCup&&rolled){
                    cout<<"Oh, thats unfortuante, you delcared bankruptcy."<<endl;
                    bankrupt(p,NULL);
                    return 0;
                }
                cout<<"There is still hope, you are not eligible to bankrupt."<<endl;
                continue;
            }
            else{
                cout<<"Face the reality pal, you are not going anywhere until you "<<endl;
                cout<<"roll a double, pay $50, use a Roll Up the Rim cup, ";
                cout<<"or declare bankruptcy"<<endl;
                continue;
            }
        }
    }
    cerr<<"SYSTEM ERROR:  reached end of line of prison break."<<endl;
    return -100;
}


// -----------------------------

bool Controller:: rareCup(){
    int pool[]={1,0,0,0,0,0,0,0,0,0};
    srand(time(NULL));
    if(pool[rand()%10]==1){
        if(pool[rand()%10]==1)return true;
    }
    return false;
}

    
    
    
// -----------------------------

Player* Controller::winner(){
    int count=0;
    Player* candidate;
    for(int i=0; i<game->getPlayerSum();i++){
        if(game->loopPlayer(i)->getStatus()!=-1){
            candidate=game->loopPlayer(i);
            count++;
        }
        if(count>=2)return NULL;
    }
    return candidate;
}

    // --------------------------
    
void Controller:: play(const int test=0){
    if(game==NULL){
        cout<<"Starting a new game starts."<<endl;
        init();
    }
    int id=-1;
    stringstream ss;
    string s;
    string tmp;
    td->print();               // print board 1st
    while(winner()==NULL){
        int DCstatus;
        int result=0;
        id++;
        if(id==game->getPlayerSum())id=0;// loop for player turns
        bool fromDC=false;
        bool rolled=false;
        Player* player=game->getPlayer(id);
        if (player->getStatus()<0)break;
        cout<<player->getName()<<"'s turn."<<endl;
        if(player->getStatus()>0){
            DCstatus=prisonBreak(player,test);
            if (DCstatus==0)continue;     // prison break fails
            else if(DCstatus>1){
                rolled=true;
                fromDC=true;
                if((DCstatus+player->getPosition())>39){
                    DCstatus=DCstatus-40;
                    game->getBuilding(0)->todo(player);
                }
                player->setPosition(DCstatus+player->getPosition());
                td->print();
                cout<<"The sum of the dice from your last attempt rolling out from DC Tims Line ";
                cout<<"is: "<<game->getSum()<<endl;
                cout<<"You used it as your current turn's rolling result."<<endl;
                result=game->getBuilding(player->getPosition())->todo(player);
                td->print();

            }
            
        }
        while(1){                // loop for actions
            if(player->getStatus()==-1)break;
            if(fromDC)tmp="roll";
            else{
                tmp="";
                getline(cin,s);
                stringstream ss(s);
                ss>>tmp;
            }
            if (tmp=="next"){
                if(!rolled){
                    cout<<"Action not allowed.  You haven't rolled yet."<<endl;
                    
                    continue;
                }
                if(id+1==game->getPlayerSum()){
                    if(game->loopPlayer(0)->getStatus()==-1)id++;
                }
                else if(game->loopPlayer(id+1)->getStatus()==-1)id++;
                break;
            }
            else if(tmp=="trade"){
                trade(player, s);
                continue;
            }
            else if(tmp=="improve"){
                improve(player,s);
                continue;
            }
            else if(tmp=="mortgage"){
                mortgage(player, s);
                continue;
                
            }
            else if(tmp=="unmortgage"){
                unmortgage(player, s);
                continue;
                
            }
            else if(tmp=="quit"){
                cout<<"You quit the game."<<endl;
                return;
            }
            else if(tmp=="assets"||tmp=="asset"){
                td->printAssets(player);
                continue;
            }
            else if(tmp=="save"){
                if(rolled){
                    cout<<"Game not saved.  You can only do that before you roll."<<endl;
                    continue;
                }
                save(s,player);
                continue;
            }
            else if(tmp=="roll"){
                int roll=0;
                if(fromDC);
                else if(rolled){
                    cout<<"Can't do that, already rolled."<<endl;
                    continue;
                }
                else{
                    int acc=1;  // row of doubles
                    while(1){
                        if(acc==4){
                            player->setPosition(10);
                            player->setStatus(1);
                            cout<<"You rolled 3 doubles in a row, how luncky.  ";
                            cout<<"As a result, you are invited to DC Tims Line for their";
                            cout<<" diluted coffee."<<endl;
                            roll=-1;
                            break;
                        }
                        if(acc>1){
                            roll=0;
                            getline(cin,s);
                            ss.clear();
                            ss.str(s);
                            ss>>tmp;
                            if(tmp!="roll"){
                                cout<<"Invalid input, at this moment you can only roll, not even rock."<<endl;
                                continue;
                            }
                        }
                        int die1=0;
                        int die2=0;
                        if(roll==-2&&acc<=1)getline(cin,s);
                        ss.clear();
                        ss.str(s);
                        ss>>tmp;
                        if(test==1&&ss>>die1&&ss>>die2){
                            if(die1<1||die1>6||die2<1||die2>6){
                                cout<<"Even in test mode you can't roll those numbers."<<endl;
                                roll=-2;
                                continue;
                            }
                                
                            game->testRoll(die1,die2);
                        }
                        else{
                            ss.clear();
                            ss.str(s);
                            ss>>tmp;
                            if(ss>>tmp){
                                cout<<"Invalid input, please try again."<<endl;
                                roll=-2;
                                continue;
                            }
                            else game->roll();
                        }
                        roll=game->getSum();
                        cout<<game->die()<<endl;
                        if(!game->isPair()) break;
                        cout<<"You rolled a double, it's not getting you anywhere though, roll again."<<endl;
                        acc++;
                    }
                    if(roll==-1)break;
                    if(roll==-2)continue;
                }
                rolled=true;
                if(!fromDC){
                    if((roll+player->getPosition())>39){
                        roll=roll-40;
                        game->getBuilding(0)->todo(player);
                    }
                    player->setPosition(roll+player->getPosition());
                    td->print();
                    result=game->getBuilding(player->getPosition())->todo(player);
                    
                }
                fromDC=false;
                if (winner()!=NULL){     // game won
                    cout<<"The monopoly is "<<winner()->getName()<<"!"<<endl;
                    cout<<"Game Over!"<<endl;
                    return;
                }
                if (result==0)continue;
                if (result==10){  // send to DC
                    player->setPosition(10);
                    player->setStatus(1);
                    td->print();
                    cout<<"You are sent to DC Tims Line";
                    cout<<" for their";
                    cout<<" diluted coffee."<<endl;
                    break;
                }
                if(result==-10){   // send to OSAP
                    player->setPosition(0);  // position of OSAP
                    td->print();
                    cout<<"You are sent to Collect OSAP."<<endl;
                    game->getBuilding(0)->todo(player);
                    continue;
                }
                else{
                    roll=result;
                    if((roll+player->getPosition())<0){
                        roll=roll+40;
                        game->getBuilding(0)->todo(player);  // collect OSAP
                    }
                    player->setPosition(roll+player->getPosition());
                    int result=game->getBuilding(player->getPosition())->todo(player);
                    if(result==0)continue;
                    else{
                        cerr<<"-----------SYSTEM ERROR: reached the end of SLC conditions"<<endl;
                        return;
                    }
                }
            }
            cout<<"Invalid input, please try again."<<endl;
            continue;
        }
    }
    cout<<"The monopoly is "<<winner()->getName()<<"!"<<endl;
}
    


    

