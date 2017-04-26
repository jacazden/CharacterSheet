#include"inclusions.h"
#include"inputhandler.h"
#include"player.h"
#include"tag.h"
#include"component.h"
#include"scomponent.h"
#include"attribute.h"
#include"skill.h"

int initiative()
{
        return dexterity.Mod();
}
bool Player::describehelper(Skill* input, std::regex query)
{
        std::smatch rgx;
        if(input==nullptr) return false;
        if(std::regex_match(input->Name(),rgx,query))
        {
                iph->Print(input->Name());
                iph->Print(input->Value());
                iph->Print(input->Proficient()?"Proficient":"Not Proficient");
                iph->Print(input->Attr()->Name());
                iph->Print(input->Description());
                return true;
        }
        return false;
}
bool Player::describehelper(Attribute* input, std::regex query)
{
        std::smatch rgx;
        if(input==nullptr) return false;
        if(std::regex_match(input->Name(),rgx,query))
        {
                iph->Print(input->Name());
                iph->Print(input->Value());
                iph->Print(input->Proficient()?"Proficient":"Not Proficient");
                iph->Print(input->Description());
                return true;
        }
        return false;
}
bool Player::describehelper(sComponent* input, std::regex query)
{
        std::smatch rgx;
        if(input==nullptr) return false;
        if(std::regex_match(input->Name(),rgx,query))
        {
                iph->Print(input->Name());
                iph->Print(input->Value());
                iph->Print(input->Description());
                return true;
        }
        return false;
}
bool Player::describehelper(Component* input, std::regex query)
{
        std::smatch rgx;
        if(input==nullptr) return false;
        if(std::regex_match(input->Name(),rgx,query))
        {
                iph->Print(input->Name());
                iph->Print(input->Value());
                iph->Print(input->Description());
                return true;
        }
        return false;
}

bool Player::describe(std::string input)
{
        input = "^"+input+"$";
        std::regex query(input,std::regex::icase);
        int id;
        bool ret = false;
        for(unsigned i=0;i<Catalog.size();i++)
        {
                id = Catalog[i]->ID();
                switch(id)
                {
                        case 1:
                                ret = describehelper(dynamic_cast<Component*>(Catalog[i]),query);
                                break;
                        case 2:
                                ret = describehelper(dynamic_cast<Attribute*>(Catalog[i]),query);
                                break;
                        case 3:
                                ret = describehelper(dynamic_cast<Skill*>(Catalog[i]),query);
                                break;
                        case 4:
                                ret = describehelper(dynamic_cast<sComponent*>(Catalog[i]),query);
                                break;
                        default:
                                break;
                }
                if(ret) return ret;
        }
        return ret;
}
bool Player::search(std::string input)//TODO
{
        input = ".*("+input+").*";
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        bool matched = false;
        for(unsigned i=0;i<Catalog.size();i++)
        {
                for(int j=0;j<Catalog[i]->TagSize();j++)
                {
                        if(std::regex_match(Catalog[i]->Tags(j),rgx,query))
                        {
                                iph->Print(Catalog[i]->Name());
                                matched=true;
                                break;
                        }
                }
        }
        return matched;
}
bool Player::Proficient(std::string input)
{
        if(input=="")return false;
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        for(unsigned i=0;i<18;i++)
        {
                if(std::regex_match(skills[i]->Name(),rgx,query))
                        return skills[i]->Proficient();
        }
        for(unsigned i=0;i<6;i++)
        {
                if(std::regex_match(attributes[i]->Name(),rgx,query))
                        return attributes[i]->Proficient();
        }
        return false;
}

bool Player::Proficient(std::string input, bool set)
{
        if(input=="")return false;
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        for(unsigned i=0;i<18;i++)
        {
                if(std::regex_match(skills[i]->Name(),rgx,query))
                        return skills[i]->Proficient(set);
        }
        for(unsigned i=0;i<6;i++)
        {
                if(std::regex_match(attributes[i]->Name(),rgx,query))
                        return attributes[i]->Proficient(set);
        }
        return false;
}

