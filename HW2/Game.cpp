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
        printMessageToScreen(ERROR, "No play type was entered. " + BAD_ARGS_MESSAGE)
        return 1; // exit in case of error
    }
    switch (argv[1]) {
        case "auto-vs-auto":
            return PlayRPS(AUTO_VS_AUTO);
            break;
        case "file-vs-file":
            return PlayRPS(FILE_VS_FILE);
            break;
        case "auto-vs-file":
            return PlayRPS(AUTO_VS_FILE);
            break;
        case "file-vs-auto":
            return PlayRPS(FILE_VS_AUTO);
            break;
        default:
            printMessageToScreen(ERROR, "The game type was not entered correctly. " + BAD_ARGS_MESSAGE);
            return 1;
            break;
    }
}