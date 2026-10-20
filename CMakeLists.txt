cmake_minimum_required(VERSION 4.2.1)
project(STM LANGUAGES C CXX ASM)


set(CPU_FLAGS
    -mcpu=cortex-m7
    -mthumb
    -mfpu=fpv5-d16
    -mfloat-abi=hard
)

set(COMMON_FLAGS
    -Wall
    -Wextra
    -ffunction-sections
    -fdata-sections
)

# set(CMAKE_C_FLAGS "${CPU_FLAGS} ${COMMON_FLAGS}")
# set(CMAKE_CXX_FLAGS "${CPU_FLAGS} ${COMMON_FLAGS}")
# set(CMAKE_ASM_FLAGS "${CPU_FLAGS}")

set(LINKER_SCRIPT
    ${CMAKE_SOURCE_DIR}/linker/STM32H753ZI.ld
)

set_source_files_properties(
    startup/stm32h753xx.s
    PROPERTIES LANGUAGE ASM
)

# set(CMAKE_EXE_LINKER_FLAGS
#     ${CPU_FLAGS}
#     -T ${LINKER_SCRIPT}
#     -Wl,--gc-sections
#     -Wl,-Map=firmware.map
# )

add_executable(firmware.elf
    startup/stm32h753xx.s
    src/main.cpp
)

target_link_options(firmware.elf PRIVATE
    ${CPU_FLAGS}
    -T ${LINKER_SCRIPT}
    -Wl,--gc-sections
    -Wl,-Map=firmware.map
)
target_include_directories(firmware.elf PRIVATE
    cmsis
    include
)

target_compile_options(firmware.elf PRIVATE
    ${CPU_FLAGS}
    ${COMMON_FLAGS}
)


add_custom_command(TARGET firmware.elf POST_BUILD
    COMMAND arm-none-eabi-objcopy
    -O binary
    firmware.elf
    firmware.bin
)
