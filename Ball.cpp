/*
 * Ball.cpp
 *
 *  Created on: Jul 5, 2018
 *      Author: gab
 */

#include <Ball.hpp>

Ball::Ball(int i_iBallColor, Graphics_Context *context)
{
    m_RightWall = false;
    m_LeftWall  = false;
    m_UpWall    = false;
    m_DownWall  = false;
    m_dXSpeed = 0;
    m_dYSpeed = 0;
    m_iColor=i_iBallColor;
    m_iXPosition = 64;
    m_iYPosition = 64;
    m_iXNextPosition = 64;
    m_iYNextPosition = 64;
    m_iXInitialPosition = 64;
    m_iYInitialPosition = 64;
    m_pGraphicsContext = context;
}

Ball::Ball(int i_iBallColor, int i_iInitialX, int i_iInitialY, Graphics_Context *context)
{
    m_RightWall = false;
    m_LeftWall  = false;
    m_UpWall    = false;
    m_DownWall  = false;
    m_dXSpeed = 0;
    m_dYSpeed = 0;
    m_iColor=i_iBallColor;
    m_iXPosition = i_iInitialX;
    m_iYPosition = i_iInitialY;
    m_iXNextPosition = i_iInitialX;
    m_iYNextPosition = i_iInitialY;
    m_iXInitialPosition = i_iInitialX;
    m_iYInitialPosition = i_iInitialY;
    m_pGraphicsContext = context;
}

Ball::Ball(int i_iBallColor, int i_iInitialX, int i_iInitialY, Graphics_Context *context, Laberynth *laberynth)
{
    m_RightWall = false;
    m_LeftWall  = false;
    m_UpWall    = false;
    m_DownWall  = false;
    m_dXSpeed = 0;
    m_dYSpeed = 0;
    m_iColor=i_iBallColor;
    m_iXPosition = i_iInitialX;
    m_iYPosition = i_iInitialY;
    m_iXNextPosition = i_iInitialX;
    m_iYNextPosition = i_iInitialY;
    m_iXInitialPosition = i_iInitialX;
    m_iYInitialPosition = i_iInitialY;
    m_pGraphicsContext = context;
    m_pLaberynth = laberynth;
}

Ball::Ball(int i_iBallColor, Graphics_Context *context, Laberynth *laberynth ,int i_iInitialX, int i_iInitialY)
{
    m_RightWall = false;
    m_LeftWall  = false;
    m_UpWall    = false;
    m_DownWall  = false;
    m_dXSpeed = 0;
    m_dYSpeed = 0;
    m_iColor=i_iBallColor;
    m_iXPosition = i_iInitialX;
    m_iYPosition = i_iInitialY;
    m_iXNextPosition = i_iInitialX;
    m_iYNextPosition = i_iInitialY;
    m_iXInitialPosition = i_iInitialX;
    m_iYInitialPosition = i_iInitialY;
    m_pGraphicsContext = context;
    m_pLaberynth = laberynth;
}



int32_t Ball::isOnCircle(int32_t i_iXTest, int32_t i_iYTest, int32_t i_i32XCenter, int32_t i_i32YCenter )
{
    if( (i_i32XCenter-i_iXTest<3 && i_iXTest-i_i32XCenter<3)&& (i_i32YCenter-i_iYTest<3 && i_iYTest-i_i32YCenter<3)){return 1;}
    if( ((i_iXTest==i_i32XCenter-3 || i_iXTest==i_i32XCenter+3 ) && (i_i32YCenter==i_iYTest||i_i32YCenter+1==i_iYTest||i_i32YCenter-1==i_iYTest)) ){return 1;}
    if( ((i_iYTest==i_i32YCenter-3 || i_iYTest==i_i32YCenter+3 ) && (i_i32XCenter==i_iXTest||i_i32XCenter+1==i_iXTest||i_i32XCenter-1==i_iXTest)) ){return 1;}
    return 0;
}

