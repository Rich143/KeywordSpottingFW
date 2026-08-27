#include <float.h>
#include "unity.h"

#include "audio_preprocessing.h"
#include "spectrogram_signal_input.h"
#include "spectrogram_output.h"

#include "test_helpers.h"

#include "mel_filterbank.h"

#include "arm_math.h"

#define DEBUG_DUMP_FILTERED_OUTPUT 0
#if DEBUG_DUMP_FILTERED_OUTPUT
#include <stdio.h>
#endif

// To get these directives to work:
// - quote the file name in " "
// - Add the directory containing the file to :paths: in project.yml
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/TransformFunctions/arm_rfft_fast_f32.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/TransformFunctions/arm_rfft_fast_init_f32.c")

// These files are referenced by rfft files above
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/TransformFunctions/arm_cfft_init_f32.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/TransformFunctions/arm_cfft_f32.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/TransformFunctions/arm_bitreversal2.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/TransformFunctions/arm_cfft_radix8_f32.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/CommonTables/arm_const_structs.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/CommonTables/arm_common_tables.c")

// Audio preproc source files
TEST_SOURCE_FILE("../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Src/common_tables.c")
TEST_SOURCE_FILE("../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Src/feature_extraction.c")
TEST_SOURCE_FILE("../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Src/mel_filterbank.c")
TEST_SOURCE_FILE("../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Src/window.c")
TEST_SOURCE_FILE("../Middlewares/ST/STM32_AI_AudioPreprocessing_Library/Src/dct.c")

// Other CMSIS-DSP source files needed by Audio preproc Lib
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/ComplexMathFunctions/arm_cmplx_mag_squared_f32.c")
TEST_SOURCE_FILE("../Drivers/CMSIS-DSP/Source/BasicMathFunctions/arm_mult_f32.c")

void setUp(void) {
    audio_preprocessing_init();
}

void tearDown(void) {}

void test_preproc(void) {
    for (int i = 0; i < AUDIO_SPECTROGRAM_COLS; i++) {
        audio_preprocessing_run(spectrogram_signal_input);
    }

    float32_t *spectrogram = audio_preprocessing_get_spectrogram();
    uint32_t spectrogram_len = audio_preprocessing_get_spectrogram_len();

    check_signal_close(spectrogram, test_mel_spectrogram_output, spectrogram_len, 1e-4f);

#if DEBUG_DUMP_FILTERED_OUTPUT
    // Print the spectrogram
    for (uint32_t i = 0; i < spectrogram_len; i++) {
        printf("%.7g ", spectrogram[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
#endif
}
