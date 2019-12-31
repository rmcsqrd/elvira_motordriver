LIBDELAY_DIR := /home/rmcsqrd/programming/elvira/functions/clib/lib/delays
GPIOD_DIR := /usr/include
LDFLAGS = -L/usr/local/libgpiod/ -lgpiod

all:
	gcc Hello_World.c $(LIBDELAY_DIR)/delays.c -o Hello_World -I $(LIBDELAY_DIR) $(LDFLAGS)
