#include"inclusions.h"
#include"tag.h"
#include"component.h"
#include"scomponent.h"
#include"attribute.h"
#include"skill.h"
#pragma once

class InputHandler;

class Player
{
private:
        InputHandler* iph;
        std::vector<Tag*> Inventory;
        std::vector<Tag*> InternalCatalog;
        bool describehelper(Skill* input, std::regex query);
        bool describehelper(Attribute* input, std::regex query);
        bool describehelper(Component* input, std::regex query);
        bool describehelper(sComponent* input, std::regex query);
protected:
        std::mt19937* rand;
        sComponent name;
        sComponent alignment;
        Component experience;
        //
        Attribute strength;
        Attribute dexterity;
        Attribute constitution;
        Attribute intelligence;
        Attribute wisdom;
        Attribute charisma;
        std::vector<Attribute*> attributes;
        //
        Skill acrobatics;
        Skill animal;
        Skill arcana;
        Skill athletics;
        Skill deception;
        Skill history;
        Skill insight;
        Skill intimidation;
        Skill investigation;
        Skill medicine;
        Skill nature;
        Skill perception;
        Skill performance;
        Skill persuasion;
        Skill religion;
        Skill sleight;
        Skill stealth;
        Skill survival;
        std::vector<Skill*> skills;
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
        template <typename T> T random(T min, T max)
        {
                return std::uniform_int_distribution<T> {min,max}(*rand);
        }
        bool random(double prob = 0.5)
        {
                return std::bernoulli_distribution {prob}(*rand);
        }
        template <typename T> T normal(T mean,T stdev)
        {
                return std::normal_distribution<T>{mean,stdev}(*rand);
        }
public:
        boost::filesystem::path pwd;
        int roll(std::string instring);
        bool describe(std::string input);
        bool search(std::string input);
        //ACCESS SPECIFIERS DOWN HERE
        //
        std::string Name(std::string input = "");
        std::string Alignment(std::string input = "");
        int Experience(int input=0);
        int Level();
        int Proficiencybonus();
        bool Proficient(std::string input);
        bool Proficient(std::string input, bool set);
        //int GainLevel();
        //Component<int> platinum
        //Component<int> gold
        //Component<int> elecrum
        //Component<int> silver
        //Component<int> copper
        //
        int Attributecheck(std::string input="");
        int Attributemod(std::string input="");
        int Attributevalue(std::string input= "", int val= -1);
        //
        int Skillcheck(std::string input="");
        int initiative();
        //
        //class
        //race
        //background
        //
        //speed -- tied into race
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
        Player();//TODO
        ~Player();
        void newplayer();//TODO
        void save(boost::filesystem::path playerdirectory);//TODO
        void load(boost::filesystem::path playerdirectory);//TODO
        void saveInventory(boost::filesystem::path playerdirectory);//TODO
        void loadInventory(boost::filesystem::path playerdirectory);//TODO
        void saveCatalog(boost::filesystem::path playerdirectory);//TODO
        void loadCatalog(boost::filesystem::path playerdirectory);//TODO
};

