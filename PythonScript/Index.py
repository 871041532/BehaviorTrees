import platform 
from ctypes import *

path = R"D:\BehaviorTrees\BehaviorTreeCPP\x64/Release\BehaviorTree.dll"

bt_lib = cdll.LoadLibrary(path)
bt_lib.fun0()
bt_lib.fun1(12)

CFuncType1 = CFUNCTYPE(c_int, c_int, c_int)
def f(a, b):
	return a + b
func = CFuncType1(f)
bt_lib.fun2(func)

bt_lib.BTInit()

bt_lib.BTDestory()