int Player::Skillcheck(std::string input)
{
        if(input=="")return 0;
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        int out = 0;
        Skill* temp = nullptr;
        for(unsigned i=0;i<18;i++)
        {
                if(std::regex_match(skills[i]->Name(),rgx,query))
                {
                        temp = skills[i];
                        break;
                }
        }
        if(temp==nullptr) return 0;
        if(temp->Attr()!=nullptr) out+=temp->Attr()->Mod();
        if(temp->Proficient()) out+=Proficiencybonus();
        return out;
}
int Player::Attributecheck(std::string input)
{
        if(input=="")return 0;
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        int out = 0;
        Attribute* temp = nullptr;
        for(unsigned i=0;i<6;i++)
        {
                if(std::regex_match(attributes[i]->Name(),rgx,query))
                {
                        temp = attributes[i];
                        break;
                }
        }
        if(temp==nullptr) return 0;
        out+=temp->Mod();
        if(temp->Proficient()) out+=Proficiencybonus();
        return out;
}
int Player::Attributemod(std::string input)
{
        if(input=="")return 0;
        Attribute* temp=nullptr;
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        for(unsigned i=0;i<6;i++)
        {
                if(std::regex_match(attributes[i]->Name(),rgx,query))
                {
                        temp = attributes[i];
                        break;
                }
        }
        if(temp==nullptr) return 0;
        return temp->Mod();
}
int Player::Attributevalue(std::string input, int val)
{
        if(input=="")return 0;
        Attribute* temp=nullptr;
        std::regex query(input,std::regex::icase);
        std::smatch rgx;
        for(unsigned i=0;i<6;i++)
        {
                if(std::regex_match(attributes[i]->Name(),rgx,query))
                {
                        temp = attributes[i];
                        break;
                }
        }
        if(temp==nullptr) return 0;
        if(val!=-1) return temp->Value(val);
        else return temp->Value();
}
std::string Player::Name(std::string input)
{
        if(input!="")return name.Value(input);
        else return name.Value();
}
std::string Player::Alignment(std::string input)
{
        if(input!="")return alignment.Value(input);
        else return alignment.Value();
}
int Player::roll(std::string instring)
{//TODO
        int num=0;
        int sides=0;
        int keep=0;
        int reroll=0;
        int advantage=0;
        std::regex diestring("^(\\d+)(d)(\\d+)([krad])?(\\d+)?([krad])?(\\d+)?([krad])?(\\d+)?");
        std::smatch rgx;
        if(std::regex_match(instring,rgx,diestring))
        {
                num = stoi(rgx[1].str());
                keep = num;
                sides = stoi(rgx[3].str());
                if(rgx.size() >4)
                {
                        std::string parse;
                        for(unsigned i=4;i<rgx.size();i++)
                        {
                                parse = rgx[i].str();
                                if(parse=="a") advantage = 1;
                                else if(parse=="d") advantage = -1;
                                else if(parse=="k")
                                {
                                        if(i+1 < rgx.size())
                                        {//TODO for now there's no try/catch here, but it probably needs one
                                                keep = stoi(rgx[i+1].str());
                                                if(keep>num)keep=num;
                                        }
                                }
                                else if(parse=="r")
                                {
                                        if(i+1 < rgx.size())
                                        {//TODO this will also need a try/catch, probably
                                                reroll = stoi(rgx[i+1].str());
                                                if(reroll>sides)reroll=sides-1;
                                        }
                                }
                        }
                }
        }
        if(sides==0 || num==0 || keep==0) return 0;
        std::vector<int> rolls;
        int temp1,temp2;
        for(int i=0;i<num;i++)
        {
                temp1 = random<int>(reroll+1,sides);
                temp2 = random<int>(reroll+1,sides);
                if(advantage>0) temp1 = temp1>temp2?temp1:temp2;
                else if(advantage<0) temp1 = temp1<temp2?temp1:temp2;
                rolls.push_back(temp1);
        }
        std::sort(rolls.begin(),rolls.end());
        std::reverse(rolls.begin(),rolls.end());
        //for(unsigned i=0;i<rolls.size();i++) iph->Print(rolls[i]);
        return std::accumulate(rolls.begin(),rolls.begin()+keep,0);
}

int Player::Experience(int input)
{
        if(input!=0) return experience.Value(input);
        else return experience.Value();
        //TODO call GainLevel() if you increase in level from adding experience
}

