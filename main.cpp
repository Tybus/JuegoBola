extern"C"{
#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "HAL_I2C.h"
#include "HAL_OPT3001.h"
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
}
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "Laberynth.h"

#define __FORE_GROUND_COLOR 0x00FFFF00
#define __BALL_COLOR 0x000000FF
/* Graphic library context */
Graphics_Context g_sContext;
Graphics_Rectangle g_sRectangle;

void Setup(void)
{
    // ****************************
    //         DEVICE CONFIG
    // ****************************
    // - Disable WDT
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;

    // ****************************
    //         PORT CONFIG
    // ****************************
    // - P1.0 is connected to the Red LED
    // - This is the heart beat indicator.
    P1->DIR |= BIT0; //Red LED


    // ****************************
    //       SCREEN CONFIG
    // ****************************
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);

    Graphics_setForegroundColor(&g_sContext, __FORE_GROUND_COLOR);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0; g_sRectangle.xMin = 127;
    g_sRectangle.yMax = 0; g_sRectangle.yMin = 127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);

    return;
}
/////////////////////////
/////////////////////////
/////////////////////////

/*
 * Main function
 */
int main(void)
{
    Setup();
    Laberynth MyLaberynth;
    MyLaberynth.drawLaberynth(__BALL_COLOR, &g_sContext);
    while(1){

    }
}
