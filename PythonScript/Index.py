import platform 
from ctypes import *

path = R"D:\BehaviorTrees\BehaviorTreeCPP\x64/Release\BehaviorTree.dll"

bt_lib = cdll.LoadLibrary(path)
# bt_lib.fun0()
# bt_lib.fun1(12)

CFuncType1 = CFUNCTYPE(c_uint, c_uint, c_uint)
def f(a, b):
	return a + b
func = CFuncType1(f)
# bt_lib.fun2(func)
CFuncType2 = CFUNCTYPE(c_int)
BOOL_FUNC = CFUNCTYPE(c_bool)
def run1():
	print("run1")
	return True
def run2():
	print("run2")
	return True
def ok():
	print("ok")
	return True
def no():
	print("no")
	return False
run1_func = CFuncType2(run1)
run2_func = CFuncType2(run2)
judge_ok = BOOL_FUNC(ok)
judge_no = BOOL_FUNC(no)

bt_lib.BTInit()
root_node = bt_lib.CreateRootNode()

selector1 = bt_lib.CreateNoRecursionPrioritySelectorNode(root_node)
bt_lib.NodeSetPreCondition(selector1, judge_ok)

selector2 = bt_lib.CreateNoRecursionPrioritySelectorNode(root_node)
bt_lib.NodeSetPreCondition(selector2, judge_ok)

action1 = bt_lib.CreateTeminalNode(selector1, run1_func)
bt_lib.NodeSetPreCondition(action1, judge_ok)

action2 = bt_lib.CreateTeminalNode(selector2, run2_func)
bt_lib.NodeSetPreCondition(action2, judge_ok)
# condition1 = bt_lib.CreateCondition(judge1_func)
# bt_lib.NodeSetPreCondition(run1_node, condition1)
# bt_lib.NodeSetPreCondition(run1_node, judge_ok)
bt_lib.TickOne(root_node)
# bt_lib.TickOne(root_node)
bt_lib.BTDestory()














