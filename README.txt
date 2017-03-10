I improved the heuristic to vastly prefer corners to other moves.
If the AI gets the corners, the pieces can't be stolen and
it can get the whole edges too.

I implemented alpha-beta pruning in order to improve the efficiency
so that more of the tree could be evaluated.