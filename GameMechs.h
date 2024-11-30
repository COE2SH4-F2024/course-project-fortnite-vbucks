#ifndef GAMEMECHS_H //doneeeeeeeeeeeeee
//dhruv edits done
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>

#include "objPos.h"
#include "objPosArrayList.h"

using namespace std;

class GameMechs
{
private:
    char input;
    bool exitFlag;
    bool loseFlag;
    int score;

    int boardSizeX;
    int boardSizeY;

    objPos foodPos; //change to foodP

public:
    GameMechs();
    GameMechs(int boardX, int boardY);
    ~GameMechs(); // is this one needed at all? Why or why not?

    bool getExitFlagStatus() const;
    void setExitTrue();
    bool getLoseFlagStatus() const;
    void setLoseFlag();

    char getInput() const;
    void setInput(char this_input);
    void clearInput();

    int getBoardSizeX() const;
    int getBoardSizeY() const;

    int getScore() const;
    void incrementScore();
    void decrementScore(); //decremement method
};

#endif
