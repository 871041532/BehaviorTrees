# -*- encoding:utf-8 -*-
import platform
from ctypes import *
from functools import partial
path = R"D:\BehaviorTrees\BehaviorTreeCPP\x64\Release\BehaviorTree.dll"
path = R"D:\BehaviorTrees\BehaviorTreeCPP\Debug2\BehaviorTree.dll"
bt_lib = cdll.LoadLibrary(path)

TERMINAL_NODE = "TeminalNode"
LIB_CREATE_TYPES = {
	"TeminalNode": lambda parent_node, call: bt_lib.CreateTeminalNode(parent_node, call),
	"PrioritySelectorNode": lambda parent_node: bt_lib.CreatePrioritySelectorNode(parent_node),
	"NoRecursionPrioritySelectorNode": lambda parent_node: bt_lib.CreateNoRecursionPrioritySelectorNode(parent_node),
	"SequenceNode": lambda parent_node: bt_lib.CreateSequenceNode(parent_node),
}

class Tree(object):
	def __init__(self, json_data):
		self.dict_data = eval(json_data)
		self.root_node = None
		self.normal_nodes = []
		self.cache_funcs = []
		self.build_tree(self.dict_data)
	
	def build_tree(self, dict_data):
		self.root_node = bt_lib.CreateRootNode()
		path = self.dict_data["Name"]
		self.build_normal(self.root_node, dict_data.get("Children", []), path)
	
	def build_normal(self, parent_node, children_data_list, path_param):
		for child_data in children_data_list:
			type = child_data["Type"]
			path =  "%s-%s"%(path_param, child_data["Name"])
			path =  child_data["Name"]
			if type != TERMINAL_NODE:
				# 复合节点
				node = LIB_CREATE_TYPES[type](parent_node)
				self.normal_nodes.append(node)
				child_data_list = child_data.get("Children", [])
				self.build_normal(node, child_data_list, path)
			else:
				# terminal
				action_name = child_data["Action"]
				action_func = BT.actions[action_name]
				@BT.to_int_cfunc
				def func():
					ret = action_func()
					if ret:
						print ("Run True:%s"%path)
					else:
						print ("Run False:%s"%path)
					return ret
				node = LIB_CREATE_TYPES[type](parent_node, func)
				self.normal_nodes.append(node)
				self.cache_funcs.append(func)
				
			# 设置condition
			condition_name_list = child_data.get("Conditions", [])
			conditions = []
			for condition_name in condition_name_list:
				condition = BT.conditions[condition_name]
				conditions.append(condition)
				
			@BT.to_bool_cfunc
			def final_condition():
				for c in conditions:
					if not c():
						print ("Evalute False:" + path)
						return False
				print ("Evalute True:" + path)
				return True
			bt_lib.NodeSetPreCondition(node, final_condition)
			self.cache_funcs.append(final_condition)
	
	def __del__(self):
		self.cache_funcs = []
		bt_lib.BTDestoryOne(self.root_node)

class BT(object):
	C_INT_CFUNC = CFUNCTYPE(c_int)
	C_BOOL_CFUNC = CFUNCTYPE(c_bool)
	conditions = {}
	actions = {}
	
	@classmethod
	def init_bt(cls):
		bt_lib.BTInit()
	
	@classmethod
	def destory_bt(cls):
		bt_lib.BTDestory()
	
	# 参数是true
	@classmethod
	def tick_one(cls, tree):
		bt_lib.TickOne(tree.root_node)
	
	@classmethod
	def tick_all(cls):
		bt_lib.TickAll()
	
	# Region---------装饰器--------------------
	@classmethod
	def collect_condition(cls, func):
		cls.conditions[func.__name__] = func
		return func
	
	@classmethod
	def collect_action(cls, func):
		cls.actions[func.__name__] = func
		return func
	
	@classmethod
	def to_int_cfunc(cls, func):
		return cls.C_INT_CFUNC(func)
	
	@classmethod
	def to_bool_cfunc(cls, func):
		return cls.C_BOOL_CFUNC(func)
	# endRegion

@BT.to_int_cfunc
@BT.collect_action
def run1():
	print ("run1")
	return True

@BT.to_int_cfunc
@BT.collect_action
def run2():
	print ("run2")
	return False

@BT.to_int_cfunc
@BT.collect_condition
def ok():
	return True

@BT.to_bool_cfunc
@BT.collect_condition
def eval1():
	print ("eval1")
	return True

@BT.to_bool_cfunc
@BT.collect_condition
def eval2():
	print ("eval2")
	return True

@BT.to_bool_cfunc
@BT.collect_condition
def eval_node1():
	print ("eval_node1")
	return False

@BT.to_bool_cfunc
@BT.collect_condition
def eval_node2():
	print ("eval_node2")
	return True

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
					"Conditions":["ok"],
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
# tree1 = Tree(json_data)
root = bt_lib.CreateRootNode()
select1 = bt_lib.CreatePrioritySelectorNode(root)
select2 = bt_lib.CreatePrioritySelectorNode(root)
action1 = bt_lib.CreateTeminalNode(select1, run1)
action2 = bt_lib.CreateTeminalNode(select2, run2)
bt_lib.NodeSetPreCondition(select1, eval1)
bt_lib.NodeSetPreCondition(select2, eval2)
bt_lib.NodeSetPreCondition(action1, eval_node1)
bt_lib.NodeSetPreCondition(action2, eval_node2)
BT.tick_all()
BT.destory_bt()













