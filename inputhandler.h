#include"inclusions.h"
#include"player.h"
#pragma once

//TODO make the printer class, as well as the input handler class (later, that can remain in the main function for now), put together the catalog and its search functions
//as well as the regex interpretation for the roll function
//
class InputHandler
{
private:
        friend class boost::serialization::access;
        Player* theplayer;
        std::string input;
        boost::filesystem::path pwd;
        std::vector<std::string> history;
        std::vector<Tag*> Catalog;
public:
        InputHandler(boost::filesystem::path directory)
        {
                theplayer = new Player;
                theplayer->pwd = directory;
        }
        ~InputHandler()
        {
                delete theplayer;
                for(int i=0;i<Catalog.size();i++)
                {
                        if(Catalog[i]->allocated==true)
                        {
                                switch(Catalog[i]->ID())
                                {
                                        case 0:
                                                delete dynamic_cast<Tag*>(Catalog[i]);
                                                break;
                                        case 1:
                                                delete dynamic_cast<Component*>(Catalog[i]);
                                                break;
                                        case 2:
                                                delete dynamic_cast<Attribute*>(Catalog[i]);
                                                break;
                                        case 3:
                                                delete dynamic_cast<Skill*>(Catalog[i]);
                                                break;
                                        case 4:
                                                delete dynamic_cast<sComponent*>(Catalog[i]);
                                                break;
                                        default:
                                                break;
                                }
                        }
                }
        }
        void Print() { return; }
        void Print(int input);
        void Print(std::string input);
        std::string GetInput(std::string input);
        void Loop();
        int load(std::string input);
        int save(std::string input="",bool skipplayer=false);
};
