# -*- encoding:utf-8 -*-

from BT import BT, Tree
import Actions
import Conditions

tree_data1 = {
	"Description": "根节点",
	"Name":"树1",
	"Type":"RootNode",
	"Children":[
		{
			"Name":"分支1",
			"Type":"PrioritySelectorNode",
			"Conditions":["ok"],
			"Children":[
				{
					"Name":"行为1",
					"Type":"TeminalNode",
					"Conditions":["ok", "no"],
					"Action":"run1"
				}
			]
		},
		{
			"Name":"分支2",
			"Type":"PrioritySelectorNode",
			"Conditions":["ok"],
			"Children":[
				{
					"Name":"行为2",
					"Type":"TeminalNode",
					"Conditions":["ok"],
					"Action":"run2"
				}
			]
		}
	]
}

tree_data2 = {
	"Description": "根节点",
	"Name":"树2",
	"Type":"RootNode",
	"Children":[
		{
			"Name":"分支1",
			"Type":"NoRecursionPrioritySelectorNode",
			"Conditions":["ok"],
			"Children":[
				{
					"Name":"行为1",
					"Type":"TeminalNode",
					"Conditions":["ok", "no"],
					"Action":"run1"
				}
			]
		},
		{
			"Name":"分支2",
			"Type":"NoRecursionPrioritySelectorNode",
			"Conditions":["ok"],
			"Children":[
				{
					"Name":"行为2",
					"Type":"TeminalNode",
					"Conditions":["ok"],
					"Action":"run2"
				}
			]
		}
	]
}

BT.init_bt()
tree1 = Tree(str(tree_data1))
tree2 = Tree(str(tree_data2))
BT.tick_all()
BT.destory_bt()













