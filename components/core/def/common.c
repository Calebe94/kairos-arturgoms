#include <freertos/FreeRTOS.h>
#include <freertos/semphr.h>
#include <stdint.h>
#include <stdbool.h>
#include <driver/i2c.h>
#include "esp_pm.h"
#include "esp_log.h"
#include "common.h"

unsigned long IRAM_ATTR micros()
{
    return (unsigned long) (esp_timer_get_time());
}

void IRAM_ATTR delay_us(uint32_t us)
{
    uint32_t m = micros();
    if(us)
    {
        uint32_t e = (m + us);
        if(m > e)
        { //overflow
            while(micros() > e)
            {
                NOP();
            }
        }
        while(micros() < e)
        {
            NOP();
        }
    }
}

void IRAM_ATTR delay_ms(uint32_t delay)
{
    delay_us(delay*1000);
}
