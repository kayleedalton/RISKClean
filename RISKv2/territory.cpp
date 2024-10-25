#include "territory.h"

Territory::Territory(int id, int owner, int troops) : id(id), owner(owner), troops(troops) {}

int Territory::getOwner() const {
    return owner;
}

void Territory::setOwner(int newOwner) {
    owner = newOwner;
}

int Territory::getTroops() const {
    return troops;
}

void Territory::addTroops(int numTroops) {
    troops += numTroops;
}

void Territory::removeTroops(int numTroops) {
    troops -= numTroops;
}

int Territory::getId() const {
    return id;
}
