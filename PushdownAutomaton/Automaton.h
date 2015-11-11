#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "Transition.h"
#include "Computation.h"

using namespace std;

#pragma once
class Automaton
{
private:
	const string epsilon = "e";
	const string emptyStack = "$";
	
	vector<string> tape_;
	vector<string> finalStates_;
	vector<Transition> transitions_;
	string startingState_;
	queue<Computation*> computationsQueue_;
	
	bool Compute(Computation * c);
	vector<Transition> GetPossibleTransitionsForConditions(string state, string tapeRead, string stackTop);

public:
	Automaton(vector<string> tape, string startingState, vector<string> finalStates, vector<Transition> transitions);
	~Automaton();
	bool Verify();	
};

