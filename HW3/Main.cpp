
#include "TournamentManager.h"
#include "ThreadPool.h"

#include <dlfcn.h>
#include <iostream>
#include <list>
#include <random>
#include <string.h>
#include <string>
#include <vector>

// size of buffer for reading in directory entries
#define BUF_SIZE 4097
#define MSG_INVALID_FORMAT "Please call using the following format: <exe> [-path <.so directory path> [-threads <number>]]"
#define ERR_RETURN -1

int main(int argc, char** argv)
{
    FILE* dl; // handle to read directory
    std::vector<void*> dl_list; // list to hold handles for dynamic libs
    std::vector<void*>::iterator itr;
    void* dlib;
    char name[BUF_SIZE];
    char in_buf[BUF_SIZE]; // input buffer for lib names
    std::vector<std::string> soFileNames; // will hold the fine names

    int numOfThreads = 4;
    std::string soFilesDirectory("./");
    std::string path("-path");
    std::string threads("-threads");

    // set the seed for the randomization
    srand((unsigned)time(NULL));

    // collect command line settings
    for (int i = 1; i < argc; i++) {
        if (path.compare(argv[i]) == 0 && argc > i + 1) {
            if (argc < i + 2) {
                std::cout << MSG_INVALID_FORMAT << std::endl;
                return ERR_RETURN;
            }
            soFilesDirectory = argv[i + 1];
            if (soFilesDirectory.at(soFilesDirectory.size() - 1) != '/') {
                soFilesDirectory = soFilesDirectory + "/";
            }
        } else if (threads.compare(argv[i]) == 0 && argc > i + 1) {
            if (argc < i + 2) {
                std::cout << MSG_INVALID_FORMAT << std::endl;
                return ERR_RETURN;
            }
            try {
                numOfThreads = std::stoi(argv[i + 1]);
            } catch (...) {
                std::cout << "Please specify a valid threads number, '" << argv[i + 1] << "' is not a valid value." << std::endl;
                return ERR_RETURN;
            }
            if (numOfThreads <= 0) {
                std::cout << "The threads number should be at least 1." << std::endl;;
                return ERR_RETURN;
            }
        }
    }

    // command string to get dynamic lib names
    std::string command_str = "ls " + soFilesDirectory + "*.so";

    // get the names of all the dynamic libs (.so  files) in the current dir
    // this executes a command "ls"
    dl = popen(command_str.c_str(), "r");
    if (!dl) {
        std::cout << "Error while attempting to open: " << soFilesDirectory << std::endl;
        return ERR_RETURN;
    }

    while (fgets(in_buf, BUF_SIZE, dl)) {
        // trim off the whitespace at the end
        char* ws = strpbrk(in_buf, " \t\n");
        if (ws) {
            *ws = '\0';
        }
        // append ./ to the front of the lib name
        if ((in_buf[0] == '.' && in_buf[1] == '/') || in_buf[0] == '/') {
            sprintf(name, "%s", in_buf);
        } else {
            sprintf(name, "./%s", in_buf);
        }
        // add the file path to the list of paths;
        soFileNames.push_back(name);
    }

    // close dl since don't need it anymore
    if (pclose(dl) != 0) {
        std::cout << "An error occured while dismissing the directory look up." << std::endl;
        return ERR_RETURN;
    }

    if (soFileNames.size() <= 1) {
        std::cout << "Not enough .so files in the directory. Needs 2 or more player algorithms." << std::endl;
        return ERR_RETURN;
    }

    // opening the libs
    for (int i = 0; i < (int)soFileNames.size(); ++i) {
        dlib = dlopen(soFileNames[i].c_str(), RTLD_NOW);
        if (dlib == NULL) {
             std::cout << "Error while attempting to open file: " << soFileNames[i] << std::endl;
            // close opened libs
            for (itr = dl_list.begin(); itr != dl_list.end(); itr++) {
                std::cout << "closing: " << *itr << std::endl;
                dlclose(*itr);
            }
            return ERR_RETURN;
        }
        std::cout << "adding: " << dlib << std::endl;
        dl_list.push_back(dlib);
    }




    std::cout << "Starting tournamnt" << std::endl;
    std::cout << "Using " << numOfThreads << " threads" << std::endl;

    // make sure the play queue and the needed information exists
    TournamentManager::get().initialize();

    // create the thread play pool
    ThreadPool playPool(TournamentManager::get().getPlayQueue());

    // run the tournament
    playPool.run(numOfThreads - 1);
    playPool.waitForAll();

    // get sorted final scores
    std::vector<std::pair<std::string, int>> finalScores;
    TournamentManager::get().getSortedScores(finalScores);

    // print the scores
    for (auto& s : finalScores) {
        std::cout << s.first << " : " << s.second << std::endl;
    }

    TournamentManager::get().clearAlgorithms();




    // close all the dynamic libs we opened
    for (itr = dl_list.begin(); itr != dl_list.end(); itr++) {
        std::cout << "closing: " << *itr << std::endl;
        dlclose(*itr);
    }

    std::cout << "closed all libs" << std::endl;

    // to handle leaks reported by valgrind (might be false leaks)
    pthread_exit(NULL);
}