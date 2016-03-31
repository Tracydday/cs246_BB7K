

#include <iostream>
#include "controller.h"
#include <cstring>

using namespace std;

int main(int argc, const char * argv[]) {
    Controller c;
    int test=0;
    bool loadResult=false;
    bool triedLoading=false;
    if(argc==3){
        if(0==(strcmp(argv[1],"-load"))){
            cout<<"Loading a saved game."<<endl;
            triedLoading=true;
            loadResult=c.load(argv[2]);
            
        }
        else if(0==(strcmp(argv[2],"-load"))){
            cout<<"Loading a saved game."<<endl;
            triedLoading=true;
            loadResult=c.load(argv[1]);
        }
        else cout<<"Invalid command line arguments."<<endl;
    }
    else if(argc==2){
        if(0==(strcmp(argv[1],"-test"))){
            cout<<"Test mode enabled."<<endl;
            test=1;
        }
        else cout<<"Invalid command line arguments."<<endl;
    }
    else if(argc==4){
        if((0==(strcmp(argv[1],"-test")))&&(0==(strcmp(argv[2],"-load")))){
            cout<<"Test mode enabled, and the game save will be loaded."<<endl;
            test=1;
            triedLoading=true;
            loadResult=c.load(argv[3]);
            
        }
        else if((0==(strcmp(argv[1],"-test")))&&(0==(strcmp(argv[3],"-load")))){
            cout<<"Test mode enabled, and the game save will be loaded."<<endl;
            test=1;
            triedLoading=true;
            loadResult=c.load(argv[2]);
            
        }
        else if((0==(strcmp(argv[2],"-test")))&&(0==(strcmp(argv[1],"-load")))){
            cout<<"Test mode enabled, and the game save will be loaded."<<endl;
            test=1;
            triedLoading=true;
            loadResult=c.load(argv[3]);
            
        }
        else if((0==(strcmp(argv[2],"-test")))&&(0==(strcmp(argv[3],"-load")))){
            cout<<"Test mode enabled, and the game save will be loaded."<<endl;
            test=1;
            triedLoading=true;
            loadResult=c.load(argv[1]);
            
        }
        else if((0==(strcmp(argv[3],"-test")))&&(0==(strcmp(argv[1],"-load")))){
            cout<<"Test mode enabled, and the game save will be loaded."<<endl;
            test=1;
            triedLoading=true;
            loadResult=c.load(argv[2]);
            
        }
        else if((0==(strcmp(argv[3],"-test")))&&(0==(strcmp(argv[2],"-load")))){
            cout<<"Test mode enabled, and the game save will be loaded."<<endl;
            test=1;
            triedLoading=true;
            loadResult=c.load(argv[1]);
            
        }
           
        else cout<<"Invalid command line arguments."<<endl;
    }
    else if(argc!=1) cout<<"Invalid command line arguments."<<endl;
    if(triedLoading==true&&loadResult==false){
        cout<<"Save file is invalid.  Game not loaded."<<endl;
        Controller sub;
        c=sub;
    }
    c.play(test);
}

