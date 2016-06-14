#include"inclusions.h"
#include"skill.h"
using namespace std;

Attribute* Skill::Attr() { return attr; }
Attribute* Skill::Attr(Attribute* input) { attr = input; return attr; }
