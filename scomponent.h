#include"inclusions.h"
#include"tag.h"
#pragma once
using namespace std;

class sComponent:public Tag
{
protected:
        string description;
        string value;
public:
        sComponent()
        {
                description = "";
                value = string();
        }
        sComponent(string n, string d, string v,vector<string> l):Tag(n,l)
        {
                description = d;
                value = v;
        }
        virtual int ID(){return 4;}
        string Description();
        string Description(string input);
        string Value();
        string Value(string input);
};
