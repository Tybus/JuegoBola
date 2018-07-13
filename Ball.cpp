/*
 * Ball.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: gab
 */

#include "Ball.hpp"

Ball::Ball(int i_iBallColor, Graphics_Context *context)
{
    m_iColor=i_iBallColor;
    m_iXPosition = 64;
    m_iYPosition = 64;
    m_iXInitialPosition = 64;
    m_iYInitialPosition = 64;
    m_pGraphicsContext = context;
}

Ball::Ball(int i_iBallColor, int i_iInitialX, int i_iInitialY, Graphics_Context *context)
{
    m_iColor=i_iBallColor;
    m_iXPosition = i_iInitialX;
    m_iYPosition = i_iInitialY;
    m_iXInitialPosition = i_iInitialX;
    m_iYInitialPosition = i_iInitialY;
    m_pGraphicsContext = context;
}

Ball::Ball(int i_iBallColor, Graphics_Context *context, Laberynth *laberynth ,int i_iInitialX, int i_iInitialY)
{
    m_iColor=i_iBallColor;
    m_iXPosition = i_iInitialX;
    m_iYPosition = i_iInitialY;
    m_iXInitialPosition = i_iInitialX;
    m_iYInitialPosition = i_iInitialY;
    m_pGraphicsContext = context;
    m_pLaberynth = laberynth;
}



int32_t Ball::isOnCircle(int32_t xtest, int32_t ytest, int32_t xNew, int32_t yNew )
{
    if( (xNew-xtest<3 && xtest-xNew<3)&& (yNew-ytest<3 && ytest-yNew<3)){return 1;}
    if( ((xtest==xNew-3 || xtest==xNew+3 ) && (yNew==ytest||yNew+1==ytest||yNew-1==ytest)) ){return 1;}
    if( ((ytest==yNew-3 || ytest==yNew+3 ) && (xNew==xtest||xNew+1==xtest||xNew-1==xtest)) ){return 1;}
    return 0;
}

void Ball::Graphics_deleteCircle(Graphics_Context *context,int32_t currentx,int32_t currenty,
                                                           int32_t newX,int32_t newY,
                                                           int32_t lRadius)
{
    Graphics_setForegroundColor(context, 0x00FFFF00);
    int i; int j;

    for(i=-2;i<3;i+=1)
    {
        for(j=-2 ; j<3; j+=1)
        {
            if (isOnCircle(currentx+i, currenty+j,  newX,  newY )==0){Graphics_drawPixel(context,currentx+i, currenty+j);}
        }
    }

    for(i=-1;i<2;i+=1)
    {
        if (isOnCircle(currentx+i, currenty+3,  newX,  newY )==0){Graphics_drawPixel(context,currentx+i, currenty+3);}
        if (isOnCircle(currentx+i, currenty-3,  newX,  newY )==0){Graphics_drawPixel(context,currentx+i, currenty-3);}
        if (isOnCircle(currentx+3, currenty+i,  newX,  newY )==0){Graphics_drawPixel(context,currentx+3, currenty+i);}
        if (isOnCircle(currentx-3, currenty+i,  newX,  newY )==0){Graphics_drawPixel(context,currentx-3, currenty+i);}
    }
}




void Ball::RefreshOnScreen()
{
    __disable_irq();
    m_iXNextPosition = (int) round(x)+m_iXInitialPosition;
    m_iYNextPosition = (int) round(y)+m_iYInitialPosition;
    __enable_irq();

    Graphics_deleteCircle(m_pGraphicsContext,
                          m_iXPosition, m_iYPosition ,
                          m_iXNextPosition, m_iYNextPosition,
                          3);

    Graphics_setForegroundColor(m_pGraphicsContext, m_iColor);
    Graphics_fillCircle(m_pGraphicsContext, m_iXNextPosition, m_iYNextPosition, 3);
    m_iXPosition= m_iXNextPosition;
    m_iYPosition= m_iYNextPosition;
}
