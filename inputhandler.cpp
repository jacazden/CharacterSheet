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
std::string GetInput(std::string input)
{
        std::string output;
        std::cout<<input;
        std::cin>>output;
        std::cout<<endl;
        return output;
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
        std::regex savecmd("^save$",std::regex::icase);
        std::regex loadcmd("^load$",std::regex::icase);
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
                        else if(std::regex_match(rgx[1].str(),temp,savecmd))
                        {
                                if(theplayer->Name()!="")
                                {
                                        save(theplayer->Name());
                                }
                                else
                                {
                                        save();
                                }
                        }
                        else if(std::regex_match(rgx[1].str(),temp,loadcmd))
                        {
                                if(rgx.size()>=5)
                                {
                                        load(rgx[4].str());
                                }
                                else
                                {
                                        load("");
                                }
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
void InputHandler::load(std::string input)
{
        using boost::filesystem::path;
        using boost::filesystem::exists;
        using boost::filesystem::create_directory;
        while(1)
        {
                std::string yesno= GetInput("Would you like to save the current player? [y/n]");
                std::regex yes("^(yes|ye|y)",std::regex::icase);
                std::regex no("^(no|n)",std::regex::icase);
                std::smatch rgx;
                if(std::regex_match(yesno,rgx,yes))
                {
                        while(theplayer->Name()=="")
                        {
                                theplayer->Name(GetInput("Please enter a character name: "));
                        }
                        save(theplayer->Name());
                }
                else if(std::regex_match(yesno,rgx,no) break;
                else Print("please answer the question properly");
        }
        save("",true);
        path datadir = pwd/"data";
        if(input=="")
                input = GetInput("what player would you like to load? (leave blank for catalog reload) ");
        if(input!="")
        {
                path playerdatapath = datadir / input;
                path playerdatafile = playerdatapath / (input+".ply");
                if(exists(playerdatafile))
                {
                        theplayer->load(playerdatapath);
                }
        }
        if(exists(datadir))
        {
                path catalogdir= datadir / "catalog";
                if(boost::filesystem::exists(catalogdir) && boost::filesystem::is_directory(catalogdir))
                {
                        Component* _cmp;
                        for(directory_entry& de : directory_iterator(catalogdir))
                        {
                                if(de.path().filename().extension().string()==".cmp")
                                {
                                        _cmp = new Component;
                                        _cmp.load(de.path());
                                        Catalog.push_back(_cmp);
                                }
                        }
                        sComponent* _scp;
                        for(directory_entry& de : directory_iterator(catalogdir))
                        {
                                if(de.path().filename().extension().string()==".scp")
                                {
                                        _scp = new sComponent;
                                        _scp.load(de.path());
                                        Catalog.push_back(_scp);
                                }
                        }
                }
        }
}
int InputHandler::save(std::string input,bool skipplayer)
{
        using boost::filesystem::path;
        using boost::filesystem::exists;
        using boost::filesystem::create_directory;
        path datadir = pwd / "data";
        path playerdatapath;
        if(!exists(datadir))
        {
                if(!create_directory(datadir)) return -1;
        }
        if(skipplayer==false && input=="")
        {
                input = theplayer->Name(GetInput("Please enter a character name (or press enter to only save the catalog): "));
        }
        if(skipplayer==false && input!="")
        {
                playerdatapath = datadir;
                if(!exists(playerdatapath))
                {
                        if(!create_directory(playerdatapath)) return -1;
                }
                theplayer->save(playerdatapath);
        }
        path catalogdir= datadir / "catalog";
        if(!exists(catalogdir)) { if(!create_directory(catalogdir)) return -1; }
        for(int i = 0;i<Catalog.size();i++)
        {
                switch(Catalog[i]->ID())
                {
                        case 1:
                                (dynamic_cast<Component*>(Catalog[i]))->save(catalogdir);
                                break;
                        case 4:
                                (dynamic_cast<sComponent*>(Catalog[i]))->save(catalogdir);
                                break;
                        default:
                                break;
                }
        }
        return 0;
}
