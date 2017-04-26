#include"inclusions.h"
#pragma once
class Tag
{
protected:
        std::string name;
        std::vector<std::string> tags;
public:
        Tag()
        {
                name = "";
                tags = std::vector<std::string>();
                allocated=false;
        }
        Tag(std::string n,std::vector<std::string> input)
        {
                name = n;
                tags = input;
                allocated=false;
        }
        virtual int ID(){return 0;}
        int add(std::string input);
        int del(std::string input);
        bool search(std::string input);
        bool match(std::string input);
        std::string Tags();
        std::string Tags(int input=0);
        int TagSize();
        std::string Name();
        std::string Name(std::string input);
        int save(boost::filesystem::path dir,bool append=false);
        Tag* load(boost::filesystem::path filepath,int seek=0);
        bool allocated;
};
