#include "kairos.h"
#include "lib/system/system.h"

static const char *TAG = "KAIROS";

void app_main(void)
{
    KAIROS_LOGI(TAG, "System is starting.");
    system_init();
    xTaskCreatePinnedToCore(task_i2c_rtc, TAG, configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);
}
