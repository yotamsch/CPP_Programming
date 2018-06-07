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

void parseArg(char* arg, int& numOfThreads, std::string& so_path){
    std::string path("-path ");
    std::string threads("-threads ");
    std::string _arg(arg);
    if(path.compare(_arg.substr(0,6)) == 0){
        so_path = _arg.substr(6);
        if(so_path.at(so_path.size()-1) != '/'){
            so_path = so_path + "/";
        }
    }
    if(threads.compare(_arg.substr(0,9))){
        numOfThreads = std::stoi(_arg.substr(9));
    }
}

int main(int argc, char** argv){
    int numOfThreads = 4;
    std::string soFilesDirectory("./"); 

    FILE *dl;   // handle to read directory 
    std::list<void *> dl_list; // list to hold handles for dynamic libs 
    std::list<void *>::iterator itr; 
    void *dlib;
    char name[1024]; 
    
    if(argc<1){
        //TODO: announce error in number of arguments
    }
    if((argc == 2 || argc == 3) && argv[1] != nullptr){
        parseArg(argv[1], numOfThreads, soFilesDirectory);
        if(argc == 3 && argv[2] != nullptr){
            parseArg(argv[2], numOfThreads, soFilesDirectory);
        }
    }
    if(argc > 3){
        //TODO: announce error in number of arguments
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