CC = g++

CFLAGS = -Wall -Wextra -std=c++11

TARGET = CharacterSheet
MAIN = main.cpp
FILES = inputhandler.cpp player.cpp skill.cpp attribute.cpp scomponent.cpp component.cpp tag.cpp

all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(FILES)

clean:
	$(RM) $(TARGET)
