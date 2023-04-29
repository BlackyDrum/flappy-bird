CC=g++
CFLAGS=-std=c++17 -Wall -Wextra -pedantic -g
LDFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lGL
INCLUDES=-Iimgui -I/usr/include/SFML

SOURCES=$(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

IMGUI_SOURCES=$(wildcard imgui/*.cpp)
IMGUI_OBJECTS=$(IMGUI_SOURCES:.cpp=.o)

EXECUTABLE=flappy-bird

all: $(SOURCES) $(IMGUI_SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(IMGUI_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(IMGUI_OBJECTS) $(EXECUTABLE)
	rm -rf build/