void Ball::ResetBall(int i_iResetX, int i_iResetY)
{
    m_dXSpeed = 0;
    m_dYSpeed = 0;
    m_iXNextPosition = i_iResetX;
    m_iYNextPosition = i_iResetY;
}

void Ball::Graphics_deleteCircle(Graphics_Context *context,int32_t i_iCurrentX,int32_t i_iCurrentY,
                                                           int32_t newX,int32_t newY,
                                                           int32_t i_iRadius)
{
    Graphics_setForegroundColor(context, 0x00FFFF00);
    int i; int j;
    int l_iHoleAmmount = (int) * m_pLaberynth->m_Maze.get_m_u8HoleAmmount();

    ///////////////////////////
    ///////////////////////////

    ////////////

    for(i=-2;i<3;i+=1)
    {
        for(j=-2 ; j<3; j+=1)
        {
            //
            int h=0;

            uint8_t * m_aHoles =  m_pLaberynth->m_Maze.get_m_aHoles();
            int l_iCurrentXX ;
            int l_iCurrentYY ;
            bool l_bPaint = false;

            for(h=0; h<l_iHoleAmmount; h++)
            {
                l_iCurrentXX = (int) m_pLaberynth->m_Maze.m_aHoles[h][0];
                l_iCurrentYY = (int) m_pLaberynth->m_Maze.m_aHoles[h][1];
                l_bPaint = isOnCircle(i_iCurrentX+i, i_iCurrentY+j, l_iCurrentXX, l_iCurrentYY);

            }


            //
            if (isOnCircle(i_iCurrentX+i, i_iCurrentY+j, newX, newY)==0 && ! l_bPaint ){Graphics_drawPixel(context,i_iCurrentX+i, i_iCurrentY+j);}
        }
    }

    for(i=-1;i<2;i+=1)
    {
        int h=0;
        //int l_iHoleAmmount = (int) * m_pLaberynth->m_Maze.get_m_u8HoleAmmount();
        uint8_t * m_aHoles =  m_pLaberynth->m_Maze.get_m_aHoles();
        int l_iCurrentXX ;
        int l_iCurrentYY ;
        bool l_bPaint = false;

        for(h=0; h<l_iHoleAmmount; h++)
        {
            l_iCurrentXX = (int) m_pLaberynth->m_Maze.m_aHoles[h][0];
            l_iCurrentYY = (int) m_pLaberynth->m_Maze.m_aHoles[h][1];
            l_bPaint = isOnCircle(i_iCurrentX+i, i_iCurrentY+3, l_iCurrentXX, l_iCurrentYY);

        }
        if ( (isOnCircle(i_iCurrentX+i, i_iCurrentY+3,  newX,  newY )==0) && ! l_bPaint ){Graphics_drawPixel(context,i_iCurrentX+i, i_iCurrentY+3);}
        l_bPaint = false;

        for(h=0; h<l_iHoleAmmount; h++)
        {
            l_iCurrentXX = (int) m_pLaberynth->m_Maze.m_aHoles[h][0];
            l_iCurrentYY = (int) m_pLaberynth->m_Maze.m_aHoles[h][1];
            l_bPaint = isOnCircle(i_iCurrentX+i, i_iCurrentY-3, l_iCurrentXX, l_iCurrentYY);

        }
        if ( (isOnCircle(i_iCurrentX+i, i_iCurrentY-3,  newX,  newY )==0) && ! l_bPaint ){Graphics_drawPixel(context,i_iCurrentX+i, i_iCurrentY-3);}
        l_bPaint = false;

        for(h=0; h<l_iHoleAmmount; h++)
        {
            l_iCurrentXX = (int) m_pLaberynth->m_Maze.m_aHoles[h][0];
            l_iCurrentYY = (int) m_pLaberynth->m_Maze.m_aHoles[h][1];
            l_bPaint = isOnCircle(i_iCurrentX+3, i_iCurrentY+i, l_iCurrentXX, l_iCurrentYY);

        }
        if ( (isOnCircle(i_iCurrentX+3, i_iCurrentY+i,  newX,  newY )==0) && ! l_bPaint ){Graphics_drawPixel(context,i_iCurrentX+3, i_iCurrentY+i);}
        l_bPaint = false;

        for(h=0; h<l_iHoleAmmount; h++)
        {
            l_iCurrentXX = (int) m_pLaberynth->m_Maze.m_aHoles[h][0];
            l_iCurrentYY = (int) m_pLaberynth->m_Maze.m_aHoles[h][1];
            l_bPaint = isOnCircle(i_iCurrentX-3, i_iCurrentY+i, l_iCurrentXX, l_iCurrentYY);

        }
        if ( (isOnCircle(i_iCurrentX-3, i_iCurrentY+i,  newX,  newY )==0) && ! l_bPaint ){Graphics_drawPixel(context,i_iCurrentX-3, i_iCurrentY+i);}
    }


    /////////////

    Graphics_setForegroundColor(context, 0x000000FF);

    int h=0;
    //int l_iHoleAmmount = (int) * m_pLaberynth->m_Maze.get_m_u8HoleAmmount();

    uint8_t * m_aHoles =  m_pLaberynth->m_Maze.get_m_aHoles();

    int l_iCurrentXX ;
    int l_iCurrentYY ;
    for(h=0; h<l_iHoleAmmount; h++)
    {

    l_iCurrentXX = (int) * (m_aHoles+h);
    l_iCurrentYY = (int) * (m_aHoles+h+1);

    Graphics_fillCircle(m_pGraphicsContext, l_iCurrentXX, l_iCurrentYY, 3);

    }




}

