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
from BT import BT

ALL_CONDITIONS = list(BT.conditions.keys())
ALL_CONDITIONS.insert(0, "无")

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
        self.type_label.setMaximumWidth(250)
        self.type_label.setWordWrap(True)
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
        self.condition_label1 = QLabel("条件1:")
        self.condition_edit1 = QComboBox()
        self.condition_edit1.addItems(ALL_CONDITIONS)
        self.condition_edit1.currentIndexChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit1)
        # c2
        self.condition_label2 = QLabel("条件2:")
        self.condition_edit2 = QComboBox()
        self.condition_edit2.addItems(ALL_CONDITIONS)
        self.condition_edit2.currentIndexChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit2)
        # c3
        self.condition_label3 = QLabel("条件3:")
        self.condition_edit3 = QComboBox()
        self.condition_edit3.addItems(ALL_CONDITIONS)
        self.condition_edit3.currentIndexChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit3)
        # c4
        self.condition_label4 = QLabel("条件4:")
        self.condition_edit4 = QComboBox()
        self.condition_edit4.addItems(ALL_CONDITIONS)
        self.condition_edit4.currentIndexChanged.connect(self.value_changed)
        self.condition_edits.append(self.condition_edit4)
        # c5
        self.condition_label5 = QLabel("条件5:")
        self.condition_edit5 = QComboBox()
        self.condition_edit5.addItems(ALL_CONDITIONS)
        self.condition_edit5.currentIndexChanged.connect(self.value_changed)
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
            c.setCurrentIndex(0)
        for i, c in enumerate(conditions):
            self.condition_edits[i].setCurrentIndex(ALL_CONDITIONS.index(c))
        self.data = data
        self.info_node = node
        self.property_changed.connect(self.info_node.refresh_show)

    def value_changed(self, *args):
        if self.data:
            self.data["Name"] = self.name_edit.text()
            self.data["Description"] = self.description_edit.toPlainText()
            c_list = []
            for c in self.condition_edits:
                t = c.currentText()
                if t != "无":
                    c_list.append(t)
            self.data["Conditions"] = c_list
            self.property_changed.emit()