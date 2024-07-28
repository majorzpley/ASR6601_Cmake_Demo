# # 支持的cmake最低版本
cmake_minimum_required(VERSION 3.12)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 设置交叉编译工具链统一路径，类似环境变量
set(TOOLCHAIN_PATH C:/Users/wyx12/Documents/Environment/gcc-arm-none-eabi-9-2020-q2-update-win32/bin)
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# 设置C语言交叉编译器
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")
set(CMAKE_LINKER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe")
set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}objcopy.exe")
set(CMAKE_SIZE "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}size.exe")

# 定义项目名称
project(app)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

enable_language(C CXX ASM)

# 添加宏定义
add_compile_definitions(
    CONFIG_DEBUG_UART=UART0;
    USE_MODEM_LORA
)

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m4")

# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${TARGET_FLAGS}")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -c -mthumb -gdwarf-2 -MD -Wall -O0 -mapcs-frame -mthumb-interwork -ansi -Wall -Os -ffunction-sections -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -fsingle-precision-constant -std=gnu99 -fno-builtin-printf -fno-builtin-sprintf -fno-builtin-snprintf")

# 设置编译选项
add_compile_options(
    -mcpu=cortex-m4
    -c
    -mthumb
    -gdwarf-2
    -MD
    -Wall
    -O0
    -mapcs-frame
    -mthumb-interwork
    -ansi
    -Wall
    -Os
    -ffunction-sections
    -mfpu=fpv4-sp-d16
    -mfloat-abi=softfp
    -fsingle-precision-constant
    -std=gnu99
    -fno-builtin-printf
    -fno-builtin-sprintf
    -fno-builtin-snprintf
)

# set(CMAKE_ASM_FLAGS
# -mcpu=cortex-m4
# -mthumb
# --gdwarf-2
# -mthumb-interwork
# )
set(CMAKE_ASM_FLAGS "${TARGET_FLAGS} -mthumb -gdwarf-2 -mthumb-interwork")

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/cfg/gcc.ld)

add_link_options(
    -T ${LINKER_SCRIPT}
    ${TARGET_FLAGS}
    -mthumb
    -mthumb-interwork
    -Wl,--gc-sections,--wrap=printf -Wl,--wrap=sprintf -Wl,--wrap=snprintf
    -Wl,--print-memory-usage
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections
)

# set(CMAKE_C_LINK_FLAGS "${TARGET_FLAGS}")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -T \"${LINKER_SCRIPT}\"")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -mthumb -mthumb-interwork")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--wrap=printf -Wl,--wrap=sprintf -Wl,--wrap=snprintf")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections")
# set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -Wl,--print-memory-usage")

# # 设置头文件路径
include_directories(
    drivers/peripheral/inc
    lora/driver
    lora/system
    lora/radio/sx126x
    lora/radio
    platform/system
    platform/CMSIS
    usr/inc
)

# #包含源文件
file(GLOB SRC_DRIVER
    drivers/peripheral/src/*.c
    platform/system/system_cm4.c
    platform/system/startup_cm4.S
)
file(GLOB SRC_TASK
    usr/src/*.c
)
file(GLOB SRC_LORA
    ${CMAKE_SOURCE_DIR}/lora/radio/sx126x/*.c
    ${CMAKE_SOURCE_DIR}/lora/driver/*.c
    ${CMAKE_SOURCE_DIR}/lora/system/delay.c
    ${CMAKE_SOURCE_DIR}/lora/system/timer.c
)

set(SOURCE_FILES
    ${SRC_TASK}
    ${SRC_DRIVER}
    ${SRC_LORA}
    ${STARTUP_SCRIPT}
)

add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(ASM_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.asm)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}"
)

add_custom_command(
    TARGET ${PROJECT_NAME}.elf
    POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
)
