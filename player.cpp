#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;
    this->side = side;
    this->board = Board();
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    
    board.doMove(opponentsMove, getOpponent());
    if (board.hasMoves(side))
    {
    	//Working AI
    // 	for (int x = 0; x < 8; x++)
    // 	{
    // 		for (int y = 0; y < 8; y++)
    // 		{
    // 			Move *m = new Move(x, y);
				// if (board.checkMove(m, side))
				// {
				// 	board.doMove(m, side);
				// 	return m;
				// }
				// delete m;
    // 		}
    // 	}
    	//AI that beats SimplePlayer
    	Move *best = nullptr;
    	int bestScore = -100000000;
    	for (int x = 0; x < 8; x++)
    	{
    		for (int y = 0; y < 8; y++)
    		{
    			Move *m = new Move(x, y);
    			if (board.checkMove(m, side))
    			{
    				int score = getScore(m);
    				if (score > bestScore)
    				{
    					best = m;
    					bestScore = score;
    				}
    			}
    		}
    	}
    	board.doMove(best, side);
    	return best;

    }
    return nullptr;
}

/**
 * @brief Calculates heuristic score of a given valid move.
 * 
 * @returns int score of move.
 */
int Player::getScore(Move *m)
{
	Board *bcopy = this->board.copy();
	bcopy->doMove(m, side);
	int score = bcopy->count(side) - bcopy->count(getOpponent());
	int x = m->getX();
	int y = m->getY();
	//if one of the corners, more valuable
	if (((x == 0) && (y == 0)) || ((x == 7) && (y == 0)) || ((x == 0) && (y == 7)) || ((x == 7) && (y == 7)))
	{
		score *= 3;
	}

	//if adjacent to one of the corners, less valuable
	//top left
	else if (((x == 1) && (y == 0)) || ((x == 1) && (y == 1)) || ((x == 0) && (y == 1)))
	{
		score *= -3;
	}
	//top right
	else if (((x == 6) && (y == 0)) || ((x == 6) && (y == 1)) || ((x == 7) && (y == 1)))
	{
		score *= -3;
	}
	//bottom left
	else if (((x == 0) && (y == 6)) || ((x == 1) && (y == 6)) || ((x == 1) && (y == 7)))
	{
		score *= -3;
	}
	//bottom right
	else if (((x == 7) && (y == 6)) || ((x == 6) && (y == 6)) || ((x == 6) && (y == 7)))
	{
		score *= -3;
	}

	delete bcopy;
	return score;
}

/**
 * @brief Gets the opposite side of the player.
 * 
 * @return The opponent's Side
 */
Side Player::getOpponent()
{
	return (side == BLACK) ? WHITE : BLACK;
}
