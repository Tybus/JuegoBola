/*
 * Ball.hpp
 *
 *  Created on: Jul 5, 2018
 *      Author: gab
 */

#ifndef XY
#define XY
double x;
double y;
#endif

extern "C"
{
//#include <ti/devices/msp432p4xx/inc/msp.h>
//#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
//#include <ti/grlib/grlib.h>
//#include "HAL_I2C.h"
//#include "HAL_OPT3001.h"
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
}
#include <stdio.h>
#include <math.h>
#include <Laberynth.h>

#ifndef BALL_HPP_
#define BALL_HPP_

class Ball
{
    public:
        //Ball(int i_iBallColor, Graphics_Context *context, Laberynth *laberynth);
        Ball(int i_iBallColor, Graphics_Context *context, Laberynth *laberynth ,int i_iInitialX, int i_iInitialY);
        Ball(int i_iBallColor, Graphics_Context *context);
        Ball(int i_iBallColor, int i_iInitialX, int i_iInitialY, Graphics_Context *context);
        void RefreshOnScreen(void);
        int m_iXPosition;
        int m_iYPosition;
        //Accelerometer();
        //uint16_t m_u16BITN;
        //virtual uint8_t run(void);
        //virtual uint8_t setup(void);
    protected:
    private:
        int m_iColor;
        int m_iXNextPosition;
        int m_iYNextPosition;
        int m_iXInitialPosition;
        int m_iYInitialPosition;
        Graphics_Context * m_pGraphicsContext;
        Laberynth * m_pLaberynth;

        void Graphics_deleteCircle(Graphics_Context *context,int32_t currentx,int32_t currenty,
                                                                   int32_t newX,int32_t newY,
                                                                   int32_t lRadius);

        int32_t isOnCircle(int32_t xtest, int32_t ytest, int32_t xNew, int32_t yNew );



};

#endif /* BALL_HPP_ */
