#include"inclusions.h"
#include"component.h"
using namespace std;

string Component::Description() { return description; }
string Component::Description(string input) { description=input; return description; }

int Component::Value() { return value; }
int Component::Value(int input) { value=input; return value; }
