#include <iostream> //doneeeeeeeeeeeeeeeeee
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"

using namespace std;

#define DELAY_CONST 100000

GameMechs *mainGameMechs;

Player *mainPlayer;
Food *mainFoodBucket;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (!mainGameMechs->getExitFlagStatus())
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}

void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    mainGameMechs = new GameMechs();
    mainPlayer = new Player(mainGameMechs, mainFoodBucket);
    mainFoodBucket = new Food(mainPlayer);
    mainPlayer = new Player(mainGameMechs, mainFoodBucket);
    mainFoodBucket->generateFood(mainGameMechs->getBoardSizeX(), mainGameMechs->getBoardSizeY());
}

void GetInput(void)
{
    if (MacUILib_hasChar())
        mainGameMechs->setInput(MacUILib_getChar());
}

void RunLogic(void)
{
    mainPlayer->updatePlayerDir();
    mainPlayer->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("Snake!\n (O = Regular food, X = +20 score, Y = -5 length)\n");

    // Iterate over the entire board
    for (int i = 0; i < mainGameMechs->getBoardSizeY(); i++)
    {
        for (int j = 0; j < mainGameMechs->getBoardSizeX(); j++)
        {
            // Draw the border
            if (i == 0 || j == 0 || i == (mainGameMechs->getBoardSizeY() - 1) || j == (mainGameMechs->getBoardSizeX() - 1))
            {
                MacUILib_printf("#");
            }
            else
            {
                bool printed = false; // Flag to track if we've printed something

                // First, print the snake
                for (int k = 0; k < mainPlayer->getPlayerPos()->getSize(); k++)
                {
                    if (mainPlayer->getPlayerPos()->getElement(k).pos->x == j && mainPlayer->getPlayerPos()->getElement(k).pos->y == i)
                    {
                        MacUILib_printf("%c", mainPlayer->getPlayerPos()->getElement(k).getSymbol());
                        printed = true;
                        break; // Stop here if we printed the snake part
                    }
                }

                // Then, print food, but only if this spot wasn't taken by the snake
                if (!printed)
                {
                    for (int k = 0; k < 5; k++)
                    {
                        if (mainFoodBucket->getFoodPos()->getElement(k).pos->x == j && mainFoodBucket->getFoodPos()->getElement(k).pos->y == i)
                        {
                            MacUILib_printf("%c", mainFoodBucket->getFoodPos()->getElement(k).getSymbol());
                            printed = true;
                            break; // Stop here if we printed the food
                        }
                    }
                }

                // If neither the snake nor food were printed, print an empty space
                if (!printed)
                    MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n");
    }

    // Display score and game over message if needed
    MacUILib_printf("Score: %d\n", mainGameMechs->getScore());
    if (mainGameMechs->getLoseFlagStatus())
        MacUILib_printf("You Lose");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    delete mainGameMechs;
    delete mainPlayer;
    delete mainFoodBucket;
    MacUILib_uninit();
}