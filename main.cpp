#define __FORE_GROUND_COLOR 0x00FFFF00
#define __BALL_COLOR        0x000000FF

extern "C"
{
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

#include <Ball.hpp>
#include <Laberynth.h>

/* Graphic library context */
Graphics_Context g_sContext;
Graphics_Rectangle g_sRectangle;

int32_t g_iAccelerationX=0;
int32_t g_iAccelerationY=0;
int32_t g_iAccelerationZ=0;

double g_dSpeedX=0;
double g_dSpeedY=0;
double g_dSpeedZ=0;

#ifndef XY
#define XY
double x;
double y;
#endif
double z=0;

double xold=0;
double yold=0;
double zold=0;


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
    //       TIMER CONFIG
    // ****************************
    // - Configure Timer32_1  with MCLK (3Mhz), Division by 1, Enable the interrupt, Periodic Mode
    // - Enable the interrupt in the NVIC
    // - Start the timer in UP mode.
    // - Re-enable interrupts
    //TIMER32_1->LOAD = 0x002DC6C0;//TIMER32_COUNT; //~1ms ---> a 48Mhz
    TIMER32_1->LOAD = 0x0000BB80;//TIMER32_COUNT;
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT1_IRQn,1);
    NVIC_EnableIRQ(T32_INT1_IRQn);
    __enable_irq();

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

    //Graphics_clearDisplay(&g_sContext);
/*
    Graphics_setForegroundColor(&g_sContext, 0x000000FF);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 0;
    g_sRectangle.yMin = 63;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
    //Graphics_drawLineH(&g_sContext, 0, 127, 63);

    Graphics_setForegroundColor(&g_sContext, __FORE_GROUND_COLOR);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0; g_sRectangle.xMin = 127;
    g_sRectangle.yMax = 0; g_sRectangle.yMin = 127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);

    //Graphics_setForegroundColor(&g_sContext, 0x00FF0000);
    //Graphics_fillCircle(&g_sContext, 64, 64, 3);
*/
    // ****************************
    //     ACCELEROMETER CONFIG
    // ****************************
    // Set P6.1 for Analog input (X-Axis).
    P6->SEL0 |= BIT1;
    P6->SEL1 |= BIT1;
    P6->DIR &= ~BIT1;
    // Set P4.0 for Analog input (Y-Axis).
    P4->SEL0 |= BIT0;
    P4->SEL1 |= BIT0;
    P4->DIR &= ~BIT0;
    // Set P4.2 for Analog input (Z-Axis).
    P4->SEL0 |= BIT2;
    P4->SEL1 |= BIT2;
    P4->DIR &= ~BIT2;
    //Configure the ADC
    ADC14->CTL0 = ADC14_CTL0_CONSEQ_1  |
                  ADC14_CTL0_PDIV_0    |
                  ADC14_CTL0_SHS_0     |
                  ADC14_CTL0_DIV_7     |
                  ADC14_CTL0_SSEL__MCLK|
                  ADC14_CTL0_SHT0_1    |
                  ADC14_CTL0_ON        |
                  ADC14_CTL0_SHP;
    //Configure the ADC memory outs, MCTL[0]= x, MCTL[1]= y, MCTL[2]= z
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_14 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[1] = ADC14_MCTLN_INCH_13 | ADC14_MCTLN_VRSEL_0;
    ADC14->MCTL[2] = ADC14_MCTLN_INCH_11 | ADC14_MCTLN_VRSEL_0| ADC14_MCTLN_EOS ;

    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_ENC;
    ADC14->IER0 = ADC14_IER0_IE2;
    NVIC_SetPriority(ADC14_IRQn,1);
    NVIC_EnableIRQ(ADC14_IRQn);

    return;
}
/////////////////////////
///////////////////////
/////////////////////////
////////////////////////
////////////////////////
/*
int32_t isOnCircle(int32_t xtest, int32_t ytest, int32_t xNew, int32_t yNew )
{
    if( (xNew-xtest<3 && xtest-xNew<3)&& (yNew-ytest<3 && ytest-yNew<3)){return 1;}
    if( ((xtest==xNew-3 || xtest==xNew+3 ) && (yNew==ytest||yNew+1==ytest||yNew-1==ytest)) ){return 1;}
    if( ((ytest==yNew-3 || ytest==yNew+3 ) && (xNew==xtest||xNew+1==xtest||xNew-1==xtest)) ){return 1;}
    return 0;
}


void Graphics_deleteCircle(const Graphics_Context *context,int32_t currentx,int32_t currenty,
                                                           int32_t newX,int32_t newY,
                                                           int32_t lRadius)
{
    //Graphics_setForegroundColor(&g_sContext, 0x00000000);
    Graphics_setForegroundColor(&g_sContext, __FORE_GROUND_COLOR);
    //if (! isOnCircle(xTest, yTest,  x,  y )){Graphics_drawPixel(&g_sContext,xTest,yTest);}


    int i;
    int j;

    for(i=-2;i<3;i+=1)
    {
        for(j=-2 ; j<3; j+=1)
        {
            if (isOnCircle(currentx+i, currenty+j,  newX,  newY )==0){Graphics_drawPixel(&g_sContext,currentx+i, currenty+j);}
        }
    }

    for(i=-1;i<2;i+=1)
    {
        if (isOnCircle(currentx+i, currenty+3,  newX,  newY )==0){Graphics_drawPixel(&g_sContext,currentx+i, currenty+3);}
        if (isOnCircle(currentx+i, currenty-3,  newX,  newY )==0){Graphics_drawPixel(&g_sContext,currentx+i, currenty-3);}
        if (isOnCircle(currentx+3, currenty+i,  newX,  newY )==0){Graphics_drawPixel(&g_sContext,currentx+3, currenty+i);}
        if (isOnCircle(currentx-3, currenty+i,  newX,  newY )==0){Graphics_drawPixel(&g_sContext,currentx-3, currenty+i);}
    }
}*/

