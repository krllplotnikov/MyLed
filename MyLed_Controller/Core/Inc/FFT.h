#ifndef INC_FFT_H_
#define INC_FFT_H_

#include "stm32f1xx_hal.h"
#include "math.h"
#include "stdlib.h"

float cosine(int i);
float sine(int i);
void FFT(int* in, int* out, int N, float Frequency);
#endif
