#pragma once

#include "arm_math_types.h"

#define SPECTROGRAM_FRAME_LEN 1024

void audio_preprocessing_init();
void audio_preprocessing_run();

float32_t *  audio_preprocessing_get_spectrogram(void);
uint32_t     audio_preprocessing_get_spectrogram_len(void);
