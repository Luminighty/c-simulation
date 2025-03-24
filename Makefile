IDIR=./include
TARGET=bin/main

CC=gcc
CFLAGS=-I$(IDIR) `sdl2-config --cflags` `pkg-config --cflags SDL2_image` -g
LDFLAGS=`sdl2-config --libs` `pkg-config --libs SDL2_image`


DEPS=$(wildcard $(IDIR)/*.h  $(IDIR)/*/*.h)
SRCS=$(wildcard src/**/*.c src/*.c)
OBJS=$(patsubst src/%.c, build/%.o, $(SRCS))


.PHONY: debug release clean

debug: CFLAGS += -g
debug: $(TARGET)

release: CFLAGS += -O2
release: $(TARGET)


build/%.o: src/%.c $(DEPS)
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS)


$(TARGET): $(OBJS)
	echo $(dir $@)
	@mkdir -p $(dir $@)
	@mkdir -p bin/assets
	@cp -R -u -p ./assets/** ./bin/assets/
	$(CC) -o $@ $^ $(LDFLAGS)


clean:
	rm -rf build bin

