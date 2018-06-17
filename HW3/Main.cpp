/**
 * @brief The main file of the tournament.
 * 
 * @file Main.cpp
 * @author Yotam Sechayk
 * @date 2018-06-07
 */
#include "ThreadPool.h"
#include "TournamentManager.h"

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
#define INF "[INFO] "
#define ERR "[ERROR] "

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
        if (path.compare(argv[i]) == 0) {
            if (argc < i + 2) {
                std::cout << ERR << MSG_INVALID_FORMAT << std::endl;
                return ERR_RETURN;
            }
            soFilesDirectory = argv[i + 1];
            if (soFilesDirectory.at(soFilesDirectory.size() - 1) != '/') {
                soFilesDirectory = soFilesDirectory + "/";
            }
        } else if (threads.compare(argv[i]) == 0) {
            if (argc < i + 2) {
                std::cout << ERR << MSG_INVALID_FORMAT << std::endl;
                return ERR_RETURN;
            }
            try {
                numOfThreads = std::stoi(argv[i + 1]);
            } catch (...) {
                std::cout << ERR << "Please specify a valid threads number, '" << argv[i + 1] << "' is not a valid value." << std::endl;
                return ERR_RETURN;
            }
            if (numOfThreads <= 0) {
                std::cout << ERR << "The threads number should be at least 1." << std::endl;
                ;
                return ERR_RETURN;
            }
        }
    }

    std::cout << INF << "Using .so files in: '" << soFilesDirectory << "'." << std::endl;

    // command string to get dynamic lib names
    std::string command_str = "ls " + soFilesDirectory + "*.so";

    // get the names of all the dynamic libs (.so  files) in the current dir
    // this executes a command "ls"
    dl = popen(command_str.c_str(), "r");
    if (!dl) {
        std::cout << "Error while attempting to look up: " << soFilesDirectory << std::endl;
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
        return ERR_RETURN;
    }

    if (soFileNames.size() <= 1) {
        std::cout << ERR << "Not enough .so files in the directory. Needs 2 or more player algorithms." << std::endl;
        return ERR_RETURN;
    }

    // opening the libs
    for (int i = 0; i < (int)soFileNames.size(); ++i) {
        dlib = dlopen(soFileNames[i].c_str(), RTLD_NOW);
        if (dlib == NULL) {
            std::cout << INF << "Error while attempting to open file: " << soFileNames[i] << ", skipping it." << std::endl;
            continue;
        }
        dl_list.push_back(dlib);
    }

    std::cout << INF << "Using " << numOfThreads << " threads (including main), on " << dl_list.size() << " algorithms." << std::endl;

    // make sure the play queue and the needed information exists
    if (TournamentManager::get().initialize() == false) {
        std::cout << ERR << "Not enough algorithms were able to register." << std::endl;
        // close all the dynamic libs we opened
        for (itr = dl_list.begin(); itr != dl_list.end(); itr++) {
            dlclose(*itr);
        }
        return ERR_RETURN;
    }

    // create the thread play pool (works with 0 or more additional threads)
    ThreadPool playPool(TournamentManager::get().getPlayQueue());

    // run the tournament wait for pool to finish
    playPool.run(numOfThreads - 1);
    playPool.waitForAll();

    // get sorted final scores
    std::vector<std::pair<std::string, int>> finalScores;
    TournamentManager::get().getSortedScores(finalScores);

    // print the scores
    for (auto& s : finalScores) {
        std::cout << s.first << " " << s.second << std::endl;
    }

    // cleas algorithm registration before closing libs
    TournamentManager::get().clearAlgorithms();

    // close all the dynamic libs we opened
    for (itr = dl_list.begin(); itr != dl_list.end(); itr++) {
        dlclose(*itr);
    }

    // makes sure all sub-threads were demolished and exists cleanly
    pthread_exit(NULL);
}