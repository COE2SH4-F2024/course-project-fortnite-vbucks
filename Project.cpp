#include <iostream> //doneeeeeeeeeeeeeeeeee
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
//dhruv edits done
using namespace std;

#define DELAY_CONST 100000

GameMechs *mechanics; 
Player *current_Player;  
Food *foodGen;  

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while (!mechanics->getExitFlagStatus()) 
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

    mechanics = new GameMechs();

    current_Player = new Player(mechanics, foodGen);  
    foodGen = new Food(current_Player); 
    current_Player = new Player(mechanics, foodGen); 
    foodGen->generateFood(mechanics->getBoardSizeX(), mechanics->getBoardSizeY()); 
}

void GetInput(void)
{
    if(MacUILib_hasChar())
    {
         mechanics->setInput(MacUILib_getChar()); 
    }
       
}

void RunLogic(void)
{
    current_Player->updatePlayerDir();  
    current_Player->movePlayer();  
}

void DrawScreen(void)
{
    MacUILib_clearScreen();
    MacUILib_printf("Snake!\nWatch your step(slither)...\nFood Menu:O = +1 point, X = +5 points, Y = -5 points\n");

    // Iterate over the entire board
    for(int i = 0; i < mechanics->getBoardSizeY(); i++) //create the board
    {
        for(int j = 0; j < mechanics->getBoardSizeX(); j++)  
        {
            //border gen
            if(i == 0 || j == 0 || i == (mechanics->getBoardSizeY() - 1) || j == (mechanics->getBoardSizeX() - 1))
            {
                MacUILib_printf("#");
            }
            else
            {
                bool printed = false; //Track if we've printed something

                //print snake
                for(int k = 0; k < current_Player->getPlayerPos()->getSize(); k++) 
                {
                    if(current_Player->getPlayerPos()->getElement(k).pos->x == j && current_Player->getPlayerPos()->getElement(k).pos->y == i) 
                    {
                        MacUILib_printf("%c", current_Player->getPlayerPos()->getElement(k).getSymbol());  
                        printed = true;
                        break; //stop if snake printed
                    }
                }

                //print food in empty spot
                if(!printed)
                {
                    for(int k = 0; k < 5; k++)
                    {
                        if(foodGen->getFoodPos()->getElement(k).pos->x == j && foodGen->getFoodPos()->getElement(k).pos->y == i)
                        {
                            MacUILib_printf("%c", foodGen->getFoodPos()->getElement(k).getSymbol()); 
                            printed = true;
                            break; //stop if food generated
                        }
                    }
                }

                //print empty space if no food or snake parts
                if(!printed)
                {
                    MacUILib_printf(" ");
                }
                    
            }
        }
        MacUILib_printf("\n");
    }

    //quit instruction and score
    MacUILib_printf("Score: %d\nESC to quit\n", mechanics->getScore());

    if(mechanics->getLoseFlagStatus())//game over message
    {
        MacUILib_printf("Game Over");
    }
        
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}

void CleanUp(void)
{
    delete mechanics; 
    delete current_Player; 
    delete foodGen; 
    MacUILib_uninit();
}