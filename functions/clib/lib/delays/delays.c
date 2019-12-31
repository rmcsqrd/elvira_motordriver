#include <time.h>
#include "delays.h"
#include <stdint.h>

// all constants convert from function unit to ns
#define s2ns  1000000000
#define ms2ns 1000000
#define us2ns 1000
#define ns2ns 1  // not required just included for posterity's sake

// delays inspired by https://stackoverflow.com/questions/7684359/how-to-use-nanosleep-in-c-what-are-tim-tv-sec-and-tim-tv-nsec

void sdelay(uint32_t sec){
    struct timespec tim, tim2;
    tim.tv_sec = 0;
    tim.tv_nsec = (long) sec*s2ns;
    nanosleep(&tim, &tim2);
}
