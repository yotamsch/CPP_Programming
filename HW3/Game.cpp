#include "TournamentManager.h"
#include <dlfcn.h>
#include <iostream>
#include <list>
#include <string>
#include <string.h>
#include <random>

// size of buffer for reading in directory entries
#define BUF_SIZE 1024

int main(int argc, char** argv)
{
    // set the seed for the randomization
    srand((unsigned)time(NULL));

    int numOfThreads = 4;
    std::string soFilesDirectory("./");
    std::string path("-path");
    std::string threads("-threads");

    for (int i = 1; i < argc; i++) {
        if (path.compare(argv[i]) == 0 && argc > i + 1) {
            soFilesDirectory = argv[i + 1];
            if (soFilesDirectory.at(soFilesDirectory.size() - 1) != '/') {
                soFilesDirectory = soFilesDirectory + "/";
            }
        } else if (threads.compare(argv[i]) == 0 && argc > i + 1) {
            numOfThreads = std::stoi(argv[i + 1]);
        }
    }

    std::cout << "Using # threads: " << numOfThreads << std::endl;

    FILE* dl; // handle to read directory
    std::list<void*> dl_list; // list to hold handles for dynamic libs
    std::list<void*>::iterator itr;
    void* dlib;
    char name[BUF_SIZE];

    std::string command_str = "ls " + soFilesDirectory + "*.so"; // command string to get dynamic lib names
    char in_buf[BUF_SIZE]; // input buffer for lib names
    // get the names of all the dynamic libs (.so  files) in the current dir
    dl = popen(command_str.c_str(), "r"); //this executes a command "ls"
    if (!dl) {
        perror("popen");
        exit(-1);
    }
    while (fgets(in_buf, BUF_SIZE, dl)) {
        // trim off the whitespace at the end
        char* ws = strpbrk(in_buf, " \t\n");
        if (ws)
            *ws = '\0';
        // append ./ to the front of the lib name
        if ((in_buf[0] == '.' && in_buf[1] == '/') || in_buf[0] == '/')
            sprintf(name, "%s", in_buf);
        else
            sprintf(name, "./%s", in_buf);
        
        TournamentManager::get().addFileName(name);
    }

    if (TournamentManager::get().getFilesNames().size() <= 1) {
        //TODO: print usage msg accordingly, "not enough competitors"
        std::cout << "not enough .so files in directory" << std::endl;
        return (-1);
    }

    for (int i = 0; i < (int)TournamentManager::get().getFilesNames().size(); ++i) {
        dlib = dlopen(TournamentManager::get().getFilesNames()[i].c_str(), RTLD_NOW);
        if (dlib == NULL) {
            // TODO: handle error message correctly
            std::cerr << dlerror() << std::endl;
            return (-1);
        }
        dl_list.insert(dl_list.end(), dlib);
    }

    std::cout << "Starting tournamnt" << std::endl;
    // run the tournament
    TournamentManager::get().run(numOfThreads);

    std::vector<std::pair<std::string,int>> finalScores;
    TournamentManager::get().getSortedScores(finalScores);

    // print the scores
    for (auto& s : finalScores) {
        std::cout << s.first << " : " << s.second << std::endl;
    }

    TournamentManager::get().clearAlgorithms();

    // close all the dynamic libs we opened
    for (itr = dl_list.begin(); itr != dl_list.end(); itr++) {
        dlclose(*itr);
    }

    std::cout << "closed all libs" << std::endl;
    
    return 0;
}