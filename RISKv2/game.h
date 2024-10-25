#ifndef GAME_H
#define GAME_H

#include <vector>
#include "territory.h"
#include "player.h"

class Game {
public:
    Game();
    void start();

private:
    Player player1;
    Player player2;
    std::vector<Territory> territories;
    int turn;
    int maxTurns; // Added variable for maximum number of turns

    void reinforcementPhase(Player& player);
    void attackPhase(Player& player, Player& opponent);
    void fortificationPhase(Player& player);
    int rollDice(int numDice);
    void displayGameState();
    bool checkVictory(Player& player);
};

#endif // GAME_H
