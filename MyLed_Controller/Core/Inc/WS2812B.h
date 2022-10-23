#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_

#include "stm32f1xx_hal.h"


extern TIM_HandleTypeDef htim1;

#define H_TIM (&htim1)
#define T_CH TIM_CHANNEL_1

#define COUNTER_PERIOD 89
#define HIGH (COUNTER_PERIOD*10 / 15)
#define LOW (COUNTER_PERIOD*10 / 30)

#define COLOR_BYTE 8
#define COLORS_BITS 24
#define MAX_NUM_LEDS 180
#define RESET_BITS 50
#define PWM_BUFF_LENGTH (MAX_NUM_LEDS * COLORS_BITS + RESET_BITS)

typedef struct{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t brightness;
}WS2812B_t;

typedef enum{
	WS2812B_READY,
	WS2812B_BUSY
}WS2812B_State;

typedef enum{
	SHOW_OK,
	SHOW_ERROR
}ShowStatus;

void WS2812B_Init(uint8_t num_leds, uint8_t brightness);
void WS2812B_SetNumLeds(uint8_t num_leds);
void WS2812B_SetPixelRGB(WS2812B_t* layer, uint8_t R, uint8_t G, uint8_t B, uint8_t led_pos);
void WS2812B_SetPixelHSV(WS2812B_t* layer, uint8_t h, uint8_t s, uint8_t v, uint8_t led_pos);
void WS2812B_SetPixelBrightness(WS2812B_t* layer, uint8_t brightness, uint8_t led_pos);
void WS2812B_SetBrightness(uint8_t brightness);
void WS2812B_SetDelay(uint16_t delay);

ShowStatus WS2812B_Show();

void RGB_to_GRB_PWM();

float interpolation(float x1, float x2, float fx1, float fx2, float x);

#endif
