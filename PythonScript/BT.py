# -*- encoding:utf-8 -*-

from ctypes import *
from functools import partial

path = R"D:\BehaviorTrees\BehaviorTreeCPP\x64\Release\BehaviorTree.dll"
# path = R"D:\BehaviorTrees\BehaviorTreeCPP\Debug2\BehaviorTree.dll"
bt_lib = cdll.LoadLibrary(path)

TERMINAL_NODE = "TeminalNode"
LIB_CREATE_TYPES = {
    "TeminalNode": lambda parent_node, call: bt_lib.CreateTeminalNode(parent_node, call),
    "PrioritySelectorNode": lambda parent_node: bt_lib.CreatePrioritySelectorNode(parent_node),
    "NoRecursionPrioritySelectorNode": lambda parent_node: bt_lib.CreateNoRecursionPrioritySelectorNode(parent_node),
    "SequenceNode": lambda parent_node: bt_lib.CreateSequenceNode(parent_node),
}

LIB_COMPOSITE_NODES = [
    "PrioritySelectorNode",
    "NoRecursionPrioritySelectorNode",
    "SequenceNode"
]


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
            if not child_data:
                continue
            type = child_data["Type"]
            path = "%s-%s" % (path_param, child_data["Name"])
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

                def func(p, call):
                    ret = call()
                    if ret:
                        print("Run True:%s" % p)
                    else:
                        print("Run False:%s" % p)
                    return ret

                temp_func = BT.to_int_cfunc(partial(func, path, action_func))
                node = LIB_CREATE_TYPES[type](parent_node, temp_func)
                self.normal_nodes.append(node)
                self.cache_funcs.append(temp_func)

            # 设置condition
            condition_name_list = child_data.get("Conditions", [])
            conditions = []
            for condition_name in condition_name_list:
                condition = BT.conditions[condition_name]
                conditions.append(condition)

            def final_condition(p, cs):
                for c in cs:
                    if not c():
                        print("pre Evalute False:%s" % p)
                        return False
                print("pre Evalute True:%s" % p)
                return True

            temp_func = BT.to_bool_cfunc(partial(final_condition, path, conditions))
            bt_lib.NodeSetPreCondition(node, temp_func)
            self.cache_funcs.append(temp_func)

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











