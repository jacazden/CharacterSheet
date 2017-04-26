#include"tag.h"

int Tag::add(std::string input)
{
        if(input!="") tags.push_back(input);
        return 1;
}

int Tag::del(std::string input)
{
        //in need of rewrite, currently unused
        return 1;
}

bool Tag::search(std::string input)
{
        //currently unused and in need of rewrite
        return false;
}

bool Tag::match(std::string input)
{
        //fuck it, rewrite all this.
        return false;
}

std::string Tag::Tags() { return std::string(""); }
std::string Tag::Tags(int input)
{
        if(input<0) return std::string("");
        unsigned in = unsigned(input);
        if(tags.size()>=1 && in<=tags.size()) return tags[input];
        return std::string("");
}
int Tag::TagSize()
{
        return tags.size();
}

std::string Tag::Name() { return name; }
std::string Tag::Name(std::string input) { name=input; return name; }

int Tag::save(boost::filesystem::path dir,bool append)
{
        using boost::filesystem::exists;
        using boost::filesystem::is_directory;
        using boost::filesystem::path;
        if((exists(dir) & is_directory(dir)) || (exists(dir)&!is_directory(dir)&append))
        {
                path filepath = dir / name + ".tag";
                if(append) std::ofstream ofs(dir.string(),std::ofstream::app);
                else std::ofstream ofs(filepath.string(), std::ofstream::out);
                ofs<<"<tag name=\""<<name<<"\">"<<std::endl;
                ofs<<"\t<name>"<<std::endl;
                ofs<<"\t\t"<<name<<std::endl;
                ofs<<"\t</name>"<<std::endl;
                ofs<<"\t<tags>"<<std::endl;
                for(int i=0;i<tags.size();i++)
                {
                        ofs<<"\t\t<tagentry>"<<tags[i]<<"</tagentry>"<<std::endl;
                }
                ofs<<"\t</tags>"<<std::endl;
                ofs<<"</tag>"<<std::endl;
                ofs.close();
                return 0;
        }
        return -1;
}
Tag* Tag::load(boost::filesystem::path filepath,int seek)
{
        using boost::filesystem::exists;
        using boost::filesystem::is_directory;
        using std::regex;
        using std::smatch;
        using std::regex_match;
        if(exists(filepath))
        {
                if(rcmp(filepath.extension().string(),".tag"))
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
                                                //regex top("tag",std::regex::icase);
                                                regex N("name",std::regex::icase);
                                                regex T("tags",std::regex::icase);
                                                regex Te("tagentry",std::regex::icase);
                                                if(regex_match(block.last()->tag,rgx,N))
                                                {
                                                        name = instring;
                                                }
                                                else if(regex_match(block.last()->tag,rgx,Te) &&
                                                        regex_match(block[block.size()-2]->tag,temp,T));
                                                {
                                                        tags.push_back(instring);
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
