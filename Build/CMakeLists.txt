# Template CMakeLists.txt configuration for STM32 MCUS
cmake_minimum_required(VERSION 3.12)
# ##############################################################################
# Edit your MCU information up to the next border
project(mainProject)

set(MCU_FAMILY STM32F4xx)
set(MCU_MODEL STM32F411xx)
set(CPU_PARAMETERS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard)

set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Startup/startup_stm32f411retx.s)
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Startup/stm32_ls.ld)
# ##############################################################################
set(EXECUTABLE ${CMAKE_PROJECT_NAME})
enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

set(INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Inc/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Src/Utilities/RegistersManipulation/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/NVIC/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/USART/
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/GPIO/)

# Sources
file(GLOB_RECURSE SOURCES FOLLOW_SYMLINKS
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Src/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/GPIO/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/GPIO/*.tpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/USART/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Drivers/NVIC/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../Core/Classes/*.cpp)

# Executable files
add_executable(${EXECUTABLE}
    ${SOURCES}
    ${STARTUP_SCRIPT})

# Embedded macros(defines)
#target_compile_definitions(${EXECUTABLE} PRIVATE
#    ${MCU_MODEL}
#    USE_HAL_DRIVER)

# Add header directories (AFTER add_executable !!)
target_include_directories(${EXECUTABLE} PRIVATE
    ${INCLUDE_DIRECTORIES})

# Compiler and linker options
target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -Wextra
    -Wpedantic
    -Wno-unused-parameter
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wno-volatile
        #-Wold-style-cast
        #-Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-Og -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--gc-sections
    -Wl,--start-group
    -lc
    -lm
    -lstdc++
    -Wl,--end-group
    -Wl,--print-memory-usage)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>)

add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}>
    ${EXECUTABLE}.bin)