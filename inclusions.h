#include<cmath>
#include<climits>
#include<array>
#include<string>
#include<vector>
#include<list>
#include<random>
#include<algorithm>
#include<numeric>
#include<limits>
#include<iostream>
#include<fstream>
#include<locale>
#include<regex>
#include<boost/archive/text_iarchive.hpp>
#include<boost/archive/text_oarchive.hpp>
#include<boost/serialization/vector.hpp>
#include<boost/serialization/list.hpp>
#include<boost/serialization/string.hpp>
#include<boost/filesystem.hpp>
#pragma once
namespace boost{namespace serialization{class access;}}

struct blk_t
{
        std::string tag;
        int mark;
        std::vector<std::tuple<std::string,std::string>> attributes;
}
bool rcmp(std::string arg,std::string regstring)
{
        std::regex obj(regstring,std::regex::icase);
        std::smatch rgx;
        bool ret = std::regex_match(arg,rgx,obj);
        return ret;
}
//std::string lower(std::string instring)
//{
//        std::string outstring;
//        for(unsigned i=0;i<instring.size();i++)
//        {
//                outstring+=std::tolower(instring[i]);
//        }
//        return outstring;
//}
