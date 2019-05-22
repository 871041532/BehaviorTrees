#pragma once
#include <unordered_map>
#include "BTNode.hpp"
#include "iostream"
#define Export extern "C" _declspec(dllexport)
using namespace std;

unordered_map<uint, BTNode*> BTRootNodes;
unordered_map<uint, BTNode*> BTNormalNodes;
unordered_map<uint, BTPrecondition*> ConditionNodes;
uint BTCurrentIndex;

Export uint CreateRootNode()
{
	BTRootNodes[BTCurrentIndex] = new BTNodeSequence(nullptr);
	return ++BTCurrentIndex;
}
Export void NodeSetPreCondition(uint nodeId, uint conditionId)
{
	BTNode* node = BTNormalNodes[nodeId];
	BTPrecondition* condition = ConditionNodes[nodeId];
	node->SetNodePrecondition(condition);
}
Export uint CreateCondition(bool(*dynamicJudge)())
{
	ConditionNodes[BTCurrentIndex] = new BTPrecondition();
	ConditionNodes[BTCurrentIndex]->SetDynamicJudge([dynamicJudge](const BTNodeInputParam& input) ->bool {return dynamicJudge();});
	return ++BTCurrentIndex;
}
Export uint CreateTeminalNode(uint parentId, int(*dynamicOnExcute)())
{
	BTNode* parent = BTRootNodes[parentId];
	BTNodeTerminal* node = new BTNodeTerminal(parent);
	node->SetDynamicOnExecute([dynamicOnExcute](const BTNodeInputParam&input, const BTNodeOutputParam&output) ->StatusBTRunning {
		StatusBTRunning result = (StatusBTRunning)dynamicOnExcute();
		return result;
	});
	BTNormalNodes[BTCurrentIndex] = node;
	return ++BTCurrentIndex;
}
Export uint CreateSequenceNode(uint parentId)
{
	BTNode* parent = BTRootNodes[parentId];
	BTNormalNodes[BTCurrentIndex] = new BTNodeSequence(parent);
	return ++BTCurrentIndex;
}
Export uint CreateLoopNode(uint parentId)
{
	BTNode* parent = BTRootNodes[parentId];
	BTNormalNodes[BTCurrentIndex] = new BTNodeSequence(parent);
	return ++BTCurrentIndex;
}
Export uint CreateParallelNode(uint parentId)
{
	BTNode* parent = BTRootNodes[parentId];
	BTNormalNodes[BTCurrentIndex] = new BTNodeParallel(parent);
	return ++BTCurrentIndex;
}

Export uint CreatePrioritySelectorNode(uint parentId)
{
	BTNode* parent = BTRootNodes[parentId];
	BTNormalNodes[BTCurrentIndex] = new BTNodePrioritySelector(parent);
	return ++BTCurrentIndex;
}

Export uint CreateNonePrioritySelectorNode(uint parentId)
{
	BTNode* parent = BTRootNodes[parentId];
	BTNormalNodes[BTCurrentIndex] = new BTNodeNonePrioritySelector(parent);
	return ++BTCurrentIndex;
}

Export void BTInit()
{
	BTCurrentIndex = 0;
}

Export void BTDestory()
{
	for (auto&& it : BTRootNodes)
	{
		delete it.second;
	}
	BTRootNodes.clear();
	BTNormalNodes.clear();  // 原始设计，子节点由父节点来清理
	for (auto&& it : ConditionNodes)
	{
		delete it.second;
	}
	ConditionNodes.clear();
}

Export void fun0()
{
	cout << "fun0" << endl;
}

Export void fun1(int a)
{
	cout << a << endl;
}

Export void fun2(int(*call)(int, int))
{
	function<int(int, int)> temp = call;
	int result = temp(2, 3);
	cout << result << endl;
}

