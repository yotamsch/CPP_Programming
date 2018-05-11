
#ifndef __H_GAME_MANAGER_RPS
#define __H_GAME_MANAGER_RPS

/**
 * @brief The full play of the RPS game.
 * 
 * @param vGameStyle An integer {1: auto-vs-auto, 2: file-vs-file, 3: auto-vs-file, 4: file-vs-auto}
 * @return int In case of success - 0, otherwise - 1
 */
int PlayRPS(int vGameStyle);

#endif // !__H_GAME_MANAGER_RPS