#include"inclusions.h"
#include"component.h"
#pragma once
using namespace std;

class Attribute : public Component
{
protected:
        bool proficient;
public:
        Attribute()
        {
                proficient = false;
        }
        Attribute(string n, string d, int v, bool p,vector<string> l):Component(n,d,v,l)
        {
                proficient = p;
        }
        virtual int ID(){return 2;}
        bool Proficient();
        bool Proficient(bool input);
        int Mod();
};
