#ifndef INC_WS2812B_EFFECTS_H_
#define INC_WS2812B_EFFECTS_H_

#include "WS2812B.h"
#include "WS2812B_Presets.h"
#include <stdlib.h>

#define END_CYCLE (-1)

int Effect_Loop(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);
int Effect_LoopOnlyBrightness(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);
int Effect_Rainbow(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);
int Effect_Fade(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);
int Effect_FadeDown(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);
int Effect_Train(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);
int Effect_TrainOnlyBrightness(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect);

#endif
