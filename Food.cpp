#include "Food.h" //doneeeeeeeeeee
#include "Player.h"
#include <stdlib.h>
#include <time.h>

Food::Food(Player *thisPlayerRef)
{
    playerRef = thisPlayerRef;
    foodBucket = new objPosArrayList();
    srand(time(NULL));
}

Food::~Food()
{
    delete foodBucket;
}

objPosArrayList *Food::getFoodPos() const
{
    // return the reference to the foodPos arrray list
    return foodBucket;
}

void Food::generateFood(int boardSizeX, int boardSizeY)
{
    for (int i = 0; i < foodBucket->getSize(); i++) // remove existing food
        foodBucket->removeTail();
    int count = 0;
    while (count < 5) // loop to create 5 food objects
    {
        char foodSymbol = 'O';
        if (count == 0)
            foodSymbol = 'X';
        if (count == 1)
            foodSymbol = 'Y';
        int xPos = rand() % (boardSizeX - 2) + 1;
        int yPos = rand() % (boardSizeY - 2) + 1;
        bool alreadyExists = false; // bool to check if the position is already taken by the player or previous food
        for (int i = 0; i < playerRef->getPlayerPos()->getSize(); i++)
        {
            alreadyExists = playerRef->getPlayerPos()->getElement(i).pos->x == xPos && playerRef->getPlayerPos()->getElement(i).pos->y == yPos;
            if (alreadyExists)
                break;
        }
        for (int i = 0; i < foodBucket->getSize(); i++)
        {
            alreadyExists = foodBucket->getElement(i).pos->x == xPos && foodBucket->getElement(i).pos->y == yPos;
            if (alreadyExists)
                break;
        }
        if (!alreadyExists)
        {
            foodBucket->insertHead(objPos(xPos, yPos, foodSymbol)); // add food if position doesnt already exist
            count++;
        }
    }
}