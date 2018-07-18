/*
 * Graphics.hpp
 *
 *  Created on: Jul 16, 2018
 *      Author: gab
 */

extern "C"
{
#include "LcdDriver/Crystalfontz128x128_ST7735.h"
#include "LcdDriver/HAL_MSP_EXP432P401R_Crystalfontz128x128_ST7735.h"
}


#ifndef GRAPHICS_HPP_
#define GRAPHICS_HPP_

class Graphics
{
    public:
        void Graphics_deleteCircle(Graphics_Context *context,
                               int32_t currentx,int32_t currenty,
                               int32_t newX,    int32_t newY,
                               int32_t lRadius);

    protected:

    private:
        int32_t isOnCircle(int32_t xtest, int32_t ytest, int32_t xNew, int32_t yNew );
};




#endif /* GRAPHICS_HPP_ */
