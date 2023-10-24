# stm32-bitbang-spi
SPI using bitbang GPIO for stm32f4


USB code is from:

    https://github.com/jrahlf/stm32_usb_cdc_improved_if



Uses cmake configuration files to drive either cli or gui build.

To build using gui, download:

    https://www.st.com/en/development-tools/stm32cubeide.html

Open project at stm32-bitbang-spi level and import project "slave" into your environment.
You should then be able to select "Run" to build code and flash to target board.

To use cli, also download:

    https://www.st.com/en/development-tools/stm32cubeclt.html

Then update the PATH variable in Makefile to point to these 3 directories:

    com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.macos64_1.1.1.202309131626/tools/bin/
    com.st.stm32cube.ide.mcu.externaltools.make.macos64_2.1.0.202305091550/tools/bin/
    com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.macos64_2.1.0.202305091550/tools/bin/


PATH to cmake and ninja should be updated in Makefile.  To flash using cli:

    make release


    

