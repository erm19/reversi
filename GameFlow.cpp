//
// Created by eyal moskowitz 314074303 on 10/11/17.
//

#include "GameFlow.h"
#include "AIPlayer.h"

/**
 * constructor for game flow
 * @param boardSize
 */
GameFlow::GameFlow(int boardSize) {
    board_ = new Board(boardSize);
    currentPlayer_ = 'X';
    logic_ = new BasicLogic(board_);
    turnsLeft_ = new int[2];
    turnsLeft_[0] = 0;
    turnsLeft_[1] = 0;
}

/**
 * runs the game.
 */
void GameFlow::run(Player &player1, int whichPlayer, char symbol) {
    Player *player2;
    if (whichPlayer == 1)
        player2 = new HumanPlayer('O');
    else player2 = new AIPlayer(symbol, board_, &player1);
    Player &p1 = player1, &p2 = *player2;
    CellCounter cellCounter = CellCounter(board_);
    CellCounter &cc = cellCounter;
    while (true) {
        board_->print();
        cout << currentPlayer_ << ": It's your turn." << endl;
        if (currentPlayer_ == 'X') {
            playOneTurn(p1, p2, cc);
        } else {
            playOneTurn(p2, p1, cc);
        }
        if ((turnsLeft_[0] == 1 && turnsLeft_[1] == 1) || cc.getSpaceCounter() == 0) break;
    }
    board_->print();
    if (cc.getXCounter() > cc.getOCounter())
        cout << "Player 1 wins with " << cc.getXCounter() << " tiles" << endl;
    else
        cout << "Player 2 wins with " << cc.getOCounter() << " tiles" << endl;
}

/**
 * plays a player's turn
 * @param curr player
 * @param opp player
 * @param cc cell counter
 */
void GameFlow::playOneTurn(Player &curr, Player &opp, CellCounter &cc) {
    vector<Point> moves;
    Point choice;
    moves = logic_->getPossibleMoves(curr, opp);
    printOptions(moves);
    choice = curr.makeMove(moves);
    if (choice.getX() == -1 && choice.getY() == -1) {
        if (currentPlayer_ == 'X') turnsLeft_[0] = 1;
        else turnsLeft_[1] = 1;
        currentPlayer_ = opp.getSymbol();
        return;
    }
    if (turnsLeft_[0] == 1 && currentPlayer_ == 'X') turnsLeft_[0] = 0;
    if (turnsLeft_[1] == 1 && currentPlayer_ == 'O') turnsLeft_[1] = 0;
    choice.setPoint(choice.getX() - 1, choice.getY() - 1);
    Point &ch = choice;
    board_->putChoice(ch, curr, opp);
    cc.count();
    currentPlayer_ = opp.getSymbol();
}

/**
 * prints the possible moves
 * @param moves vector
 */
void GameFlow::printOptions(vector<Point> &moves) {
    for (int i = 0; i < moves.size(); ++i) {
        if (i == moves.size() - 1) moves[i].print();
        else {
            moves[i].print();
            cout << ",";
        }
    }
    cout << endl;
}

/**
 * destructor for game flow
 */
GameFlow::~GameFlow() {
    delete[] turnsLeft_;
    delete logic_;
    delete board_;
}