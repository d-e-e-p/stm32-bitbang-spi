
#include <algorithm>

#include "main.h"
#include "local.hpp"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_gpio.h"


// Usage: DEBUGPRINT("x = " << x);
#define DEBUGPRINT(x) \
    std::cout << "Function: " << __FUNCTION__ << ", Line: " << __LINE__ << " - " << (x) << std::endl

void dump_gpio_info(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) {
// Get the GPIO mode
  uint32_t moder = GPIOx->MODER & (0x3 << (GPIO_Pin * 2));

  // Get the GPIO output type
  uint32_t otyper = GPIOx->OTYPER & (0x1 << GPIO_Pin);

  // Get the GPIO pull-up/pull-down resistor
  uint32_t pupdr = GPIOx->PUPDR & (0x3 << (GPIO_Pin * 2));

  // Get the GPIO input data register
  uint32_t idr = GPIOx->IDR & (0x1 << GPIO_Pin);

  // Get the GPIO output data register
  uint32_t odr = GPIOx->ODR & (0x1 << GPIO_Pin);

  // Get the GPIO bit set/reset register
  uint32_t bsrr = GPIOx->BSRR & (0x1 << GPIO_Pin);

  // Get the GPIO lock register
  //uint32_t lckr = GPIOx->LCKR & (0x1 << GPIO_Pin);

  // Get the GPIO alternate function register
  uint32_t afr = GPIOx->AFR[GPIO_Pin / 8] & (0xF << ((GPIO_Pin % 8) * 4));

  // Print the GPIO settings to the console
  uprintf("GPIO settings for port %d, pin %d:\r\n", GPIOx, GPIO_Pin);
  uprintf("  Mode: %s\r\n", (moder == GPIO_MODE_INPUT) ? "Input" : "Output");
  uprintf("  Output type: %s\r\n", (otyper == OUTPUT_PP) ? "Push-pull" : "Open-drain");
  uprintf("  Pull-up/pull-down resistor: %s\r\n", pupdr ? "No pull-up/pull-down resistor" : "Pull-down resistor");
  //uprintf("  Pull-up/pull-down resistor: %s\r\n", (pupdr == GPIO_PUPDR_NOPULL) ? "No pull-up/pull-down resistor" : (pupdr == GPIO_PUPDR_PULLUP) ? "Pull-up resistor" : "Pull-down resistor");
  uprintf("  Input data register: %s\r\n", (idr == GPIO_PIN_SET) ? "High" : "Low");
  uprintf("  Output data register: %s\r\n", (odr == GPIO_PIN_SET) ? "High" : "Low");
  uprintf("  Bit set/reset register: %s\r\n", (bsrr == GPIO_PIN_SET) ? "Set" : "Reset");
  //uprintf("  Lock register: %s\r\n", (lckr == GPIO_LCKR_LOCKED) ? "Locked" : "Unlocked");
  uprintf("  Alternate function register: %d\r\n", afr);
}


void print_all_gpio_settings(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin) {
  // Get the GPIO mode
  uint32_t moder = GPIOx->MODER & (0x3 << (GPIO_Pin * 2));

  // Get the GPIO output type
  uint32_t otyper = GPIOx->OTYPER & (0x1 << GPIO_Pin);

  // Get the GPIO pull-up/pull-down resistor
  uint32_t pupdr = GPIOx->PUPDR & (0x3 << (GPIO_Pin * 2));

  // Get the GPIO input data register
  uint32_t idr = GPIOx->IDR & (0x1 << GPIO_Pin);

  // Get the GPIO output data register
  uint32_t odr = GPIOx->ODR & (0x1 << GPIO_Pin);

  // Get the GPIO bit set/reset register
  uint32_t bsrr = GPIOx->BSRR & (0x1 << GPIO_Pin);

  // Get the GPIO lock register
  uint32_t lckr = GPIOx->LCKR & (0x1 << GPIO_Pin);

  // Get the GPIO alternate function register
  uint32_t afr = GPIOx->AFR[GPIO_Pin / 8] & (0xF << ((GPIO_Pin % 8) * 4));

   // Extract the mode, speed, and pull-up/pull-down resistor settings
  char mode_str[80];
  char speed_str[80];
  char pull_str[80];

  switch (moder) {
    case GPIO_MODE_INPUT:
      strcpy(mode_str, "Input");
      break;
    case GPIO_MODE_OUTPUT_PP:
      strcpy(mode_str, "Output (push-pull)");
      break;
    case GPIO_MODE_OUTPUT_OD:
      strcpy(mode_str, "Output (open-drain)");
      break;
    case GPIO_MODE_AF_PP:
      strcpy(mode_str, "Alternate function (push-pull)");
      break;
    case GPIO_MODE_AF_OD:
      strcpy(mode_str, "Alternate function (open-drain)");
      break;
    case GPIO_MODE_IT_RISING:
      strcpy(mode_str, "Input interrupt (rising edge)");
      break;
    case GPIO_MODE_IT_FALLING:
      strcpy(mode_str, "Input interrupt (falling edge)");
      break;
    case GPIO_MODE_IT_RISING_FALLING:
      strcpy(mode_str, "Input interrupt (rising or falling edge)");
      break;
    case GPIO_MODE_EVT_RISING:
      strcpy(mode_str, "Event interrupt (rising edge)");
      break;
    case GPIO_MODE_EVT_FALLING:
      strcpy(mode_str, "Event interrupt (falling edge)");
      break;
    case GPIO_MODE_EVT_RISING_FALLING:
      strcpy(mode_str, "Event interrupt (rising or falling edge)");
      break;
    case GPIO_MODE_ANALOG:
      strcpy(mode_str, "Analog");
      break;
  }

  switch (otyper) {
    case OUTPUT_PP:
      strcpy(speed_str, "Push-pull");
      break;
    case OUTPUT_OD:
      strcpy(speed_str, "Open-drain");
      break;
  }

  switch (pupdr) {
    case GPIO_NOPULL:
      strcpy(pull_str, "No pull-up/pull-down resistor");
      break;
    case GPIO_PULLUP:
      strcpy(pull_str, "Pull-up resistor");
      break;
    case GPIO_PULLDOWN:
      strcpy(pull_str, "Pull-down resistor");
      break;
  }
  uprintf("  Mode: %s\r\n", mode_str);
  uprintf("  Output type: %s\r\n", speed_str);
  uprintf("  Pull-up/pull-down resistor: %s\r\n", pull_str);
  uprintf("  Input data register: %s\r\n", idr ? "High" : "Low");
  uprintf("  Output data register: %s\r\n", odr ? "High" : "Low");
  uprintf("  Bit set/reset register: %s\r\n", bsrr ? "Set" : "Reset");
  uprintf("  Lock register: %s\r\n", lckr ? "Locked" : "Unlocked");
  uprintf("  Alternate function register: %d\r\n", afr);
}


