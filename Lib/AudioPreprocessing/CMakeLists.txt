add_library(AudioPreprocessing STATIC
    audio_preprocessing.c
    audio_preprocessing.h
)

target_link_libraries(AudioPreprocessing PRIVATE
    STM32AudioProc)
    #CMSISDSP::CMSISDSP)

target_include_directories(AudioPreprocessing PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
