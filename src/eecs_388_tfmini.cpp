/******************************************************************************
 *   Header Includes
 *******************************************************************************/
#include <Arduino.h>
#include <stdint.h>
#include <stdio.h>

#include "eecs_388_lib.h"

#define RED() gpio_write(GPIO_13, ON); \
              gpio_write(GPIO_12, OFF)

#define GREEN() gpio_write(GPIO_13, OFF); \
                gpio_write(GPIO_12, ON)

/******************************************************************************
 *   Function: setup() - Initializes the Arduino System
 *      Pre condition: 
 *          Hardware must be properly connected (sensors, LEDS, etc.)
 *      Post condition: 
 *          Runs initialization calls one time on power up
 *          Input/Output (IO) pins are configured
 *******************************************************************************/
void setup() {
    gpio_mode(GPIO_13, GPIO_OUTPUT); // red
    gpio_mode(GPIO_12, GPIO_OUTPUT); // gree

    uart_init();
}

/******************************************************************************
 *   Function: loop() - Main execution loop
 *      Pre condition: 
 *          setup() has been executed and system is initialized
 *      Post condition: 
 *          Performs a single iteration of the system's function
 *          Repeates indefinetely unless the board is reset or powered off
 *******************************************************************************/
void loop()  {
    uint16_t dist = 0;              /* LIDAR distance data is 16 bits. */

    ser_printline("Setup completed.");
    ser_write( '\n' );

    while( 1 ) {
        /*
         *  Task 1.2:
         *  - read a data frame from the TFmini sensor

         *  - from Table 6, we know each LIDAR measurement sends 9 bytes
         *  - the function `ser_read()` can process 1 byte per function call

         *  - This if-statement below will read (and check) the first two bytes of a valid data frame
         *  - You will need to write code to read the subsequent bytes to get the distance data
         *  - You will need to process the data received from the sensor to get the correct distance value
         */
        if ('Y' == ser_read() && 'Y' == ser_read()) {
            char dist_l = ser_read();
            char dist_h = ser_read();

            short dist = (dist_h << 8) | dist_l;
            ser_printf("Distance: %d", (int)75);
            if (dist < 75) {
                RED();
            } else {
                GREEN();
            }
        }
    }
}