#include "WS2812B_CustomEffects.h"


extern uint8_t NUM_LEDS;
extern uint8_t BRIGHTNESS;
extern WS2812B_t leds[];

WS2812B_t layer1[MAX_NUM_LEDS] = {0};
WS2812B_t layer2[MAX_NUM_LEDS] = {0};

uint8_t effect_delay = 50;
uint8_t color_music_delay = 50;
uint8_t max_amplitude_low = 35;
uint8_t max_amplitude_medium = 35;
uint8_t max_amplitude_high = 35;
WS2812B_CustomEffect current_effect = NOEFFECT;
WS2812B_CustomEffect previous_effect = NOEFFECT;
WS2812B_ColorMusic current_cm = NOCOLORMUSIC;

int buff_full = 0;
int samples[FFT_SIZE] = {0};
int amplitudes[FFT_SIZE/2] = {0};

void WS2812B_MakeEffect(WS2812B_CustomEffect custom_effect){
	current_cm = NOCOLORMUSIC;
	current_effect = custom_effect;
	switch(custom_effect){
	case NOEFFECT: break;
	case RAINBOW_LOOP: RainbowLoop(); break;
	case FLIP_FLOP: FlipFlop(); break;
	case FADE: Fade(); break;
	case RAINBOW: Rainbow(); break;
	case RAINBOW_FADE: RainbowFade(); break;
	case RANDOM_COLOR_FADE: RandomColorFade(); break;
	case POLICE: Police(); break;
	}
	previous_effect = current_effect;
}
void WS2812B_MakeColorMusic(WS2812B_ColorMusic color_music){
	current_effect = NOEFFECT;
	current_cm = color_music;
	switch(color_music){
	case NOCOLORMUSIC: break;
	case CM_1: ColorMusic_1(); break;
	case CM_2: ColorMusic_2(); break;
	case CM_3: ColorMusic_3(); break;
	}
}

void WS2812B_SetEffectDelay(uint8_t delay){
	effect_delay = delay;
}
void WS2812B_SetColorMusicDelay(uint8_t delay){
	color_music_delay = delay;
}
void WS2812B_SetMaxAmplitudeL(uint8_t amplitude){
	max_amplitude_low = amplitude;
}
void WS2812B_SetMaxAmplitudeM(uint8_t amplitude){
	max_amplitude_medium = amplitude;
}
void WS2812B_SetMaxAmplitudeH(uint8_t amplitude){
	max_amplitude_high = amplitude;
}

void RainbowLoop(){
	if(previous_effect != current_effect){
		  Preset_Rainbow(layer1, 0, NUM_LEDS - 1, 0);
		  Preset_OnOff(layer1, 0, NUM_LEDS, 1);
	}
	Effect_Loop(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 0);
	for(int i = 0; i < NUM_LEDS; i++){
		leds[i].R = layer1[i].R;
		leds[i].G = layer1[i].G;
		leds[i].B = layer1[i].B;
		leds[i].brightness = BRIGHTNESS;
	}
}

void FlipFlop(){
	if(previous_effect != current_effect){
		for(int i = 0; i < NUM_LEDS; i++)
			WS2812B_SetPixelRGB(layer1, 0, 0, 0, i);
		Preset_Hue(layer1, 0, (NUM_LEDS / 6) - 1, rand()%255);
		Preset_Raindrop(layer1, 0, (NUM_LEDS / 6) - 1, 0);
	}
	static int lr = 1;
	if(lr)
	{
		if(Effect_Train(layer1, 0, NUM_LEDS - 1, 1, effect_delay, 0) == END_CYCLE){
			Preset_Hue(layer1, 0, (NUM_LEDS / 6) - 1, rand()%255);
			Preset_Raindrop(layer1, 0, (NUM_LEDS / 6) - 1, 0);
			lr = 0;
		}
	}
	if(!lr){
		if(Effect_Train(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 1) == END_CYCLE){
			Preset_Hue(layer1, NUM_LEDS - (NUM_LEDS / 6), NUM_LEDS - 1, rand()%255);
			Preset_Raindrop(layer1, NUM_LEDS - (NUM_LEDS / 6), NUM_LEDS - 1, 1);
			lr = 1;
		}
	}
	for(int i = 0; i < NUM_LEDS; i++){
		leds[i] = layer1[i];
	}
}

