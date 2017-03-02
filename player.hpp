#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
#include <vector>
using namespace std;

class Player {

public:
    Player(Side side);
    ~Player();

    void setBoard(Board *board);
    Move *doMove(Move *opponentsMove, int msLeft);
    Side getOpponent();
    int getMoveScore(Board b, Move *m);
    Move *minimaxMove(Board *b, int d, int current);
    int max(vector<int> scores);
    int min(vector<int> scores);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
private:
	Board board;
	Side side;
};

#endif
