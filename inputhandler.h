#include"inclusions.h"
#include"player.h"
#pragma once

//TODO make the printer class, as well as the input handler class (later, that can remain in the main function for now), put together the catalog and its search functions
//as well as the regex interpretation for the roll function
//
class InputHandler
{
private:
        Player* theplayer;
        std::string input;
        std::vector<std::string> history;
public:
        InputHandler()
        {
                theplayer = new Player;
        }
        ~InputHandler()
        {
                delete theplayer;
        }
        void Print() { return; }
        void Print(int input);
        void Print(std::string input);
        void Loop();
};
