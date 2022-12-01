/*
 * MARBLE_API.h
 * API consisting of wrapper functions providing access to low-level features
 * of Marble Mini (v1 and v2) and Marble.
 * The functions defined herein are necessarily uController-agnostic.
 */

#ifndef _MARBLE_API_H_
#define _MARBLE_API_H_
#ifndef SIMULATION

#include <stdbool.h>
#include <stdint.h>
#include "common.h"

#ifdef MARBLEM_V1
# define DEMO_STRING          "Marble Mini v1 UART DEMO\r\n"
#else
# ifdef MARBLE_V2
#  define DEMO_STRING              "Marble v2 UART DEMO\r\n"
# endif /* MARBLE_V2 */
#endif /* MARBLEM_V1 */

#define FLASH_VOLTAGE_MV                              (3300)

#ifdef RTEMS_SUPPORT
#include <rtems.h>
// Optionally be more specific and only include the file where these are defined
//#include <rtems/rtems/intr.h>
#define INTERRUPTS_DISABLE()  do { \
  rtems_interrupt_level level; \
  rtems_interrupt_disable(level); \
} while (0)
#define INTERRUPTS_ENABLE()   do { \
  rtems_interrupt_enable(level); \
} while (0)
#define BSP_GET_SYSTICK()       (0) // TODO
#else
#define INTERRUPTS_DISABLE                     __disable_irq
#define INTERRUPTS_ENABLE                       __enable_irq
#define BSP_GET_SYSTICK()                      marble_get_tick()
#endif

#define UART_MSG_TERMINATOR                           ('\n')
#define UART_MSG_ABORT                                (27)  // esc
#define UART_MSG_BKSP                                 (8)   // backspace
#define UART_MSG_DEL                                  (128) // del

/* Initialize uC and peripherals before main code can run. */
uint32_t marble_init(bool use_xtal);

// TODO - Move these for encapsulation
void print_status_counters(void);

uint32_t marble_get_tick(void);

/****
* UART
****/
void marble_UART_init(void);

int marble_UART_send(const char *str, int size);

int marble_UART_recv(char *str, int size);

void USART1_ISR(void);

/****
* LED
****/
void marble_LED_set(uint8_t led_num, bool on);

bool marble_LED_get(uint8_t led_num);

void marble_LED_toggle(uint8_t led_num);

void marble_Pmod3_5_write(bool on);
/****
* Push-Buttons
****/
bool marble_SW_get(void);

/****
* FPGA int
****/
bool marble_FPGAint_get(void);

/****
* FMC & PSU
****/
void marble_FMC_pwr(bool on);

typedef enum {
   M_FMC_STATUS_FMC1_PWR = 0,
   M_FMC_STATUS_FMC1_FUSE,
   M_FMC_STATUS_FMC2_PWR,
   M_FMC_STATUS_FMC2_FUSE,
} M_FMC_STATUS;

uint8_t marble_FMC_status(void);

void marble_PSU_pwr(bool on);

typedef enum {
   M_PWR_STATUS_PSU_EN = 0,
   M_PWR_STATUS_POE,
   M_PWR_STATUS_OTEMP
} M_PWR_STATUS;

uint8_t marble_PWR_status(void);

/****
* FPGA reset/init control
* Central to this whole job, may need refinement
****/
void reset_fpga(void);

/****
* SPI/SSP
****/
typedef void *SSP_PORT;
//SSP_PORT SSP_FPGA;  // points to hspi1 after init of marble_v2 or LPC_SSP0 after init of marblemini_v1
                    // Used in: marble_board.c, mailbox.c
                    // Solution: Declare in to marble_board.c, extern in mailbox.c

//SSP_PORT SSP_PMOD;  // points to hspi2 after init of marble_v2 or LPC_SSP1 after init of marblemini_v1
                    // Used in: marble_board.c
                    // Solution: Declare in to marble_board.c

int marble_SSP_write16(SSP_PORT ssp, uint16_t *buffer, unsigned size);
int marble_SSP_read16(SSP_PORT ssp, uint16_t *buffer, unsigned size);
int marble_SSP_exch16(SSP_PORT ssp, uint16_t *tx_buf, uint16_t *rx_buf, unsigned size);

/************
* GPIO user-defined handlers
************/
void marble_GPIOint_handlers(void (*FPGA_DONE_handler)(void));

/************
* MGT Multiplexer
************/
#ifdef MARBLE_V2
void marble_MGTMUX_set(uint8_t mgt_num, bool on);

uint8_t marble_MGTMUX_status(void);
#endif

/****
* I2C
****/
#ifdef MARBLE_LPC1776
typedef int I2C_BUS;
#elif MARBLE_STM32F207
typedef void *I2C_BUS;
#else
#error Marble microcontroller API not defined!
#endif

// These also need to move to prevent multiple global variable definitions of same name
//I2C_BUS I2C_PM; // Points to hi2c3 for marble_v2 or I2C1 for marblemini_v1
                // Used in: marble_board.c, i2c_pm.c
                // Solution: Declare in marble_board.c, extern in i2c_pm.c
//I2C_BUS I2C_IPMB; // Used only in marble_board.c -> move there
//I2C_BUS I2C_FPGA; // Points to hi2c1 after init of marble_v2 or I2C2 after init of marblemini_v1
                  // Used in: marble_board.c, i2c_fpga.c
                  // Solution: Declare in marble_board.c, extern in i2c_fpga.c

int marble_I2C_probe(I2C_BUS I2C_bus, uint8_t addr);
int marble_I2C_send(I2C_BUS I2C_bus, uint8_t addr, const uint8_t *data, int size);
int marble_I2C_cmdsend(I2C_BUS I2C_bus, uint8_t addr, uint8_t cmd, uint8_t *data, int size);
int marble_I2C_recv(I2C_BUS I2C_bus, uint8_t addr, uint8_t *data, int size);
int marble_I2C_cmdrecv(I2C_BUS I2C_bus, uint8_t addr, uint8_t cmd, uint8_t *data, int size);
int marble_I2C_cmdsend_a2(I2C_BUS I2C_bus, uint8_t addr, uint16_t cmd, uint8_t *data, int size);
int marble_I2C_cmdrecv_a2(I2C_BUS I2C_bus, uint8_t addr, uint16_t cmd, uint8_t *data, int size);

/************
* MDIO to PHY
************/
void marble_MDIO_write(uint16_t reg, uint32_t data);
uint32_t marble_MDIO_read(uint16_t reg);

/************
* System Timer and Stopwatch
************/
uint32_t marble_SYSTIMER_ms(uint32_t delay);
void marble_SYSTIMER_handler(void (*handler)(void));

void marble_SLEEP_ms(uint32_t delay);
void marble_SLEEP_us(uint32_t delay);

#endif /* SIMULATION */
#endif /* _MARBLE_API_H_ */