/////////////////////////
///////////////////////
/////////////////////////
////////////////////////
////////////////////////

/*
 * Main function
 */
int main(void)
{
    Setup();
    x=0;
    y=0;

    Ball ball(__BALL_COLOR ,&g_sContext);

    while(1)
    {
        //#########################
        // Trigger the conversion in the ADC,
        // the ADC14_IRQHandler( ) procedure run at the end of conversion
        //ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;
/*
        if((int32_t) round(x) > 54 || (int32_t) round(x) < -54){vx=0; }
        if((int32_t) round(y) > 54 || (int32_t) round(y) < -54){vy=0; }

        //Graphics_setForegroundColor(&g_sContext, 0x00000000);
        //Graphics_fillCircle(&g_sContext, ((int32_t) round(xold))+64, ((int32_t) round(yold))+64, 3);

        __disable_irq();
        Graphics_deleteCircle(&g_sContext,((int32_t) round(xold))+64,((int32_t) round(yold))+64,
                              ((int32_t) round(x))+64, ((int32_t) round(y))+64,3);


        Graphics_setForegroundColor(&g_sContext, __BALL_COLOR);
        Graphics_fillCircle(&g_sContext, ((int32_t) round(x))+64, ((int32_t) round(y))+64, 3);
        xold=x;
        yold=y;
        __enable_irq();
*/

        ball.RefreshOnScreen();
    }
}

extern "C"
{

void ADC14_IRQHandler(void)
{
    __disable_irq();

    g_iAccelerationX=ADC14->MEM[0]-8192;
    g_iAccelerationY=ADC14->MEM[1]-8192;
    g_iAccelerationZ=ADC14->MEM[2]-8192;

    ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
    __enable_irq();
    return;
}

void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0U;
    //P1->OUT ^= BIT0; // - Toggle the heart beat indicator (1ms)

    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;
    g_dSpeedX+= g_iAccelerationX*0.001*0.1;//0.0010986;
    g_dSpeedY+=-g_iAccelerationY*0.001*0.1;//0.0010986;

    x+=g_dSpeedX*0.001;
    y+=g_dSpeedY*0.001;
    //Graphics_fillCircle(&g_sContext, ((int32_t) (x))+64, ((int32_t) (y))+64, 4);
    return;
}
}
