#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
#include <limits>
#include <ctime>

using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    void setBoard(Board *board);
    Move *doMove(Move *opponentsMove, int msLeft);
    Side getOpponent();
    int getMoveScore(Board b, Move *m, Side s);
    Move *minimaxMove(Board *b, int d, int current);
    Move *alpha_beta(Board *b, int depth, int current, int alpha, int beta);
    Move *iterative_deepening(Board *bcopy);
    int max(vector<int> scores);
    int min(vector<int> scores);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
private:
	Board board;
	Side side;
	time_t start;
};

#endif
