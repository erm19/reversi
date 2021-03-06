//
// Created by abby on 21/11/17.
//

#include "../include/AIPlayer.h"
#include "../include/BasicLogic.h"

/**
 * AIPLayer constructor.
 * @param symbol - the symbol of the AIPlayer.
 * @param board  - the board.
 * @param opp  - the opponent player.
 * @param logic  - the rules of the game.
 */
AIPlayer::AIPlayer(char symbol, Board *board, Player *opp) {
    board_ = board;
    symbol_ = symbol;
    opp_ = opp;
}

/**
 * makes the move for the AI player
 * @param moves
 * @return the move
 */
Point AIPlayer::makeMove(vector<Point> &moves) {
    int counter = board_->getSize() * board_->getSize() + 1;
    Point temp, move, currChoice;
    Board copyBoard = Board(board_);
    BasicLogic bl = BasicLogic(&copyBoard);
    Player &curr = *this, &oppo = *opp_;
    if(moves.empty()) {
        cout << "Computer had no possible moves." << endl;
        return Point(-1, -1);
    }
    //go over all the moves for the computer and play them on the copy board
    for(int i = 0; i < moves.size(); i++) {
        move = Point(moves[i].getX() - 1, moves[i].getY() - 1);
        currChoice = move;
        copyBoard.putChoice(move, curr, oppo);
        move.setPoint(move.getX() + 1, move.getY() + 1);
        //for each move copyboard gets the possible moves of the human player
        vector<Point> moves2 = bl.getPossibleMoves(oppo, curr);
        if(moves2.empty()) return move;
        for(int j = 0; j < moves2.size(); j++) {
            int newCounter = makeHumanPLayerMove(copyBoard, moves2[j]);
            if(newCounter < counter) {
                counter = newCounter;
                temp = move;
            }
            resetCopy(copyBoard);
            copyBoard.putChoice(currChoice, curr, oppo);
        }
        resetCopy(copyBoard);
    }
    playerMove(temp);
    return temp;
}

/**
 * calculates the moves grade by doing each of the other player's move
 * @param copyBoard
 * @param move
 * @return the moves grade
 */
int AIPlayer:: makeHumanPLayerMove(Board &copyBoard, Point move) {
    move.setPoint(move.getX() - 1, move.getY() - 1);
    copyBoard.putChoice(move, *opp_,*this);
    CellCounter cellCounter = CellCounter(&copyBoard);
    CellCounter &cc = cellCounter;
    cc.count();
    if(symbol_ == 'X') {
        int oCounter = cc.getCounter('O') - cc.getCounter('X');
        return oCounter;
    }
    if(symbol_ == 'O') {
        int xCounter = cc.getCounter('X') - cc.getCounter('O');
        return xCounter;
    }
}

/**
 * gets the player's symbol
 * @return the symbol
 */
char AIPlayer::getSymbol() const {
    return symbol_;
}

/**
 * resets the copy board according to the board.
 * @param copy
 */
void AIPlayer::resetCopy(Board &copy) {
    for (int i = 0; i < board_->getSize(); ++i) {
        for (int j = 0; j < board_->getSize(); ++j) {
            Point p = Point(i, j);
            copy.setStatus(board_->getStatus(p), p);
        }
    }
}

/**
 * prints the player's choice
 * @param move
 */
void AIPlayer::playerMove(Point &move) {
    cout << symbol_ << " has played ";
    move.print();
    cout << endl << endl;
}