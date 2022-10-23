#include "WS2812B_Presets.h"

extern WS2812B_t leds[];
extern uint8_t NUM_LEDS;
extern uint8_t BRIGHTNESS;

void Preset_Rainbow(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored){
	float step = (float)255 / (float)(end - begin);
	int j = 0;
	if(!mirrored){
		for(int i = begin; i <= end; i++){
			WS2812B_SetPixelHSV(layer, j * (uint8_t)step, 255, 255, i);
			j++;
		}
	}
	else{
		for(int i = end; i >= begin; i--){
			WS2812B_SetPixelHSV(layer, j * (uint8_t)step, 255, 255, i);
			j++;
		}
	}
}

void Preset_Raindrop(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored){
	float step = (float)BRIGHTNESS/ (float)(end - begin);
	float j = 0;
	if(!mirrored){
		for(int i = begin; i <= end; i++){
			WS2812B_SetPixelBrightness(layer, (uint8_t)(j * step + 1), i);
			j++;
		}
	}
	else{
		for(int i = end; i >= begin; i--){
			WS2812B_SetPixelBrightness(layer, (uint8_t)(j * step + 1), i);
			j++;
		}
	}
}

void Preset_OnOff(WS2812B_t* layer, uint16_t begin, uint16_t end, uint16_t state){
	for(int i = begin; i <= end; i++){
		if(state == 0)
			WS2812B_SetPixelBrightness(layer, 0, i);
		else WS2812B_SetPixelBrightness(layer, BRIGHTNESS, i);
	}
}

void Preset_RandomColor(WS2812B_t* layer, uint16_t begin, uint16_t end){
	int hue = rand() % 255;
	for(int i = begin; i <= end; i++)
		WS2812B_SetPixelHSV(layer, hue, 255, 255, i);
}

void Preset_Hue(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t hue){
	for(int i = begin; i <= end; i++)
		WS2812B_SetPixelHSV(layer, hue, 255, 255, i);
}

void Preset_Gradient(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t hue_b, uint8_t hue_e, uint8_t mirrored){
	float j = 0;
	if(!mirrored){
		if(hue_e >= hue_b){
			float step = (hue_e - hue_b) / (end - begin);
			for(int i = begin; i <= end; i++){
				WS2812B_SetPixelHSV(layer, (uint8_t)(hue_b + step * j), 255, 255, i);
				j++;
			}
		}
		else{
			float step = (hue_b - hue_e) / (end - begin);
			for(int i = begin; i <= end; i++){
				WS2812B_SetPixelHSV(layer, (uint8_t)(hue_e + step * j), 255, 255, i);
				j++;
			}
		}
	}
	else{
		if(hue_e >= hue_b){
			float step = (hue_e - hue_b) / (end - begin);
			for(int i = end; i >= begin; i--){
				WS2812B_SetPixelHSV(layer, (uint8_t)(hue_b + step * j), 255, 255, i);
				j++;
			}
		}
		else{
			float step = (hue_b - hue_e) / (end - begin);
			for(int i = end; i >= begin; i--){
				WS2812B_SetPixelHSV(layer, (uint8_t)(hue_e + step * j), 255, 255, i);
				j++;
			}
		}
	}
}





void Preset_RandomPixelOnOff(){
	int led_state;
	uint8_t prew_bright;
	for(int i = 0; i < NUM_LEDS; i++){
		if(leds[i].brightness != 0){
			prew_bright = leds[i].brightness;
			break;
		}
	}

	for(int i = 0; i < NUM_LEDS; i++){
		led_state = rand() % 2;
		if(led_state)
			leds[i].brightness = prew_bright;
		else leds[i].brightness = 0;
	}
}


