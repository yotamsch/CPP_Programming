/**
 * @brief The main cpp file which will be compiled to execute the game
 * 
 * @file Game.cpp
 * @author Yotam Sechayk
 * @date 2018-04-27
 */

#include "GameManagerRPS.h"

#define BAD_ARGS_MESSAGE "Please enter (as the first argument): auto-vs-auto, file-vs-file, auto-vs-file or file-vs-auto and try again."

int main(int argc, char** argv) {
    if (argc < 2) {
        printMessageToScreen(ERROR, "No play type was entered.");
        printMessageToScreen(ERROR, BAD_ARGS_MESSAGE);
        return 1; // exit in case of error
    }
    if (argv[1] == "auto-vs-auto") {
            return PlayRPS(AUTO_VS_AUTO);
    }
    if (argv[1] == "file-vs-file") {
        return PlayRPS(FILE_VS_FILE);
        }
    if (argv[1] == "auto-vs-file") {
        return PlayRPS(AUTO_VS_FILE);
    }
    if (argv[1] == "file-vs-auto") {
        return PlayRPS(FILE_VS_AUTO);
    }
    else {
        printMessageToScreen(ERROR, "The game type was not entered correctly.");
        printMessageToScreen(ERROR, BAD_ARGS_MESSAGE);
        return 1;
    }
}