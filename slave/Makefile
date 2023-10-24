#
# Makefile for spi cmake projects
# https://github.com/d-e-e-p/stm32-bitbang-spi
# Copyright (c) 2023 Sandeep <deep@tensorfield.ag>
# 

.PHONY: all clean debug release
.DEFAULT_GOAL := help
SHELL=/bin/bash 
export CMAKE_BUILD_PARALLEL_LEVEL:= 4
export CMAKE_GENERATOR:=Ninja
export CMAKE_VERBOSE_MAKEFILE:=ON
export CMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake
export PATH:=/Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.macos64_1.1.1.202309131626/tools/bin:/Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.make.macos64_2.1.0.202305091550/tools/bin:/Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.macos64_2.1.0.202305091550/tools/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/opt/homebrew/bin
#SHELL=/bin/bash -vx # for debug


help: ## this message
	@echo "make targets are: clean debug release, eg:"
	@echo "	make release"

all: clean debug release

clean: ## remove build dir
	rm -rf Debug/ Release/

## create debug version .. use --fresh to ignore cache
debug: 
	cmake -S . -B Debug -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Debug
	cmake --build Debug --config Debug 
	STM32_Programmer_CLI --connect port=SWD freq=4000 mode=UR reset=HWrst --write Debug/slave.elf 
	STM32_Programmer_CLI --connect port=SWD reset=HWrst


release: 
	cmake --fresh -S . -B Release -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Release
	cmake --build Release --config Release 
	STM32_Programmer_CLI -c port=SWD freq=4000 -w Release/slave.elf -rst

docs: ## generate Doxygen HTML documentation, including API docs
	rm -rf ./build/docs/CMakeCache.txt
	rm -rf ./build/docs/doxygen
	cmake -S docs -B build/docs
	cmake --build build/docs --target GenerateDocs -v
	-open build/docs/doxygen/html/index.html

windows_unicode_fix: ## needed for unicode output on windows
	chcp.com 65001



