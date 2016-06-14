#include"inclusions.h"
#include"attribute.h"
using namespace std;

bool Attribute::Proficient() { return proficient; }
bool Attribute::Proficient(bool input) { proficient = input; return proficient; }

int Attribute::Mod()
{
        return (value-10)/2;
}
