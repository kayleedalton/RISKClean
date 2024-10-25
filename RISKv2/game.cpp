#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

Game::Game() : player1(1), player2(2), turn(1), maxTurns(5) { // Initialize maxTurns
    // Initialize the territories
    territories.push_back(Territory(1, 1, 10)); // Player 1 starts with 10 troops in Territory 1
    territories.push_back(Territory(2, 2, 5));  // Player 2 starts with 5 troops in Territory 2

    player1.addTerritory(&territories[0]);
    player2.addTerritory(&territories[1]);

    std::srand(std::time(nullptr));
}

void Game::start() {
    int turnCounter = 0;

    while (true) {
        if (turnCounter >= maxTurns) {
            std::cout << "Maximum number of turns reached. Ending game in a draw.\n";
            break;
        }

        std::cout << "==============================\n";
        std::cout << "Player " << turn << "'s turn\n";
        std::cout << "==============================\n";

        Player& currentPlayer = (turn == 1) ? player1 : player2;
        Player& opponent = (turn == 1) ? player2 : player1;

        displayGameState();

        reinforcementPhase(currentPlayer);
        attackPhase(currentPlayer, opponent);
        fortificationPhase(currentPlayer);

        if (checkVictory(opponent)) {
            std::cout << "Player " << currentPlayer.getId() << " wins the game!\n";
            break;
        }

        turn = (turn == 1) ? 2 : 1;
        turnCounter++;
    }
}

void Game::reinforcementPhase(Player& player) {
    int newTroops = std::max(3, player.getTerritoryCount() / 3);
    std::cout << "Player " << player.getId() << " receives " << newTroops << " troops.\n";

    // Automatically reinforce the first territory
    Territory* territory = player.getTerritories().front();
    player.reinforceTerritory(territory, newTroops);
    std::cout << "Automatically reinforcing Player " << player.getId() << "'s Territory " << territory->getId() << " with " << newTroops << " troops. Total troops in Territory " << territory->getId() << ": " << territory->getTroops() << ".\n";
}

void Game::attackPhase(Player& player, Player& opponent) {
    std::cout << "=== Attack Phase ===\n";

    Territory* attackingTerritory = player.getTerritories().front();
    Territory* defendingTerritory = opponent.getTerritories().front();

    std::cout << "Player " << player.getId() << " is automatically attacking Player " << opponent.getId() << " from Territory " << attackingTerritory->getId() << " to Territory " << defendingTerritory->getId() << ".\n";

    // Simple dice rolling logic for combat
    int attackerDice = std::min(attackingTerritory->getTroops() - 1, 3);
    int defenderDice = std::min(defendingTerritory->getTroops(), 2);

    int attackerRoll = rollDice(attackerDice);
    int defenderRoll = rollDice(defenderDice);

    if (attackerRoll > defenderRoll) {
        defendingTerritory->removeTroops(1);
        std::cout << "Defender lost 1 troop. ";
    } else {
        attackingTerritory->removeTroops(1);
        std::cout << "Attacker lost 1 troop. ";
    }

    // Check if the defending territory is captured
    if (defendingTerritory->getTroops() <= 0) {
        std::cout << "Player " << player.getId() << " has captured Territory " << defendingTerritory->getId() << "!\n";
        defendingTerritory->setOwner(player.getId());
        opponent.removeTerritory(defendingTerritory);
        player.addTerritory(defendingTerritory);
    }

    std::cout << "Player " << player.getId() << "'s Territories After Attack:\n";
    for (Territory* t : player.getTerritories()) {
        std::cout << "- Territory " << t->getId() << " (" << t->getTroops() << " troops)\n";
    }
}

void Game::fortificationPhase(Player& player) {
    std::cout << "=== Fortify Phase ===\n";
    std::cout << "Player " << player.getId() << " automatically skips fortification.\n";
}

int Game::rollDice(int numDice) {
    int maxRoll = 0;
    for (int i = 0; i < numDice; ++i) {
        int roll = std::rand() % 6 + 1;
        maxRoll = std::max(maxRoll, roll);
    }
    return maxRoll;
}

void Game::displayGameState() {
    std::cout << "Player 1's Territories:\n";
    for (Territory* t : player1.getTerritories()) {
        std::cout << "- Territory " << t->getId() << " (" << t->getTroops() << " troops)\n";
    }

    std::cout << "Player 2's Territories:\n";
    for (Territory* t : player2.getTerritories()) {
        std::cout << "- Territory " << t->getId() << " (" << t->getTroops() << " troops)\n";
    }
}

bool Game::checkVictory(Player& player) {
    return player.getTerritoryCount() == 0;
}