void start_timers() {
  HAL_TIM_Base_Init(&htim2);
  HAL_TIM_Base_Start(&htim2);
  HAL_TIM_Base_Init(&htim4);
  HAL_TIM_Base_Start_IT(&htim4);
  uprintf("timers tim2 and tim4 started: tim2 = %d \r\n", __HAL_TIM_GET_COUNTER(&htim2));
}


void dump_spi1_gpio_info() {
  uprintf(" SPI1_SCK: ");   dump_gpio_info(SPI_Port, SPI_SCK_Pin);
  uprintf(" SPI1_MISO: ");  dump_gpio_info(SPI_Port, SPI_MISO_Pin);
  uprintf(" SPI1_MOSI: ");  dump_gpio_info(SPI_Port, SPI_MOSI_Pin);
  uprintf(" SPI1_CS: ");    dump_gpio_info(SPI_Port, SPI_NSS_Pin);

}


// Function to initialize GPIO pins
void gpio_init(void) {
    // Enable the GPIOA clock
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // Configure the GPIO pins as inputs or outputs
    GPIO_InitTypeDef GPIO_InitStruct {};
    GPIO_InitStruct.Pin = SPI_MOSI_Pin | SPI_SCK_Pin | SPI_NSS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;  // MISO has to become output
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    //GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    HAL_GPIO_DeInit(GPIOA, SPI_MISO_Pin);

    // Configure the MOSI pin as an output
    GPIO_InitStruct.Pin = SPI_MISO_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP; // MOSI as output
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

// utilities 
bool sck_is_low() {
  return (HAL_GPIO_ReadPin(GPIOA, SPI_SCK_Pin) == GPIO_PIN_RESET);
}

bool sck_is_high() {
  return (HAL_GPIO_ReadPin(GPIOA, SPI_SCK_Pin) == GPIO_PIN_SET);
}

bool nss_is_low() {
  return (HAL_GPIO_ReadPin(GPIOA, SPI_NSS_Pin) == GPIO_PIN_RESET);
}

bool nss_is_high() {
  return (HAL_GPIO_ReadPin(GPIOA, SPI_NSS_Pin) == GPIO_PIN_SET);
}

void set_miso(bool txd_bit) {
  GPIO_PinState txd_val = txd_bit ? GPIO_PIN_SET : GPIO_PIN_RESET;
  HAL_GPIO_WritePin(GPIOA, SPI_MISO_Pin, txd_val);
}

bool get_mosi() {
  return (HAL_GPIO_ReadPin(GPIOA, SPI_MOSI_Pin) == GPIO_PIN_SET);
}


// Function to exchange data using bit-banging SPI
uint8_t spi_transmit_receive(uint8_t txd_byt) {
    uint8_t rxd_byt = 0;
    int bit;
    bool txd_bit;

    // set the first bit of transmit
    bit = 7;
    txd_bit = txd_byt & (1 << bit);
    set_miso(txd_bit);

    // Wait for the NSS (Slave Select) pin to go low
    while (nss_is_high()) {
    }

    for (bit = 7; bit >= 0; --bit) {
        // Wait for the rising edge of clock
        while (sck_is_low()) {
          // handle nss going high here
          //if (nss_is_high()) {
           // return 0xEE;
          //}
        }

        // sample MOSI (PA7) when the clock goes high
        rxd_byt |= (HAL_GPIO_ReadPin(GPIOA, SPI_MOSI_Pin) << bit);

        // Now wait for the falling edge of clock
        while (sck_is_high()) {
          // handle nss going high here
          //if ((bit > 0) & nss_is_high()) {
           // return 0xEE;
          //}
        }

        if (bit > 0) {
          // Set MISO (PA6) based on the data bit
          txd_bit = txd_byt & (1 << (bit - 1));
          set_miso(txd_bit);
          //uprintf("bit %d txd %02x \r\n", bit, txd_byt);
        }
        // handle nss going high here
    }

    return rxd_byt;
}




//
// bitbang version of spi slave
//

void bitbang_spi_slave() {
  gpio_init();
  dump_spi1_gpio_info();
  uint8_t rxd, txd {};
  uprintf("starting bitbang_spi_slave: \r\n");
  /*
  while(true) {
    set_miso(true); HAL_Delay(100);
    set_miso(false); HAL_Delay(100);
  }
  */
  HAL_Delay(1000);
  while (true) {
    rxd = spi_transmit_receive(txd);
    uprintf("bb: tx=%02x rx=%02x\r\n", txd, rxd);
    txd = rxd;
  }
  
}
