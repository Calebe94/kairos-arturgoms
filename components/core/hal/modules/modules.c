#include "modules.h"

kairos_err_t init_modules(void){
  kairos_err_t passed = KAIROS_ERR_FAIL;
  passed |= i2cdev_init();
  passed |= init_rtc();
  return passed;
}
