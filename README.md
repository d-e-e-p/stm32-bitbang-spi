
# stm32-bitbang-spi
SPI using bitbang GPIO for stm32f4

## Credits

- Cmake setup from [an5952-how-to-use-cmake-in-stm32cubeide-stmicroelectronics.pdf](https://www.st.com/resource/en/application_note/an5952-how-to-use-cmake-in-stm32cubeide-stmicroelectronics.pdf)
- USB interface from  [Improved usb cdc interface for stm32](https://github.com/jrahlf/stm32_usb_cdc_improved_if)


## Motivation

This implementation can be used to:
- Compare with hardware SPI to isolate problems
- Used by processors that don't have hardware SPI
- Support parameters outside hardware implementation, eg 32-bit data size
- Used when bitbang version achieves faster speeds than hardware version

## Getting Started

cmake configuration files drive either cli or gui build.

### GUI 

To build using gui, first download:

    [https://www.st.com/en/development-tools/stm32cubeide.html](https://www.st.com/en/development-tools/stm32cubeide.html)

Then checkout STM32CubeF4:

```bash
    cd /somewhere/to/store/repository/
    git clone https://github.com/STMicroelectronics/STM32CubeF4.git
```

Update the STM32CubeF4 line in CMakeLists.txt to point to this location.

Open project at stm32-bitbang-spi level and import project "slave" into your environment.
You should then be able to select "Run" to build code and flash to target board.

### CLI 
To use cli, in addition to steps above also download:

    [https://www.st.com/en/development-tools/stm32cubeclt.html](https://www.st.com/en/development-tools/stm32cubeclt.html)

Then update the PATH variable in Makefile to point to the equivalent of these 3 directories under stm32cubeide and stm32cubeclt install dirs:

    com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.macos64_1.1.1.202309131626/tools/bin/
    com.st.stm32cube.ide.mcu.externaltools.make.macos64_2.1.0.202305091550/tools/bin/
    com.st.stm32cube.ide.mcu.externaltools.cubeprogrammer.macos64_2.1.0.202305091550/tools/bin/

cmake and ninja should also be installed and path to these updated in Makefile.
To flash using cli:

```bash

> make

make targets are: clean debug release, eg:
	make release


> make clean

rm -rf Debug/ Release/

> make release

cmake -S . -B Release -DCMAKE_TOOLCHAIN_FILE=cubeide-gcc.cmake -DCMAKE_BUILD_TYPE=Release
-- The C compiler identification is GNU 11.3.1
-- The CXX compiler identification is GNU 11.3.1
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.macos64_1.1.1.202309131626/tools/bin/arm-none-eabi-gcc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.macos64_1.1.1.202309131626/tools/bin/arm-none-eabi-g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- The ASM compiler identification is GNU
-- Found assembler: /Applications/STM32CubeIDE.app/Contents/Eclipse/plugins/com.st.stm32cube.ide.mcu.externaltools.gnu-tools-for-stm32.11.3.rel1.macos64_1.1.1.202309131626/tools/bin/arm-none-eabi-gcc
-- Configuring done (1.2s)
-- Generating done (0.0s)
-- Build files have been written to: /Users/deep/stm32-bitbang-spi/slave/Release
cmake --build Release --config Release
[0/2] Re-checking globbed directories...
[109/109] Linking CXX executable slave.elf
   text	   data	    bss	    dec	    hex	filename
 316272	   1528	  27760	 345560	  545d8	/Users/deep/stm32-bitbang-spi/slave/Release/slave.elf
STM32_Programmer_CLI --connect port=SWD freq=4000 mode=UR reset=HWrst --write Release/slave.elf
      -------------------------------------------------------------------
                        STM32CubeProgrammer v2.14.0
      -------------------------------------------------------------------

```

    


### Dir Structure

Makefile has the cmake commands to build and flash the target board.

```bash
.
├── slave
│   ├── Makefile
│   ├── CMakeLists.txt
│   ├── Core
│   │   ├── Inc
│   │   │   ├── local.hpp
│   │   │   ├── main.h
│   │   │   ├── output.hpp
│   │   │   ├── queue.hpp
│   │   │   ├── spi.hpp   <-- spi driver lives here
│   │   │   ├── stm32_assert.h
│   │   │   ├── stm32f4xx_hal_conf.h
│   │   │   └── stm32f4xx_it.h
│   │   ├── Src
│   │   │   ├── main.cpp
│   │   │   ├── output.cpp
│   │   │   ├── spi.cpp
│   │   │   ├── stm32f4xx_hal_msp.c
│   │   │   ├── stm32f4xx_it.c
│   │   │   ├── syscalls.c
│   │   │   ├── sysmem.c
│   │   │   └── system_stm32f4xx.c
│   │   └── Startup
│   │       └── startup_stm32f407vgtx.s
│   ├── Release/
│   ├── Debug/

```

### Coding style


Roughly following https://google.github.io/styleguide/cppguide.html except 
in this case all functions and variables are snake_case.


```cpp
# naming conventions
MyExcitingClass, MyExcitingEnum.
a_local_variable, a_struct_data_member, a_class_data_member_.

std::string table_name;  // OK - lowercase with underscore.

class TableInfo {
  ...
 private:
  std::string table_name_;  // OK - underscore at end.
};

// global constexpr or const,
const int kDaysInAWeek = 7;

// functions should generally with a capital letter and have a capital letter for each new word.
// in this case all functions are snake_case:
int count();
void set_count(int count);

// Namespace names are all lower-case, with words separated by underscores.


```

## Authors

* **Sandeep** - [@d-e-e-p](https://github.com/d-e-e-p)

## License

The project is available under the [MIT](https://opensource.org/licenses/MIT) license.
See [LICENSE](LICENSE) file for details
