#include <ti/devices/msp432p4xx/inc/msp.h>
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ti/grlib/grlib.h>
#include "HAL_I2C.h"
#include "HAL_OPT3001.h"
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
#include <stdio.h>
#include <math.h>

/* Graphic library context */
Graphics_Context g_sContext;
Graphics_Rectangle g_sRectangle;
//uint16_t ax; //= 0U;
//uint16_t ay; //= 0U;
//uint16_t az; //= 0U;

int ax=0;
int ay=0;
int az=0;

double vx=0;
double vy=0;
double vz=0;

double x=0;
double y=0;
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
    TIMER32_1->LOAD = 0x00000BB8;//TIMER32_COUNT;
    TIMER32_1->CONTROL = TIMER32_CONTROL_SIZE | TIMER32_CONTROL_PRESCALE_0 | TIMER32_CONTROL_MODE | TIMER32_CONTROL_IE | TIMER32_CONTROL_ENABLE;
    NVIC_SetPriority(T32_INT1_IRQn,1);
    NVIC_EnableIRQ(T32_INT1_IRQn);
    __enable_irq();

    // ****************************
    //       SCREEN CONFIG
    // ****************************
    /////////////////////////////////////////////////////////////////////
    /* Initializes display */
    Crystalfontz128x128_Init();

    /* Set default screen orientation */
    Crystalfontz128x128_SetOrientation(LCD_ORIENTATION_UP);

    /* Initializes graphics context */
    Graphics_initContext(&g_sContext, &g_sCrystalfontz128x128,
                         &g_sCrystalfontz128x128_funcs);

    Graphics_clearDisplay(&g_sContext);
/*
    Graphics_setForegroundColor(&g_sContext, 0x000000FF);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 0;
    g_sRectangle.yMin = 63;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
    //Graphics_drawLineH(&g_sContext, 0, 127, 63);

    Graphics_setForegroundColor(&g_sContext, 0x00DAA520);
    //Graphics_drawRectangle(&g_sContext,&g_sRectangle);
    g_sRectangle.xMax = 0;
    g_sRectangle.xMin = 127;//127;
    g_sRectangle.yMax = 64;
    g_sRectangle.yMin = 127;//127;
    Graphics_fillRectangle(&g_sContext,&g_sRectangle);
*/
    Graphics_setForegroundColor(&g_sContext, 0x00FF0000);
    Graphics_fillCircle(&g_sContext, 64, 64, 3);





    return;
}




void AccelerometerSetup()
{
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

}


/*
 * Main function
 */
int main(void)
{
    Setup();
    AccelerometerSetup();



    while(1)
    {
        //#########################
        // Trigger the conversion in the ADC,
        // the ADC14_IRQHandler( ) procedure run at the end of conversion
        //ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;

        if((int32_t) round(x) > 54 || (int32_t) round(x) < -54){vx=0; }
        if((int32_t) round(y) > 54 || (int32_t) round(y) < -54){vy=0; }

        Graphics_setForegroundColor(&g_sContext, 0x00000000);
        Graphics_fillCircle(&g_sContext, ((int32_t) round(xold))+64, ((int32_t) round(yold))+64, 4);




        __disable_irq();
        Graphics_setForegroundColor(&g_sContext, 0x00FF0000);
        Graphics_fillCircle(&g_sContext, ((int32_t) round(x))+64, ((int32_t) round(y))+64, 4);
        xold=x;
        yold=y;
        __enable_irq();

    }
}



void ADC14_IRQHandler(void)
{
    __disable_irq();

    ax=ADC14->MEM[0]-8192;
    ay=ADC14->MEM[1]-8192;
    az=ADC14->MEM[2]-8192;

    ADC14->CLRIFGR0 = ADC14_CLRIFGR0_CLRIFG0;
    __enable_irq();
    return;
}

void T32_INT1_IRQHandler(void)
{
    TIMER32_1->INTCLR = 0U;
    //P1->OUT ^= BIT0; // - Toggle the heart beat indicator (1ms)

    ADC14->CTL0 = ADC14->CTL0 | ADC14_CTL0_SC;
    vx+=ax*0.001*0.1;//0.0010986;
    vy+=-ay*0.001*0.1;//0.0010986;

    x+=vx*0.001;
    y+=vy*0.001;

    //Graphics_fillCircle(&g_sContext, ((int32_t) (x))+64, ((int32_t) (y))+64, 4);

    return;
}
