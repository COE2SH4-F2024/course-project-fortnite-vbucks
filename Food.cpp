#include "Food.h" //doneeeeeeeeeee
#include "Player.h"
#include <stdlib.h>
#include <time.h>

//dhruv editws done
//commented

Food::Food(Player *thisPlayerRef)
{
    playerRef = thisPlayerRef;
    foodGenerator = new objPosArrayList(); //initializes food position list

    srand(time(NULL));
}

Food::~Food() //clears up allocated memory
{
    delete foodGenerator;
}

objPosArrayList *Food::getFoodPos() const //returns food positions
{
    //return refrence
    return foodGenerator;
}

void Food::generateFood(int boardSizeX, int boardSizeY)
{
    for(int i = 0; i < foodGenerator->getSize(); i++) //clears existing food
        foodGenerator->removeTail();
    int count = 0;
    while (count < 5) //create 5 food objs
    {
        char foodSymbol = 'O';
        if(count == 0)
            foodSymbol = 'X';
        if(count == 1)
            foodSymbol = 'Y';

        int xPos = rand() % (boardSizeX - 2) + 1;
        int yPos = rand() % (boardSizeY - 2) + 1;

        bool taken = false; //checks if an position is occupied by food or the player
        for(int i = 0; i < playerRef->getPlayerPos()->getSize(); i++)
        {
            taken = playerRef->getPlayerPos()->getElement(i).pos->x == xPos && playerRef->getPlayerPos()->getElement(i).pos->y == yPos;
            if(taken)
                break;
        }
        for(int i = 0; i < foodGenerator->getSize(); i++)
        {
            taken = foodGenerator->getElement(i).pos->x == xPos && foodGenerator->getElement(i).pos->y == yPos;
            if(taken)
                break;
        }
        if(!taken) //adds food to the list if the position is free
        {
            foodGenerator->insertHead(objPos(xPos, yPos, foodSymbol)); //add food if position doesnt already exist
            count++;
        }
    }
} 