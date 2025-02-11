# Собрать многофайловый проект
# Подсказка: Опция -I в gcc помогает решить проблему с поиском заголовочных файлов. (#include "" No such file or directory)
# Для использования make его необходимо установить: sudo apt install make

CC = gcc
CFLAGS = -I./pipes -I./background -I./app
TARGET = main

.PHONY: clean

all: $(TARGET)

main.o: app/main.c
	$(CC) $(CFLAGS) -c -o main.o app/main.c

background.o: background/background.c
	$(CC) $(CFLAGS) -c -o background.o background/background.c

write_pipe.o: pipes/write_pipe.c
	$(CC) $(CFLAGS) -c -o write_pipe.o pipes/write_pipe.c

read_pipe.o: pipes/read_pipe.c
	$(CC) $(CFLAGS) -c -o read_pipe.o pipes/read_pipe.c

$(TARGET): main.o background.o write_pipe.o read_pipe.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o background.o write_pipe.o read_pipe.o


clean:
	rm $(TARGET) *.o