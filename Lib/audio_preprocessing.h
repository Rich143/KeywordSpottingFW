#pragma once

#include "arm_math_types.h"

// At 16000 Hz, 512 = (1/(16000))*512*1000 = 32 ms
// Choose this to be a power of 2 so that the FFT is also a power of 2
#define AUDIO_SPECTROGRAM_FRAME_LEN 512
#define AUDIO_SAMPLE_RATE_HZ        16000

#define AUDIO_SPECTROGRAM_NMELS     30
#define AUDIO_SPECTROGRAM_ROWS      AUDIO_SPECTROGRAM_NMELS
#define AUDIO_SPECTROGRAM_COLS      32

typedef enum {
    AUDIO_PREPROCESSING_STATUS_OK = 0,
    AUDIO_PREPROCESSING_STATUS_ERROR_SPECTROGRAM_FULL,
    AUDIO_PREPROCESSING_STATUS_ERROR_OTHER,
} audio_preprocessing_status_t;

audio_preprocessing_status_t audio_preprocessing_init();
audio_preprocessing_status_t audio_preprocessing_run(float32_t * pInSignal);

float32_t *audio_preprocessing_get_spectrogram(void);
uint32_t   audio_preprocessing_get_spectrogram_len(void);
uint32_t   audio_preprocessing_get_spectrogram_filled_cols(void);
uint32_t   audio_preprocessing_clear_spectrogram(void);
