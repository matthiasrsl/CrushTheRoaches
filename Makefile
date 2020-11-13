SRC_PATH=src
INC_PATH=include
OUT_PATH=bin
CFLAGS=-Wall -Wextra -pedantic -I$(INC_PATH)/ -fno-strict-aliasing
LDFLAGS=

.DEFAULT: echo "$< n'existe pas."

.PHONY: all clean fix run

all: clear build run

build: ./game.gba fix clean

fix: ./game.gba
	gbafix $^

./game.gba:  $(OUT_PATH)/main.elf
	arm-none-eabi-objcopy -v -O binary $^ $@

$(OUT_PATH)/main.elf: $(OUT_PATH)/main.o $(OUT_PATH)/palette.o $(OUT_PATH)/sprites.o $(OUT_PATH)/entity.o
	arm-none-eabi-gcc $^ -mthumb-interwork -mthumb -specs=gba.specs -o $@

$(OUT_PATH)/main.o: $(SRC_PATH)/main.c
	arm-none-eabi-gcc $(CFLAGS) -c $^ -mthumb-interwork -mthumb -O2 -o $@

$(OUT_PATH)/palette.o: $(SRC_PATH)/palette.c
	arm-none-eabi-gcc $(CFLAGS) -c $^ -mthumb-interwork -mthumb -O2 -o $@

$(OUT_PATH)/sprites.o: $(SRC_PATH)/sprites.c
	arm-none-eabi-gcc $(CFLAGS) -c $^ -mthumb-interwork -mthumb -O2 -o $@

$(OUT_PATH)/entity.o: $(SRC_PATH)/entity.c
	arm-none-eabi-gcc $(CFLAGS) -c $^ -mthumb-interwork -mthumb -O2 -o $@

run:
	mgba game.gba


# Nettoyage.

clean:
	rm -f *.o
	rm -f bin/*

clear:
	clear