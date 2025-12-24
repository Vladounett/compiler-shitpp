FLAGS = -Wall -Wextra

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

compilershitpp: $(OBJ)
	g++ $(FLAGS) $(OBJ) -o s++

clean:
	rm -f src/*.o s++

CC = gcc
CFLAGS = -Wall -Wextra -g
LIBFLAGS = `sdl2-config --cflags --libs` -lm