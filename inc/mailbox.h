#ifndef MAILBOX_H_
#define MAILBOX_H_

#include "console.h"

/* Mailbox */
typedef enum {
   MB3_COUNT_HI = 0,
   MB3_COUNT_LO,
   MB3_PAD1,
   MB3_PAD2,
   MB3_LM75_0_HI,
   MB3_LM75_0_LO,
   MB3_LM75_1_HI,
   MB3_LM75_1_LO,
   MB3_FMC_ST,
   MB3_PWR_ST,
   MB3_MGTMUX_ST,
   MB3_PAD3,
   MB3_GIT32_4,
   MB3_GIT32_3,
   MB3_GIT32_2,
   MB3_GIT32_1,
   MB3_SIZE
} PAGE3_ENUM;

typedef enum {
   MB4_MAX_T1_HI,
   MB4_MAX_T1_LO,
   MB4_MAX_T2_HI,
   MB4_MAX_T2_LO,
   MB4_MAX_F1_TACH,
   MB4_MAX_F2_TACH,
   MB4_MAX_F1_DUTY,
   MB4_MAX_F2_DUTY,
   MB4_COUNT_HI,
   MB4_COUNT_LO,
   MB4_SIZE
} PAGE4_ENUM;

typedef enum {
   MB2_FMC_MGT_CTL = 0,
   MB2_SIZE
} PAGE2_ENUM;

void mbox_update(bool verbose);
void mbox_peek(void);

int push_fpga_mac_ip(mac_ip_data_t *pmac_ip_data);
//int push_fpga_mac_ip(unsigned char data[10]);

#endif // MAILBOX_H_
