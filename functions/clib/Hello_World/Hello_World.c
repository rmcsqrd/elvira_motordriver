// include statements
#include <gpiod.h>
#include <stdint.h>
#include "delays.h"
// function prototypes

/*
void main(void);
struct gpiod_chip *output_chip;
struct gpiod_line *output_line;
void main(){
    output_chip = gpiod_chip_open_lookup(0);
    output_line = gpiod_chip_get_line(output_chip, 200);
    while(1){
        gpiod_line_set_value(output_line, 1);
        sdelay(1); 
        gpiod_line_set_value(output_line, 0);
        sdelay(1); 
    }
}
*/

void main(void);
void main(){
    struct gpiod_chip* chip = gpiod_chip_open_by_name("gpiochip0");
    struct gpiod_line* line = gpiod_chip_get_line(chip, 200);
    while(1){
        gpiod_line_request_output(line, "foo", 0);
        gpiod_chip_close(chip);
        sdelay(1);
        gpiod_line_request_output(line, "foo", 1);
        gpiod_chip_close(chip);
        sdelay(1);
    }
}
    
