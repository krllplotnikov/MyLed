#include "WS2812B.h"
#include "WS2812B_Effects.h"

extern WS2812B_t leds[];
extern uint8_t NUM_LEDS;
extern uint8_t BRIGHTNESS;


int Effect_Loop(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static unsigned long T[16] = {0};
	static int counter[16] = {0};
	if((HAL_GetTick() - T[n_effect]) >= delay){
		WS2812B_t tmp;
		if(!mirrored){
			tmp = layer[end];
			for(int i = end; i >= begin; i--)
				layer[i] = layer[i - 1];
			layer[begin] = tmp;
		}
		else{
			tmp = layer[begin];
			for(int i = begin; i <= end; i++)
				layer[i] = layer[i + 1];
			layer[end] = tmp;
		}
		T[n_effect] = HAL_GetTick();
		if(counter[n_effect] >= (end - begin))
		{
			counter[n_effect] = 0;
			return END_CYCLE;
		}
		counter[n_effect]++;
		return counter[n_effect];
	}
	return 0;
}

int Effect_LoopOnlyBrightness(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static unsigned long T[16] = {0};
	static int counter[16] = {0};
	if((HAL_GetTick() - T[n_effect]) >= delay){
		WS2812B_t tmp;
		if(!mirrored){
			tmp.brightness = layer[end].brightness;
			for(int i = end; i >= begin; i--)
				layer[i].brightness = layer[i - 1].brightness;
			layer[begin].brightness = tmp.brightness;
		}
		else{
			tmp.brightness = layer[begin].brightness;
			for(int i = begin; i <= end; i++)
				layer[i].brightness = layer[i + 1].brightness;
			layer[end].brightness = tmp.brightness;
		}
		T[n_effect] = HAL_GetTick();
		if(counter[n_effect] >= (end - begin))
		{
			counter[n_effect] = 0;
			return END_CYCLE;
		}
		counter[n_effect]++;
		return counter[n_effect];
	}
	return 0;
}
int Effect_Rainbow(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static unsigned long T[16] = {0};
	static uint8_t counter[16] = {0};
	if((HAL_GetTick() - T[n_effect]) >= delay){
		for(int i = begin; i <= end; i++){
			WS2812B_SetPixelHSV(layer, counter[n_effect], 255, 255, i);
		}
		counter[n_effect]++;
		T[n_effect] = HAL_GetTick();
		if(counter[n_effect] == 0)
			return END_CYCLE;
		return counter[n_effect];
	}
	return 0;
}

int Effect_Fade(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static int updown[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	static int counter[16] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	static unsigned long T[16] = {0};
	if(!mirrored){
		if((HAL_GetTick() - T[n_effect]) >= delay){
			if(updown[n_effect])
			{
				for(int i = begin; i <= end; i++){
					if(layer[i].brightness != 0)
						WS2812B_SetPixelBrightness(layer, counter[n_effect], i);
				}
				counter[n_effect]++;
				if(counter[n_effect] >= BRIGHTNESS)
					updown[n_effect] = 0;
			}

			else if(!updown[n_effect])
			{
				for(int i = begin; i <= end; i++){
					if(layer[i].brightness != 0)
						WS2812B_SetPixelBrightness(layer, counter[n_effect], i);
				}
				counter[n_effect]--;
				if(counter[n_effect] <= 1)
					updown[n_effect] = 1;
			}
			T[n_effect] = HAL_GetTick();
			if(counter[n_effect] == 1)
				return END_CYCLE;
			return counter[n_effect];
		}
	}
	else{
		if((HAL_GetTick() - T[n_effect]) >= delay){
			if(!updown[n_effect])
			{
				for(int i = begin; i <= end; i++){
					if(layer[i].brightness != 0)
						WS2812B_SetPixelBrightness(layer, BRIGHTNESS - counter[n_effect] + 1, i);
				}
				counter[n_effect]--;
				if(counter[n_effect] <= 1)
					updown[n_effect] = 1;

			}

			else if(updown[n_effect])
			{
				for(int i = begin; i <= end; i++){
					if(layer[i].brightness != 0)
						WS2812B_SetPixelBrightness(layer, BRIGHTNESS - counter[n_effect] + 1, i);
				}
				counter[n_effect]++;
				if(counter[n_effect] >= BRIGHTNESS)
					updown[n_effect] = 0;
			}
			T[n_effect] = HAL_GetTick();
			if(counter[n_effect] == 1)
				return END_CYCLE;
			return counter[n_effect];
		}
	}
	return 0;
}


int Effect_FadeDown(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static unsigned long T[16] = {0};
	if((HAL_GetTick() - T[n_effect]) >= delay){
		if(!mirrored){
			for(int i = begin; i <= end; i++)
				if(layer[i].brightness > 0){
					layer[i].brightness--;
					WS2812B_SetPixelBrightness(layer, layer[i].brightness, i);
				}
		}
		else{
			for(int i = begin; i <= end; i++)
				if(layer[i].brightness < BRIGHTNESS){
					layer[i].brightness++;
					WS2812B_SetPixelBrightness(layer, layer[i].brightness, i);
				}
		}
		T[n_effect] = HAL_GetTick();
		return END_CYCLE;
	}
	return 0;
}

int Effect_Train(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static unsigned long T[16] = {0};
	static int counter[16] = {0};
	if((HAL_GetTick() - T[n_effect]) >= delay){
		if(!mirrored){
			for(int i = end; i > begin; i--){
				layer[i] = layer[i - 1];
			}
			WS2812B_SetPixelBrightness(layer, 0, begin);
			WS2812B_SetPixelRGB(layer, 0, 0, 0, begin);
		}
		else{
			for(int i = begin; i < end; i++){
				layer[i] = layer[i + 1];
			}
			WS2812B_SetPixelBrightness(layer, 0, end);
			WS2812B_SetPixelRGB(layer, 0, 0, 0, end);
		}
		T[n_effect] = HAL_GetTick();
		counter[n_effect]++;
		if(counter[n_effect] >= (end - begin)){
			counter[n_effect] = 0;
			return END_CYCLE;
		}
		return counter[n_effect];
	}
	return 0;
}

int Effect_TrainOnlyBrightness(WS2812B_t* layer, uint16_t begin, uint16_t end, uint8_t mirrored, uint16_t delay, uint8_t n_effect){
	static unsigned long T[16] = {0};
	static int counter[16] = {0};
	if((HAL_GetTick() - T[n_effect]) >= delay){
		if(!mirrored){
			for(int i = end; i > begin; i--){
				layer[i].brightness = layer[i - 1].brightness;
			}
			WS2812B_SetPixelBrightness(layer, 0, begin);
			WS2812B_SetPixelRGB(layer, 0, 0, 0, begin);
		}
		else{
			for(int i = begin; i < end; i++){
				layer[i].brightness = layer[i + 1].brightness;
			}
			WS2812B_SetPixelBrightness(layer, 0, end);
			WS2812B_SetPixelRGB(layer, 0, 0, 0, end);
		}
		T[n_effect] = HAL_GetTick();
		counter[n_effect]++;
		if(counter[n_effect] >= (end - begin)){
			counter[n_effect] = 0;
			return END_CYCLE;
		}
		return counter[n_effect];
	}
	return 0;
}
