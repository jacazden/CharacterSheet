#include"inclusions.h"
#include"inputhandler.h"
#include"player.h"
void InputHandler::Print(std::string input)
{
        std::cout<<input<<std::endl;
        return;
}
void InputHandler::Print(int input)
{
        std::cout<<input<<std::endl;
        return;
}
void InputHandler::Loop()
{
        std::string splashtext = "Welcome to the character sheet utility";
        std::string helptext = "Current commands:\n\tSearch <string>\n\tDescribe <string>"
                        "\n\troll <dice string>\n\t<dice string>\n\t<string> (default searches)"
                        "\n\tquit\n\texit";
        std::string prompt = "--> ";
        std::regex basicinput("^(\\w+)(\\s+)?((\\w+)?(\\s+)?(\\w+)?(\\s+)?(\\w+)?(\\s+)?(\\w+)?)?",std::regex::icase);
        std::regex dice("^(\\d+)(d)(\\d+)([krad])?(\\d+)?([krad])?(\\d+)?([krad])?(\\d+)?");
        std::regex quit("^(quit|exit)$",std::regex::icase);
        std::regex rollcmd("^roll$",std::regex::icase);
        std::regex searchcmd("^search$",std::regex::icase);
        std::regex describecmd("^describe$",std::regex::icase);
        std::regex helpcmd("^help$",std::regex::icase);
        std::smatch rgx, temp;
        std::cout<<splashtext;
        while(true)
        {
                //to do the output formatting for blocks of text, for now we're putting a printer class between
                //the player and standard out. it'll just take strings as input, and print them.
                //later this will be modified (as will this while funtion) to provide a more detailed
                //ncurses based io system.
                //
                //the ncurses based io system will also let us put in the history functionality, as well as
                //SUCKER! THIS LETS US PUT IN THE HISTORY FUNCTIONALITY. YOU MEAN JUST THE ARROW KEYS.
                //      its ok past me, second past me was high when he wrote that;
                //do a terminal based GUI. until i have a great deal of the program working, thats a poor thing to
                //implement, so the printer function will at first be just a pass straight through to
                //stdio. later you'll have it actually do some formatting for you
                input="";
                std::cout<<prompt;
                getline(std::cin,input);
                if(input.empty())
                {
                        if(history.size()>=1)input = history[history.size()-1];
                }
                if(std::regex_match(input,rgx,basicinput))
                {
                        history.push_back(input);
                        if(std::regex_match(rgx[1].str(),temp,quit))//quit
                                break;
                        else if(std::regex_match(rgx[1].str(),temp,rollcmd))//roll via command
                        {//TODO make this able to "roll strength check"
                                if(rgx.size()>=5)
                                {
                                        std::cout<<"Result: "<<theplayer->roll(rgx[4])<<std::endl;
                                }
                        }
                        else if(std::regex_match(rgx[1].str(),temp,dice))//roll directly
                        {
                                std::cout<<"Result: "<<theplayer->roll(rgx[1])<<std::endl;
                        }
                        else if(std::regex_match(rgx[1].str(),temp,searchcmd))//command search
                        {
                                if(rgx.size()>4)
                                {
                                        theplayer->search(rgx[3].str());
                                }
                        }
                        else if(std::regex_match(rgx[1].str(),temp,describecmd))//command describe
                        {
                                if(rgx.size()>=4) theplayer->describe(rgx[3].str());
                        }
                        else if(std::regex_match(rgx[1].str(),temp,helpcmd))
                        {
                                std::cout<<helptext<<std::endl;
                        }
                        else//seach functions
                        {
                                if(!theplayer->describe(rgx[0].str()))
                                        theplayer->search(rgx[0].str());
                        }
                }
                std::cout<<std::endl;
        }
        return;
}
