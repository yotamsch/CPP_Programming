#include "TournamentManager.h"
#include <iostream>
#include <string>
#include <string.h>
#include <dlfcn.h> 
#include <iostream> 
#include <list>
TournamentManager TournamentManager::theTournamentManager;


// size of buffer for reading in directory entries 
static unsigned int BUF_SIZE = 1024;

int main(int argc, char** argv){
    int numOfThreads = 4;
    std::string soFilesDirectory("./"); 

    FILE *dl;   // handle to read directory 
    std::list<void *> dl_list; // list to hold handles for dynamic libs 
    std::list<void *>::iterator itr; 
    void *dlib;
    char name[1024]; 
    
    if(argc<1){
        //TODO: announce error
    }
    if(argc == 3){
        //TODO: update soFilesDirectory and numOfThreads
        //assuming PATH IS IN argv[3] and number of threads is in argv[2]
        numOfThreads = std::stoi(argv[2]);
        soFilesDirectory.assign(argv[3]);
    }
    std::string command_str = "ls "+ soFilesDirectory + "*.so";  // command string to get dynamic lib names
    char in_buf[BUF_SIZE]; // input buffer for lib names 
    // get the names of all the dynamic libs (.so  files) in the current dir 
    dl = popen(command_str.c_str(), "r"); //this executes a command "ls"
    if(!dl){
        perror("popen");
        exit(-1);
    }
    while(fgets(in_buf, BUF_SIZE, dl)){
        // trim off the whitespace 
        char *ws = strpbrk(in_buf, " \t\n"); 
        if(ws) *ws = '\0';
        // append ./ to the front of the lib name
        sprintf(name, "./%s", in_buf);
        TournamentManager::getSoFilesNames().push_back(name);
    }
    if(TournamentManager::getSoFilesNames().size() <= 1 ){
        //TODO: print usage msg accordingly, "not enough competitors"
        return(-1);
    }
    for(int i = 0; i < TournamentManager::getSoFilesNames().size(); i++){
        dlib = dlopen(TournamentManager::getSoFilesNames()[i].c_str(), RTLD_NOW);
        if(dlib == NULL){
            std::cerr << dlerror() << std::endl; 
            return(-1);
        }
        dl_list.insert(dl_list.end(), dlib);
    }

    TournamentManager::getTournamentManager().run();
    
    // close all the dynamic libs we opened
    for(itr=dl_list.begin(); itr!=dl_list.end(); itr++){
        dlclose(*itr);
    }

    return 0;
}