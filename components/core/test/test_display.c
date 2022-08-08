#include <stdint.h>
#include "test_display.h"
#include "drv/display/gdeh0154d67.h"
#include "lvgl/lvgl.h"
#include "demo.h"

static const char *TAG = "TEST_DISPLAY";

#define LV_TICK_PERIOD_MS 1

static void lv_tick_task(void *arg)
{
    (void) arg;

    lv_tick_inc(LV_TICK_PERIOD_MS);
}

static void my_flush_cb(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    EPD_HW_Init(); //Electronic paper initialization
    uint8_t *buf = (uint8_t *) color_p;
    /* EPD_Dis_Part(area->x1,area->y1,buf, area->x2,area->y2); */
    /* EPD_Dis_Part(0,0,buf, 200,200); */

    EPD_WhiteScreen_ALL(buf);
    /* delay_ms(100); */

       /* IMPORTANT!!!
     * Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}

static void btn_event_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t * btn = lv_event_get_target(e);
    if(code == LV_EVENT_CLICKED) {
        static uint8_t cnt = 0;
        cnt++;

        /*Get the first child of the button which is the label and change its text*/
        lv_obj_t * label = lv_obj_get_child(btn, 0);
        lv_label_set_text_fmt(label, "Button: %d", cnt);
    }
}

/**
 * Create a button with a label and react on click event.
 */
void lv_example_get_started_1(void)
{
    lv_obj_t * btn = lv_btn_create(lv_scr_act());     /*Add a button the current screen*/
    lv_obj_set_pos(btn, 10, 10);                            /*Set its position*/
    lv_obj_set_size(btn, 120, 50);                          /*Set its size*/
    lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_ALL, NULL);           /*Assign a callback to the button*/

    lv_obj_t * label = lv_label_create(btn);          /*Add a label to the button*/
    lv_label_set_text(label, "Button");                     /*Set the labels text*/
    lv_obj_center(label);
}


void task_test_display()
{

    EPD_HW_Init();//Electronic paper initialization
    EPD_WhiteScreen_White();  //Show all white
    /* EPD_HW_Init(); //Electronic paper initialization */
    /* EPD_WhiteScreen_ALL(calebe94_200x200_rotate_map); //Refresh the picture in full screen */

    /* while (1) */
    /* { */
    /*         vTaskDelay(100); */
    /* } */
    lv_init();

    /* Initialize SPI or I2C bus used by the drivers */
    /* lvgl_driver_init(); */

    /* lv_color_t* buf1 = heap_caps_malloc(200 * sizeof(lv_color_t), MALLOC_CAP_DMA); */
    /* assert(buf1 != NULL); */
    /* static lv_color_t *buf2 = NULL; */

    /* xTaskCreatePinnedToCore(task_test_display, TAG, configMINIMAL_STACK_SIZE * 8, NULL, 5, NULL, APP_CPU_NUM); */

    /*A static or global variable to store the buffers*/
    static lv_disp_draw_buf_t disp_buf;
    /*Static or global buffer(s). The second buffer is optional*/
    static lv_color_t buf_1[200 * 10];

    /*Initialize `disp_buf` with the buffer(s) */
    lv_disp_draw_buf_init(&disp_buf, buf_1, NULL, 200*10);

    /* Initialize the working buffer depending on the selected display.
     * NOTE: buf2 == NULL when using monochrome displays. */
    /* lv_disp_buf_init(&disp_buf, buf_1, buf_2, size_in_px); */

    lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.flush_cb = my_flush_cb;
    disp_drv.draw_buf = &disp_buf;          /*Set an initialized buffer*/
    disp_drv.hor_res = 200;                 /*Set the horizontal resolution in pixels*/
    disp_drv.ver_res = 200;
    disp_drv.sw_rotate = 1;
    disp_drv.rotated = LV_DISP_ROT_180;

    lv_disp_drv_register(&disp_drv);

    const esp_timer_create_args_t periodic_timer_args = {
        .callback = &lv_tick_task,
        .name = "periodic_gui"
    };
    esp_timer_handle_t periodic_timer;
    ESP_ERROR_CHECK(esp_timer_create(&periodic_timer_args, &periodic_timer));
    ESP_ERROR_CHECK(esp_timer_start_periodic(periodic_timer, LV_TICK_PERIOD_MS * 1000));
    /* create_demo_application(); */
    lv_example_get_started_1();
    while (1) {
        /* Delay 1 tick (assumes FreeRTOS tick is 10ms */
        vTaskDelay(pdMS_TO_TICKS(10));

        /* Try to take the semaphore, call lvgl related function on success */
        lv_task_handler();
    }
}
