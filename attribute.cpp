#include"inclusions.h"
#include"attribute.h"

bool Attribute::Proficient() { return proficient; }
bool Attribute::Proficient(bool input) { proficient = input; return proficient; }

int Attribute::Mod()
{
        return (value-10)/2;
}

int Attribute::save(boost::filesystem::path dir,bool append)
{
        using boost::filesystem::exists;
        using boost::filesystem::is_directory;
        using boost::filesystem::path;
        if((exists(dir) & is_directory(dir)) || (exists(dir)&!is_directory(dir)&append))
        {
                path filepath = dir / name + ".atr";
                if(append) std::ofstream ofs(dir.string(),std::ofstream::app);
                else std::ofstream ofs(filepath.string(), std::ofstream::out);
                ofs<<"<attribute name=\""<<name<<"\">"<<std::endl;
                ofs<<"\t<name>"<<name<<"</name>"<<std::endl;
                ofs<<"\t<value>"<<value<<"</value>"<<std::endl;
                ofs<<"\t<proficient>"<<proficient<<"</proficient>"<<std::endl;
                ofs<<"\t<tags>"<<std::endl;
                for(int i=0;i<tags.size();i++)
                {
                        ofs<<"\t\t<tagentry>"<<tags[i]<<"</tagentry>"<<std::endl;
                }
                ofs<<"\t</tags>"<<std::endl;
                ofs<<"\t<description>"<<description<<"</description>"<<std::endl;
                ofs<<"</attribute>"<<std::endl;
                ofs.close();
                return 0;
        }
        return -1;
}
Attribute* Attribute::load(boost::filesystem::path filepath,int seek)
{
        using boost::filesystem::exists;
        using boost::filesystem::is_directory;
        using std::regex;
        using std::smatch;
        using std::regex_match;
        if(exists(filepath))
        {
                if(rcmp(filepath.extension().string(),".scp"))
                {
                        std::ifstream ifs(filepath.string(),std::ifstream::in);
                        regex begin("<(\w+)(\s+(\w+)=\"(\w+)\")?(\s+(\w+)=\"(\w+)\")?>",std::regex::icase);
                        regex end("</(\w+)>",std::regex::icase);
                        std::string instring="";
                        char ch;
                        blk_t* blk;
                        std::vector<blk_t*> block;
                        std::smatch rgx,temp;
                        if(seek)
                        {
                                ifs.seekg(seek);
                        }
                        while(ifs>>std::noskipws>>ch)
                        {
                                if(ch=="<")
                                {
                                        if(instring!="")
                                        {
                                                regex top("component",std::regex::icase);
                                                regex N("name",std::regex::icase);
                                                regex T("tags",std::regex::icase);
                                                regex Te("tagentry",std::regex::icase);
                                                regex V("value",std::regex::icase);
                                                regex D("description",std::regex::icase);
                                                regex P("proficient",std::regex::icase);
                                                regex True("true",std::regex::icase);
                                                regex False("false",std::regex::icase);
                                                if(regex_match(block.last()->tag,rgx,N))
                                                {
                                                        name = instring;
                                                }
                                                else if(regex_match(block.last()->tag,rgx,Te) &&
                                                        regex_match(block[block.size()-2]->tag,temp,T))
                                                {
                                                        tags.push_back(instring);
                                                }
                                                else if(regex_match(block.last()->tag,rgx,V))
                                                {
                                                        value = instring;
                                                }
                                                else if(regex_match(block.last()->tag,rgx,D))
                                                {
                                                        description = instring;
                                                }
                                                else if(regex_match(block.last()->tag,rgx,P))
                                                {
                                                        if(regex_match(instring,temp,True))proficient=true;
                                                        else if(regex_match(instring,temp,False))proficient=false;
                                                }
                                        }
                                        instring="";
                                        instring+=ch;
                                }
                                else if(ch==">")
                                {
                                        instring+=ch;
                                        if(instring!="")
                                        {
                                                if(regex_match(instring,rgx,begin))
                                                {
                                                        blk = new block;
                                                        blk->tag =rgx[1].string();
                                                        if(rgx.size()>=5)
                                                        {
                                                                blk->attributes.push_back(std::make_tuple(rgx[3].string(),rgx[4].string()));
                                                        }
                                                        if(rgx.size()>=8)
                                                        {
                                                                blk->attributes.push_back(std::make_tuple(rgx[6].string(),rgx[7].string()));
                                                        }
                                                        block.push_back(blk);
                                                }
                                                else if(regex_match(instring,rgx,end))
                                                {
                                                        regex regtemp(rgx[1].string(),std::regex::icase);
                                                        if(regex_match(block.last()->tag,temp,regtemp))
                                                        {
                                                                blk = block.last();
                                                                delete blk;
                                                                block.pop_back();
                                                                if(block.size()==0)
                                                                {
                                                                        return this;
                                                                }
                                                        }
                                                }
                                        }
                                        instring="";
                                }
                                else
                                {
                                        instring+=ch;
                                }
                        }
                        return this;
                }
        }
        return nullptr;
}
