#include <string>
#include <stack>

using namespace std;
class Computation
{
private:
	string state_;
	int tapePos_;
	int depth_;
	stack<string> stack_;


public:
	string getState();
	int getTapePos();
	int getDepth();
	stack<string> getStack();
	Computation(string state, int tapePos, int depth, stack<string> stack);
	~Computation();
};

