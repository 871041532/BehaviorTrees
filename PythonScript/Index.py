# -*- encoding:utf-8 -*-

from BT import BT, Tree
import Actions
import Conditions

Tree_data = {
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

BT.init_bt()
json_data = str(Tree_data)
tree1 = Tree(json_data)
BT.tick_all()
BT.destory_bt()













