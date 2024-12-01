#ifndef FOOD_H //doneeeeeeeeeeeeee
#define FOOD_H
//dhruv edits done
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
    objPosArrayList *foodGenerator;

    Player *playerRef;
};

#endif