void Fade(){
	if(previous_effect != current_effect)
		Preset_OnOff(layer1, 0, NUM_LEDS - 1, 1);
	Effect_Fade(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 0);
	for(int i = 0; i < NUM_LEDS; i++)
		leds[i].brightness = layer1[i].brightness;
}

void Rainbow(){
	if(previous_effect != current_effect){
		  Preset_Hue(layer1, 0, NUM_LEDS - 1, 0);
		  Preset_OnOff(layer1, 0, NUM_LEDS - 1, 1);
	}
	Effect_Rainbow(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 0);
	for(int i = 0; i < NUM_LEDS; i++){
		leds[i].R = layer1[i].R;
		leds[i].G = layer1[i].G;
		leds[i].B = layer1[i].B;
		leds[i].brightness = BRIGHTNESS;
	}
}

void RainbowFade(){
	if(previous_effect != current_effect){
		Preset_Hue(layer1, 0, NUM_LEDS - 1, 0);
		Preset_OnOff(layer1, 0, NUM_LEDS - 1, 1);
	}
	Effect_Rainbow(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 0);
	Effect_Fade(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 0);
	for(int i = 0; i < NUM_LEDS; i++){
		leds[i] = layer1[i];
	}
}

void RandomColorFade(){
	if(previous_effect != current_effect){
		Preset_RandomColor(layer1, 0, NUM_LEDS - 1);
		Preset_OnOff(layer1, 0, NUM_LEDS - 1, 1);
	}
	if(Effect_Fade(layer1, 0, NUM_LEDS - 1, 0, effect_delay, 0) == END_CYCLE)
		Preset_RandomColor(layer1, 0, NUM_LEDS - 1);
	for(int i = 0; i < NUM_LEDS; i++)
		leds[i] = layer1[i];
}

void Police(){
	if(previous_effect != current_effect){
		Preset_OnOff(layer1, 0, NUM_LEDS - 1, 1);
		for(int i = 0; i < NUM_LEDS / 2; i++)
			WS2812B_SetPixelRGB(layer1, 255, 0, 0, i);
		for(int i = NUM_LEDS / 2; i < NUM_LEDS; i++)
			WS2812B_SetPixelRGB(layer1, 0, 0, 255, i);
	}
	Effect_Fade(layer1, 0, NUM_LEDS / 2 - 1, 0, effect_delay, 0);
	Effect_Fade(layer1, NUM_LEDS / 2, NUM_LEDS - 1, 1, effect_delay, 1);
	for(int i = 0; i < NUM_LEDS; i++){
		leds[i] = layer1[i];
	}
}




void WS2812B_CM_Init(){
	HAL_ADC_Start_IT(H_ADC);
	HAL_TIM_Base_Start(H_TIM_ADC);
}

void ColorMusic_1(){
	Effect_FadeDown(layer1, 0, NUM_LEDS - 1, 0, color_music_delay, 0);
	Preset_Rainbow(layer1, 0, NUM_LEDS / 2 - 1, 0);
	Preset_Rainbow(layer1, NUM_LEDS / 2, NUM_LEDS - 1, 1);

	for(int i = 0; i < NUM_LEDS; i++)
		leds[i] = layer1[i];

	if(buff_full){
		FFT(samples, amplitudes, FFT_SIZE, Fd);
		if(find_max_ampl(1, 3) > max_amplitude_low * 1000){
			Preset_Raindrop(layer1, 0, NUM_LEDS / 6 - 1, 1);
			Preset_Raindrop(layer1, NUM_LEDS - NUM_LEDS / 6, NUM_LEDS - 1, 0);
		}
		if(find_max_ampl(4, 20) > max_amplitude_medium * 1000){
			Preset_Raindrop(layer1, NUM_LEDS / 6, (NUM_LEDS / 6) * 2 - 1, 0);
			Preset_Raindrop(layer1, NUM_LEDS - (NUM_LEDS / 6) * 2, NUM_LEDS - (NUM_LEDS / 6) - 1, 1);
		}
		if(find_max_ampl(21, 127) > max_amplitude_high * 1000){
			Preset_Raindrop(layer1, (NUM_LEDS / 6) * 2, (NUM_LEDS / 6) * 3 - 1, 0);
			Preset_Raindrop(layer1, (NUM_LEDS / 6) * 3, NUM_LEDS - (NUM_LEDS / 6) * 2 - 1, 1);
		}
		buff_full = 0;
	}
}