void Ball::RefreshPhysicalState(double i_dDeltaTime)
{
    uint8_t i =  m_pLaberynth->checkColition((uint8_t) round(m_iXPosition),(uint8_t) round(m_iYPosition));

    m_RightWall = (bool) (i & RCOLITION);
    m_LeftWall  = (bool) (i & LCOLITION);
    m_DownWall  = (bool) (i & DCOLITION);
    m_UpWall    = (bool) (i & UCOLITION);

    if(!( (m_LeftWall  && m_iXAcceleration<0 ) || (m_RightWall && m_iXAcceleration>0 )  ))
    {
        m_dXSpeed+=   m_iXAcceleration*i_dDeltaTime*0.1;
    }
    if(!( (m_UpWall  && m_iYAcceleration>0 ) || (m_DownWall && m_iYAcceleration<0 )  ))
    {
        m_dYSpeed+= - m_iYAcceleration*i_dDeltaTime*0.1;
    }

    m_iXNextPosition+=  m_dXSpeed*i_dDeltaTime;
    m_iYNextPosition+=  m_dYSpeed*i_dDeltaTime;

    if((m_iXNextPosition > m_iXPosition && m_RightWall)
            ||
       (m_iXNextPosition < m_iXPosition && m_LeftWall))
    {
        m_iXNextPosition =  (double) m_iXPosition;
        m_dXSpeed = 0;
    }

    if((m_iYNextPosition > m_iYPosition && m_DownWall)
            ||
       (m_iYNextPosition < m_iYPosition && m_UpWall))
    {
        m_iYNextPosition = (double) m_iYPosition;
        m_dYSpeed = 0;
    }

    if((bool) (i & HOLE))
    {
        ResetBall(14, 14);
    }

}

void Ball::RefreshOnScreen()
{
    //__disable_irq();
    int l_iXNextPosition = (int) round(m_iXNextPosition);
    int l_iYNextPosition = (int) round(m_iYNextPosition);

    Graphics_deleteCircle(m_pGraphicsContext,
                          m_iXPosition, m_iYPosition ,
                          l_iXNextPosition, l_iYNextPosition,
                          3);

    Graphics_setForegroundColor(m_pGraphicsContext, m_iColor);
    Graphics_fillCircle(m_pGraphicsContext, l_iXNextPosition, l_iYNextPosition, 3);
    m_iXPosition= l_iXNextPosition;
    m_iYPosition= l_iYNextPosition;

}
