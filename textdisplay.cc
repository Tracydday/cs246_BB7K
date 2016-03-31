
#include "textdisplay.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const int row = 67;
const int col = 111;
const int total = 8;
const int member = 3;

TextDisplay::TextDisplay(){
    
    theDisplay = new char *[row];
    for (int i = 0; i < row; i++) {
        theDisplay[i] = new char[col];
        for(int j = 0;j < col ; j++){
            theDisplay[i][j]=' ';
        }
    }
    ifstream in;
     in.open("board.txt");
     string a;
     
     for(int i = 0; i<row; i++){
     getline(in,a);
     for(int j= 0; j<col;j++){
     theDisplay[i][j] = a[j];
     }
     }
    
     
       boardplayer = new char * [total];
    for (int i = 0; i < total; i++) {
        boardplayer[i] = new char [member];
        for (int j = 0; j < member; j++) {
            boardplayer[i][j] = 'f';
        }
    }
}

void TextDisplay::notify( Building*  b){
    // the position in 2d array.
    int row_i;
    int col_i;
    int row_mc;
    int col_m;
    int col_c;
    int pos = b->getPosition();
    if (pos == 1) {
        row_i = 61;
        col_i = 91;
        row_mc = 62;
        col_m = 91;
        col_c = 98;
    }
    else if(pos == 3){
        row_i = 61;
        col_i = 71;
        row_mc = 62;
        col_m = 71;
        col_c = 78;
        
    }
    else if(pos == 6){
        row_i = 61;
        col_i = 41;
        row_mc = 62;
        col_m = 41;
        col_c = 48;
        
    }
    else if(pos == 8){
        row_i = 61;
        col_i = 21;
        row_mc = 62;
        col_m = 21;
        col_c = 28;
    }
    else if(pos == 9){
        row_i = 61;
        col_i = 11;
        row_mc = 62;
        col_m = 11;
        col_c = 18;
    }
    else if(pos == 11){
        row_i = 55;
        col_i = 1;
        row_mc = 56;
        col_m = 1;
        col_c = 8;
        
    }
    else if(pos == 13){
        row_i = 43;
        col_i = 1;
        row_mc = 44;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 14){
        row_i = 37;
        col_i = 1;
        row_mc = 38;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 16){
        row_i = 25;
        col_i = 1;
        row_mc = 26;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 18){
        row_i = 13;
        col_i = 1;
        row_mc = 14;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 19){
        row_i = 7;
        col_i = 1;
        row_mc = 8;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 21){
        row_i = 1;
        col_i = 11;
        row_mc = 2;
        col_m = 11;
        col_c = 18;
    }
    else if(pos == 23){
        row_i = 1;
        col_i = 31;
        row_mc = 2;
        col_m = 31;
        col_c = 38;
    }
    else if(pos == 24){
        row_i = 1;
        col_i = 41;
        row_mc = 2;
        col_m = 41;
        col_c = 48;
    }
    else if(pos == 26){
        row_i = 1;
        col_i = 61;
        row_mc = 2;
        col_m = 61;
        col_c = 68;
    }
    else if(pos == 27){
        row_i = 1;
        col_i = 71;
        row_mc = 2;
        col_m = 71;
        col_c = 78;
    }
    else if(pos == 29){
        row_i = 1;
        col_i = 91;
        row_mc = 2;
        col_m = 91;
        col_c = 98;
    }
    else if(pos == 31){
        row_i = 7;
        col_i = 101;
        row_mc = 8;
        col_m = 101;
        col_c = 108;
    }
    else if(pos == 32){
        row_i = 13;
        col_i = 101;
        row_mc = 14;
        col_m = 101;
        col_c = 108;
    }
    else if(pos == 34){
        row_i = 25;
        col_i = 101;
        row_mc = 26;
        col_m = 101;
        col_c = 108;
    }
    else if(pos == 37){
        row_i = 43;
        col_i = 101;
        row_mc = 44;
        col_m = 101;
        col_c = 108;
    }
    else if(pos == 39){
        row_i = 55;
        col_i = 101;
        row_mc = 56;
        col_m = 101;
        col_c = 108;
    }
    
    else if(pos ==5){
        row_mc = 62;
        col_m = 51;
        col_c = 58;
    }
    else if(pos == 12){
        row_mc = 50;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 15){
        row_mc = 32;
        col_m = 1;
        col_c = 8;
    }
    else if(pos == 25){
        row_mc = 2;
        col_m = 51;
        col_c = 58;
    }
    else if(pos == 28){
        row_mc = 2;
        col_m = 81;
        col_c = 88;
    }
    else if(pos == 35){
        row_mc = 32;
        col_m = 101;
        col_c = 108;
    }
    
    
    char owner_name =' ';
    int statuts = b->getStatus(); //ownership(10 - no owner), level(0,1,2,3,4,5), mortgage(-1)
    string mort = "MORT:";
    int mlen = mort.length();
    string own = "Owner:";
    int ulen = own.length();
    
    if (statuts == -1) {
        if (b->getOwner() != NULL) {
            owner_name =b->getOwner()->getPiece()[0];
        }
        theDisplay[row_mc][col_c]=owner_name;
        for (int i = 0; i < mlen; i++) {
            theDisplay[row_mc][col_m+i] =mort[i];
        }
    }
    else if (statuts == 0){
        if (b->getOwner() != NULL) {
            owner_name =b->getOwner()->getPiece()[0];
        }
        
        theDisplay[row_mc][col_c]=owner_name;
        for (int i = 0; i < ulen; i++) {
            theDisplay[row_mc][col_m+i] = own[i];
        }
    }
    else if (statuts > 0 && statuts <= 5 ){
        if (b->getOwner() != NULL) {
            owner_name =b->getOwner()->getPiece()[0];
        }
        
        theDisplay[row_mc][col_c]=owner_name;
        for (int i = 0; i < ulen; i++) {
            theDisplay[row_mc][col_m+i] = own[i];
        }
        for (int j = 0; j < 5; j++) {
            theDisplay[row_i][col_i+j] = ' ';
        }
        for (int j = 0; j < statuts; j++) {
            theDisplay[row_i][col_i+j] = 'I';
        }
    }
    
}

