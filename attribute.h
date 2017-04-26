#include"inclusions.h"
#include"component.h"
#pragma once

class Attribute : public Component
{
protected:
        bool proficient;
public:
        Attribute()
        {
                proficient = false;
        }
        Attribute(std::string n, std::string d, int v, bool p,std::vector<std::string> l):Component(n,d,v,l)
        {
                proficient = p;
        }
        virtual int ID(){return 2;}
        bool Proficient();
        bool Proficient(bool input);
        int Mod();
        int save(boost::filesystem::path dir,bool append=false);
        Attribute* load(boost::filesystem::path filepath,int seek=0);
};
