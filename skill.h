#include"inclusions.h"
#include"attribute.h"
#pragma once
using namespace std;

class Skill : public Attribute
{
protected:
        Attribute* attr;
public:
        Skill()
        {
                attr = nullptr;
        }
        Skill(string n, string d, bool p,Attribute* a,vector<string> l):Attribute(n,d,0,p,l)
        {
                attr = a;
        }
        virtual int ID(){return 3;}
        Attribute* Attr();
        Attribute* Attr(Attribute* input);
};
