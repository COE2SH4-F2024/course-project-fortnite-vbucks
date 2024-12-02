#include "Player.h" //doneeeeeeeeee
#include "Food.h"
// dhruv edits
//commented 

Player::Player(GameMechs *thisGMRef, Food *foodGenRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    mainFoodGenRef = foodGenRef;

    // more actions to be included
    playerPosArrayList = new objPosArrayList();
    playerPosArrayList->insertHead(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'));
}

Player::~Player()//free allocated memory
{
    delete playerPosArrayList;
}

objPosArrayList *Player::getPlayerPos() const
{
    //return the reference to the playerPos array list
    return playerPosArrayList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if(input != 0) //passes if input is not null
    {
        switch (input)
        {

        case 27: //press ESC to terminate/quit game at any time
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
            if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = UP;
            }
            break;
        case 'd':
            if(myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = RIGHT;
            }
            break;
        case 's':
            if(myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = DOWN;
            }
            break;
        case 'a':
            if(myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = LEFT;
            }
            break;

        default:
            break;
        }
    }
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos newHead = (playerPosArrayList->getHeadElement());
    //change position with wraparound logic
    switch (myDir)
    {
    case UP:
        if(newHead.pos->y - 1 == 0)
            newHead = (objPos(newHead.pos->x, mainGameMechsRef->getBoardSizeY() - 2, '*'));
        else
            newHead = (objPos(newHead.pos->x, newHead.pos->y - 1, '*'));
        break;
    case RIGHT:
        if(newHead.pos->x + 1 == mainGameMechsRef->getBoardSizeX() - 1)
            newHead = (objPos(1, newHead.pos->y, '*'));
        else
            newHead = (objPos(newHead.pos->x + 1, newHead.pos->y, '*'));
        break;
    case DOWN:
        if(newHead.pos->y + 1 == mainGameMechsRef->getBoardSizeY() - 1)
            newHead = (objPos(newHead.pos->x, 1, '*'));
        else
            newHead = (objPos(newHead.pos->x, newHead.pos->y + 1, '*'));
        break;
    case LEFT:
        if(newHead.pos->x - 1 == 0)
            newHead = (objPos(mainGameMechsRef->getBoardSizeX() - 2, newHead.pos->y, '*'));
        else
            newHead = (objPos(newHead.pos->x - 1, newHead.pos->y, '*'));
        break;
    default:
        break;
    }

    bool foodEaten = false; //checks if food is eaten

    if(myDir != STOP)
    {
        playerPosArrayList->insertHead(newHead); //inserts a new position
        for(int i = 1; i < playerPosArrayList->getSize(); i++)
        {
            if(newHead.pos->x == playerPosArrayList->getElement(i).pos->x && newHead.pos->y == playerPosArrayList->getElement(i).pos->y) //checks pos with self 
            {
                mainGameMechsRef->setExitTrue(); //ends game/game over
                mainGameMechsRef->setLoseFlag();
            }
        }

        for(int i = 0; i < 5; i++)
        {
            if(mainFoodGenRef->getFoodPos()->getElement(i).pos->x == newHead.pos->x && mainFoodGenRef->getFoodPos()->getElement(i).pos->y == newHead.pos->y) //check pos with food
            {
                foodEaten = true;
                char foodType = mainFoodGenRef->getFoodPos()->getElement(i).getSymbol();

                //ipdates the score depending on type
                if(foodType == 'O') //eating O +1
                {
                    mainGameMechsRef->incrementScore();  
                }
                else if(foodType == 'X') //eating X +5
                {
                    for(int j = 0; j < 5; j++)  
                        mainGameMechsRef->incrementScore();
                }
                else if(foodType == 'Y') //eating Y -5
                {
                    for(int j = 0; j < 5; j++) 
                        mainGameMechsRef->decrementScore();
                }

                mainFoodGenRef->generateFood(mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
                break;
            }
        }
        if(!foodEaten) //removes tail if nothing eaten
            playerPosArrayList->removeTail();
    }
}

// More methods to be added