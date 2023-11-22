/*  file: uart_fifo.h
 *  Author: Auto-generated by mkqueue.py
 */

#ifndef __UART_FIFO_H
#define __UART_FIFO_H

#ifdef __cplusplus
extern "C" {
#endif

// ================================= Includes ==================================
#include <stdio.h>
#include <stdint.h>

// ============================== Exported Macros ==============================
#define UART_QUEUE_ITEMS                            (100)
#define UART_QUEUE_OK                              (0x00)
#define UART_QUEUE_FULL                            (0x01)
#define UART_QUEUE_EMPTY                           (0x02)

#define UART_DATA_NOT_LOST                            (0)
#define UART_DATA_LOST                                (1)

#define UARTTX_QUEUE_ITEMS                         (1024)
#define UARTTX_QUEUE_OK                            (0x00)
#define UARTTX_QUEUE_FULL                          (0x01)
#define UARTTX_QUEUE_EMPTY                         (0x02)

// ============================= Exported Typedefs =============================

// ======================= Exported Function Prototypes ========================
void UARTQUEUE_Init(void);
void UARTQUEUE_Clear(void);
uint8_t UARTQUEUE_Add(uint8_t *item);
uint8_t UARTQUEUE_Get(volatile uint8_t *item);
uint8_t UARTQUEUE_Pop(uint8_t *item);
uint8_t UARTQUEUE_Rewind(int n);
uint8_t UARTQUEUE_Status(void);
int UARTQUEUE_ShiftOut(uint8_t *pData, int len);
int UARTQUEUE_ShiftUntil(uint8_t *pData, uint8_t target, int len);
void UARTQUEUE_SetDataLost(uint8_t lost);
uint8_t UARTQUEUE_IsDataLost(void);
int UARTQUEUE_FillLevel(void);
uint8_t UARTTXQUEUE_Add(uint8_t *item);
uint8_t UARTTXQUEUE_Get(volatile uint8_t *item);
uint8_t UARTTXQUEUE_Status(void);
int USART_Tx_LL_Queue(char *msg, int len);
int USART_Rx_LL_Queue(volatile char *msg, int len);


#ifdef __cplusplus
}
#endif

#endif // __UART_FIFO_H
