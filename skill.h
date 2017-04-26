#include"inclusions.h"
#include"attribute.h"
#pragma once

class Skill : public Attribute
{
protected:
        Attribute* attr;
public:
        Skill()
        {
                attr = nullptr;
        }
        Skill(std::string n, std::string d, bool p,Attribute* a,std::vector<std::string> l):Attribute(n,d,0,p,l)
        {
                attr = a;
        }
        virtual int ID(){return 3;}
        Attribute* Attr();
        Attribute* Attr(Attribute* input);
        int save(boost::filesystem::path dir,bool append=false);
        Skill* load(boost::filesystem::path filepath,int seek=0);
};
