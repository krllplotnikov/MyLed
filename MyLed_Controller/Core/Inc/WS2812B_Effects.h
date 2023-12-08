#ifndef INC_WS2812B_EFFECTS_H_
#define INC_WS2812B_EFFECTS_H_

#include <WS2812B.h>

typedef enum {
	EFFECT_NONE,
	EFFECT_RAINBOWLOOP,
	EFFECT_FLIPFLOP,
	EFFECT_FADE,
	EFFECT_RAINBOW,
	EFFECT_RAINBOWFADE,
	EFFECT_RANDOMCOLORFADE,
	EFFECT_POLICE
} Effects;

void WS2812B_MakeEffect(WS2812B_t *strip, Effects effect, uint16_t delay);

void Effect_RainbowLoop(WS2812B_t *strip, uint16_t delay);
void Effect_Fade(WS2812B_t *strip, uint16_t delay);
void Effect_Police(WS2812B_t *strip, uint16_t delay);

#endif
