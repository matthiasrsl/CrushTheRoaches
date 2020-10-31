INC_PATH=./
OUT_PATH=./

.DEFAULT: echo "$< n'existe pas."

.PHONY: all clean fix run

all: build run

build: $(OUT_PATH)/game.gba fix clean

fix: $(OUT_PATH)/game.gba
	gbafix $^

$(OUT_PATH)/game.gba:  $(OUT_PATH)/main.elf
	arm-none-eabi-objcopy -v -O binary $^ $@

$(OUT_PATH)/main.elf: $(OUT_PATH)/main.o
	arm-none-eabi-gcc $^ -mthumb-interwork -mthumb -specs=gba.specs -o $@

$(OUT_PATH)/main.o: main.c
	arm-none-eabi-gcc -c $^ -mthumb-interwork -mthumb -O2 -o $@

run:
	mgba game.gba


# Nettoyage.

clean:
	rm -f *.o