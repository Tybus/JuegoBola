/*
 * Laberynth.cpp
 *
 *  Created on: Jul 3, 2018
 *      Author: david
 */

#include <Laberynth.h>
#include <stdlib.h>
#include <list>
#include <stdio.h>
Maze::Maze(){
    //Set the size variables
    m_u8SizeX = 5;
    m_u8SizeY = 5;
    for(uint8_t l_u8IteratorX = 0; l_u8IteratorX < m_u8SizeX; l_u8IteratorX++){
        for(uint8_t l_u8IteratorY = 0; l_u8IteratorY < m_u8SizeY; l_u8IteratorY++){
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
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pDownWall = new bool(false);
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pRightWall = new bool(false);

            //Stablish adjacents
            if(l_u8IteratorX == 0 ){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall =  new bool(false);
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[0] =  NULL;
            }
            else {
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall =
                        m_SMainBoard[l_u8IteratorX - 1][l_u8IteratorY].m_pRightWall;
            }
            if(l_u8IteratorY == 0 ){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall = new bool(false);
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[2] =  NULL;
            }
            else {
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall =
                        m_SMainBoard[l_u8IteratorX][l_u8IteratorY - 1].m_pDownWall;
            }
            if(l_u8IteratorX == m_u8SizeX -1){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[1] =  NULL;
                *m_SMainBoard[l_u8IteratorX][l_u8IteratorY - 1].m_pRightWall = true;
            }
            if(l_u8IteratorY == m_u8SizeY -1){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[3] =  NULL;
                *m_SMainBoard[l_u8IteratorX][l_u8IteratorY - 1].m_pDownWall = true;
            }
        }
    }
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
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pDownWall = new bool(false);
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pRightWall = new bool(false);

            if(l_u8IteratorX == 0 ){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall =  new bool(false);
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pAdjacents[0] =  NULL;
            }
            else {
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall =
                        m_SMainBoard[l_u8IteratorX - 1][l_u8IteratorY].m_pRightWall;
            }
            if(l_u8IteratorY == 0 ){
                m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall = new bool(false);
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

            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pRightWall = false;
            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pLeftWall = false;
            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pUpWall = false;
            *m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_pDownWall = false;
            m_SMainBoard[l_u8IteratorX][l_u8IteratorY].m_bInside = false;

        }
    }
    for(uint8_t l_u8IteratorX = 0; l_u8IteratorX < m_u8SizeX;  l_u8IteratorX++){
        *m_SMainBoard[l_u8IteratorX][0].m_pUpWall = true;
        *m_SMainBoard[l_u8IteratorX][m_u8SizeY -1].m_pDownWall = true;
    }
    for(uint8_t l_u8IteratorY = 0; l_u8IteratorY < m_u8SizeY;  l_u8IteratorY++){
        *m_SMainBoard[0][l_u8IteratorY].m_pLeftWall = true;
        *m_SMainBoard[m_u8SizeX -1][l_u8IteratorY].m_pRightWall = true;
    }
}
void Maze::primMaze(void){
    uint16_t l_u16TotalSquares =25;
    uint16_t l_u16InSquareAmm = 0;
    uint16_t l_u16FrontierSquareAmm = 0;
    uint8_t l_u8RandomX = rand()%m_u8SizeX; //%5
    uint8_t l_u8RandomY = rand()%m_u8SizeY;
    Square * l_pInSquares[25]; //x,y
    Square * l_pFrontierSquares[25]; //x,y


    l_pInSquares[0] = &m_SMainBoard[l_u8RandomX][l_u8RandomY];
    l_pInSquares[0]->m_bInside = true;
    l_u16InSquareAmm++;
    printf("Current In Squeares: \n");
    for(int i = 0; i< l_u16InSquareAmm ; i++){
        printf("( %d, %d)", l_pInSquares[i]->m_u8XCoord, l_pInSquares[i]->m_u8YCoord);
    }
    printf("\n Printing maze progress: \n");
    printMaze();

    while(l_u16InSquareAmm < l_u16TotalSquares ){
        Square * l_pFrontiersToCheck[4];
        uint8_t l_u8FrontierAppendAmm = 0;
        //Check the frontiers
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
            l_u8FrontierAppendAmm++; //the adjacents are not correctly located.
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

        //Delete the barriers after adding the new box ->Here is the bug.
        uint8_t l_u8AdjacentsInsideAmm = 0;
        bool * l_pAdjacentsWalls[4];
        printf("Left Adjacent: (%d,%d)\n",
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[0]->m_u8XCoord,
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[0]->m_u8YCoord);

        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[0]->m_bInside &&
                l_pInSquares[l_u16InSquareAmm -1]->m_u8XCoord != 0 ){ //The left one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm] = l_pInSquares[l_u16InSquareAmm -1]->m_pLeftWall;
            l_u8AdjacentsInsideAmm++;
            printf("Left is inside");
        }
        printf("Right Adjacent: (%d,%d)\n",
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[1]->m_u8XCoord,
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[1]->m_u8YCoord);
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[1]->m_bInside &&
                l_pInSquares[l_u16InSquareAmm -1]->m_u8XCoord != m_u8SizeX -1){ //The Right one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm] = l_pInSquares[l_u16InSquareAmm -1]->m_pRightWall;
            l_u8AdjacentsInsideAmm++;
            printf("Right is inside");
        }
        printf("Up Adjacent: (%d,%d)\n",
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[2]->m_u8XCoord,
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[2]->m_u8YCoord);
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[2]->m_bInside &&
                l_pInSquares[l_u16InSquareAmm -1]->m_u8YCoord != 0){ //The top one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm]  = l_pInSquares[l_u16InSquareAmm -1]->m_pUpWall;
            l_u8AdjacentsInsideAmm++;
            printf("Up is inside");
        }
        printf("Down Adjacent: (%d,%d)\n",
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[3]->m_u8XCoord,
               l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[3]->m_u8YCoord);
        if(l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[3]->m_bInside &&
                l_pInSquares[l_u16InSquareAmm -1]->m_u8YCoord != m_u8SizeY -1){ //The Bottom one is also inside
            l_pAdjacentsWalls[l_u8AdjacentsInsideAmm]  = l_pInSquares[l_u16InSquareAmm -1]->m_pDownWall;
            l_u8AdjacentsInsideAmm++;
            printf("Down is inside");
        }
        if(l_u8AdjacentsInsideAmm > 1 ){
            l_u8Random = rand()%l_u8AdjacentsInsideAmm;
            *l_pAdjacentsWalls[l_u8Random] = true;
        }
        printf("Current In Squeares: \n");
        for(int i = 0; i< l_u16InSquareAmm ; i++){
            printf("( %d, %d)", l_pInSquares[i]->m_u8XCoord, l_pInSquares[i]->m_u8YCoord);
        }
        printf("\n Printing maze progress: \n");
        printMaze();
    }
}
void Maze::printMaze(){
    printf("\n _ _ _ _ _\n");

    for(int j = 0 ; j< 5 ; j++){
        printf("|");
        for(int i = 0 ; i< 5; i++){
            if(*m_SMainBoard[i][j].m_pDownWall == true)
                printf("_");
            else
                printf(" ");
            if(*m_SMainBoard[i][j].m_pRightWall == true)
                printf("|");
            else
                printf(" ");
        }
        printf("\n");
    }
}
uint8_t Maze::checkColition(uint8_t i_u8CurrentX,
                                 uint8_t i_u8CurrentY,
                                 uint8_t i_u8NextX,
                                 uint8_t i_u8NextY){
    uint8_t l_u8XSquare, l_u8YSquare;
    uint8_t l_u8MaxX, l_u8MinX, l_u8MaxY, l_u8MinY;
    uint8_t l_u8ReturnValue = 0;
    int16_t l_u8XDistance = 0;
    int16_t l_u8YDistance = 0;
    Square *l_pCurrentSquare;
    //X and Y Should be greater than or equal to 8.
    l_u8XSquare = (i_u8CurrentX -8) / 24; //Whole values.
    l_u8YSquare = (i_u8CurrentY -8) / 24;
    //Set the max values:
    l_u8MaxX = i_u8CurrentX + 3;
    l_u8MinX = i_u8CurrentX - 3;
    l_u8MaxY = i_u8CurrentY + 3;
    l_u8MinY = i_u8CurrentY - 3;
    //load the Square location
    l_pCurrentSquare = &m_SMainBoard[l_u8XSquare][l_u8YSquare];

    if(l_u8MinX <= 7 + l_u8XSquare*24){ //If the ball is stuck in the left wall.
        if(*l_pCurrentSquare->m_pLeftWall)
            l_u8ReturnValue |= LCOLITION;
    }
    else if(l_u8MaxX >= (l_u8XSquare + 1 )*24){
        if(*l_pCurrentSquare->m_pRightWall)
            l_u8ReturnValue |= RCOLITION;
    }

    if(l_u8MinY <= 7 + l_u8YSquare*24){ //If the ball is stuck in the left wall.
        if(*l_pCurrentSquare->m_pUpWall)
            l_u8ReturnValue |= UCOLITION;
    }
    else if(l_u8MaxY >= (l_u8YSquare + 1 )*24){
        if(*l_pCurrentSquare->m_pDownWall)
            l_u8ReturnValue |= DCOLITION;
    }
    //Detect if quantum jump TBD.
    if(l_u8ReturnValue != 0 &&
            ((i_u8CurrentX - i_u8NextX != 1 ||
                    i_u8CurrentX - i_u8NextX != -1) ||
                    (i_u8CurrentY - i_u8NextY != 1 ||
                            i_u8CurrentY - i_u8NextY != -1))){
        l_u8ReturnValue |= QUANTUM;
    }

    //Hole TBD.
    for(int i = 0; i< m_u8HoleAmmount; i++){
        l_u8XDistance = i_u8CurrentX - m_aHoles[i][0];
        l_u8YDistance = i_u8CurrentY - m_aHoles[i][1];

        l_u8XDistance = abs(l_u8XDistance);

        l_u8YDistance = abs(l_u8YDistance);

        if(l_u8XDistance <= 3 && l_u8YDistance <= 3){
            if(sqrt(l_u8XDistance*l_u8XDistance + l_u8YDistance*l_u8YDistance) <= 3 )
                l_u8ReturnValue |= HOLE;
        }

    }
    return l_u8ReturnValue;
}
void Laberynth::printMaze(){
    m_Maze.printMaze();

}
Laberynth::Laberynth(){
    this->generateLaberynth();
}
void Laberynth::generateLaberynth(void){
    m_Maze.resetMaze();
    printf("Reset Maze: \n");
    m_Maze.printMaze();
    m_Maze.primMaze();
}
uint8_t Laberynth::checkColition(uint8_t i_u8CurrentX,
                                 uint8_t i_u8CurrentY,
                                 uint8_t i_u8NextX,
                                 uint8_t i_u8NextY){
    uint8_t l_u8ReturnValue;
    l_u8ReturnValue = m_Maze.checkColition(i_u8CurrentX,
                                 i_u8CurrentY,
                                 i_u8NextX,
                                 i_u8NextY);


    return l_u8ReturnValue;
}

Laberynth::~Laberynth()
{
    // TODO Auto-generated destructor stub
}

