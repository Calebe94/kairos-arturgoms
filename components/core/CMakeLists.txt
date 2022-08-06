idf_component_register(
                        INCLUDE_DIRS 
                        "./" 
                        "test/" 
                        "drv/protocols" 
                        "drv/rtc"
                        "hal/rtc"
                        "hal/modules"
                        "lib/system"
                        SRCS 
                        "test/i2c_scanner.c" 
                        "test/i2c_rtc.c" 
                        "drv/protocols/i2c.c" 
                        "drv/rtc/pcf8563.c"
                        "hal/rtc/rtc.c"
                        "hal/modules/modules.c"
                        "lib/system/system.c"
                        REQUIRES
                        "driver" 
                        "nvs_flash" 
                        "esp_netif"
)

set(EXTRA_COMPONENT_DIRS $ENV{IDF_PATH}/examples/common_components/protocol_examples_common)
