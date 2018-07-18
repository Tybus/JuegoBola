/*
 * Laberynth.h
 *
 *  Created on: Jul 3, 2018
 *      Author: david
 */

#ifndef LABERYNTH_H_
#define LABERYNTH_H_

#define __FORE_GROUND_COLOR 0x00FFFF00
#define __BALL_COLOR 0x000000FF
#define RCOLITION 0b000001
#define LCOLITION 0b000010
#define UCOLITION 0b000100
#define DCOLITION 0b001000
#define HOLE      0b010000
#define QUANTUM   0b100000

#define RWALL     0b000001
#define LWALL     0b000010
#define UWALL     0b000100
#define DWALL     0b001000

#include <stdint.h>
#include <math.h>
extern "C"{
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
}
class Maze{
    struct Square{
        uint8_t m_u8XCoord;
        uint8_t m_u8YCoord;
        bool * m_pLeftWall;
        bool * m_pRightWall;
        bool * m_pUpWall;
        bool * m_pDownWall;
        bool m_bFrontier;
        bool m_bInside;
        Square * m_pAdjacents[4]; //Left Right Up Down

    };
public:
    Maze();
    Maze(uint8_t i_u8SizeX, uint8_t i_u8SizeY);
    void resetMaze(void);
    void primMaze(void);
    void printMaze(void);
    uint8_t checkColition(uint8_t i_u8CurrentX,uint8_t i_u8CurrentY);
    void drawLaberynth(int i_iLaberynthColor, Graphics_Context *i_GContext);
    uint8_t * get_m_u8HoleAmmount(void);
    uint8_t * get_m_u8lvl(void);
    uint8_t * get_m_aHoles(void);
    uint8_t m_aHoles[127][2];

private:
    void coordToSqueare(uint8_t i_u8XCoord, uint8_t i_u8YCoord, uint8_t * o_pRetCoord);
    void WallToCoord(uint8_t i_u8XSquare, uint8_t i_u8YSquare, uint8_t i_u8Wall ,uint8_t *o_pRetCoord);
    uint8_t m_u8SizeX;
    uint8_t m_u8SizeY;
    Square m_SMainBoard[5][5];
    //uint8_t m_aHoles[127][2];
    uint8_t m_u8HoleAmmount;
    uint8_t m_u8lvl;
    uint8_t m_aRectCoords[60][4];
    uint8_t m_u8NumberOfRects;
    uint8_t BallTouches(uint8_t i_u8BallX, uint8_t i_u8BallY);
    uint8_t CheckCorners(uint8_t i_u8BallX, uint8_t i_u8BallY);
};

class Laberynth{
public:
    Laberynth();
    virtual ~Laberynth();
    uint8_t checkColition(uint8_t i_u8CurrentX,uint8_t i_u8CurrentY);
    void printMaze();
    void drawLaberynth(int i_iLaberynthColor, Graphics_Context *i_GContext);
    Maze m_Maze;
private:
    void generateLaberynth(void);
    //Maze m_Maze;

};

#endif /* LABERYNTH_H_ */
