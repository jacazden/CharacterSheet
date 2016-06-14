#include"inclusions.h"
#pragma once
using namespace std;

class Tag
{
protected:
        string name;
        vector<string> tags;
public:
        Tag()
        {
                name = "";
                tags = vector<string>();
        }
        Tag(string n,vector<string> input)
        {
                name = n;
                tags = input;
        }
        virtual int ID(){return 0;}
        int add(string input);
        int del(string input);
        bool search(string input);
        bool match(string input);
        string Tags();
        string Tags(int input=0);
        int TagSize();
        string Name();
        string Name(string input);
};
