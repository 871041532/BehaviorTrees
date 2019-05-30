# -*- coding: utf-8 -*-
import sys
from PyQt5.QtWidgets import QPushButton, QApplication, QMainWindow, QFileDialog, QToolTip, QDialog
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5 import QtCore, QtGui, QtWidgets
import json
from BT import BT, Tree, LIB_COMPOSITE_NODES
import Actions
import Conditions
from functools import partial

COLORS = {
    "RootNode": ("F08080", QColor(0xF08080)),
    "PrioritySelectorNode": ("48D1CC", QColor(0x48D1CC)),
    "NoRecursionPrioritySelectorNode": ("4cb4e7", QColor(0x4cb4e7)),
    "SequenceNode": ("77c34f", QColor(0x77c34f)),
    "TeminalNode": ("F08080", QColor(0xF08080)),
}

class BaseNode(QtWidgets.QWidget):
    clicked = pyqtSignal(dict, QWidget)
    after_operationed = pyqtSignal()

    def __init__(self, parent):
        super(BaseNode, self).__init__(parent)
        # self.setMinimumSize(self.get_width(), self.get_height())
        self.setGeometry(0, 0, self.get_width(), self.get_height())
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)

        self.name_label = QLabel(self)
        self.name_label.setText("default")
        self.name_label.setAlignment(Qt.AlignCenter)
        self.name_label.setStyleSheet("font:10pt '微软雅黑';border-width: 1px;color:rgb(30,30,30);")  # border-style: solid;border-color: rgb(0, 0, 0);
        self.name_label.setWordWrap(True)
        self.layout.addWidget(self.name_label)
        self.data = None
        self.type = None
        # 父节点
        self.parent_node = None
        self.show()

    def contextMenuEvent(self, event):
        menu = QMenu(self)
        menu.setStyleSheet("font:10pt '微软雅黑';border-width: 1px;color:rgb(20,20,20);")
        child_style = "QMenu{%s} QMenu::item:selected { background-color:rgb(31,111,181);}"%self.cool_color
        if self.type != "TeminalNode":
            menu2 = QMenu("添加组合节点")
            menu.addMenu(menu2)
            menu2.setStyleSheet(child_style)
            for node_name in LIB_COMPOSITE_NODES:
                menu2.addAction(QAction(node_name, self, triggered=partial(self.on_add_composite_node, node_name)))

            add_action = QAction("添加组合节点", self, triggered=self.on_add_composite_node)
            menu.addAction(add_action)
            modify_action = QAction("添加动作节点", self, triggered=self.on_add_terminal_node)
            menu.addAction(modify_action)
        if self.type != "RootNode":
            remove_action = QAction("删除", self, triggered=self.on_remove_this_node)
            menu.addAction(remove_action)

        # # 添加新测试menu
        # menu2 = QMenu("测试")
        # menu2.setStyleSheet()
        # menu.addMenu(menu2)
        # for i in range(0, 200):
        #     menu2.addAction(QAction("测试1", self, triggered=self.on_add_composite_node))
        #     menu2.addAction(QAction("测试2", self, triggered=self.on_add_composite_node))

        menu.exec_(QCursor.pos())

    # 添加组合节点
    def on_add_composite_node(self, node_name):
        if "Children" not in self.data:
            self.data["Children"] = []
        self.data["Children"].append({
            "Type":node_name,
            "Name":"默认",
        })
        self.after_operationed.emit()

    # 添加最终节点动作
    def on_add_terminal_node(self):
        pass

    # 删除
    def on_remove_this_node(self):
        self.data.clear()
        self.after_operationed.emit()

    def mousePressEvent(self, event):
        self.clicked.emit(self.data, self)

    def set_data(self, data, parent_node):
        self.data = data
        name = self.data["Name"]
        self.type = self.data["Type"]
        self.cool_color = "background-color:#%s" % COLORS[self.type][0]
        self.name_label.setText(name)
        self.setStyleSheet(self.cool_color)
        self.parent_node = parent_node

    def refresh_show(self):
        if self.data:
            self.name_label.setText(self.data["Name"])
    
    @staticmethod
    def get_static_width():
        return 150

    def get_width(self):
        return 150

    def get_height(self):
        return 70

    def paintEvent(self, event):
        if self.type:
            painter = QPainter(self)
            painter.setBrush(COLORS[self.type][1])
            pen = QPen()
            pen.setStyle(Qt.NoPen)
            pen.setWidth(0)
            painter.setPen(pen)
            # 画自己
            if self.type == "TeminalNode":
                # 普通矩形
               pass
            else:
                # 椭圆
                self.resize(self.get_width() - 15, self.get_height() - 15)
                painter.drawEllipse(0, 0, self.width(), self.height())
                painter.drawLine(0, 0, 50, 50)
            painter.end()