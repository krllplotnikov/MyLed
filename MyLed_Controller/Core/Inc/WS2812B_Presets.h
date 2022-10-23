#ifndef INC_WS2812B_PRESETS_H_
#define INC_WS2812B_PRESETS_H_

#include "WS2812B.h"
#include <stdlib.h>

void Preset_Rainbow(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored);
void Preset_OnOff(WS2812B_t* layer, uint16_t begin, uint16_t end, uint16_t state);
void Preset_Raindrop(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored);
void Preset_RandomColor(WS2812B_t* layer, uint16_t begin, uint16_t end);
void Preset_RandomPixelOnOff();
void Preset_Hue(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t hue);
void Preset_Gradient(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t hue_b, uint8_t hue_e, uint8_t mirrored);
#endif
