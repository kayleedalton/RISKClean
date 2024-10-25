#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "territory.h"

class Player {
public:
    Player(int id);

    int getId() const;
    int getTerritoryCount() const;
    void addTerritory(Territory* territory);
    void removeTerritory(Territory* territory);
    void reinforceTerritory(Territory* territory, int numTroops);

    std::vector<Territory*>& getTerritories();

private:
    int id;
    std::vector<Territory*> territories;
};

#endif // PLAYER_H
