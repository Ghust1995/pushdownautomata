#include "stdafx.h"
#include "Automaton.h"

Automaton::Automaton(vector<string> tape, string startingState, vector<string> finalStates, vector<Transition> transitions)
{
	tape_ = tape;
	finalStates_ = finalStates;
	transitions_ = transitions;
	startingState_ = startingState;
}


Automaton::~Automaton()
{
}

vector<Transition> Automaton::GetPossibleTransitionsForConditions(string state, string tapeRead, string stackTop)
{
	vector<Transition> ts;

	for each (Transition t in transitions_)
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


bool Automaton::Compute(Computation * c)
{
	string state = c->getState();
	int tapePos = c->getTapePos();
	int depth = c->getDepth();
	stack<string> stackNew = c->getStack();
	
	bool accepted = false;

	string stackTop = stackNew.size() ? stackNew.top() : epsilon;
	string tapeRead = tapePos < tape_.size() ? tape_.at(tapePos) : epsilon;

	for (int i = 0; i < depth; i++) cout << "\t|";
	cout << "--Current state: " << state << "\t(Tape: " << tapeRead << " StackTop: " << stackTop << ")" << "Size: " << stackNew.size();
	cout << "\n";

	// Se as condicoes atuais determinarem um final valido
	if (!(tapePos < tape_.size()) && stackTop.compare(emptyStack) && (find(finalStates_.begin(), finalStates_.end(), state) != finalStates_.end()))
	{
		accepted = true;
	}

	vector<Transition> possibleTransitions = GetPossibleTransitionsForConditions(state, tapeRead, stackTop);
	for each (Transition t in possibleTransitions)
	{
		int nextTapePos = tapePos;
		stack<string> stackCopy = stackNew;
		// Caso a transiçao retire algo da pilha
		if (t.charPop.compare(epsilon))		stackCopy.pop();
		// Caso a transiçao leia o caracter da fita
		if (t.charTape.compare(epsilon))	nextTapePos++;
		// Caso a transiçao coloque algo na pilha
		if (t.charPush.compare(epsilon))	stackCopy.push(t.charPush);

		for (int i = 0; i < depth; i++) cout << "\t|";
		cout << "--Transition: " << "[" << t.fromState << " " << t.charTape << " " << t.charPop << "]";
		cout << " --> " << "[" << t.toState << " " << t.charPush << "]";
		cout << "\n";

		computationsQueue_.push(new Computation(t.toState, nextTapePos, depth + 1, stackCopy));
	}

	for (int i = 0; i < depth; i++) cout << "\t|";
	cout << (accepted ? "Aceita!" : "");
	cout << "\n";

	return accepted;
}


bool Automaton::Verify()
{
	stack<string> stack;
	bool accepted = false;
	computationsQueue_.push(new Computation(startingState_, 0, 0, stack));
	while (!computationsQueue_.empty())
	{
		Computation * c = computationsQueue_.front();
		computationsQueue_.pop();
		accepted = Compute(c);
		if (accepted)  break;
	}
	return accepted;
}