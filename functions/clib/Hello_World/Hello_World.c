/*

// include statements
#include <gpiod.h>
#include <stdint.h>
#include "delays.h"

// function prototypes
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


#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int offset;

	if (argc != 3) {
		fprintf(stderr, "usage: %s <controler> <offset>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (sscanf(argv[2], "%d", &offset) != 1) {
		fprintf(stderr, "invalid offset: %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	for (;;) {
		gpiod_ctxless_set_value(argv[1], offset, 0, 0, argv[0], NULL, NULL);
		gpiod_ctxless_set_value(argv[1], offset, 1, 0, argv[0], NULL, NULL);
	}
	return EXIT_SUCCESS;
}

