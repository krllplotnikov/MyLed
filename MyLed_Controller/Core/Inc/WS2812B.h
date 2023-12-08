#ifndef INC_WS2812B_H_
#define INC_WS2812B_H_

#include "stm32f1xx_hal.h"
#include "stdlib.h"
#include "math.h"

#define HIGH 61
#define LOW 28

#define COLOR_BYTE 8
#define COLORS_BITS 24
#define RESET_BITS 50

#define SHOW_END 0
#define SHOW_RUNNING 1

typedef struct{
	uint8_t R;
	uint8_t G;
	uint8_t B;
	uint8_t brightness;
}RGB_t;

typedef struct{
	TIM_HandleTypeDef* htim;
	uint32_t tim_ch;
	uint16_t max_numleds;
	uint16_t numleds;
	uint16_t *pwm_buff;
	uint16_t fps;
	uint8_t brightness;
	uint8_t onOff;
	RGB_t *leds;
}WS2812B_t;

typedef struct{
	uint8_t mirrored;
	unsigned long repeatTime;
	uint16_t counter;
	uint8_t direction;
}Animation_t;

void WS2812B_Init(WS2812B_t* strip, uint16_t numleds, TIM_HandleTypeDef* htim, uint32_t tim_ch);
void WS2812B_SetNumLeds(WS2812B_t* strip, uint16_t numleds);
void WS2812B_SetPixelRGB(WS2812B_t* strip, uint8_t R, uint8_t G, uint8_t B, uint16_t led_pos);
void WS2812B_SetPixelHUE(WS2812B_t* strip, uint8_t h, uint16_t led_pos);
void WS2812B_SetPixelBrightness(WS2812B_t* strip, uint8_t brightness, uint16_t led_pos);
void WS2812B_SetPixelBrightnessCRT(WS2812B_t* strip, float brightness, uint16_t led_pos);
void WS2812B_SetBrightness(WS2812B_t* strip, uint8_t brightness);
void WS2812B_SetFPS(WS2812B_t* strip, uint16_t fps);
void WS2812B_Off(WS2812B_t* strip);
void WS2812B_Show(WS2812B_t* strip);

//Presets
void Preset_Rainbow(WS2812B_t *strip, uint16_t begin, uint16_t end, uint8_t mirrored);
void Preset_Raindrop(WS2812B_t *strip, uint16_t begin, uint16_t end, uint8_t mirrored);
void Preset_HUE(WS2812B_t* strip, uint8_t h, uint16_t begin, uint16_t end);
void Preset_OnOff(WS2812B_t* strip, uint8_t state, uint16_t begin, uint16_t end);

//Animations
void AnimationInit(Animation_t* animation, uint8_t mirrored);
void Animation_Loop(WS2812B_t *strip, Animation_t* animation, uint16_t begin, uint16_t end, uint16_t delay);
void Animation_Fade(WS2812B_t *strip, Animation_t* animation, uint16_t begin, uint16_t end, uint16_t delay);
void Animation_Train(WS2812B_t *strip, Animation_t* animation, uint16_t begin, uint16_t end, uint16_t delay);
//
void RGB_to_GRB_PWM(WS2812B_t* strip);
float interpolation(float x1, float x2, float fx1, float fx2, float x);
float crt2(float in, float max);

#endif
