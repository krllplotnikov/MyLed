#ifndef INC_WS2812B_CUSTOMEFFECTS_H_
#define INC_WS2812B_CUSTOMEFFECTS_H_

#include <FFT.h>
#include "WS2812B.h"
#include "WS2812B_Presets.h"
#include "WS2812B_Effects.h"

#define FFT_SIZE 256
extern TIM_HandleTypeDef htim3;
extern ADC_HandleTypeDef hadc1;
#define H_TIM_ADC (&htim3)
#define H_ADC (&hadc1)
#define Fd 16000

typedef enum{
	NOEFFECT,
	RAINBOW_LOOP,
	FLIP_FLOP,
	FADE,
	RAINBOW,
	RAINBOW_FADE,
	RANDOM_COLOR_FADE,
	POLICE
}WS2812B_CustomEffect;

typedef enum{
	NOCOLORMUSIC,
	CM_1,
	CM_2,
	CM_3
}WS2812B_ColorMusic;

void WS2812B_SetEffectDelay(uint8_t delay);
void WS2812B_SetColorMusicDelay(uint8_t delay);
void WS2812B_SetMaxAmplitudeL(uint8_t amplitude);
void WS2812B_SetMaxAmplitudeM(uint8_t amplitude);
void WS2812B_SetMaxAmplitudeH(uint8_t amplitude);

void WS2812B_MakeColorMusic(WS2812B_ColorMusic color_music);
void WS2812B_MakeEffect(WS2812B_CustomEffect custom_effect);

void RainbowLoop();
void FlipFlop();
void Fade();
void Rainbow();
void RainbowFade();
void RandomColorFade();
void Police();


void LayerTest();



void WS2812B_CM_Init();
void ColorMusic_1();
void ColorMusic_2();
void ColorMusic_3();

int find_max_ampl(int start, int stop);
int find_max_freq(int start, int stop);


#endif
