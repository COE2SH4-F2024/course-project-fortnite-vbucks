#ifndef PLAYER_H //doneeeeeeeeeeee
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Food;

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

public:
    enum Dir
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        STOP
    }; // This is the direction state

    Player(GameMechs *thisGMRef, Food *foodGenRef);
    ~Player();

    objPosArrayList *getPlayerPos() const;
    void updatePlayerDir();
    void movePlayer();

    // More methods to be added here

private:
    objPosArrayList *playerPosArrayList;
    enum Dir myDir;

    // Need a reference to the Main Game Mechanisms
    GameMechs *mainGameMechsRef;
    Food *mainFoodGenRef;
};

#endif