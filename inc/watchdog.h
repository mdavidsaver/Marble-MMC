/*
 * File: watchdog.h
 * Desc: FPGA Watchdog system for authenticating host and rebooting FPGA to
 *       golden image when needed.
 */

#ifndef __WATCHDOG_H
#define __WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void FPGAWD_GetNonce(uint8_t *pdata);
void FPGAWD_DoneHandler(void);
void FPGAWD_HandleHash(const uint8_t *hash);
void FPGAWD_Poll(void);
int FPGAWD_SetPeriod(unsigned int period);
int FPGAWD_GetPeriod(void);
void FPGAWD_ShowState(void);

#ifdef __cplusplus
}
#endif

#endif // __WATCHDOG_H

