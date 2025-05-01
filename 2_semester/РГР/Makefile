CC = gcc

CFLAGS = -I. $(shell pkg-config --cflags gtk+-3.0)

LIBS = ui/libui.a -lm $(shell pkg-config --libs gtk+-3.0)

TARGET = program

SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean(base)