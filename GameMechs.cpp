#include "GameMechs.h" //doneeeeeeeeeeee
// dhruv edits done (most of this stuff was given)

GameMechs::GameMechs()
{
    boardSizeX = 30;
    boardSizeY = 15;

    exitFlag = false;
    loseFlag = false;

    score = 0;
    input = 0;

    srand(time(NULL));
    foodPos = objPos(0, 0, 'O');
}

GameMechs::GameMechs(int boardX, int boardY)
{
    boardSizeX = boardX;
    boardSizeY = boardY; 
    
    score = 0;
    input = 0;

    exitFlag = false;
    loseFlag = false;
}

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}

void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here
void GameMechs::decrementScore()
{
    score--;
}