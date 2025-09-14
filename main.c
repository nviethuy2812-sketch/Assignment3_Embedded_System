#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void delay1(int16_t time){
    int i,j;
    for(i = 0; i < time; i++){
        for(j = 0; j < 0x2aff; j++);
    }
}

void config(){
    GPIO_InitTypeDef gpio;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE);
    
    gpio.GPIO_Pin = GPIO_Pin_0;
    gpio.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &gpio);
    
    gpio.GPIO_Pin = GPIO_Pin_13;
    gpio.GPIO_Mode = GPIO_Mode_IPU;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &gpio);
}

int main(){
    int8_t cnt = 0, status = 0;
    
    config();
    
    while(1){
        status = GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
        delay1(2);
        
        if(status == 0 && GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13) == 1) {
            cnt = !cnt;
        }
        
        if(cnt == 1){
            GPIO_ResetBits(GPIOB, GPIO_Pin_0);
        } else {
            GPIO_SetBits(GPIOB, GPIO_Pin_0);
        }
    }
}
