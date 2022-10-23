#include "WS2812B.h"
#include "math.h"

unsigned long T;
uint8_t STATE;
uint16_t DELAY = 10;
uint8_t BRIGHTNESS = 16;
uint8_t NUM_LEDS = 60;
uint16_t PWM_buff[PWM_BUFF_LENGTH];

WS2812B_t leds[MAX_NUM_LEDS] = {0};

void WS2812B_Init(uint8_t num_leds, uint8_t brightness){
	WS2812B_SetNumLeds(num_leds);
	WS2812B_SetDelay(DELAY);

	for(int i = 0; i < NUM_LEDS; i++)
		WS2812B_SetPixelRGB(leds, 0, 0, 0, i);
	WS2812B_SetBrightness(brightness);
	WS2812B_Show();
}

void WS2812B_SetDelay(uint16_t delay){
	DELAY = delay;
}

void WS2812B_SetPixelBrightness(WS2812B_t* layer, uint8_t brightness, uint8_t led_pos){
	layer[led_pos].brightness = brightness;
}

void WS2812B_SetBrightness(uint8_t brightness){
	BRIGHTNESS = brightness;
	for(int i = 0; i < NUM_LEDS; i++)
		leds[i].brightness = brightness;
}

void WS2812B_SetNumLeds(uint8_t num_leds){
	NUM_LEDS = num_leds;
	for(int i = 0; i < MAX_NUM_LEDS; i++)
		WS2812B_SetPixelRGB(leds, 0, 0, 0, i);
	WS2812B_SetBrightness(BRIGHTNESS);
	for(int i = 0; i < PWM_BUFF_LENGTH - RESET_BITS; i++)
		PWM_buff[i] = LOW;
}
ShowStatus WS2812B_Show(){
	if((HAL_GetTick() - T) > DELAY){
		if(STATE != WS2812B_BUSY){
			RGB_to_GRB_PWM();
			HAL_TIM_PWM_Start_DMA(H_TIM, T_CH, (uint32_t*)PWM_buff, PWM_BUFF_LENGTH);
			STATE = WS2812B_BUSY;
			T = HAL_GetTick();
			return SHOW_OK;
		}
	}
	return SHOW_ERROR;
}

void WS2812B_SetPixelRGB(WS2812B_t* layer, uint8_t R, uint8_t G, uint8_t B, uint8_t led_pos){
	layer[led_pos].R = R;
	layer[led_pos].G = G;
	layer[led_pos].B = B;
}

void WS2812B_SetPixelHSV(WS2812B_t* layer, uint8_t h, uint8_t s, uint8_t v, uint8_t led_pos){
	float H = interpolation(0, 255, 0, 360, h);
	float S = interpolation(0, 255, 0, 1, s);
	float V = interpolation(0, 255, 0, 1, v);
	if(S == 0){
		layer[led_pos].R = V * 255;
		layer[led_pos].G = V * 255;
		layer[led_pos].B = V * 255;
		return;
	}
	float sector = floor (H / 60);
	float frac = H / 60 - sector;
	float T = (V * (1 - S)) * 255;
	float P = (V * (1 - S * frac)) * 255;
	float Q = (V * (1 - S * (1 - frac))) * 255;
	V = V * 255;

	switch((int)sector)
	{
		case 0: layer[led_pos].R = V; layer[led_pos].G = Q; layer[led_pos].B = T; break;
		case 1: layer[led_pos].R = P; layer[led_pos].G = V; layer[led_pos].B = T; break;
		case 2: layer[led_pos].R = T; layer[led_pos].G = V; layer[led_pos].B = Q; break;
		case 3: layer[led_pos].R = T; layer[led_pos].G = P; layer[led_pos].B = V; break;
		case 4: layer[led_pos].R = Q; layer[led_pos].G = T; layer[led_pos].B = V; break;
		case 5: layer[led_pos].R = V; layer[led_pos].G = T; layer[led_pos].B = P; break;
	}
}



//----------------
void RGB_to_GRB_PWM(){
	for(int i = 0; i < NUM_LEDS; i++){
		uint8_t r = leds[i].R;
		r = interpolation(0, 255, 0, leds[i].brightness, r);
		uint8_t g = leds[i].G;
		g = interpolation(0, 255, 0, leds[i].brightness, g);
		uint8_t b = leds[i].B;
		b = interpolation(0, 255, 0, leds[i].brightness, b);
		for(int j = 0; j < COLOR_BYTE; j++){
			if(1 & (g >> (COLOR_BYTE - j - 1)))
				PWM_buff[j + (i * COLORS_BITS)] = HIGH;
			else PWM_buff[j + (i * COLORS_BITS)] = LOW;

			if(1 & (r >> (COLOR_BYTE - j - 1)))
				PWM_buff[j + (i * COLORS_BITS) + 8] = HIGH;
			else PWM_buff[j + (i * COLORS_BITS) + 8] = LOW;

			if(1 & (b >> (COLOR_BYTE - j - 1)))
				PWM_buff[j + (i * COLORS_BITS) + 16] = HIGH;
			else PWM_buff[j + (i * COLORS_BITS) + 16] = LOW;
		}
	}
}


void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == H_TIM){
		HAL_TIM_PWM_Stop_DMA(H_TIM, T_CH);
		STATE = WS2812B_READY;
	}
}

//x1 = 0; x2 = 255; fx1 = 0;  fx2 = brightness; x = value;
float interpolation(float x1, float x2, float fx1, float fx2, float x){
	return fx1 + (x - x1)*((fx2 - fx1)/(x2 - x1));
}
