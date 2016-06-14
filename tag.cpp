#include"tag.h"
using namespace std;

int Tag::add(string input)
{
        if(input!="") tags.push_back(input);
        return 1;
}

int Tag::del(string input)
{
        //in need of rewrite, currently unused
        return 1;
}

bool Tag::search(string input)
{
        //currently unused and in need of rewrite
        return false;
}

bool Tag::match(string input)
{
        //fuck it, rewrite all this.
        return false;
}

string Tag::Tags() { return string(""); }
string Tag::Tags(int input)
{
        if(input<0) return string("");
        unsigned in = unsigned(input);
        if(tags.size()>=1 && in<=tags.size()) return tags[input];
        return string("");
}
int Tag::TagSize()
{
        return tags.size();
}

string Tag::Name() { return name; }
string Tag::Name(string input) { name=input; return name; }
