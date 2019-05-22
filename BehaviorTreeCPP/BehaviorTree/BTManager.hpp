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
BTNodeInputParam* GlobalInput = nullptr;
BTNodeOutputParam* GlobalOutput = nullptr;
Export void Tick()
{
	for (auto&& it : BTRootNodes)
	{
		if (it.second->Evaluate(*GlobalInput))
		{
			it.second->Tick(*GlobalInput, *GlobalOutput);
		}
	}
}
Export uint CreateRootNode()
{
	BTNode* root = new BTNodeSequence(nullptr);
	BTRootNodes[BTCurrentIndex] = root;
	BTNormalNodes[BTCurrentIndex] = root;
	return BTCurrentIndex++;
}
Export void NodeSetPreCondition(uint nodeId, uint conditionId)
{
	BTNode* node = BTNormalNodes[nodeId];
	BTPrecondition* condition = ConditionNodes[conditionId];
	node->SetNodePrecondition(condition);
}
Export uint CreateCondition(bool(*dynamicJudge)())
{
	ConditionNodes[BTCurrentIndex] = new BTPrecondition();
	ConditionNodes[BTCurrentIndex]->SetDynamicJudge([dynamicJudge](const BTNodeInputParam& input) ->bool {return dynamicJudge();});
	return BTCurrentIndex++;
}
Export uint CreateTeminalNode(uint parentId, int(*dynamicOnExcute)())
{
	BTNode* parent = BTNormalNodes[parentId];
	BTNodeTerminal* node = new BTNodeTerminal(parent);
	parent->AddChildNode(node);
	node->SetDynamicOnExecute([dynamicOnExcute](const BTNodeInputParam&input, const BTNodeOutputParam&output) ->StatusBTRunning {
		StatusBTRunning result = (StatusBTRunning)dynamicOnExcute();
		return result;
	});
	BTNormalNodes[BTCurrentIndex] = node;
	return BTCurrentIndex++;
}
Export uint CreateSequenceNode(uint parentId)
{
	BTNode* parent = BTNormalNodes[parentId];
	auto node = new BTNodeSequence(parent);
	parent->AddChildNode(node);
	BTNormalNodes[BTCurrentIndex] = node;
	return BTCurrentIndex++;
}
Export uint CreateLoopNode(uint parentId)
{
	BTNode* parent = BTNormalNodes[parentId];
	BTNormalNodes[BTCurrentIndex] = new BTNodeSequence(parent);
	return BTCurrentIndex++;
}
Export uint CreateParallelNode(uint parentId)
{
	BTNode* parent = BTNormalNodes[parentId];
	auto node = new BTNodeParallel(parent);
	parent->AddChildNode(node);
	BTNormalNodes[BTCurrentIndex] = node;
	return BTCurrentIndex++;
}

Export uint CreatePrioritySelectorNode(uint parentId)
{
	BTNode* parent = BTNormalNodes[parentId];
	auto node = new BTNodePrioritySelector(parent);
	parent->AddChildNode(node);
	BTNormalNodes[BTCurrentIndex] = node;
	return BTCurrentIndex++;
}

Export uint CreateNonePrioritySelectorNode(uint parentId)
{
	BTNode* parent = BTNormalNodes[parentId];
	auto node = new BTNodeNonePrioritySelector(parent);
	parent->AddChildNode(node);
	BTNormalNodes[BTCurrentIndex] = node;
	return BTCurrentIndex++;
}

Export void BTInit()
{
	BTCurrentIndex = 1;
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

