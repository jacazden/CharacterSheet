#include"inclusions.h"
#include"scomponent.h"
using namespace std;

string sComponent::Description() { return description; }
string sComponent::Description(string input) { description=input; return description; }

string sComponent::Value() { return value; }
string sComponent::Value(string input) { value=input; return value; }
