
#ifndef __H_GAME_MANAGER_RPS
#define __H_GAME_MANAGER_RPS

/**
 * @brief The full play of the RPS game.
 * 
 * @param vGameStyle An integer {1: auto-vs-auto, 2: file-vs-file, 3: auto-vs-file, 4: file-vs-auto}
 * @return int In case of success - 0, otherwise - 1
 */
// TODO maybe get rid of the possibility of 'args'
int PlayRPS(int vGameStyle, const char* outfile_path = "./rps.output", const char* p1_posfile_path = "./player1.rps_board", const char* p2_posfile_path = "./player2.rps_board", const char* p1_movfile_path = "./player1.rps_moves", const char* p2_movfile_path = "./player2.rps_moves");

#endif // !__H_GAME_MANAGER_RPS