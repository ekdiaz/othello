#include "player.hpp"
using namespace std;

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

/**
 * @brief Sets the internal board state to the given board.
 * 
 * @param[in] board - pointer to Board object
 */
void Player::setBoard(Board *board)
{
	this->board = *board;
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
    	// Move *best = nullptr;
    	// int bestScore = -100000000;
    	// for (int x = 0; x < 8; x++)
    	// {
    	// 	for (int y = 0; y < 8; y++)
    	// 	{
    	// 		Move *m = new Move(x, y);
    	// 		if (board.checkMove(m, side))
    	// 		{
    	// 			int score = getMoveScore(this->board, m);
    	// 			if (score > bestScore)
    	// 			{
    	// 				best = m;
    	// 				bestScore = score;
    	// 			}
    	// 		}
    	// 	}
    	// }
    	// board.doMove(best, side);
    	// return best;

    	//AI that implements 2-ply depth minimax
    	Board *bcopy = this->board.copy();
    	Move *m = minimaxMove(bcopy, 2, 0);
    	board.doMove(m, side);
    	delete bcopy;
    	return m;

    }
    return nullptr;
}

/**
 * @brief Calculates heuristic score of a given valid move.
 * 
 * @returns int score of move.
 */
int Player::getMoveScore(Board b, Move *m)
{
	Board *bcopy = b.copy();
	bcopy->doMove(m, side);
	int score = bcopy->count(side) - bcopy->count(getOpponent());
	if (m == nullptr)
	{
		return score;
	}
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
 * @brief Recursively calculates the best move at a depth d.
 *
 * @param[in] b is the current Board in the tree
 * @param[in] d is the max depth of the decision tree
 * @param[in] current is the current depth of the tree
 * @return the pointer to the Move that should be made.
 */
Move *Player::minimaxMove(Board *b, int d, int current)
{
	if (current >= d)
	{
		return nullptr;
	}
	vector<Move*> moves;
	if (current % 2 == 0)
	{
		moves = b->possibleMoves(side);
	}
	else
	{
		moves = b->possibleMoves(getOpponent());
	}
	vector<int> scores;
	
	for (unsigned int i = 0; i < moves.size(); i++)
	{
		//For each possible move, create a new board copy and make that move
		Board *bcpy = b->copy();
		if (current % 2 == 0)
		{
			bcpy->doMove(moves[i], side);
		}
		else
		{
			bcpy->doMove(moves[i], getOpponent());
		}
		Move *m = minimaxMove(bcpy, d, current + 1);
		scores.push_back(getMoveScore(*bcpy, m));
		delete bcpy;
	}
	if (scores.size() == 0)
	{
		return nullptr;
	}
	//our turn
	if (current % 2 == 0)
	{
		int scoreIndex = max(scores);
		return moves[scoreIndex];
	}
	//opponent's turn
	else
	{
		int scoreIndex = min(scores);
		return moves[scoreIndex];
	}
}

/**
 * @brief Returns the index with the max value of a vector.
 */
int Player::max(vector<int> scores)
{
	int maximum = -1;
	for (unsigned int i = 0; i < scores.size(); i++)
	{
		if (i == 0)
		{
			maximum = i;
		}
		if (scores[i] > scores[maximum])
		{
			maximum = i;
		}
	}
	return maximum;
}

/**
 * @brief Returns the index with the min value of a vector.
 */
int Player::min(vector<int> scores)
{
	int minimum = -1;
	for (unsigned int i = 0; i < scores.size(); i++)
	{
		if (i == 0)
		{
			minimum = i;
		}
		if (scores[i] > scores[minimum])
		{
			minimum = i;
		}
	}
	return minimum;
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
