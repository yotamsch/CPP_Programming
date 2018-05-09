/**
 * @brief The main cpp file which will be compiled to execute the game
 * 
 * @file Game.cpp
 * @author Yotam Sechayk
 * @date 2018-04-27
 */

#include "GameManagerRPS.h"
#include "GameUtilitiesRPS.h"
#include <string.h>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printMessageToScreen(ERROR, "No play type was entered.");
        printMessageToScreen(ERROR, BAD_ARGS_MESSAGE);
        return 1; // exit in case of error
    }
    if (strcmp(argv[1], "auto-vs-auto") == 0)
    {
        return PlayRPS(AUTO_VS_AUTO);
    }
    if (strcmp(argv[1], "file-vs-file") == 0)
    {
        return PlayRPS(FILE_VS_FILE);
    }
    if (strcmp(argv[1], "auto-vs-file") == 0)
    {
        return PlayRPS(AUTO_VS_FILE);
    }
    if (strcmp(argv[1], "file-vs-auto") == 0)
    {
        return PlayRPS(FILE_VS_AUTO);
    }
    else
    {
        printMessageToScreen(ERROR, "The game type was not entered correctly.");
        printMessageToScreen(ERROR, BAD_ARGS_MESSAGE);
        return 1;
    }
}