int Player::Level()
{
        if(Experience()>=355000) return 20;
        else if(Experience()>305000) return 19;
        else if(Experience()>265000) return 18;
        else if(Experience()>225000) return 17;
        else if(Experience()>195000) return 16;
        else if(Experience()>165000) return 15;
        else if(Experience()>140000) return 14;
        else if(Experience()>120000) return 13;
        else if(Experience()>100000) return 12;
        else if(Experience()>85000) return 11;
        else if(Experience()>64000) return 10;
        else if(Experience()>48000) return 9;
        else if(Experience()>34000) return 8;
        else if(Experience()>23000) return 7;
        else if(Experience()>14000) return 6;
        else if(Experience()>6500) return 5;
        else if(Experience()>2700) return 4;
        else if(Experience()>900) return 3;
        else if(Experience()>300) return 2;
        else return 1;
}

int Player::Proficiencybonus()
{
        return ((Level()-1)/4)+2;
}

Player::Player()
{//TODO add attribute declarations to this
        name = sComponent("Name","Player Name","",std::vector<std::string>{"Player","Character","Description","Name"});
        alignment = sComponent("Alignment","Player's alignment or deity","",std::vector<std::string>{"Player","Character","Description","Alignment","God"});
        experience = Component("Experience","Total earned experience so far",0,std::vector<std::string>{"Player","Character","Experience","Level"});
        strength = Attribute("Strength","Strength measures bodily power, athletic training, and\n the extent to which you can exert raw physical force.",0,false
                        ,std::vector<std::string>{"Strength","Attribute"});
        dexterity = Attribute("Dexterity","Dexterity measures agility, reflexes, and balance.",0,false,std::vector<std::string>{"Dexterity","Attribute"});
        constitution = Attribute("Constitution","Constitution measures health, stamina, and vital force.",0,false,std::vector<std::string>{"Constitution","Attribute"});
        intelligence = Attribute("Intelligence","Intelligence measures mental acuity, accuracy of recall,\nand the ability to reason.",0,false
                        ,std::vector<std::string>{"Intelligence","Attribute"});
        wisdom = Attribute("Wisdom","Wisdom reflects how attuned you are to the world\naround you and represents perceptiveness and intuition.",0,false
                        ,std::vector<std::string>{"Wisdom","Attribute"});
        charisma = Attribute("Charisma","Charisma measures your ability to interact effectively\nwith others. It includes such factors as confidence\nand eloquence"
                        ", and it can represent a charming or\ncommanding personality.",0,false,std::vector<std::string>{"Charisma","Attribute"});
    
        athletics = Skill("Athletics","  Athletics. Your Strength (Athletics) check covers\ndifficult situations you encounter while climbing,\njumping, or swimming. "
                        "Examples include the\nfollowing activities:\n\n:: You attempt to climb a sheer or slippery cliff, avoid\nhazards while scaling a wall, or "
                        "cling to a surface\nwhile something is trying to knock you off.\n:: You try to jump an unusually long distance or pull\noff a stunt midjump."
                        "\n:: You struggle to swim or stay afloat in treacherous cur-\nrents, storm-tossed waves, or areas of thick seaweed.\nOr another creature "
                        "tries to push or pull you underwa-\nter or otherwise interfere with your swimming."
                        ,false,&strength,std::vector<std::string>{"Athletics","Strength","Skill"});
        acrobatics = Skill("Acrobatics","  Acrobatics. Your Dexterity (Acrobatics) check covers\nyour attempt to stay on your feet in a tricky situation,\nsuch as when"
                        " you\"re trying to run across a sheet of ice.\nbalance on a tightrope, or stay upright on a rocking\nship\"s deck. The DM might also call "
                        "for a Dexterity\n(Acrobatics) check to see if you can perform acrobatic\nstunts, including dives, rolls, somersaults, and flips."
                        ,false,&dexterity,std::vector<std::string>{"Acrobatics","Dexterity","Skill"});
        sleight = Skill("Sleight of Hand","  Sleight of Hand. Whenever you attempt an act of\nlegerdemain or manual trickery, such as planting\nsomething on someone "
                        "else or concealing an object on\nyour person, make a Dexterity (Sleight of Hand) check.\nThe DM might also call for a Dexterity (Sleight of "
                        "Hand)\ncheck to determine whether you can lift a coin purse off\nanother person or slip something out of another person\"s pocket."
                        ,false,&dexterity,std::vector<std::string>{"Sleight","Sleight of Hand","Dexterity","Skill"});
        stealth = Skill("Stealth","  Stealth. Make a Dexterity (Stealth) check when you\nattempt to conceal yourself from enemies, slink past\nguards, slip away "
                        "without being noticed, or sneak up on\nsomeone without being seen or heard."
                        ,false,&dexterity,std::vector<std::string>{"Stealth","Dexterity","Skill"});
        arcana = Skill("Arcana","  Arcana. Your Intelligence (Arcana) check measures\nyour ability to recall lore about spells, magic items,\neldritch symbols, "
                        "magical traditions, the planes of\n existence, and the inhabitants of those planes."
                        ,false,&intelligence,std::vector<std::string>{"Arcana","Intelligence","Skill"});
        history = Skill("History","  History. Your Intelligence (History) check measures\n your ability to recall lore about historical events,\nlegendary people, "
                        "ancient kingdoms, past disputes,\n recent wars, and lost civilizations."
                        ,false,&intelligence,std::vector<std::string>{"History","Intelligence","Skill"});
        investigation = Skill("Investigation","  Investigation. When you look around for clues and\nmake deductions based on those clues, you might make an\n"
                        "Intelligence (Investigation) check. You might deduce the\nlocation of a hidden object, discern from the appearance\nof a wound what kind "
                        "of weapon dealt it, or determine\nthe weakest point in a tunnel that could cause it to\ncollapse. Porint through ancient scrolls in search "
                        "of\na hidden fragment of knowlege might also call for an\nIntelligence (Investigation) check."
                        ,false,&intelligence,std::vector<std::string>{"Investigation","Intelligence","Skill"});
        nature = Skill("Nature","  Nature. Your Intelligence (Nature) check measures\n your ability to recall lore about terrain, plants and\nanimals, the weather, "
                        "and natural cycles."
                        ,false,&intelligence,std::vector<std::string>{"Nature" ,"Intelligence","Skill"});
        religion = Skill("Religion","  Religion. Your Intelligence (Religion) check measures\nyour ability to recall lore about deities, rites and prayers,\nreligious "
                        "hierarchies, holy symbols, and the practices\nof secret cults."
                        ,false,&intelligence,std::vector<std::string>{"Religion","Intelligence","Skill"});
        animal = Skill("Animal Handling","  Animal Handling. When there is any question\nwhether you can calm down a domesticated animal,\nkeep a mount from getting "
                        "spooked, or intuit an animal\"s\nintentions, the DM might call for a Wisdom (Animal\nHandling) check. You also make a Wisdom (Animal\n"
                        "Handling) check to control your mount when you attempt\na risky maneuver."
                        ,false,&wisdom,std::vector<std::string>{"Animal Handling","Animal" ,"Wisdom","Skill"});
        insight = Skill("Insight","  Insight. Your Wisdom (Insight) check decides whether\nyou can determine the true intentions of a creature, such\nas when searching "
                        "out a lie or predicting someone\"s\nnext move. Doing so involves gleaning clues from body\nlanguage, speach habits, and changes in mannerisms."
                        ,false,&wisdom,std::vector<std::string>{"Insight","Wisdom","Skill"});
        medicine = Skill("Medicine","  Medicine. A Wisdom (Medicine) check lets you try to\nstabilize a dying companion or diagnose an illness."
                        ,false,&wisdom,std::vector<std::string>{"Medicine","Wisdom","Skill"});
        perception = Skill("Perception","  Perception. Your Wisdom (Perception) check lets\nyou spot, hear, or otherwise detect the presence of\nSomething. It "
                        "measures your general awareness of\nyour surroundings and the keenness of your senses.\nFor example, you might try to hear a conversation\n"
                        "through a closed door, eavesdrop under an open window,\nor hear monsters moving stealthily in the forest. Or you\n might try to spot things "
                        "that are obscured or easy to\nmiss, whether they are orcs lying in ambush on a road,\nthugs hiding in the shadows of an alley, or candlelight\n"
                        "under a closed secret door."
                        ,false,&wisdom,std::vector<std::string>{"Perception","Wisdom","Skill"});
        survival = Skill("Survival","  Survival. The DM might ask you to make a Wisdom\n(Survival) check to follow tracks, hunt wild game, guide\nyour group through "
                        "frozen wastelands, identify signs\nthat owlbears live nearby, predict the weather, or avoid\nquicksand and other natural hazards."
                        ,false,&wisdom,std::vector<std::string>{"Survival","Wisdom","Skill"});
        deception = Skill("Deception","  Deception. Your Charisma (Deception) check\ndetermines whether you can convincingly hide the\ntruth, either verbally or "
                        "through your actions. This\n deception can encompass everything from misleading\nothers through ambiguity to telling outright lies. Typical"
                        "\nsituations include trying to fast-talk a guard, con a\nmerchant, earn money through gambling, pass yourself\noff in a disguise, dull "
                        "someone\"s suspicions with false\nassurances, or maintain an straight face while telling\na blatant lie."
                        ,false,&charisma,std::vector<std::string>{"Deception","Charisma","Skill"});
        intimidation = Skill("Intimidation","  Intimidation. When you attempt to influence someone\nthrough overt threats, hostile actions, and physical\nviolence"
                        ", the DM might ask you to make a Charisma\n(Intimidation) check. Examples include trying to pry\ninformation out of a prisoner, convincing"
                        " street thugs\nto back down from a confrontation, or using the edge of\na broken bottle to convince a sneering vizier to\nreconsider a decision."
                        ,false,&charisma,std::vector<std::string>{"Intimidation","Charisma","Skill"});
        performance = Skill("Performance","  Performance. Your Charisma (Performance) check\ndetermines how well you can delight an audience with\nmusic, dance, acting"
                        ", storytelling, or some other form of\nentertainment."
                        ,false,&charisma,std::vector<std::string>{"Performance","Charisma","Skill"});
        persuasion = Skill("Persuasion","  Persuasion. When you attempt to influence someone\nor a group of people with tact, social graces, or good\nnature, the DM "
                        "might ask you to make a Charisma\n(Persuasion) check. Typically, you use perusasion when\nacting in good faith, to foster friendships, make "
                        "cordial\nrequests, or exhibit proper etiquette. Examples of\npersuading others include convincing a chamberalin to\nlet your party see the "
                        "king, negotiating peace between\nwarring tribes, or inspiring a crowd of townsfolk."
                        ,false,&charisma,std::vector<std::string>{"Persuasion","Charisma","Skill"});
        rand = new std::mt19937(/*might need to put an actual random seed here*/);
        rand->discard(1000);
    
        attributes = std::vector<Attribute*>{&strength,&dexterity,&constitution,&intelligence,&wisdom,&charisma};
        skills = std::vector<Skill*>{&acrobatics,&animal,&arcana,&athletics,&deception,&history,&insight,&intimidation
                ,&investigation,&medicine,&nature,&perception,&performance,&persuasion,&religion
                ,&sleight,&stealth,&survival};
        Catalog = std::vector<Tag*>{&name,&alignment,&experience,&strength,&dexterity,&constitution
                ,&intelligence,&wisdom,&charisma,&acrobatics,&animal,&arcana,&athletics,&deception,&history
                ,&insight,&intimidation,&investigation,&medicine,&nature,&perception,&performance,&persuasion
                ,&religion,&sleight,&stealth,&survival};
}
Player::~Player()
{
        delete rand;
        for(int i=0;i<Inventory.size();i++)
        {
                if(Inventory[i]->allocated==true)
                {
                        switch(Inventory[i]->ID())
                        {
                                case 0:
                                        delete dynamic_cast<Tag*>(Inventory[i]);
                                        break;
                                case 1:
                                        delete dynamic_cast<Component*>(Inventory[i]);
                                        break;
                                case 2:
                                        delete dynamic_cast<Attribute*>(Inventory[i]);
                                        break;
                                case 3:
                                        delete dynamic_cast<Skill*>(Inventory[i]);
                                        break;
                                case 4:
                                        delete dynamic_cast<sComponent*>(Inventory[i]);
                                        break;
                                default:
                                        break;
                        }
                }
        }
        for(int i=0;i<InternalCatalog.size();i++)
        {
                if(InternalCatalog[i]->allocated==true)
                {
                        switch(InternalCatalog[i]->ID())
                        {
                                case 0:
                                        delete dynamic_cast<Tag*>(InternalCatalog[i]);
                                        break;
                                case 1:
                                        delete dynamic_cast<Component*>(InternalCatalog[i]);
                                        break;
                                case 2:
                                        delete dynamic_cast<Attribute*>(InternalCatalog[i]);
                                        break;
                                case 3:
                                        delete dynamic_cast<Skill*>(InternalCatalog[i]);
                                        break;
                                case 4:
                                        delete dynamic_cast<sComponent*>(InternalCatalog[i]);
                                        break;
                                default:
                                        break;
                        }
                }
        }
}
void Player::newplayer()
{
}
void Player::save(boost::filesystem::path playerdirectory)//TODO
{
        using boost::filesystem::exists;
        using boost::filesystem::is_directory;
        using boost::filesystem::path;
        if(exists(playerdirectory) & is_directory(playerdirectory))
        {
                path playerfile = playerdirectory / (Name()+ ".ply");
                std::ofstream ofs(playerfile.string(), std::ofstream::out);
                ofs<<"<player name=\""<<Name()<<"\">\n";
                ofs.close();
                //player base information
                name->save(playerfile,true);
                alignment->save(playerfile,true);
                experience->save(playerfile,true);
                //player attributes
                strength->save(playerfile,true);
                dexterity->save(playerfile,true);
                constitution->save(playerfile,true);
                intelligence->save(playerfile,true);
                wisdom->save(playerfile,true);
                charisma->save(playerfile,true);
                //player skills
                acrobatics->save(playerfile,true);
                animal->save(playerfile,true);
                arcana->save(playerfile,true);
                athletics->save(playerfile,true);
                deception->save(playerfile,true);
                history->save(playerfile,true);
                insight->save(playerfile,true);
                intimidation->save(playerfile,true);
                investigation->save(playerfile,true);
                medicine->save(playerfile,true);
                nature->save(playerfile,true);
                perception->save(playerfile,true);
                performance->save(playerfile,true);
                persuasion->save(playerfile,true);
                religion->save(playerfile,true);
                sleight->save(playerfile,true);
                stealth->save(playerfile,true);
                survival->save(playerfile,true);
                //end file
                std::ofstream ofs(playerfile.string(), std::ofstream::app);
                ofs<<"</player>";
                ofs.close();
                //write inventory and catalog
                saveInventory(playerdirectory);
                saveCatalog(playerdirectory);
                return 0;
        }
        return -1;
        //
        //Component platinum
        //Component gold
        //Component elecrum
        //Component silver
        //Component copper
        //
        //class
        //race
        //background
        //
        //speed -- tied into race
        //initiative
        //armor class
        //max health
        //current health
        //hit dice
        //hit die value
        //short rest
        //long rest
        //death saves
        //list of features
        //list of proficiencies
        //
        //spellbook.
}
void Player::load(boost::filesystem::path playerdirectory)//TODO
{
        boost::filesystem::path playerfile = playerdirectory;
        for(directory_entry& de : directory_iterator(playerdirectory))
        {
                if(de.path().filename().extension().string()==".ply")
                {
                        playerfile = de.path();
                        break;
                }
        }
        if(boost::filesystem::is_directory(playerfile))
        {
                iph->Print("Failed to load player, playerfile is corrupt or missing");
                return;
        }
        regex begin("<(\w+)(\s+(\w+)=\"(\w+)\")?(\s+(\w+)=\"(\w+)\")?>",std::regex::icase);
        regex end("</(\w+)>",std::regex::icase);
        std::ifstream ifs(playerfile.string(),std::ifstream::in);
        std::string instring="";
        char ch;
        blk_t* blk;
        std::vector<blk_t*> block;
        std::smatch rgx,temp;
        std::vector<int> marks;
        int tempmark;
        while(ifs>>std::noskipws>>ch)
        {
                                if(ch=="<")
                                {
                                        tempmark = ifs.tellg() - 1;
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
                                                        if(rcmp(rgx[1].string(),
                                                                "(tag|component|scomponent|attribute|skill)"))
                                                        {
                                                                blk = new block;
                                                                blk->tag =rgx[1].string();
                                                                blk->mark = tempmark;
                                                                if(rgx.size()>=5)
                                                                {
                                                                        blk->attributes.push_back(
                                                                                std::make_tuple(
                                                                                rgx[3].string(),rgx[4].string()));
                                                                }
                                                                if(rgx.size()>=8)
                                                                {
                                                                        blk->attributes.push_back(
                                                                                std::make_tuple(
                                                                                rgx[6].string(),rgx[7].string()));
                                                                }
                                                                block.push_back(blk);
                                                        }
                                                }
                                                //TODO
                                                //move this to the end as a memory release of declared blk
                                                //objects
                                                //
                                                //else if(regex_match(instring,rgx,end))
                                                //{
                                                //        regex regtemp(rgx[1].string(),std::regex::icase);
                                                //        if(regex_match(block.last()->tag,temp,regtemp))
                                                //        {
                                                //                blk = block.last();
                                                //                delete blk;
                                                //                block.pop_back();
                                                //                if(block.size()==0)
                                                //                {
                                                //                        break;
                                                //                }
                                                //        }
                                                //}
                                        }
                                        instring="";
                                }
                                else
                                {
                                        instring+=ch;
                                }
        }
        ifs.close();
        //note, there is a reason that this wasn't done as a loop, despite that being the easiest way to do it.
        //it was one in blocks like this because the skills have to be done after the attributes, so it may as
        //well be done in conceptual blocks. speed could be regained(but not much) by implementing a more strict
        //approach to "first load" and "second load", where all standalones can be in "first", and all pointer
        //dependent variables can be loaded in "second"
        for(int i=0;i<block.size();i++)
        {
                if(rcmp(block[i]->tag,"name")) name.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"alignment")) alignment.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"experience")) experience.load(playerfile,block[i]->mark);
        }
        for(int i=0;i<block.size();i++)
        {
                if(rcmp(block[i]->tag,"strength"))              strength.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"dexterity"))        dexterity.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"constitution"))     constitution.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"intelligence"))     intelligence.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"wisdom"))           wisdom.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"charisma"))         charisma.load(playerfile,block[i]->mark);
                attributes = std::vector<Attribute*>
                        {&strength,&dexterity,&constitution,&intelligence,&wisdom,&charisma};
        }
        for(int i=0;i<block.size();i++)
        {
                if(rcmp(block[i]->tag,"acrobatics"))            acrobatics.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"animal"))           animal.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"arcana"))           arcana.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"athletics"))        athletics.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"deception"))        deception.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"history"))          history.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"insight"))          insight.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"intimidation"))     intimidation.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"investigation"))    investigation.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"medicine"))         medicine.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"nature"))           nature.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"perception"))       perception.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"performance"))      performance.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"persuasion"))       persuasion.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"religion"))         religion.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"sleight"))          sleight.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"stealth"))          stealth.load(playerfile,block[i]->mark);
                else if(rcmp(block[i]->tag,"survival"))         survival.load(playerfile,block[i]->mark);
                skills = std::vector<Skill*>
                {&acrobatics,&animal,&arcana,&athletics,&deception,&history,&insight,&intimidation
                ,&investigation,&medicine,&nature,&perception,&performance,&persuasion,&religion
                ,&sleight,&stealth,&survival};
                for(int i=0;i<skills.size();i++)
                {
                        for(int j=0;j<attributes.size();j++)
                        {
                                if(rcmp(skills[i]->Attr()->Name(),attributes[j]->Name()))
                                {
                                        Attribute* temp=skills[i]->Attr();
                                        skills[i]->Attr(attributes[j]);
                                        delete temp;
                                }
                        }
                }
        }
        loadInventory(playerdirectory);
        loadCatalog(playerdirectory);
        //
        //Component<int> platinum
        //Component<int> gold
        //Component<int> elecrum
        //Component<int> silver
        //Component<int> copper
        //
        //class
        //race
        //background
        //
        //speed -- tied into race
        //initiative
        //armor class
        //max health
        //current health
        //hit dice
        //hit die value
        //short rest
        //long rest
        //death saves
        //list of features
        //list of proficiencies
        //
        //spellbook.
}
void Player::saveInventory(boost::filesystem::path playerdirectory)
{
        boost::filesystem::path temp = playerdirectory / "inventory";
        if(!boost::filesystem::exists(temp)) create_directory(temp);
        for(int i=0;i<inventory.size();i++)
        {
                switch(Inventory[i]->ID())
                {
                        case 1:
                                (dynamic_cast<Component*>(Inventory[i]))->save(temp);
                                break;
                        case 2:
                                (dynamic_cast<Attribute*>(Inventory[i]))->save(temp);
                                break;
                        case 3:
                                (dynamic_cast<Skill*>(Inventory[i]))->save(temp);
                                break;
                        case 4:
                                (dynamic_cast<sComponent*>(Inventory[i]))->save(temp);
                                break;
                        default:
                                break;
                }
        }
}
void Player::saveCatalog(boost::filesystem::path playerdirectory)
{
        boost::filesystem::path temp = playerdirectory / "intcatalog";
        if(!boost::filesystem::exists(temp)) create_directory(temp);
        for(int i=0;i<InternalCatalog.size();i++)
        {
                switch(InternalCatalog[i]->ID())
                {
                        case 1:
                                (dynamic_cast<Component*>(InternalCatalog[i]))->save(temp);
                                break;
                        case 2:
                                (dynamic_cast<Attribute*>(InternalCatalog[i]))->save(temp);
                                break;
                        case 3:
                                (dynamic_cast<Skill*>(InternalCatalog[i]))->save(temp);
                                break;
                        case 4:
                                (dynamic_cast<sComponent*>(InternalCatalog[i]))->save(temp);
                                break;
                        default:
                                break;
                }
        }
}
void Player::loadCatalog(boost::filesystem::path playerdirectory)
{
        boost::filesystem::path thepath = playerdirectory / "intcatalog";
        if(boost::filesystem::exists(thepath) && boost::filesystem::is_directory(thepath))
        {
                Tag* _tag;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".tag")
                        {
                                _tag = new Tag;
                                _tag->load(de.path());
                                _tag->allocated=true;
                                InternalCatalog.push_back(_tag);
                        }
                }
                Component* _cmp;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".cmp")
                        {
                                _cmp = new Component;
                                _cmp->load(de.path());
                                _cmp->allocated=true;
                                InternalCatalog.push_back(_cmp);
                        }
                }
                sComponent* _scp;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".scp")
                        {
                                _scp = new sComponent;
                                _scp->load(de.path());
                                _scp->allocated=true;
                                InternalCatalog.push_back(_scp);
                        }
                }
                Attribute* _atr;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".atr")
                        {
                                _atr = new Attribute;
                                _atr->load(de.path());
                                _atr->allocated=true;
                                InternalCatalog.push_back(_atr);
                        }
                }
                Skill* _skl;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".skl")
                        {
                                _skl = new Skill;
                                _skl->load(de.path());
                                _skl->allocated=true;
                                Attribute* temp = _skl->Attr()
                                for(int i=0;i<attributes.size();i++)
                                {
                                        if(temp->Name()==attributes[i]->Name())
                                        {
                                                _skl->Attr(attributes[i]);
                                                delete temp;
                                        }
                                }
                                InternalCatalog.push_back(_skl);
                        }
                }
        }
}
void Player::loadInventory(boost::filesystem::path playerdirectory)
{
        boost::filesystem::path thepath = playerdirectory / "inventory";
        if(boost::filesystem::exists(thepath) && boost::filesystem::is_directory(thepath))
        {
                Tag* _tag;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".tag")
                        {
                                _tag = new Tag;
                                _tag.load(de.path());
                                Inventory.push_back(_tag);
                        }
                }
                Component* _cmp;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".cmp")
                        {
                                _cmp = new Component;
                                _cmp.load(de.path());
                                Inventory.push_back(_cmp);
                        }
                }
                sComponent* _scp;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".scp")
                        {
                                _scp = new sComponent;
                                _scp.load(de.path());
                                Inventory.push_back(_scp);
                        }
                }
                Attribute* _atr;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".atr")
                        {
                                _atr = new Attribute;
                                _atr.load(de.path());
                                Inventory.push_back(_atr);
                        }
                }
                Skill* _skl;
                for(directory_entry& de : directory_iterator(thepath))
                {
                        if(de.path().filename().extension().string()==".skl")
                        {
                                _skl = new Skill;
                                _skl.load(de.path());
                                Attribute* temp = _skl->Attr()
                                for(int i=0;i<attributes.size();i++)
                                {
                                        if(temp->Name()==attributes[i]->Name())
                                        {
                                                _skl->Attr(attributes[i]);
                                                delete temp;
                                        }
                                }
                                Inventory.push_back(_skl);
                        }
                }
        }
}
