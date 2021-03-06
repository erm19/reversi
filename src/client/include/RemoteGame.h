//
// Created by eyal on 07/12/17.
//

#ifndef EX1_REMOTEGAME_H
#define EX1_REMOTEGAME_H

#define COLOR_LENGTH 6
#define PLAY_LENGTH 30

#include <stdio.h>
#include "Board.h"
#include "GameLogic.h"
#include "BasicLogic.h"
#include "HumanPlayer.h"
#include "CellCounter.h"
#include "SubMenu.h"
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <sstream>

class RemoteGame {
public:
    RemoteGame(const char *serverIP, int serverPort, int boardSize);
    void run();
    ~RemoteGame();
private:
    Board *board_;
    GameLogic *logic_;
    const char *serverIp_;
    int serverPort_;
    int clientSocket_;

    void connectToServer();
    bool readFromServer(Player *curr, Player *opp, string &play, CellCounter &cc);
    int playOneTurn(Player *curr, Player *opp, CellCounter &cc, int &i);
    int commandAndColor(SubMenu &sm);
    int socketWrite(string s);
    int socketRead(string &s);
    string getCommand(string args);
    string getGameName(string &args);
    Point stringToPoint(string s);
};


#endif //EX1_REMOTEGAME_H