void ColorMusic_2(){
	static uint8_t hue = 0;

	Effect_Train(layer1, 0, NUM_LEDS - 1, 0, color_music_delay, 0);
	Effect_FadeDown(layer1, NUM_LEDS - NUM_LEDS / 4, NUM_LEDS - 1, 0, color_music_delay, 0);
	for(int i = 0; i < NUM_LEDS; i++)
	  leds[i] = layer1[i];

	if(buff_full){
		FFT(samples, amplitudes, FFT_SIZE, Fd);
		if(find_max_ampl(1, 10) > max_amplitude_low * 1000){
			Preset_Hue(layer1, 0, NUM_LEDS / (NUM_LEDS / 10) - 1, hue);
			Preset_Raindrop(layer1, 0, NUM_LEDS / (NUM_LEDS / 10) - 1, 0);
			hue+=6;
		}
		if(find_max_ampl(21, 120) > max_amplitude_high * 1000){
			Effect_Train(layer1, 0, NUM_LEDS - 1, 0, color_music_delay / 2, 1);
			hue+=12;
		}
		buff_full = 0;
	}
}

void ColorMusic_3(){
	static int start_coord = 0;
	Effect_FadeDown(layer1, 0, NUM_LEDS - 1, 0, color_music_delay, 0);

	for(int i = 0; i < NUM_LEDS; i++)
		leds[i] = layer1[i];

	if(buff_full){
		FFT(samples, amplitudes, FFT_SIZE, Fd);
		if(find_max_ampl(1, 3) > max_amplitude_low * 1000){
			start_coord = rand() % (NUM_LEDS - (NUM_LEDS / 6) - 1);
			Preset_Hue(layer1, start_coord, start_coord + (NUM_LEDS / 6) - 1, rand() % 20);
			Preset_Raindrop(layer1, start_coord, start_coord + (NUM_LEDS / 10) - 1, 0);
			Preset_Raindrop(layer1, start_coord + (NUM_LEDS / 10), start_coord + (NUM_LEDS / 10) + (NUM_LEDS / 10) - 1, 1);
		}
		if(find_max_ampl(1, 20) > max_amplitude_medium * 1000){
			start_coord = rand() % (NUM_LEDS - (NUM_LEDS / 6) - 1);
			Preset_Hue(layer1, start_coord, start_coord + (NUM_LEDS / 6) - 1, rand() % 40 + 60);
			Preset_Raindrop(layer1, start_coord, start_coord + (NUM_LEDS / 10) - 1, 0);
			Preset_Raindrop(layer1, start_coord + (NUM_LEDS / 10), start_coord + (NUM_LEDS / 10) + (NUM_LEDS / 10) - 1, 1);
		}
		if(find_max_ampl(21, 127) > max_amplitude_high * 1000){
			start_coord = rand() % (NUM_LEDS - (NUM_LEDS / 6) - 1);
			Preset_Hue(layer1, start_coord, start_coord + (NUM_LEDS / 6) - 1, rand() % 55 + 200);
			Preset_Raindrop(layer1, start_coord, start_coord + (NUM_LEDS / 10) - 1, 0);
			Preset_Raindrop(layer1, start_coord + (NUM_LEDS / 10), start_coord + (NUM_LEDS / 10) + (NUM_LEDS / 10) - 1, 1);
		}
		buff_full = 0;
	}
}

int find_max_ampl(int start, int stop){
	int max_ampl = amplitudes[start];
	for(int i = start; i < stop - 1; i++){
		if(amplitudes[i] > max_ampl)
			max_ampl = amplitudes[i];
	}
	return max_ampl;
}

int find_max_freq(int start, int stop){
	int step = Fd / FFT_SIZE;
	int max_freq = step * start;
	int max_ampl = amplitudes[start];
	for(int i = start; i < stop - 1; i++){
		if(amplitudes[i] > max_ampl)
			max_freq = step * i;
	}
	return max_freq;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	if(hadc == H_ADC){
		static int i = 0;
		if(i < FFT_SIZE && !buff_full){
		  samples[i] = HAL_ADC_GetValue(H_ADC) - 2048;
		  i++;
		}
		else {
			buff_full = 1;
			i = 0;
		}
	}
}
