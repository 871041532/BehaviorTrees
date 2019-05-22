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
	return False
def judge1():
	print("judge1")
	return True
run1_func = CFuncType2(run1)
run2_func = CFuncType2(run2)
judge1_func = BOOL_FUNC(judge1)

bt_lib.BTInit()
root_node = bt_lib.CreateRootNode()
run1_node = bt_lib.CreateTeminalNode(root_node, run1_func)
run2_node = bt_lib.CreateTeminalNode(root_node, run2_func)

condition1 = bt_lib.CreateCondition(judge1_func)
bt_lib.NodeSetPreCondition(run1_node, condition1)

bt_lib.Tick()
bt_lib.Tick()
bt_lib.Tick()
bt_lib.BTDestory()














