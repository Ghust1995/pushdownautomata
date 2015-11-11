#include <string>

using namespace std;

#pragma once
class Transition
{
public:
	string fromState;
	string toState;
	string charTape;
	string charPop;
	string charPush;
	
	Transition();
	~Transition();
};

