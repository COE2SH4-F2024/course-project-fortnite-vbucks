#include "Player.h" //doneeeeeeeeee
#include "Food.h"
// dhruv edits
Player::Player(GameMechs *thisGMRef, Food *foodGenRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    mainFoodGenRef = foodGenRef;

    // more actions to be included
    playerPosArrayList = new objPosArrayList();
    playerPosArrayList->insertHead(objPos(mainGameMechsRef->getBoardSizeX() / 2, mainGameMechsRef->getBoardSizeY() / 2, '*'));
}

Player::~Player()
{
    delete playerPosArrayList;
}

objPosArrayList *Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosArrayList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic
    char input = mainGameMechsRef->getInput();
    if (input != 0) // if not null character
    {
        switch (input)
        {

        case 27: // exit
            mainGameMechsRef->setExitTrue();
            break;
        case 'w':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = UP;
            }
            break;
        case 'd':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = RIGHT;
            }
            break;
        case 's':
            if (myDir == LEFT || myDir == RIGHT || myDir == STOP)
            {
                myDir = DOWN;
            }
            break;
        case 'a':
            if (myDir == UP || myDir == DOWN || myDir == STOP)
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
    // wraparound logic
    switch (myDir)
    {
    case UP:
        if (newHead.pos->y - 1 == 0)
            newHead = (objPos(newHead.pos->x, mainGameMechsRef->getBoardSizeY() - 2, '*'));
        else
            newHead = (objPos(newHead.pos->x, newHead.pos->y - 1, '*'));
        break;
    case RIGHT:
        if (newHead.pos->x + 1 == mainGameMechsRef->getBoardSizeX() - 1)
            newHead = (objPos(1, newHead.pos->y, '*'));
        else
            newHead = (objPos(newHead.pos->x + 1, newHead.pos->y, '*'));
        break;
    case DOWN:
        if (newHead.pos->y + 1 == mainGameMechsRef->getBoardSizeY() - 1)
            newHead = (objPos(newHead.pos->x, 1, '*'));
        else
            newHead = (objPos(newHead.pos->x, newHead.pos->y + 1, '*'));
        break;
    case LEFT:
        if (newHead.pos->x - 1 == 0)
            newHead = (objPos(mainGameMechsRef->getBoardSizeX() - 2, newHead.pos->y, '*'));
        else
            newHead = (objPos(newHead.pos->x - 1, newHead.pos->y, '*'));
        break;
    default:
        break;
    }
    bool foodEaten = false;
    if (myDir != STOP)
    {
        playerPosArrayList->insertHead(newHead); // insert at head at new position
        for (int i = 1; i < playerPosArrayList->getSize(); i++)
        {
            if (newHead.pos->x == playerPosArrayList->getElement(i).pos->x && newHead.pos->y == playerPosArrayList->getElement(i).pos->y) // if collision with self detected at any point, exit/lose
            {
                mainGameMechsRef->setExitTrue();
                mainGameMechsRef->setLoseFlag();
            }
        }

        for (int i = 0; i < 5; i++)
        {
            if (mainFoodGenRef->getFoodPos()->getElement(i).pos->x == newHead.pos->x && mainFoodGenRef->getFoodPos()->getElement(i).pos->y == newHead.pos->y) // if food eaten, check if special food
            {
                foodEaten = true;
                char foodType = mainFoodGenRef->getFoodPos()->getElement(i).getSymbol();

                // Updated scoring system:
                if (foodType == 'O') {
                    mainGameMechsRef->incrementScore();  // Eating 'O' adds 1 point
                }
                else if (foodType == 'X') {
                    mainGameMechsRef->incrementScore();  // Eating 'X' adds 5 points
                    for (int j = 0; j < 4; j++)  // Adds 4 more points (total 5)
                        mainGameMechsRef->incrementScore();
                }
                else if (foodType == 'Y') {
                    mainGameMechsRef->decrementScore();  // Eating 'Y' subtracts 5 points
                    for (int j = 0; j < 4; j++)  // Subtracting 5 points when eating 'Y'
                        mainGameMechsRef->decrementScore();
                }
                mainFoodGenRef->generateFood(mainGameMechsRef->getBoardSizeX(), mainGameMechsRef->getBoardSizeY());
                break;
            }
        }
        if (!foodEaten)
            playerPosArrayList->removeTail();
    }
}

// More methods to be added