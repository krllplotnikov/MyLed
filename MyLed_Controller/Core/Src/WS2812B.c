#include <WS2812B.h>

unsigned long T;

void WS2812B_Init(WS2812B_t* strip, uint16_t numleds, TIM_HandleTypeDef* htim, uint32_t tim_ch){
	strip->leds = calloc(numleds, sizeof(RGB_t));
	strip->pwm_buff = calloc(numleds * COLORS_BITS + RESET_BITS, sizeof(uint16_t));
	strip->htim = htim;
	strip->tim_ch = tim_ch;
	strip->brightness = 127;
	strip->max_numleds = numleds;
	strip->numleds = 60;
	strip->fps = 60;
	strip->onOff = 1;
	for(int i = 0; i < strip->max_numleds; i++){
		strip->leds[i].R = 255;
		strip->leds[i].G = 0;
		strip->leds[i].B = 0;
		strip->leds[i].brightness = 127;
	}
}

void WS2812B_SetFPS(WS2812B_t* strip, uint16_t fps){
	strip->fps = fps;
}

void WS2812B_SetBrightness(WS2812B_t* strip, uint8_t brightness){
	strip->brightness = brightness;
	for(int i = 0; i < strip->numleds; i++)
		strip->leds[i].brightness = brightness;
}

void WS2812B_SetPixelBrightness(WS2812B_t* strip, uint8_t brightness, uint16_t led_pos){
	strip->leds[led_pos].brightness = brightness;
}


void WS2812B_SetPixelBrightnessCRT(WS2812B_t* strip, float brightness, uint16_t led_pos){
	strip->leds[led_pos].brightness = (uint8_t)(crt2(brightness, strip->brightness));
}

void WS2812B_SetNumLeds(WS2812B_t* strip, uint16_t numleds){
	if(numleds <= strip->max_numleds)
		strip->numleds = numleds;
	WS2812B_SetBrightness(strip, strip->brightness);
	for(int i = 0; i < strip->max_numleds * COLORS_BITS; i++)
		strip->pwm_buff[i] = LOW;
}

void WS2812B_Show(WS2812B_t* strip){
	if(HAL_GetTick() - T > 1000/strip->fps){
		HAL_TIM_PWM_Stop_DMA(strip->htim, strip->tim_ch);
		RGB_to_GRB_PWM(strip);
		HAL_TIM_PWM_Start_DMA(strip->htim, strip->tim_ch, (uint32_t*)(strip->pwm_buff), strip->max_numleds * COLORS_BITS + RESET_BITS);
		T = HAL_GetTick();
	}
}

void WS2812B_Off(WS2812B_t* strip){
	if(HAL_GetTick() - T > 1000/strip->fps){
		HAL_TIM_PWM_Stop_DMA(strip->htim, strip->tim_ch);
		for(size_t i = 0; i < strip->max_numleds * COLORS_BITS; i++)
			strip->pwm_buff[i] = LOW;
		HAL_TIM_PWM_Start_DMA(strip->htim, strip->tim_ch, (uint32_t*)(strip->pwm_buff), strip->max_numleds * COLORS_BITS + RESET_BITS);
		T = HAL_GetTick();
	}
}
void WS2812B_SetPixelRGB(WS2812B_t* strip, uint8_t R, uint8_t G, uint8_t B, uint16_t led_pos){
	strip->leds[led_pos].R = R;
	strip->leds[led_pos].G = G;
	strip->leds[led_pos].B = B;
}

void WS2812B_SetPixelHUE(WS2812B_t* strip, uint8_t h, uint16_t led_pos){
	uint8_t shift = 0;
	if(h > 170){
		shift = (h - 170) * 3;
		WS2812B_SetPixelRGB(strip, shift, 0, ~shift, led_pos);
	}else if(h > 85){
		shift = (h - 85) * 3;
		WS2812B_SetPixelRGB(strip, 0, ~shift, shift, led_pos);
	}else{
		shift = h * 3;
		WS2812B_SetPixelRGB(strip, ~shift, shift, 0, led_pos);
	}
}

//Presets
void Preset_Rainbow(WS2812B_t *strip, uint16_t begin, uint16_t end, uint8_t mirrored){
	if(mirrored){
		for(uint16_t i = begin; i <= end; i++) {
			WS2812B_SetPixelHUE(strip, (uint8_t)(interpolation(0, (end - begin), 0, 255, end - i)), i);
		}
	}else{
		for(uint16_t i = begin; i <= end; i++) {
			WS2812B_SetPixelHUE(strip, (uint8_t)(interpolation(0, (end - begin), 0, 255, i)), i);
		}
	}
}

