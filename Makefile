all: demo

CC = c++

SRC = $(shell find src -type f -name '*.cpp')
LIBS = -lglog -lgflags
FLAGS = -std=c++11 -pthread -O3 -g

demo:
	$(CC) -o $@.bin $(SRC) $(INCLUDE) $(LIBS) $(FLAGS)

clean:
	rm -rf *.bin *.bin.*
