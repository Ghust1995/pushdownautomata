// PushdownAutomaton.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include "Transition.h"
#include "Automaton.h"

using namespace std; 

const string epsilon = "e";

const string emptyStack = "$";


void getNextLineWordList(vector<string> *outVector, istream *stream)
{
	string line;
	stringstream ins;

	getline(*stream, line);

	ins.str(line);
	string word;
	for (int i = 0; ins >> word; i++)
	{
		(*outVector).push_back(word);
	}
	ins.clear();
}

void getTransitions(vector<Transition> *transitions, istream *stream)
{
	vector<string> transitionRaw;
	getNextLineWordList(&transitionRaw, stream);
	while (*stream)
	{
		Transition t;
		t.fromState = transitionRaw.at(0);
		t.charTape = transitionRaw.at(1);
		t.charPop = transitionRaw.at(2);
		t.toState = transitionRaw.at(3);
		t.charPush = transitionRaw.at(4);

		(*transitions).push_back(t);
		transitionRaw.clear();
		getNextLineWordList(&transitionRaw, stream);

	}
}

vector<Transition> GetPossibleTransitionsForConditions(vector<Transition> transitions, string state, string tapeRead, string stackTop, int tabs)
{
	vector<Transition> ts;

	for each (Transition t in transitions)
	{
		// Se nao tivermos no estado atual
		if (t.fromState.compare(state)) continue;

		// Se nao houver uma transicao para o caracter atual nem para o epsilon
		if (t.charTape.compare(tapeRead) && t.charTape.compare(epsilon)) continue;

		// Se nao houver uma transição para o topo da pilha nem para o epsion
		if (t.charPop.compare(stackTop) && t.charPop.compare(epsilon)) continue;

		ts.push_back(t);
	}
	return ts;
}


int _tmain(int argc, _TCHAR* argv[])
{	
	vector<string> states, finalStates, startingStates; 
	vector<string> tapeAlfa, stackAlfa;
	vector<string> inputTape;
	vector<Transition> transitions;

	ifstream inFile("automatonc.txt");
	stringstream ins;

	string line;

	// Na primeira linha temos os estados
	getNextLineWordList(&states, &inFile);

	// Na segunda linha temos o alfabeto da fita
	getNextLineWordList(&tapeAlfa, &inFile);

	// Na terceira linha temos o alfabeto da pilha
	getNextLineWordList(&stackAlfa, &inFile);

	// Na quarta linha temos o estado inicial
	getNextLineWordList(&startingStates, &inFile);
	string startingState = startingStates.at(0);

	// Na quinta linha temos os estados finais
	getNextLineWordList(&finalStates, &inFile);

	// Na sexta linha temos a entrada
	getNextLineWordList(&inputTape, &inFile);

	// Apos a sexta linha temos as transicoes
	getTransitions(&transitions, &inFile);

	inFile.clear();

	// Logica do automato de pilha
	Automaton * automaton = new Automaton(inputTape, startingState, finalStates, transitions);

	
	bool accepted = false;
	accepted = automaton->Verify();

	if (accepted)
		cout << "Cadeia Aceita!";
	else
		cout << "Cadeia Recusada!";

	char exit;
	cin >> exit;
	return 0;
}