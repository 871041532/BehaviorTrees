# -*- coding: utf-8 -*-

import sys
from PyQt5.QtWidgets import QPushButton, QApplication, QMainWindow, QFileDialog, QToolTip, QDialog
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import Qt, pyqtSignal
from PyQt5 import QtCore, QtGui, QtWidgets
from NodeWidget import BaseNode

class MyDockWidget(QtWidgets.QDockWidget):
    property_changed = pyqtSignal()
    def __init__(self, *args):
        super(MyDockWidget, self).__init__(*args)
        self.setFeatures(QDockWidget.DockWidgetMovable)
        self.setAllowedAreas(Qt.LeftDockWidgetArea | Qt.RightDockWidgetArea)
        self.widget = QWidget()
        self.setWidget(self.widget)
        self.layout = QVBoxLayout()
        self.widget.setLayout(self.layout)

        # 类型
        temp_layout = QHBoxLayout()
        self.type_label = QLabel("Type:")
        # temp_layout.addWidget(self.type_label)
        self.layout.addWidget(self.type_label)

        # 名称
        temp_layout = QHBoxLayout()
        self.name_label = QLabel("Name:")
        temp_layout.addWidget(self.name_label)
        self.name_edit = QLineEdit()
        self.name_edit.setPlaceholderText("在此输入名称")
        self.name_edit.textChanged.connect(self.value_changed)
        temp_layout.addWidget(self.name_edit)
        self.layout.addLayout(temp_layout)

        self.condition_edits = []
        # 描述
        self.description_label = QLabel("Description:")
        self.description_edit = QTextEdit("")
        self.description_edit.textChanged.connect(self.value_changed)
        # c1
        self.condition_label1 = QLabel("condition1:")
        self.condition_edit1 = QLineEdit("")
        self.condition_edit1.textChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit1)
        # c2
        self.condition_label2 = QLabel("condition2:")
        self.condition_edit2 = QLineEdit("")
        self.condition_edit2.textChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit2)
        # c3
        self.condition_label3 = QLabel("condition3:")
        self.condition_edit3 = QLineEdit("")
        self.condition_edit3.textChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit3)
        # c4
        self.condition_label4 = QLabel("condition4:")
        self.condition_edit4 = QLineEdit("")
        self.condition_edit4.textChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit4)
        # c5
        self.condition_label5 = QLabel("condition5:")
        self.condition_edit5 = QLineEdit("")
        self.condition_edit5.textChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit5)

        self.layout.addWidget(self.description_label)
        self.layout.addWidget(self.description_edit)
        self.layout.addWidget(self.condition_label1)
        self.layout.addWidget(self.condition_edit1)
        self.layout.addWidget(self.condition_label2)
        self.layout.addWidget(self.condition_edit2)
        self.layout.addWidget(self.condition_label3)
        self.layout.addWidget(self.condition_edit3)
        self.layout.addWidget(self.condition_label4)
        self.layout.addWidget(self.condition_edit4)
        self.layout.addWidget(self.condition_label5)
        self.layout.addWidget(self.condition_edit5)
        self.data = None
        self.info_node = None

    def receive_click_node(self, data, node):
        if self.info_node:
            self.property_changed.disconnect(self.info_node.refresh_show)
        self.data = None
        self.name_edit.setText(data["Name"])
        if "Description" not in data:
            data["Description"] = ""
        self.description_edit.setText(data["Description"])
        self.type_label.setText("Type: " + data["Type"])
        if "Conditions" not in data:
            data["Conditions"] = []
        conditions = data["Conditions"]
        for c in self.condition_edits:
            c.setText("")
        for i, c in enumerate(conditions):
            self.condition_edits[i].setText(c)
        self.data = data
        self.info_node = node
        self.property_changed.connect(self.info_node.refresh_show)

    def value_changed(self, *args):
        if self.data:
            self.data["Name"] = self.name_edit.text()
            self.data["Description"] = self.description_edit.toPlainText()
            c_list = []
            for c in self.condition_edits:
                t = c.text()
                if t:
                    c_list.append(t)
            self.data["Conditions"] = c_list
            self.property_changed.emit()