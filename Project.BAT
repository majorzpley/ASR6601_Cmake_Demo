SET CPU_TYPE=ARMCM4_FP
SET CPU_VENDOR=ARM
SET UV2_TARGET=Project
SET CPU_CLOCK=0x016E3600
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\system_cm4.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-as" @".\objects\startup_cm4._ia"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_adc.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_bstimer.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_crc.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_dac.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_delay.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_dma.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_flash.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_gpio.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_i2c.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_i2s.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_iwdg.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_lcd.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_lptimer.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_lpuart.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_pwr.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_rcc.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_rtc.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_spi.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_system.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_timer.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_uart.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_wdg.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\app.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\main.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\sx126x_init.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\system_init.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\tremo_it.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\radio.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\sx126x.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\rtc-board.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\sx1262-board.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\utilities.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\delay.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\objects\timer.__i"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-gcc" @".\Objects\app.lnp"
"E:\APPS\gcc-arm-none-eabi-9-2020-q2-update-win32\bin\arm-none-eabi-objcopy.exe" -O ihex ./Objects/app.elf ./Objects/app.hex
