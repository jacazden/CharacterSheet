#include"inclusions.h"
#include"tag.h"
#pragma once

class sComponent:public Tag
{
protected:
        std::string description;
        std::string value;
public:
        sComponent()
        {
                description = "";
                value = std::string();
        }
        sComponent(std::string n, std::string d, std::string v,std::vector<std::string> l):Tag(n,l)
        {
                description = d;
                value = v;
        }
        virtual int ID(){return 4;}
        std::string Description();
        std::string Description(std::string input);
        std::string Value();
        std::string Value(std::string input);
        int save(boost::filesystem::path dir,bool append=false);
        sComponent* load(boost::filesystem::path filepath,int seek=0);
};
