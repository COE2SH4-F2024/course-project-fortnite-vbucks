#ifndef FOOD_H //doneeeeeeeeeeeeee
#define FOOD_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Player.h"

class Player;

class Food
{

public:
    Food(Player *thisPlayerRef);
    ~Food();

    objPosArrayList *getFoodPos() const;
    void generateFood(int boardSizeX, int boardSizeY);

    // More methods to be added here

private:
    objPosArrayList *foodBucket;

    // Need a reference to the Player
    Player *playerRef;
};

#endif