/*
 * Laberynth.h
 *
 *  Created on: Jul 3, 2018
 *      Author: david
 */

#ifndef LABERYNTH_H_
#define LABERYNTH_H_
#include <stdint.h>
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
private:
    uint8_t m_u8SizeX;
    uint8_t m_u8SizeY;
    Square m_SMainBoard[5][5];
};

class Laberynth{
public:
    Laberynth();
    virtual ~Laberynth();
    uint8_t checkColition(uint8_t i_u8CurrentX,uint8_t i_u8CurrentY,uint8_t i_u8NextX,uint8_t i_u8NextY);
    void printMaze();
private:
    void generateLaberynth(void);
    Maze m_Maze;

};

#endif /* LABERYNTH_H_ */
