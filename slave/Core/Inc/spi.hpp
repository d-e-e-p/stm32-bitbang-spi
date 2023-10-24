

#include "stm32f4xx_hal.h"

void dump_gpio_info(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void dump_spi1_gpio_info();
void start_timers();
void bitbang_spi_slave();
