# 支持的cmake最低版本
cmake_minimum_required(VERSION 3.12)

# 设置构建系统的类型为通用（Generic）。这意味着 CMake 不会假设任何特定的操作系统或编译器环境，而是尽可能地以最通用的方式进行配置。
set(CMAKE_SYSTEM_NAME Generic)

# 这条指令在 CMake 中用于指定目标处理器架构为 ARM。
set(CMAKE_SYSTEM_PROCESSOR arm)

# 指定在尝试编译检查代码片段时，生成的目标类型应为静态库（STATIC_LIBRARY）。
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# 设置交叉编译工具链统一路径，类似环境变量
set(TOOLCHAIN_PATH C:/Users/wyx12/Documents/Environment/gcc-arm-none-eabi-9-2020-q2-update-win32/bin)

# 设置交叉编译工具链前缀
set(TOOLCHAIN_PREFIX arm-none-eabi-)

# 显式指定C语言交叉编译器路径
set(CMAKE_C_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")

# 指定 C++ 编译器的完整路径
set(CMAKE_CXX_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe")

# 用于指定汇编语言的编译器路径
set(CMAKE_ASM_COMPILER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}gcc.exe")

# 指定链接器的路径
set(CMAKE_LINKER "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}g++.exe")

# 设置了objcopy工具的路径。objcopy是一个非常有用的工具，主要用于修改和处理对象文件（如 ELF 文件），常用于嵌入式开发、创建固件映像或对二进制文件进行操作，比如去除符号表、重定位节、格式转换等
set(CMAKE_OBJCOPY "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}objcopy.exe")

# 指定 size 工具的路径。Size 工具通常用于显示编译后二进制文件（如可执行文件或库）中各个节的大小，这对于分析程序的大小和优化非常重要。
set(CMAKE_SIZE "${TOOLCHAIN_PATH}/${TOOLCHAIN_PREFIX}size.exe")

# 定义项目名称
project(app)

# 指定 C 语言的标准版本为 C99。C99 是 C 语言的一个标准，引入了许多新特性，包括复合字面量、变长数组、内联函数等，这些特性在之前的 C89/90 标准中是没有的
set(CMAKE_C_STANDARD 99)

# 用于指定 C++ 语言的标准版本为 C++11。C++11 是 C++ 语言的一个重要更新，引入了许多新特性，包括自动类型推导 (auto)、范围基础的 for 循环、右值引用、移动语义、lambda 函数、线程支持库等。
set(CMAKE_CXX_STANDARD 11)

# 用于声明项目将使用 C、C++ 和汇编 (ASM) 这三种编程语言。调用 enable_language 函数是为了通知 CMake 构建系统项目中包含的源代码类型，从而让 CMake 能够正确地识别和处理不同类型的源文件。
enable_language(C CXX ASM)

# 添加宏定义
add_compile_definitions(
    CONFIG_DEBUG_UART=UART0;
    USE_MODEM_LORA
)

# MCU specific flags
set(TARGET_FLAGS "-mcpu=cortex-m4")

# 设置编译选项
add_compile_options(

    # 指定目标处理器架构为 ARM Cortex-M4。这个选项通常在编译和链接针对基于 Cortex-M4 的微控制器的代码时使用
    -mcpu=cortex-m4

    # 编译器会将源代码转换为对象文件，但不会尝试将这些对象文件链接成一个可执行文件或库。
    -c

    # 在 ARM 架构中，处理器可以在两种模式之间切换：ARM 模式和 Thumb 模式。ARM 模式使用 32 位指令集，而 Thumb 模式使用压缩的 16 位指令集
    # 使用 -mthumb 选项编译代码通常用于针对嵌入式系统和微控制器，这些系统往往对内存和代码大小有严格的要求。通过选择 -mthumb，你可以确保生成的代码占用更少的空间，这对于资源受限的设备尤其重要
    -mthumb

    # 编译器会在生成的二进制文件中嵌入 DWARF v2 格式的调试元数据。这使得调试器能够理解源代码结构、变量类型、函数调用栈等信息，从而帮助开发者在开发和维护阶段更有效地进行调试和故障排除。
    -gdwarf-2

    # CMake 会利用编译器的 -MD 选项来自动生成依赖关系，并将其整合到构建系统中，确保构建过程的高效性和准确性。
    -MD

    # 编译器会报告出它能够检测到的大部分潜在问题和不良编程实践，但这些警告并不会导致编译失败
    -Wall

    # 当使用 -O0 编译时，编译器不会对代码进行任何优化，这通常用于调试目的，因为未优化的代码更接近源代码的原始语义，有助于在调试器中准确地跟踪代码执行流程
    -O0

    # 编译器会生成遵循 APCS 标准的函数调用帧，这对于确保与使用相同标准的其他代码或库的兼容性非常重要。在 ARM 架构中，尤其是对于嵌入式系统和实时操作系统，遵循一致的调用约定对于正确处理函数调用和异常处理至关重要。
    -mapcs-frame

    # 用于 ARM 编译器的选项，主要用于支持 Thumb 和 ARM 指令集之间的互操作
    -mthumb-interwork

    # 用于强制编译器按照 ANSI C 标准进行编译，这通常指的是 C89 或 C90 标准
    -ansi

    # 编译器优化选项，用于在代码大小和执行速度之间寻找一个平衡点，倾向于生成更小的代码。这里的 "s" 代表 "size"，意味着优化目标是减少二进制代码的大小，同时尽量保持合理的执行效率。
    -Os

    # 编译器选项，用于指示编译器将每个函数的代码放置在独立的段（section）中。在链接阶段，这允许链接器或最终的固件生成工具选择性地保留或丢弃不需要的函数段，从而有助于减小程序的最终大小。这对于嵌入式系统和资源受限的环境尤为重要，因为它们通常需要精简的固件大小以节省宝贵的存储空间。
    -ffunction-sections

    # ARM 编译器的命令行选项，用于指定目标处理器的浮点单元（FPU）类型。具体来说，fpv4-sp-d16 指的是 ARMv7E-M 架构中的一个 FPU 实现，它支持单精度（SP）和双精度（DP）浮点运算，并且具有 16 个浮点寄存器
    -mfpu=fpv4-sp-d16

    # 用于指定浮点抽象接口（Floating Point ABI）为软浮点（Soft Floating Point）。在 ARM 架构中，软浮点 ABI 意味着浮点运算将通过软件库（通常是 libm）来实现，而不是直接使用硬件浮点单元（FPU）。
    -mfloat-abi=softfp

    # 用于指示编译器将所有的浮点常量视为单精度（32位）浮点数，即使源代码中使用了双精度（64位）浮点数的语法。这个选项在编译时可以减少代码大小和提高执行效率，尤其是在目标平台只支持单精度浮点运算或者单精度浮点运算比双精度更快的情况下。
    -fsingle-precision-constant

    # 编译器选项，用于指定使用 GNU 扩展的 C99 标准进行编译。C99 是 C 语言的一个标准版本，引入了若干新特性，如复合字面量、变长数组、内联函数等。GNU 扩展则是在 C99 标准的基础上增加了 GNU 编译器集合（GCC）特有的功能和行为
    -std=gnu99

    # 用于禁止编译器使用内置的 printf 函数。通常，编译器为了优化性能和代码大小，会将一些常用的标准库函数如 printf 内置化，即在编译时直接使用编译器提供的高效版本，而不是链接到标准库中的版本。
    -fno-builtin-printf

    # 用于禁止编译器使用内置的 sprintf 函数。sprintf 函数用于将格式化的字符串写入一个字符数组中，而不是像 printf 函数那样输出到标准输出流。
    -fno-builtin-sprintf

    # 用于禁止编译器使用内置的 snprintf 函数。snprintf 函数类似于 sprintf，但它允许指定目标缓冲区的最大长度，从而避免缓冲区溢出的风险，提高了安全性。
    -fno-builtin-snprintf
)

# 用于设置汇编语言源文件的编译标志
set(CMAKE_ASM_FLAGS "${TARGET_FLAGS} -mthumb -gdwarf-2 -mthumb-interwork")

# 用于设置链接脚本文件
set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/cfg/gcc.ld)

# 不是 CMake 的一个标准命令，但你可能想要在链接阶段添加额外的选项。在 CMake 中，你可以使用 target_link_options 命令来向目标可执行文件或库添加链接器选项。这个命令允许你指定在链接阶段应该应用的额外链接器标志
add_link_options(
    -T ${LINKER_SCRIPT}
    ${TARGET_FLAGS}
    -mthumb
    -mthumb-interwork
    -Wl,--gc-sections,--wrap=printf -Wl,--wrap=sprintf -Wl,--wrap=snprintf
    -Wl,--print-memory-usage
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections
)

# 设置头文件路径
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

# 包含源文件
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

# 用于创建生成一个elf文件
add_executable(${PROJECT_NAME}.elf ${SOURCE_FILES} ${LINKER_SCRIPT})

set(HEX_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.hex)
set(ASM_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.asm)
set(BIN_FILE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}.bin)

# 设置自定义命令将elf文件生成hex和bin文件
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${HEX_FILE}
    COMMAND ${CMAKE_OBJCOPY} -O binary -S $<TARGET_FILE:${PROJECT_NAME}.elf> ${BIN_FILE}
    COMMENT "Building ${HEX_FILE} Building ${BIN_FILE}"
)

# 显示elf文件大小
add_custom_command(
    TARGET ${PROJECT_NAME}.elf
    POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
)
