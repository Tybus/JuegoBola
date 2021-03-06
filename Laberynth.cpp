/*
 * Laberynth.cpp
 *
 *  Created on: jul 3, 2018
 *      Author: david
 */

#include <Laberynth.h>
#include <stdlib.h>
#include <list>
#include <stdio.h>
Graphics_Context g_sContext;
Maze::Maze(){
    //Set the size variables
    m_u8lvl = 0;
    m_u8HoleAmmount = m_u8lvl;
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

    m_u8lvl++;
    m_u8HoleAmmount++;
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
        if(l_pInSquares[l_u16InSquareAmm -1 ]->m_u8XCoord != 0){ //just the left one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                    l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[0];
            l_u8FrontierAppendAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1]->m_u8XCoord != m_u8SizeX -1 ){ // just the right one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                    l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[1];
            l_u8FrontierAppendAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1 ]->m_u8YCoord != 0){ //just the top one
            l_pFrontiersToCheck[l_u8FrontierAppendAmm] =
                     l_pInSquares[l_u16InSquareAmm -1]->m_pAdjacents[2];
            l_u8FrontierAppendAmm++;
        }
        if(l_pInSquares[l_u16InSquareAmm -1 ]->m_u8YCoord != m_u8SizeY -1){ //just the bottom one
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
    //Generate holes.
    uint8_t l_u8RandomX2;
    uint8_t l_u8RandomY2;
    uint8_t l_u8HoleX;
    uint8_t l_u8HoleY;
    uint8_t l_aSquareCoords[4];
    for(int i = 0; i< m_u8HoleAmmount; i++){
        l_u8RandomX = rand()%m_u8SizeX; //%5
        l_u8RandomY = rand()%m_u8SizeY;
        l_u8RandomX2 = rand()%8 + 12;
        l_u8RandomY2 = rand()%8 + 12;

        WallToCoord(l_u8RandomX, l_u8RandomY,0, l_aSquareCoords);

        l_u8HoleX = l_aSquareCoords[0] +l_u8RandomX2;

        WallToCoord(l_u8RandomX, l_u8RandomY, 2, l_aSquareCoords);

        l_u8HoleY = l_aSquareCoords[2] + l_u8RandomY2;

        m_aHoles[i][0] = l_u8HoleX;
        m_aHoles[i][1] = l_u8HoleY;


    }
    //Save the rects into coordinates
    uint8_t l_aCoordinates[4];
    m_u8NumberOfRects = 0;
    for(int i = 0; i<5 ;i++){
        WallToCoord(0,i,0, l_aCoordinates);
        m_aRectCoords[m_u8NumberOfRects][0] = l_aCoordinates[0];
        m_aRectCoords[m_u8NumberOfRects][1] = l_aCoordinates[1];
        m_aRectCoords[m_u8NumberOfRects][2] = l_aCoordinates[2];
        m_aRectCoords[m_u8NumberOfRects][3] = l_aCoordinates[3];
        m_u8NumberOfRects++;
        WallToCoord(i,0,2, l_aCoordinates);
        m_aRectCoords[m_u8NumberOfRects][0] = l_aCoordinates[0];
        m_aRectCoords[m_u8NumberOfRects][1] = l_aCoordinates[1];
        m_aRectCoords[m_u8NumberOfRects][2] = l_aCoordinates[2];
        m_aRectCoords[m_u8NumberOfRects][3] = l_aCoordinates[3];
        m_u8NumberOfRects++;
    }
    for(int i = 0; i<5; i++){
        for(int j = 0; j<5; j++){
            if(*m_SMainBoard[i][j].m_pRightWall == true){
                WallToCoord(i, j, 1, l_aCoordinates);
                m_aRectCoords[m_u8NumberOfRects][0] = l_aCoordinates[0];
                m_aRectCoords[m_u8NumberOfRects][1] = l_aCoordinates[1];
                m_aRectCoords[m_u8NumberOfRects][2] = l_aCoordinates[2];
                m_aRectCoords[m_u8NumberOfRects][3] = l_aCoordinates[3];
                m_u8NumberOfRects++;
            }
            if(*m_SMainBoard[i][j].m_pDownWall == true){
                WallToCoord(i,j,3,l_aCoordinates);
                m_aRectCoords[m_u8NumberOfRects][0] = l_aCoordinates[0];
                m_aRectCoords[m_u8NumberOfRects][1] = l_aCoordinates[1];
                m_aRectCoords[m_u8NumberOfRects][2] = l_aCoordinates[2];
                m_aRectCoords[m_u8NumberOfRects][3] = l_aCoordinates[3];
                m_u8NumberOfRects++;
            }
        }
    }

}
uint8_t Maze::BallTouches(uint8_t i_u8BallX, uint8_t i_u8BallY){

    uint8_t l_u8MinX = i_u8BallX - 4;
    uint8_t l_u8MaxX = i_u8BallX + 4;
    uint8_t l_u8MinY = i_u8BallY - 4;
    uint8_t l_u8MaxY = i_u8BallY + 4;
    uint8_t l_u8RetVal = 0;

    for(int i = 0; i<m_u8NumberOfRects; i++){
        if(l_u8MinX == m_aRectCoords[i][1] && // Ball Min is block max
                i_u8BallY >= m_aRectCoords[i][2] && // Ball Y more than Y min
                i_u8BallY <= m_aRectCoords[i][3]){ // Ball Y Less tan Y Max
            l_u8RetVal |= LWALL; //It touches the Down Wall
        }
        if(l_u8MaxX == m_aRectCoords[i][0] && // Ball Max is block min
                i_u8BallY >= m_aRectCoords[i][2] && // Ball Y more than Y min
                i_u8BallY <= m_aRectCoords[i][3]){ // Ball Y Less tan Y Max
            l_u8RetVal |= RWALL; //It Touches the Down Wall

        }
        if(l_u8MinY == m_aRectCoords[i][3] && // Ball Min is block max
                i_u8BallX >= m_aRectCoords[i][0] && // Ball X more than X min
                i_u8BallX <= m_aRectCoords[i][1]){ // Ball X Less tan X Max
            l_u8RetVal |= UWALL;
        }
        if(l_u8MaxY == m_aRectCoords[i][2] && // Ball Max is block min
                i_u8BallX >= m_aRectCoords[i][0] && // Ball X more than X min
                i_u8BallX <= m_aRectCoords[i][1]){ // Ball X Less tan X Max
            l_u8RetVal |= DWALL;
        }
    }
    l_u8RetVal |= CheckCorners(i_u8BallX, i_u8BallY);
    return l_u8RetVal;
}
uint8_t Maze::CheckCorners(uint8_t i_u8BallX, uint8_t i_u8BallY){
    /*
    uint8_t l_u8MinX = i_u8BallX - 4;
    uint8_t l_u8MaxX = i_u8BallX + 4;
    uint8_t l_u8MinY = i_u8BallY - 4;
    uint8_t l_u8MaxY = i_u8BallY + 4;
    uint8_t l_u8TopLeftCorner[2];
    uint8_t l_u8TopRightCorner[2];
    uint8_t l_u8BottomLeftCorner[2];
    uint8_t l_u8BottomRightCorner[2];

    l_u8TopLeftCorner[0] = l_u8MinX -1;
    l_u8TopLeftCorner[1] = l_u8MinY -1;

    l_u8TopRightCorner[0] = l_u8MaxX +1;
    l_u8TopRightCorner[1] = l_u8MinY -1;

    l_u8BottomLeftCorner[0] = l_u8MinX -1;
    l_u8BottomLeftCorner[1] = l_u8MinY +1;

    l_u8BottomRightCorner[0] = l_u8MaxX +1;
    l_u8BottomRightCorner[1] = l_u8MaxY +1;

    uint8_t l_u8RetVal = 0;

    for(int i = 0;  i< m_u8NumberOfRects; i++){
        if(l_u8TopLeftCorner[0] == m_aRectCoords[i][1] && //RectX Max
                l_u8TopLeftCorner[1] == m_aRectCoords[i][2]){ //RectY Min
            l_u8RetVal |= UWALL | LWALL;
        }
        if(l_u8TopRightCorner[0] == m_aRectCoords[i][0] &&// RectX Min
                l_u8TopRightCorner[1] == m_aRectCoords[i][3]){ //RectY Max
            l_u8RetVal |= UWALL | RWALL;
        }
        if(l_u8BottomLeftCorner[0] == m_aRectCoords[i][1] && //RectX Max
                l_u8BottomLeftCorner[1] == m_aRectCoords[i][3] ){ //RectY Max
            l_u8RetVal |= DWALL | LWALL;
        }
        if(l_u8BottomRightCorner[0] == m_aRectCoords[i][0] && //RectX Min
                l_u8BottomRightCorner[1] == m_aRectCoords[i][2] ){ //RectY Min
            l_u8RetVal |= DWALL | RWALL;
        }

    }

    return l_u8RetVal;
    */
    return 0;
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
                                 uint8_t i_u8CurrentY){
    uint8_t l_u8XDistance;
    uint8_t l_u8YDistance;
    uint8_t l_u8ReturnValue = 0;

    l_u8ReturnValue |= BallTouches(i_u8CurrentX, i_u8CurrentY);

    //Hole TBD.
    for(int i = 0; i< m_u8HoleAmmount; i++){
        l_u8XDistance = i_u8CurrentX - m_aHoles[i][0];
        l_u8YDistance = i_u8CurrentY - m_aHoles[i][1];

        l_u8XDistance = abs(l_u8XDistance);

        l_u8YDistance = abs(l_u8YDistance);

        if(l_u8XDistance <= 3 && l_u8YDistance <= 3){
            if(sqrt(l_u8XDistance*l_u8XDistance + l_u8YDistance*l_u8YDistance) <= 3 ){
                //resetMaze();
                //primMaze();
                //drawLaberynth(__BALL_COLOR, &g_sContext);
                l_u8ReturnValue |= HOLE;
            }
        }

    }
    //Win condition
    l_u8XDistance = i_u8CurrentX - (119 - 4);
    l_u8YDistance = i_u8CurrentY - (119 - 4);
    l_u8XDistance = abs(l_u8XDistance);
    l_u8YDistance = abs(l_u8YDistance);

    if(l_u8XDistance <= 3 && l_u8YDistance <= 3){
        if(sqrt(l_u8XDistance*l_u8XDistance + l_u8YDistance*l_u8YDistance) <= 3 ){

            resetMaze();
            primMaze();
            drawLaberynth(__BALL_COLOR, &g_sContext);
            l_u8ReturnValue |= HOLE;
        }
    }

    return l_u8ReturnValue;
}
void Maze::drawLaberynth(int i_iLaberynthColor, Graphics_Context *i_pContext){
    Graphics_Rectangle l_GraphicsRectangle;
    Graphics_clearDisplay(i_pContext);
    Graphics_setForegroundColor(&g_sContext, __FORE_GROUND_COLOR);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    l_GraphicsRectangle.xMax = 0; l_GraphicsRectangle.xMin = 127;
    l_GraphicsRectangle.yMax = 0; l_GraphicsRectangle.yMin = 127;
    Graphics_fillRectangle(i_pContext,&l_GraphicsRectangle);
    Graphics_setForegroundColor(i_pContext, __BALL_COLOR);


    //First draw the border.
    l_GraphicsRectangle.xMin = 0;
    l_GraphicsRectangle.xMax = 7;
    l_GraphicsRectangle.yMin = 0;
    l_GraphicsRectangle.yMax = 127;
    Graphics_fillRectangle(i_pContext, &l_GraphicsRectangle);

    l_GraphicsRectangle.xMin = 120;
    l_GraphicsRectangle.xMax = 127;
    l_GraphicsRectangle.yMin = 0;
    l_GraphicsRectangle.yMax = 127;
    Graphics_fillRectangle(i_pContext, &l_GraphicsRectangle);

    l_GraphicsRectangle.xMin = 0;
    l_GraphicsRectangle.xMax = 127;
    l_GraphicsRectangle.yMin = 0;
    l_GraphicsRectangle.yMax = 7;
    Graphics_fillRectangle(i_pContext, &l_GraphicsRectangle);

    l_GraphicsRectangle.xMin = 0;
    l_GraphicsRectangle.xMax = 127;
    l_GraphicsRectangle.yMin = 120;
    l_GraphicsRectangle.yMax = 127;
    Graphics_fillRectangle(i_pContext, &l_GraphicsRectangle);

    //Then draw the maze

    for(int i = 0; i<m_u8SizeX; i++){
        for(int j = 0; j <m_u8SizeY; j++){
            if(*m_SMainBoard[i][j].m_pRightWall){
                l_GraphicsRectangle.xMin = 24*(i +1);
                l_GraphicsRectangle.xMax = 24*(i +1) + 6;
                l_GraphicsRectangle.yMin = 24*j;
                l_GraphicsRectangle.yMax = 24*(j+1) + 6 ;
                Graphics_fillRectangle(i_pContext, &l_GraphicsRectangle);

            }
            if(*m_SMainBoard[i][j].m_pDownWall){
                l_GraphicsRectangle.yMin = 24*(j+1);
                l_GraphicsRectangle.yMax = 24*(j+1) +6;
                l_GraphicsRectangle.xMin = 24*i;
                l_GraphicsRectangle.xMax = 24*(i+1) + 6;

                Graphics_fillRectangle(i_pContext, &l_GraphicsRectangle);

            }
        }
    }
    //Then draw the circles.
    for(int i = 0; i< m_u8HoleAmmount; i++){
        Graphics_fillCircle(i_pContext, m_aHoles[i][0], m_aHoles[i][1], 3);
    }
    Graphics_fillCircle(i_pContext, 119-4, 119-4, 3);

}
void Maze::coordToSqueare(uint8_t i_u8XCoord, uint8_t i_u8YCoord, uint8_t * o_pRetCoord){

    o_pRetCoord[0] = (i_u8XCoord -8) / 24; //Whole values.
    o_pRetCoord[1] = (i_u8YCoord -8) / 24;

}
void Maze::WallToCoord(uint8_t i_u8XSquare, uint8_t i_u8YSquare, uint8_t i_u8Wall ,uint8_t *o_pRetCoord){
    switch(i_u8Wall){
    case 0: //Left Wall
        o_pRetCoord[0] = 24*i_u8XSquare ;//Xmin
        o_pRetCoord[1] = 24*i_u8XSquare +6; //Xmax
        o_pRetCoord[2] = 24*i_u8YSquare; //Ymin
        o_pRetCoord[3] = 24*(i_u8YSquare +1) + 6 ; //Ymax
        break;
    case 1: //Right Wall
        o_pRetCoord[0] = 24*(i_u8XSquare +1);
        o_pRetCoord[1] = 24*(i_u8XSquare +1) + 6;
        o_pRetCoord[2] = 24*i_u8YSquare;
        o_pRetCoord[3] = 24*(i_u8YSquare+1) + 6 ;
        break;
    case 2: //Up Wall
        o_pRetCoord[2] = 24*i_u8YSquare ;//Xmin
        o_pRetCoord[3] = 24*i_u8YSquare +6; //Xmax
        o_pRetCoord[0] = 24*i_u8XSquare; //Ymin
        o_pRetCoord[1] = 24*(i_u8XSquare +1) + 6 ; //Ymax
        break;

    case 3: //Down Wall
        o_pRetCoord[2] = 24*(i_u8YSquare+1);
        o_pRetCoord[3] = 24*(i_u8YSquare+1) +6;
        o_pRetCoord[0] = 24*i_u8XSquare;
        o_pRetCoord[1] = 24*(i_u8XSquare+1) + 6;
        break;
    }

}

uint8_t* Maze::get_m_u8HoleAmmount(void){ return & m_u8HoleAmmount;}

uint8_t* Maze::get_m_u8lvl(void){ return & m_u8lvl;}

uint8_t * Maze::get_m_aHoles(void){ return & m_aHoles[0][0];}


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
                                 uint8_t i_u8CurrentY){
    uint8_t l_u8ReturnValue;
    l_u8ReturnValue = m_Maze.checkColition(i_u8CurrentX,
                                 i_u8CurrentY);


    return l_u8ReturnValue;
}
void Laberynth::drawLaberynth(int i_iLaberynthColor, Graphics_Context *i_pContext){
    m_Maze.drawLaberynth(i_iLaberynthColor, i_pContext);
}
Laberynth::~Laberynth()
{
    // TODO Auto-generated destructor stub
}

