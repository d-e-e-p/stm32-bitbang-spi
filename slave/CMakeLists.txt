#############################################################################################################################
# file:  CMakeLists.txt
# brief: Template "CMakeLists.txt" for building of executables and static libraries.
#
# usage: Edit "VARIABLES"-section to suit project requirements.
#        For debug build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Debug -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#          make -C Debug VERBOSE=1
#        For release build:
#          cmake -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake  -S ./ -B Release -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
#          make -C Release VERBOSE=1
#############################################################################################################################
cmake_minimum_required(VERSION 3.20)

###################### CONSTANTS ######################################
set (PROJECT_TYPE_EXECUTABLE          "exe")
set (PROJECT_TYPE_STATIC_LIBRARY      "static-lib")
set (MCPU_CORTEX_M0				      "-mcpu=cortex-m0")
set (MCPU_CORTEX_M0PLUS				  "-mcpu=cortex-m0plus")
set (MCPU_CORTEX_M3				      "-mcpu=cortex-m3")
set (MCPU_CORTEX_M4				      "-mcpu=cortex-m4")
set (MCPU_CORTEX_M7				      "-mcpu=cortex-m7")
set (MCPU_CORTEX_M33				  "-mcpu=cortex-m33")
set (MFPU_FPV4_SP_D16                 "-mfpu=fpv4-sp-d16")
set (MFPU_FPV5_D16                    "-mfpu=fpv5-d16")
set (RUNTIME_LIBRARY_REDUCED_C        "--specs=nano.specs")
set (RUNTIME_LIBRARY_STD_C            "")
set (RUNTIME_LIBRARY_SYSCALLS_MINIMAL "--specs=nosys.specs")
set (RUNTIME_LIBRARY_SYSCALLS_NONE    "")
set (MFLOAT_ABI_SOFTWARE              "-mfloat-abi=soft")
set (MFLOAT_ABI_HARDWARE              "-mfloat-abi=hard")
set (MFLOAT_ABI_MIX                   "-mfloat-abi=softfp")
#######################################################################

###################### VARIABLES ######################################
set (PROJECT_NAME             "slave")
set (PROJECT_TYPE             "exe")
set (LINKER_SCRIPT            "../STM32F407VGTX_FLASH.ld")
set (MCPU                     "-mcpu=Cortex-M4")
set (MFPU                 "-mfpu=fpv4-sp-d16")
set (MFLOAT_ABI               "")
set (RUNTIME_LIBRARY          "--specs=nano.specs")
set (RUNTIME_LIBRARY_SYSCALLS "--specs=nosys.specs")

# requires 'cmake .. --fresh' to pick up file add/drop
set (STM32CubeF4 /Users/deep/build/tf/STM32CubeF4)
file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS 
    Core/Startup/startup_stm32f407vgtx.s
    Core/Src/*.c
    Core/Src/*.cpp
    USB_DEVICE/App/*.c
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/*.c
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Src/*.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_exti.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.c
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.c
)

#
#set (PROJECT_SOURCES
#	# LIST SOURCE FILES HERE
#	Startup/startup_stm32f407vgtx.s
#	Src/main.cpp
#	Src/syscalls.c
#	Src/sysmem.c
#    ../USB_DEVICE/App/usb_device.c  
#    ../USB_DEVICE/App/usbd_cdc_if.c  
#    ../USB_DEVICE/App/usbd_desc.c
#	)

set (PROJECT_DEFINES
	# LIST COMPILER DEFINITIONS HERE
    -DUSE_HAL_DRIVER 
    -DSTM32F407xx
    -DUSE_FULL_ASSERT
    )

set (PROJECT_INCLUDES
	# LIST INCLUDE DIRECTORIES HERE
    Core/Inc
    USB_DEVICE/App
    USB_DEVICE/Target
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${STM32CubeF4}/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy
    ${STM32CubeF4}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM32CubeF4}/Drivers/CMSIS/Include
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Core/Inc
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc
    ${STM32CubeF4}/Middlewares/ST/STM32_USB_Device_Library/Class/HID/Inc
    )

############ MODIFY ACCORDING TO REQUIREMENTS) ########################

#######################################################################

################## PROJECT SETUP ######################################
project(${PROJECT_NAME})
enable_language(ASM)

if (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_EXECUTABLE})
  add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
  add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>)
elseif (${PROJECT_TYPE} MATCHES ${PROJECT_TYPE_STATIC_LIBRARY})
  add_library(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

add_compile_definitions (${PROJECT_DEFINES})
include_directories (${PROJECT_INCLUDES})

set (CMAKE_EXECUTABLE_SUFFIX ".elf")
set (CMAKE_STATIC_LIBRARY_SUFFIX ".a")
set (CMAKE_C_FLAGS "${MCPU} -std=gnu11 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
set (CMAKE_CXX_FLAGS "${MCPU} -std=c++17 ${MFPU} ${MFLOAT_ABI} ${RUNTIME_LIBRARY} -mthumb -Wall -Werror")
set (CMAKE_EXE_LINKER_FLAGS "-T${LINKER_SCRIPT} ${RUNTIME_LIBRARY_SYSCALLS} -Wl,-Map=test.map -Wl,--gc-sections -static -Wl,--start-group -lc -lm -Wl,--end-group")
set (CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS} -x assembler-with-cpp")
