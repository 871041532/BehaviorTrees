# BehaviorTrees
C++、C#版的行为树，配上基于PyQt的图形化编辑工具
行为树模型使用 作者Finney的 http://www.aisharing.com/archives/517
此模型是基于前提的行为树模型
    ·包括前提（Precondition），选择节点（Selector），并行节点（Parallel），序列节点（Sequence），动作节点等。
    ·构想的最终版是：1.基于C++、C#底层语言，2.绑定Lua或Python脚本层动态配置。3.并且使用基于PyQt5的编辑界面 4.跨平台跨所有游戏引擎，一次开发处处使用