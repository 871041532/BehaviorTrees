#pragma once
#include <unordered_map>
#include "BTNode.hpp"
#include "iostream"
#define Export extern "C" _declspec(dllexport)
using namespace std;

unordered_map<uint, BTNode*> BTRootNodes;
unordered_map<uint, BTNode*> BTNormalNodes;
uint BTCurrentIndex = 1;
BTNodeInputParam* GlobalInput = nullptr;
BTNodeOutputParam* GlobalOutput = nullptr;

Export void TickOne(uint rootId)
{
	BTNode* rootNode = BTRootNodes[rootId];
	BTGlobal::RECURSION_OK = true;
	if (rootNode ->Evaluate(*GlobalInput) && BTGlobal::RECURSION_OK)
	{
		rootNode ->Tick(*GlobalInput, *GlobalOutput);
	}
}

Export void TickAll()
{
	for (auto&& it : BTRootNodes)
	{
		BTGlobal::RECURSION_OK = true;
		if (it.second->Evaluate(*GlobalInput) && BTGlobal::RECURSION_OK)
		{
			it.second->Tick(*GlobalInput, *GlobalOutput);
		}
	}
}
Export uint CreateRootNode()
{
	BTNode* root = new BTNodePrioritySelector(nullptr);
	BTRootNodes[BTCurrentIndex] = root;
	BTNormalNodes[BTCurrentIndex] = root;
	return BTCurrentIndex++;
}

Export void NodeSetPreCondition(uint nodeId, bool(*dynamicjudge)())
{
	BTNode* node = BTNormalNodes[nodeId];
	node->SetPreCondition(dynamicjudge);
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

Export uint CreateNoRecursionPrioritySelectorNode(uint parentId)
{
	BTNode* parent = BTNormalNodes[parentId];
	auto node = new BTNodeNoRecursionPrioritySelector(parent);
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
}

Export void BTDestoryOne(uint rootId)
{
	delete BTRootNodes[rootId];
	BTRootNodes.erase(rootId);
}