void Preset_HUE(WS2812B_t* strip, uint8_t h, uint16_t begin, uint16_t end){
	for(uint16_t i = begin; i <= end; i++){
		WS2812B_SetPixelHUE(strip, h, i);
	}
}

void Preset_Raindrop(WS2812B_t *strip, uint16_t begin, uint16_t end, uint8_t mirrored){
	float step = (float)strip->brightness / (float)(end - begin);
	if(!mirrored){
		float b = 0;
		for(uint16_t i = begin; i <= end; i++){
			WS2812B_SetPixelBrightnessCRT(strip, b, i);
			//WS2812B_SetPixelBrightness(strip, b, i);
			if(strip->leds[i].brightness < (255 / strip->brightness + 1))
				strip->leds[i].brightness = 255 / strip->brightness + 1;
			b += step;
		}
	}else{
		float b = strip->brightness;
		for(uint16_t i = begin; i <= end; i++){
			WS2812B_SetPixelBrightnessCRT(strip, b, i);
			//WS2812B_SetPixelBrightness(strip, b, i);
			if(strip->leds[i].brightness < (255 / strip->brightness + 1))
				strip->leds[i].brightness = 255 / strip->brightness + 1;
			b -= step;
		}
	}
}

void Preset_OnOff(WS2812B_t* strip, uint8_t state, uint16_t begin, uint16_t end){
	if(!state){
		for(uint16_t i = begin; i <= end; i++){
			WS2812B_SetPixelBrightness(strip, 0, i);
		}
	}else{
		for(uint16_t i = begin; i <= end; i++){
			WS2812B_SetPixelBrightness(strip, strip->brightness, i);
		}
	}
}
//Animations
void AnimationInit(Animation_t* animation, uint8_t mirrored){
	animation->mirrored = mirrored;
	animation->counter = 0;
	animation->direction = 0;
	animation->repeatTime = 0;
}

void Animation_Loop(WS2812B_t *strip, Animation_t* animation, uint16_t begin, uint16_t end, uint16_t delay){
	if (HAL_GetTick() - animation->repeatTime > delay) {
		if (animation->mirrored) {
			RGB_t temp;
			temp.R = strip->leds[begin].R;
			temp.G = strip->leds[begin].G;
			temp.B = strip->leds[begin].B;
			temp.brightness = strip->leds->brightness;
			for (int i = begin; i < end; i++) {
				strip->leds[i].R = strip->leds[i + 1].R;
				strip->leds[i].G = strip->leds[i + 1].G;
				strip->leds[i].B = strip->leds[i + 1].B;
				strip->leds[i].brightness = strip->leds[i + 1].brightness;
			}
			strip->leds[end].R = temp.R;
			strip->leds[end].G = temp.G;
			strip->leds[end].B = temp.B;
			strip->leds[end].brightness = temp.brightness;
		} else{
			RGB_t temp;
			temp.R = strip->leds[end].R;
			temp.G = strip->leds[end].G;
			temp.B = strip->leds[end].B;
			temp.brightness = strip->leds->brightness;
			for (int i = end; i > begin; i--) {
				strip->leds[i].R = strip->leds[i - 1].R;
				strip->leds[i].G = strip->leds[i - 1].G;
				strip->leds[i].B = strip->leds[i - 1].B;
				strip->leds[i].brightness = strip->leds[i - 1].brightness;
			}
			strip->leds[begin].R = temp.R;
			strip->leds[begin].G = temp.G;
			strip->leds[begin].B = temp.B;
			strip->leds[begin].brightness = temp.brightness;
		}
		animation->repeatTime = HAL_GetTick();
	}
}

