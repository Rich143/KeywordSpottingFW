#include "feature_extraction.h"
#include "arm_math.h"

#include "audio_preprocessing.h"

#define NFFT             SPECTROGRAM_FRAME_LEN
#define NMELS            30

#define SPECTROGRAM_ROWS NMELS
#define SPECTROGRAM_COLS 32

/* Private macro ------------------------------------------------------------*/

/* Private variables --------------------------------------------------------*/
static float32_t
    aSpectrogram[SPECTROGRAM_ROWS * SPECTROGRAM_COLS]; // Stored in
                                                       // column-major format
                                                       // for easier access to
                                                       // a frames worth
                                                       // (single column) of
                                                       // data
static float32_t aColBuffer[SPECTROGRAM_ROWS];
static uint32_t SpectrColIndex;
float32_t aWorkingBuffer1[NFFT];

static arm_rfft_fast_instance_f32 S_Rfft;
static MelFilterTypeDef           S_MelFilter;
static SpectrogramTypeDef         S_Spectr;
static MelSpectrogramTypeDef      S_MelSpectr;

/* Public functions ---------------------------------------------------------*/
void audio_preprocessing_init(void) {
    /* Init RFFT */
    arm_rfft_fast_init_1024_f32(&S_Rfft);

    /* Init Spectrogram */
    S_Spectr.pRfft    = &S_Rfft;
    S_Spectr.Type     = SPECTRUM_TYPE_POWER;
    S_Spectr.pWindow  = (float32_t *) hannWin_1024;
    S_Spectr.SampRate = 16000;
    S_Spectr.FrameLen = 1024;
    S_Spectr.FFTLen   = 1024;
    S_Spectr.pScratch = aWorkingBuffer1;

    /* Init Mel filter */
    S_MelFilter.pStartIndices = (uint32_t *) melFiltersStartIndices_1024_30;
    S_MelFilter.pStopIndices  = (uint32_t *) melFiltersStopIndices_1024_30;
    S_MelFilter.pCoefficients = (float32_t *) melFilterLut_1024_30;
    S_MelFilter.NumMels       = 30;

    /* Init MelSpectrogram */
    S_MelSpectr.SpectrogramConf = &S_Spectr;
    S_MelSpectr.MelFilter       = &S_MelFilter;

    SpectrColIndex = 0;
}

void audio_preprocessing_run(float32_t * pInSignal) {
    float32_t pInSignalCopy[SPECTROGRAM_FRAME_LEN];


    for (uint32_t i = 0; i < SPECTROGRAM_COLS; i++) {
    /*for (uint32_t i = 0; i < 1; i++) {*/
        SpectrColIndex = i;
        memcpy(pInSignalCopy, pInSignal, SPECTROGRAM_FRAME_LEN * sizeof(float32_t));

        MelSpectrogramColumn(&S_MelSpectr, pInSignalCopy, &aSpectrogram[SpectrColIndex * SPECTROGRAM_ROWS]);
    }
}

float32_t * audio_preprocessing_get_spectrogram(void) {
    return aSpectrogram;
}

uint32_t audio_preprocessing_get_spectrogram_len(void) {
    return SPECTROGRAM_ROWS * SPECTROGRAM_COLS;
}
