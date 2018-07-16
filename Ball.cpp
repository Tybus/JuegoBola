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



int32_t Ball::isOnCircle(int32_t xtest, int32_t ytest, int32_t xNew, int32_t yNew )
{
    if( (xNew-xtest<3 && xtest-xNew<3)&& (yNew-ytest<3 && ytest-yNew<3))                    {return 1;}
    if( ((xtest==xNew-3 || xtest==xNew+3 ) && (yNew==ytest||yNew+1==ytest||yNew-1==ytest)) ){return 1;}
    if( ((ytest==yNew-3 || ytest==yNew+3 ) && (xNew==xtest||xNew+1==xtest||xNew-1==xtest)) ){return 1;}
    return 0;
}

void Ball::ResetBall()
{
    m_dXSpeed = 0;
    m_dYSpeed = 0;
    //m_iXPosition = 64;
    //m_iYPosition = 64;
    m_iXNextPosition = 64;
    m_iYNextPosition = 64;
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

void Ball::RefreshPhysicalState(double i_dDeltaTime)
{
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    //uint8_t i;
    uint8_t i =  m_pLaberynth->checkColition((uint8_t) round(m_iXPosition),(uint8_t) round(m_iYPosition));

    m_RightWall = (bool) (i & RCOLITION);
    m_LeftWall  = (bool) (i & LCOLITION);
    m_DownWall  = (bool) (i & DCOLITION);
    m_UpWall    = (bool) (i & UCOLITION);

    //if(i & RCOLITION){m_dXSpeed = -0.2*m_dXSpeed;}
    //if(i & LCOLITION){m_dXSpeed = -0.2*m_dXSpeed;}
    //if(i & UCOLITION){m_dYSpeed = -0.2*m_dYSpeed;}
    //if(i & DCOLITION){m_dYSpeed = -0.2*m_dYSpeed;}

    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /////////////////////////////////////////////////
    /*
    if(m_iXPosition >=123 ){m_RightWall = true; }
    if(m_iXPosition <123 ) {m_RightWall = false; }

    if(m_iXPosition <=4 )  {m_LeftWall = true; }
    if(m_iXPosition >4 )   {m_LeftWall = false; }

    if(m_iYPosition >=123 ){m_DownWall = true; }
    if(m_iYPosition <123 ) {m_DownWall = false; }

    if(m_iYPosition <=4 )  {m_UpWall = true; }
    if(m_iYPosition >4 )   {m_UpWall = false; }
    */
    //m_dXSpeed+=   m_iXAcceleration*i_dDeltaTime*0.1;//0.0010986;
    //m_dYSpeed+= - m_iYAcceleration*i_dDeltaTime*0.1;//0.0010986;
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
        m_dXSpeed = -m_dXSpeed;
    }

    if((m_iYNextPosition > m_iYPosition && m_DownWall)
            ||
       (m_iYNextPosition < m_iYPosition && m_UpWall))
    {
        m_iYNextPosition = (double) m_iYPosition;
        m_dYSpeed = -m_dYSpeed;
    }


/*
    if(m_iXNextPosition >123 || m_iXNextPosition < 4 )
    {
        m_iXNextPosition = m_iXPosition;
        m_dXSpeed = -m_dXSpeed;
    }

    if(!(m_iXNextPosition >123 || m_iXNextPosition < 4) ){m_iXNextPosition+=  m_dXSpeed*i_dDeltaTime;}//0.001;}

    if(m_iYNextPosition >123 || m_iYNextPosition < 4 )
    {
        m_iYNextPosition = m_iYPosition;
        m_dYSpeed = -m_dYSpeed;
    }

    if(!(m_iYNextPosition >123 || m_iYNextPosition < 4) ){m_iYNextPosition+=  m_dYSpeed*i_dDeltaTime;}//0.001;}

    if(!( (m_LeftWall  && m_dXSpeed<0 ) || (m_RightWall && m_dXSpeed>0 )  ))
    {
        m_iXNextPosition+=  m_dXSpeed*i_dDeltaTime;//0.001;
    }//0.0010986; }
    if(!( (m_UpWall  && m_dYSpeed<0 ) || (m_DownWall && m_dYSpeed>0 )  ))
    {
        m_iYNextPosition+=  m_dYSpeed*i_dDeltaTime;//0.001;
    }

    //m_dXSpeed+=   m_iXAcceleration*i_dDeltaTime*0.0297;//0.0010986;
    //m_dYSpeed+= - m_iYAcceleration*i_dDeltaTime*0.0297;//0.0010986;

    //m_iXNextPosition+=  m_dXSpeed*i_dDeltaTime;//0.001;
    //m_iYNextPosition+=  m_dYSpeed*i_dDeltaTime;//0.001;
*/
}

void Ball::RefreshOnScreen()
{
    //__disable_irq();
    int l_iXNextPosition = (int) round(m_iXNextPosition);
    int l_iYNextPosition = (int) round(m_iYNextPosition);

    //uint8_t l_iXNextPosition = (uint8_t) round(m_iXNextPosition);
    //uint8_t l_iYNextPosition = (uint8_t) round(m_iYNextPosition);
    //uint8_t l_iXCurrentPosition = (uint8_t) round(m_iXPosition);
    //uint8_t l_iYCurrentPosition = (uint8_t) round(m_iXPosition);
    //__enable_irq();

    //uint8_t i;
    //i =  m_pLaberynth->checkColition((uint8_t) round(m_iXPosition),(uint8_t) round(m_iYPosition),(uint8_t) l_iXNextPosition,(uint8_t) l_iYNextPosition);
/*
    if(i & RCOLITION){m_dXSpeed = -0.2*m_dXSpeed;}
    if(i & LCOLITION){m_dXSpeed = -0.2*m_dXSpeed;}
    if(i & UCOLITION){m_dYSpeed = -0.2*m_dYSpeed;}
    if(i & DCOLITION){m_dYSpeed = -0.2*m_dYSpeed;}
*/
    /*
    if(i & RCOLITION){m_dXSpeed = 0;}
    if(i & LCOLITION){m_dXSpeed = 0;}
    if(i & UCOLITION){m_dYSpeed = 0;}
    if(i & DCOLITION){m_dYSpeed = 0;}
*/
    /*
    if(m_iXPosition >=123 ){m_RightWall = true; }
    if(m_iXPosition <123 ) {m_RightWall = false; }

    if(m_iXPosition <=4 )  {m_LeftWall = true; }
    if(m_iXPosition >4 )   {m_LeftWall = false; }

    if(m_iYPosition >=123 ){m_DownWall = true; }
    if(m_iYPosition <123 ) {m_DownWall = false; }

    if(m_iYPosition <=4 )  {m_UpWall = true; }
    if(m_iYPosition >4 )   {m_UpWall = false; }
*/
    /*
    if(l_iXNextPosition >123 || l_iXNextPosition < 4 )
    {
        l_iXNextPosition = m_iXPosition;
        m_dXSpeed = -m_dXSpeed;
    }
    if(l_iYNextPosition >123 || l_iYNextPosition < 4 )
    {
        l_iYNextPosition = m_iYPosition;
        m_dYSpeed = -m_dYSpeed;
    }
*/

    Graphics_deleteCircle(m_pGraphicsContext,
                          m_iXPosition, m_iYPosition ,
                          l_iXNextPosition, l_iYNextPosition,
                          3);

    Graphics_setForegroundColor(m_pGraphicsContext, m_iColor);
    Graphics_fillCircle(m_pGraphicsContext, l_iXNextPosition, l_iYNextPosition, 3);
    m_iXPosition= l_iXNextPosition;
    m_iYPosition= l_iYNextPosition;

}