void Animation_Fade(WS2812B_t *strip, Animation_t* animation, uint16_t begin, uint16_t end, uint16_t delay){
	if (HAL_GetTick() - animation->repeatTime > delay){
		float step = (float)strip->brightness / 255;
		if(animation->mirrored){
			if(animation->direction == 0){
				for(uint16_t i = begin; i <= end; i++){
					if(strip->leds[i].brightness >= 0){
						WS2812B_SetPixelBrightness(strip, strip->brightness - (strip->brightness - animation->counter * step), i);
					}
				}
				animation->counter++;
				if(animation->counter * step >= strip->brightness){
					animation->direction = 1;
				}
			}
			if(animation->direction == 1){
				for(uint16_t i = begin; i <= end; i++){
					if(strip->leds[i].brightness <= strip->brightness){
						WS2812B_SetPixelBrightness(strip, strip->brightness - (strip->brightness - animation->counter * step), i);
					}
				}
				animation->counter--;
				if(animation->counter * step <= 0){
					animation->direction = 0;
				}
			}
		} else{
			if(animation->direction == 0){
				for(uint16_t i = begin; i <= end; i++){
					if(strip->leds[i].brightness >= 0){
						WS2812B_SetPixelBrightness(strip, strip->brightness - (animation->counter * step), i);
					}
				}
				animation->counter++;
				if(animation->counter * step >= strip->brightness){
					animation->direction = 1;
				}
			}
			if(animation->direction == 1){
				for(uint16_t i = begin; i <= end; i++){
					if(strip->leds[i].brightness <= strip->brightness){
						WS2812B_SetPixelBrightness(strip, strip->brightness - (animation->counter * step), i);
					}
				}
				animation->counter--;
				if(animation->counter * step <= 0){
					animation->direction = 0;
				}
			}
		}
		animation->repeatTime = HAL_GetTick();
	}
}

void Animation_Train(WS2812B_t *strip, Animation_t* animation, uint16_t begin, uint16_t end, uint16_t delay){
	if (HAL_GetTick() - animation->repeatTime > delay) {
		if (!animation->mirrored) {
			for (int i = begin; i < end; i++) {
				strip->leds[i].R = strip->leds[i + 1].R;
				strip->leds[i].G = strip->leds[i + 1].G;
				strip->leds[i].B = strip->leds[i + 1].B;
				strip->leds[i].brightness = strip->leds[i + 1].brightness;
			}
			strip->leds[end].R = 0;
			strip->leds[end].G = 0;
			strip->leds[end].B = 0;
			strip->leds[end].brightness = 0;
		} else{
			for (int i = end; i > begin; i--) {
				strip->leds[i].R = strip->leds[i - 1].R;
				strip->leds[i].G = strip->leds[i - 1].G;
				strip->leds[i].B = strip->leds[i - 1].B;
				strip->leds[i].brightness = strip->leds[i - 1].brightness;
			}
			strip->leds[begin].R = 0;
			strip->leds[begin].G = 0;
			strip->leds[begin].B = 0;
			strip->leds[begin].brightness = 0;
		}
		animation->repeatTime = HAL_GetTick();
	}
}
//----------------
void RGB_to_GRB_PWM(WS2812B_t* strip){
	for(int i = 0; i < strip->numleds; i++){
		uint8_t r = strip->leds[i].R;
		r = interpolation(0, 255, 0, strip->leds[i].brightness, r);
		uint8_t g = strip->leds[i].G;
		g = interpolation(0, 255, 0, strip->leds[i].brightness, g);
		uint8_t b = strip->leds[i].B;
		b = interpolation(0, 255, 0, strip->leds[i].brightness, b);
		for(int j = 0; j < COLOR_BYTE; j++){
			if(1 & (g >> (COLOR_BYTE - j - 1)))
				strip->pwm_buff[j + (i * COLORS_BITS)] = HIGH;
			else strip->pwm_buff[j + (i * COLORS_BITS)] = LOW;

			if(1 & (r >> (COLOR_BYTE - j - 1)))
				strip->pwm_buff[j + (i * COLORS_BITS) + 8] = HIGH;
			else strip->pwm_buff[j + (i * COLORS_BITS) + 8] = LOW;

			if(1 & (b >> (COLOR_BYTE - j - 1)))
				strip->pwm_buff[j + (i * COLORS_BITS) + 16] = HIGH;
			else strip->pwm_buff[j + (i * COLORS_BITS) + 16] = LOW;
		}
	}
}


//x1 = 0; x2 = 255; fx1 = 0;  fx2 = brightness; x = value;
float interpolation(float x1, float x2, float fx1, float fx2, float x){
	return (fx1 + (x - x1)*((fx2 - fx1)/(x2 - x1)));
}
float crt2(float in, float max){
	//return (in * in * in + max) / 65536;
	return (in * in + max) / 256;
}