int findrow(int pos){
    int row_p;
    if (pos >=0 && pos <=10) {
        row_p = 65;
    }
    else if (pos >=20 && pos <=30) {
        row_p = 5;
    }
    else if (pos == 11 || pos == 39){
        row_p = 59;
    }
    else if (pos == 12 || pos == 38){
        row_p = 53;
    }
    else if (pos == 13 || pos == 37){
        row_p = 47;
    }
    else if (pos == 14 || pos == 36){
        row_p = 41;
    }
    else if (pos == 15 || pos == 35){
        row_p = 35;
    }
    else if (pos == 16 || pos == 34){
        row_p = 29;
    }
    else if (pos == 17 || pos == 33){
        row_p = 23;
    }
    else if (pos == 18 || pos == 32){
        row_p = 17;
    }
    else if (pos == 19 || pos == 31){
        row_p = 11;
    }
    return row_p;
}

int findcol(int pos){
    int col_p;
    if (pos >=0 && pos <=10) {
        col_p = 101- pos*10;
    }
    else if (pos >=20 && pos <30) {
        col_p = 1 + pos%10*10;
    }
    else if (pos >= 11 && pos <= 19 ){
        col_p = 1;
    }
    else if (pos >= 30 || pos <= 39){
        col_p = 101;
    }
    return col_p;
}


void TextDisplay::addPlayer( Player *  p){
    int pos =p->getPosition();
    for (int i = 0; i < total; i++) {
        if(boardplayer[i][0] == 'f'){
            boardplayer[i][0]= p->getPiece()[0];
            
            if ( pos>=10) {
                boardplayer[i][1] = pos/10 + '0';
                boardplayer[i][2] = pos%10 + '0';
            }
            else if(pos < 10 && pos >=0){
                boardplayer[i][1] = pos + '0';
                boardplayer[i][2] = 'f';
            }
            break;
        }
    }
    if (pos == 0) {
        for (int j = 0; j < total; j++) {
            if (theDisplay[65][101 + j] == ' ') {
                theDisplay[65][101 + j] = p->getPiece()[0];
                break;
            }
        }
    }
    
    // loading a player, show the position on the theDisplay.
    else if (pos != 0){
        int row_p = findrow(pos);
        int col_p =findcol(pos);
        for (int i = 0 ; i < total; i++) {
            if (theDisplay[row_p][col_p+i] == ' ') {
                theDisplay[row_p][col_p+i] =  p->getPiece()[0];
                break;
            }
        }
    }
    
}

