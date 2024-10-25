#include "player.h"
#include <algorithm> // Required for std::remove

Player::Player(int id) : id(id) {}

int Player::getId() const {
    return id;
}

int Player::getTerritoryCount() const {
    return territories.size();
}

void Player::addTerritory(Territory* territory) {
    territories.push_back(territory);
}

void Player::removeTerritory(Territory* territory) {
    territories.erase(std::remove(territories.begin(), territories.end(), territory), territories.end());
}

void Player::reinforceTerritory(Territory* territory, int numTroops) {
    territory->addTroops(numTroops);
}

std::vector<Territory*>& Player::getTerritories() {
    return territories;
}
