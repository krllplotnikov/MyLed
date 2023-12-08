#include <WS2812B_Effects.h>

Effects prevEffect = 0;
Effects curEffect = 0;
uint16_t prevNumleds = 0;
uint16_t curNumleds = 0;

void WS2812B_MakeEffect(WS2812B_t *strip, Effects effect, uint16_t delay) {
	curEffect = effect;
	curNumleds = strip->numleds;
	switch (effect) {
	case EFFECT_NONE:break;
	case EFFECT_RAINBOWLOOP: Effect_RainbowLoop(strip, delay); break;
	case EFFECT_FADE: Effect_Fade(strip, delay); break;
	case EFFECT_POLICE: Effect_Police(strip, delay); break;
	}
	prevEffect = effect;
	prevNumleds = strip->numleds;
}

void Effect_RainbowLoop(WS2812B_t *strip, uint16_t delay) {
	static Animation_t loop;
	if (prevEffect != curEffect || curNumleds != prevNumleds) {
		AnimationInit(&loop, 0);
		Preset_Rainbow(strip, 0, strip->numleds - 1, 0);
		WS2812B_SetBrightness(strip, strip->brightness);
	}
	Animation_Loop(strip, &loop, 0, strip->numleds - 1, delay);
}

void Effect_Fade(WS2812B_t *strip, uint16_t delay){
	static Animation_t fade;
	if (prevEffect != curEffect || curNumleds != prevNumleds) {
		AnimationInit(&fade, 0);
	}
	Animation_Fade(strip, &fade, 0, strip->numleds - 1, delay);
}

void Effect_Police(WS2812B_t *strip, uint16_t delay){
	static Animation_t fade_red, fade_blue;
	if (prevEffect != curEffect || curNumleds != prevNumleds) {
		AnimationInit(&fade_red, 0);
		AnimationInit(&fade_blue, 1);
		Preset_HUE(strip, 0, 0, strip->numleds / 2 - 1);
		Preset_HUE(strip, 130, strip->numleds / 2, strip->numleds - 1);
	}
	Animation_Fade(strip, &fade_red, 0, strip->numleds / 2 - 1, delay);
	Animation_Fade(strip, &fade_blue, strip->numleds / 2, strip->numleds - 1, delay);
}
