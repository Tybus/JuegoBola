/*
 * Laberynth.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: david
 */

#include <Laberynth.h>
#include <stdlib.h>
#include <list>
Maze::Maze(){

}
Maze::Maze(uint8_t i_u8SizeX, uint8_t i_u8SizeY){
    //Set the size variables
    m_u8SizeX = i_u8SizeX;
    m_u8SizeY = i_u8SizeY;
    for(uint8_t l_u8IteratorX = 0; l_u8IteratorX < i_u8SizeX; l_u8IteratorX++){
        for(uint8_t l_u8IteratorY = 0; l_u8IteratorY < i_u8SizeY; l_u8IteratorY++){
            //Set the coordenate of the square.
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_u8XCoord = l_u8IteratorX;
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_u8YCoord = l_u8IteratorY;

            //Set the adjacent squares //Array Out of bounds error to fix
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[0] =
                    &m_SMainBoard[l_u8IteratorX - 1][l_u8IteratorY]; //Left Square
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[1] =
                    &m_SMainBoard[l_u8IteratorX + 1][l_u8IteratorY]; //Right Square
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[2] =
                    &m_SMainBoard[l_u8IteratorX][l_u8IteratorY - 1]; //Up Square
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[3] =
                    &m_SMainBoard[l_u8IteratorX][l_u8IteratorY + 1]; //Down Square

            //Create the new walls.
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pDownWall = new bool(true);
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pRightWall = new bool(true);

            if(l_u8IteratorX == 0 ){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall =  new bool(true);
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[0] =  NULL;
            }
            else {
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall =
                        m_SMainBoard[l_u8IteratorX - 1][l_u8IteratorY].m_pRightWall;
            }
            if(l_u8IteratorY == 0 ){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall = new bool(true);
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[2] =  NULL;
            }
            else {
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall =
                        m_SMainBoard[l_u8IteratorX][l_u8IteratorY - 1].m_pDownWall;
            }
            if(l_u8IteratorX == i_u8SizeX -1){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[1] =  NULL;
            }
            if(l_u8IteratorY == i_u8SizeY -1){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[3] =  NULL;
            }
        }
    }
}
void Maze::resetMaze(void){
    for(uint8_t l_u8IteratorX = 0; l_u8IteratorX < m_u8SizeX;  l_u8IteratorX++){
        for(uint8_t l_u8IteratorY = 0; l_u8IteratorY < m_u8SizeY; l_u8IteratorY++){

            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pDownWall = true;
            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pRightWall = true;
            *m_SMainBoard[l_u8IteratorY][l_u8IteratorY].m_pLeftWall = true;
            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall = true;
            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pDownWall = true;

        }
    }
}
void Maze::primMaze(void){
    uint16_t l_u16TotalSquares = m_u8SizeX*m_u8SizeY;
    uint16_t l_u16InSquareAmm = 0;
    uint16_t l_u16FrontierSquareAmm = 0;
    uint8_t l_u8RandomX = rand()%m_u8SizeX; //%5
    uint8_t l_u8RandomY = rand()%m_u8SizeY;
    Square * l_pInSquares[l_u16TotalSquares]; //x,y
    Square * l_pFrontierSquares[l_u16TotalSquares]; //x,y


    l_pInSquares[0] = &m_SMainBoard[l_u8RandomX][l_u8RandomY];
    l_pInSquares[0]->m_bInside = true;
    l_u16InSquareAmm++;

    while(l_u16InSquareAmm < l_u16TotalSquares ){
        Square * l_pFrontiersToCheck[4];
        uint8_t l_u8FrontierAppendAmm = 0;
        if(l_pInSquares[l_u16InSquareAmm -1 ]->m_u8XCoord != 0){ //Just the left one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                    l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[0];
            l_u8FrontierAppendAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1]->m_u8XCoord != m_u8SizeX -1 ){ // Just the right one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                    l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[1];
            l_u8FrontierAppendAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1 ]->m_u8YCoord != 0){ //Just the top one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                     l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[2];
            l_u8FrontierAppendAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1 ]->m_u8YCoord != m_u8SizeY -1){ //Just the bottom one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                     l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[3];
            l_u8FrontierAppendAmm++;
        }

        for(int i = 0;  i< l_u8FrontierAppendAmm ; i++){
            bool l_bAppend = 1;
            for(int j = 0; j < l_u16FrontierSquareAmm ; j++){
                if(l_pFrontiersToCheck[i] == l_pFrontierSquares[j]){
                    l_bAppend = 0;
                    break;
                }
            }
            if(l_bAppend){
                l_pFrontierSquares[l_u16FrontierSquareAmm] = l_pFrontiersToCheck[i];
                l_u16FrontierSquareAmm++;
            }
        }

        for(int j = 0; j < l_u16InSquareAmm ; j++){
            for(int i = 0; i < l_u16FrontierSquareAmm ; i++){
                if(l_pInSquares[j] == l_pFrontierSquares[i]){
                    l_pFrontierSquares[i] = l_pFrontierSquares[l_u16FrontierSquareAmm -1];
                    l_u16FrontierSquareAmm--;
                    break;
                }

            }
        }
        //Add a random adyacent to the In
        uint8_t l_u8Random = rand()%l_u16FrontierSquareAmm;
        l_pInSquares[l_u16InSquareAmm] = l_pFrontierSquares[l_u8Random];
        l_pInSquares[l_u16InSquareAmm]->m_bInside = true;
        l_u16InSquareAmm++;

        //Remove the square form the frontier
        l_pFrontierSquares[l_u8Random] = l_pFrontierSquares[l_u16FrontierSquareAmm -1];
        l_u16FrontierSquareAmm--;

        //Delete the barriers after adding the new box
        uint8_t l_u8AdjacentsInsideAmm = 0;
        bool * l_pAdjacentsWalls[4];
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[0]->m_bInside){ //The left one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm] = l_pInSquares[l_u16InSquareAmm -1]->m_pLeftWall;
            l_u8AdjacentsInsideAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[1]->m_bInside){ //The Right one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm] = l_pInSquares[l_u16InSquareAmm -1]->m_pRightWall;
            l_u8AdjacentsInsideAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[2]->m_bInside){ //The top one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm]  = l_pInSquares[l_u16InSquareAmm -1]->m_pUpWall;
            l_u8AdjacentsInsideAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[3]->m_bInside){ //The Bottom one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm]  = l_pInSquares[l_u16InSquareAmm -1]->m_pDownWall;
            l_u8AdjacentsInsideAmm++;
        }
        l_u8Random = rand()%l_u8AdjacentsInsideAmm;
        *l_pAdjacentsWalls[l_u8Random] = false;
    }
}
Laberynth::Laberynth(){
    m_Maze = Maze(5,5);
    this->generateLaberynth();
}
void Laberynth::generateLaberynth(void){
    m_Maze.resetMaze();
    m_Maze.primMaze();
}
Laberynth::~Laberynth()
{
    // TODO Auto-generated destructor stub
}

