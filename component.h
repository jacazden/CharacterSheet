#include"inclusions.h"
#include"tag.h"
#pragma once

class Component:public Tag
{
protected:
        std::string description;
        int value;
public:
        Component()
        {
                description = "";
                value = 0;
        }
        Component(std::string n, std::string d, int v,std::vector<std::string> l):Tag(n,l)
        {
                description = d;
                value = v;
        }
        virtual int ID(){return 1;}
        std::string Description();
        std::string Description(std::string input);
        int Value();
        int Value(int input);
        int save(boost::filesystem::path dir,bool append=false);
        Component* load(boost::filesystem::path filepath,int seek=0);
};
