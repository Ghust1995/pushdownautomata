#include "stdafx.h"
#include "Computation.h"


Computation::Computation(string state, int tapePos, int depth, stack<string> stack)
{
	state_ = state;
	tapePos_ = tapePos;
	depth_ = depth;
	stack_ = stack;
}


Computation::~Computation()
{
}


string Computation::getState()
{
	return state_;
}

int Computation::getTapePos()
{
	return tapePos_;
}

int Computation::getDepth()
{
	return depth_;
}

stack<string> Computation::getStack()
{
	return stack_;
}