void TextDisplay::notify( Player*  p){
    int pos = 0;
    const char bu= 'f';
    char PlayerName = p->getPiece()[0];
    int status = p->getStatus();
    
    // find the previous position on boardplayer;
    
    for (int i = 0; i < total; i++) {
        if (boardplayer[i][0] == PlayerName) {
            if (boardplayer[i][2] == bu) {
                pos = boardplayer[i][1] - 48;
            }
            else if(boardplayer[i][2] != bu){
                pos = (boardplayer[i][1] - '0')*10 + (boardplayer[i][2] - '0');
            }
            break;
        }
    }
    // previous position and clear it on board;
        int row_p = findrow(pos);
        int col_p =findcol(pos);
        for (int i = 0 ; i < total; i++) {
            if (theDisplay[row_p][col_p+i] == p->getPiece()[0]) {
                theDisplay[row_p][col_p+i] = ' ';
                break;
            }
        }
    
        int rowPdc = 63;
        int colPdc =1;
        int row_t = 64;
        for (int i = 0 ; i < total; i++) {
            if (theDisplay[rowPdc][colPdc+i] == PlayerName) {
                theDisplay[rowPdc][colPdc+i] =  ' ';
                theDisplay[row_t][colPdc+i] = ' ';
                break;
            }
        }
    // set player's new position when status = 0;
    if (status == 0) {
        for (int i = 0; i < total; i++) {
            if (boardplayer[i][0] == PlayerName) {
                pos = p->getPosition();
                
                if ( pos >= 10) {
                    boardplayer[i][1] = (pos /10) +'0';
                    boardplayer[i][2] = (pos %10) + '0';
                    
                }
                boardplayer[i][1] = pos +'0';
                boardplayer[i][2] = 'f';
                break;
                
            }
        }
        int row_p = findrow(pos);
        int col_p =findcol(pos);
        for (int i = 0 ; i < total; i++) {
            if (theDisplay[row_p][col_p+i] == ' ') {
                theDisplay[row_p][col_p+i] =  PlayerName;
                break;
            }
        }
        
    }
    
    // player in DC Tims Line;
    else if (status >= 1 && status <= 3){
        for (int i = 0; i < total; i++) {
            if (boardplayer[i][0] == PlayerName) {
                pos = p->getPosition();
                if ( pos >= 10) {
                    boardplayer[i][1] = (pos /10) +'0';
                    boardplayer[i][2] = (pos %10) + '0';
                    break;
                }
            }
        }
        
        int rowPdc = 63;
        int colPdc =1;
        int row_t = 64;
        for (int i = 0 ; i < total; i++) {
            if (theDisplay[rowPdc][colPdc+i] == ' ') {
                theDisplay[rowPdc][colPdc+i] =  PlayerName;
                theDisplay[row_t][colPdc+i] = status+'0';
                break;
            }
        }
    }
    
}

void TextDisplay::print(){
    for (int i = 0; i < row; i++) {
        
        for (int j = 0; j < col; j++) {
            cout << theDisplay[i][j];
        }
        
        cout << endl;
    }
    
}

void TextDisplay::printAssets( Player*  p){
    vector<Building*> property = p->getProperty();
    int countProperty= 0;
   // int totalProValue = 0;
    cout << p->getName()<< ",Your total asserts:" <<endl;;
    cout << "Money: $" <<  p->getMoney() << endl;
    cout << "Cup: " << p->getCup() <<endl;
    cout << "Property:" <<endl;
    if (property.size() == 0) {
        cout << "You have 0 property" << endl;
    }
    else if(property.size() != 0){
        for (int i=0; i<property.size(); i++) {
            Building * tmp = property[i];
            cout<< "Property Name: "<< tmp->getName() << " Value: " << tmp->getValue() << " Status: " << tmp->getStatus()<< endl;
            //totalProValue += property[i]->getValue();
            countProperty++;
        }
        if (countProperty == 1) {
             cout << "You have: " << 1 << "property" << endl;
        }
        else if (countProperty > 1){
            cout << "You have: " << countProperty << " properties" << endl;
            
        }
    }
   
    
}


TextDisplay::~TextDisplay(){
    
    for (int i = 0; i < row; i++) {
        delete []theDisplay[i];
    }
    delete [] theDisplay;
    
    for (int j = 0; j< total; j++) {
        delete [] boardplayer[j];
    }
    delete []boardplayer;
    
    
}

