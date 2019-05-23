#include <iostream>
#include "BTNode.hpp"
#include "BTTest.hpp"
#include "BTManager.hpp"
using namespace std;

StatusBTRunning MoveActionExecute2(const BTNodeInputParam& input, BTNodeOutputParam& output)
{
	int& outParam = output.GetRealDataType<int>();
	cout << "MoveAction tick2" << endl;
	if (outParam++ > 1) {
		return StatusBTRunning::Finish;
	}
	return StatusBTRunning::Executing;
}

void MoveActionEnter2(const BTNodeInputParam& input)
{
	cout << "MoveAction enter2" << endl;
}

void MoveActionExit2(const BTNodeInputParam& in, StatusBTRunning status)
{
	cout << "MoveAction Exit2" << endl;
}

class MoveAction: public BTNodeTerminal
{
public:
	MoveAction(BTNode* _o_ParentNode) :BTNodeTerminal(_o_ParentNode) {}
};

class JumpAction : public BTNodeTerminal
{
public:
	JumpAction(BTNode* _o_ParentNode) :BTNodeTerminal(_o_ParentNode) {}
	virtual StatusBTRunning OnExecute(const BTNodeInputParam& input, BTNodeOutputParam& output) override
	{
		cout << "JumpAction tick" << endl;
		return StatusBTRunning::Finish;
	}
};

int main()
{
	int a = 1;
	int b = 1;
	BTNodeInputParam input(&a);
	BTNodeOutputParam output(&b);

	BTNode& root = BTNodeFactory::CreateSequenceNode(nullptr, "root");
	BTNodeFactory::CreateTeminalNode<MoveAction>(&root, "MoveAction").SetDynamicOnExecute(MoveActionExecute2).SetDynamicOnEnter(MoveActionEnter2).SetDynamicOnExit(MoveActionExit2);
	BTNodeFactory::CreateTeminalNode<JumpAction>(&root, "JumpActiontick")
		.SetNodePrecondition(new BTPreconditionTrue());
	if (root.Evaluate(input))
	{
		root.Tick(input, output);
	}
	if (root.Evaluate(input))
	{
		root.Tick(input, output);
	}
	if (root.Evaluate(input))
	{
		root.Tick(input, output);
	}
	if (root.Evaluate(input))
	{
		root.Tick(input, output);
	}
	if (root.Evaluate(input))
	{
		root.Tick(input, output);
	}

	auto run1 = []()->int {
		cout << "run1" << endl;
		return 1;
	};
	auto run2 = []()->int {
		cout << "run2" << endl;
		return 0;
	};
	auto judge = []()->bool {
		return false;
	};
	BTInit();
	auto id = CreateRootNode();
	auto id2 = CreateTeminalNode(id, run1);
	NodeSetDynamicCondition(id2, judge);
	TickAll();
	BTDestory();

	system("pause");
}