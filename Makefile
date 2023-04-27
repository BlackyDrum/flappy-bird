# Compiler options
CC = g++
CFLAGS = -Wall -Werror -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source and object files
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# Name of the executable file
TARGET = flappy_bird

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

