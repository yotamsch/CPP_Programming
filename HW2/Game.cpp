/**
 * @brief The main cpp file which will be compiled to execute the game
 * 
 * @file Game.cpp
 * @author Yotam Sechayk
 * @date 2018-04-27
 */

#include "GameManagerRPS.h"
#include "GameUtilitiesRPS.h"

#include <iostream>
#include <string>

// Prints a message to the screen with the desired label type
void printMessageToScreen(const std::string&& rrType, const std::string&& rrMsg, const std::string&& rrInfo = "")
{
    std::cout << rrType << " " << rrMsg << " " << rrInfo << std::endl;
}

int main(int argc, char** argv)
{
    const std::string ava = "auto-vs-auto";
    const std::string fvf = "file-vs-file";
    const std::string avf = "auto-vs-file";
    const std::string fva = "file-vs-auto";
    int gameResult;

    if (argc < 2) {
        printMessageToScreen(ERROR, "No play type was entered.", BAD_ARGS_MESSAGE);
        // printMessageToScreen(INFO, BAD_ARGS_MESSAGE);
        return 1; // exit in case of error
    }

    printMessageToScreen(INFO, argv[1]);

    if (!ava.compare(argv[1])) {
        gameResult = PlayRPS(AUTO_VS_AUTO);
    } else if (!fvf.compare(argv[1])) {
        // TODO maybe get rid of the possibility of 'args'
        if (argc >= 7) {
            gameResult = PlayRPS(FILE_VS_FILE, argv[2], argv[3], argv[4], argv[5], argv[6]);
        } else {
            gameResult = PlayRPS(FILE_VS_FILE);
        }
    } else if (!avf.compare(argv[1])) {
        gameResult = PlayRPS(AUTO_VS_FILE);
    } else if (!fva.compare(argv[1])) {
        gameResult = PlayRPS(FILE_VS_AUTO);
    } else {
        printMessageToScreen(ERROR, "The game type was not entered correctly.", BAD_ARGS_MESSAGE);
        // printMessageToScreen(INFO, BAD_ARGS_MESSAGE);
        return 1;
    }
    if (gameResult != 0) {
        printMessageToScreen(ERROR, "Failed to open/create output file.");
        return 1;
    }
}