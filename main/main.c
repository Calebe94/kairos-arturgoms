#include "kairos.h"
#include "lib/system/system.h"
#include "drv/display/gdeh0154d67.h"
#include "def/demo.h"

static const char *TAG = "KAIROS";

void app_main(void)
{
    KAIROS_LOGI(TAG, "System is starting.");
    system_init();
    display_init();
    unsigned char fen_L,fen_H,miao_L,miao_H;

    EPD_HW_Init(); //Electronic paper initialization
    EPD_WhiteScreen_ALL(gImage_1); //Refresh the picture in full screen
    delay_ms(2000);
    //////////////////////Partial refresh digital presentation//////////////////////////////////////
    EPD_HW_Init(); //Electronic paper initialization
    EPD_SetRAMValue_BaseMap(gImage_basemap);  //Partial refresh background color,Brush map is a must, please do not delete
    delay_ms(100);
    EPD_Dis_Part(0,32,gImage_num1,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num2,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num3,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num4,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num5,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num6,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num7,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num8,32,32); //x,y,DATA,resolution 32*32
    EPD_Dis_Part(0,32,gImage_num9,32,32); //x,y,DATA,resolution 32*32
    delay_ms(2000);
    ////////////////////////////////////////////////////////////////////////
    //Clean

    EPD_HW_Init();//Electronic paper initialization
    EPD_WhiteScreen_White();  //Show all white
    EPD_DeepSleep();  //Enter deep sleep,Sleep instruction is necessary, please do not delete!!!

    xTaskCreatePinnedToCore(task_i2c_rtc, TAG, configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM);

    while(1);
}
