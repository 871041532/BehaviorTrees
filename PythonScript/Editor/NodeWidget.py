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

COLORS = {
    "RootNode": ("F08080", QColor(0xF08080)),
    "PrioritySelectorNode": ("48D1CC", QColor(0x48D1CC)),
    "TeminalNode": ("F08080", QColor(0xF08080)),
}

class BaseNode(QtWidgets.QWidget):
    clicked = pyqtSignal(dict, QWidget)
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

    def mousePressEvent(self, event):
        self.clicked.emit(self.data, self)

    def set_data(self, data, parent_node):
        self.data = data
        name = self.data["Name"]
        self.type = self.data["Type"]
        color = "background-color:#%s" % COLORS[self.type][0]
        self.name_label.setText(name)
        self.setStyleSheet(color)
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
                self.resize(self.get_width() - 10, self.get_height() - 10)
                painter.drawEllipse(0, 0, self.width(), self.height())
                painter.drawLine(0, 0, 50, 50)
            painter.end()