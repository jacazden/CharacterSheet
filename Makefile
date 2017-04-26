CC = g++

CFLAGS = -Wall -Wextra -lmenu -lpanel -lncurses -lboost_system -lboost_filesystem -std=c++11

TARGET = CharacterSheet
MAIN = CharacterSheet.cpp
FILES = inputhandler.cpp player.cpp skill.cpp attribute.cpp scomponent.cpp component.cpp tag.cpp

all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(FILES)

clean:
	$(RM) $(TARGET)
