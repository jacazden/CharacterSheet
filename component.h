#include"inclusions.h"
#include"tag.h"
#pragma once
using namespace std;

class Component:public Tag
{
protected:
        string description;
        int value;
public:
        Component()
        {
                description = "";
                value = 0;
        }
        Component(string n, string d, int v,vector<string> l):Tag(n,l)
        {
                description = d;
                value = v;
        }
        virtual int ID(){return 1;}
        string Description();
        string Description(string input);
        int Value();
        int Value(int input);
};
