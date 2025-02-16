#ifndef _HAL_MODULES_H_
#define _HAL_MODULES_H_

#include "def/common.h"
#include "def/board.h"
#include "drv/protocols/i2c.h"
#include "hal/rtc/rtc.h"

kairos_err_t init_modules(void);

#endif // _HAL_MODULES_H_
