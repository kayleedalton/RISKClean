#ifndef TERRITORY_H
#define TERRITORY_H

class Territory {
public:
    Territory(int id, int owner, int troops);

    int getOwner() const;
    void setOwner(int newOwner);

    int getTroops() const;
    void addTroops(int numTroops);
    void removeTroops(int numTroops);

    int getId() const;

private:
    int id;
    int owner;
    int troops;
};

#endif // TERRITORY_H
