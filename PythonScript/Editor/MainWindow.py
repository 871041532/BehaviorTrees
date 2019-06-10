# -*- coding: utf-8 -*-

import sys 
from PyQt5.QtWidgets import QPushButton, QApplication, QMainWindow, QFileDialog, QToolTip, QDialog
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets
from NodeWidget import BaseNode
from MyDockWidget import MyDockWidget

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(1000, 596)
        MainWindow.setToolTip("")
        MainWindow.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout_3.setObjectName("gridLayout_3")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 705, 23))
        self.menubar.setObjectName("menubar")
        self.menu_F = QtWidgets.QMenu(self.menubar)
        self.menu_F.setObjectName("menu_F")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.actionOpen = QtWidgets.QAction(MainWindow)
        self.actionOpen.setObjectName("actionOpen")
        self.actionNew = QtWidgets.QAction(MainWindow)
        self.actionNew.setObjectName("actionNew")
        self.actionSave = QtWidgets.QAction(MainWindow)
        self.actionSave.setObjectName("actionSave")
        self.menu_F.addAction(self.actionOpen)
        self.menu_F.addAction(self.actionNew)
        self.menu_F.addAction(self.actionSave)
        self.menubar.addAction(self.menu_F.menuAction())

        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "主界面"))
        self.menu_F.setTitle(_translate("MainWindow", "文件(&F)"))
        self.actionOpen.setText(_translate("MainWindow", "打开"))
        self.actionNew.setText(_translate("MainWindow", "新建"))
        self.actionSave.setText(_translate("MainWindow", "保存"))
        self.actionSave.setToolTip(_translate("MainWindow", "保存当前文件"))
        self.actionSave.setShortcut(_translate("MainWindow", "Ctrl+S"))


class MainForm(QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(MainForm, self).__init__()
        self.setupUi(self)
        self.actionOpen.triggered.connect(self.on_open_file)
        self.actionNew.triggered.connect(self.on_create_file)
        self.actionSave.triggered.connect(self.on_save_file)

        self.context = QWidget()
        self.context.setGeometry(0, 0, 1000, 1000)
        # self.context.setMinimumSize(1000, 1000)
        # self.scroll_area = QScrollArea()
        # self.scroll_area.setWidget(self.context)
        self.gridLayout_3.addWidget(self.context)
        import qdarkstyle
        self.setStyleSheet(qdarkstyle.load_stylesheet_pyqt5())
        self.property_win = MyDockWidget(self.tr("属性窗口"), self)
        self.addDockWidget(Qt.RightDockWidgetArea, self.property_win)
        # data
        self.file_path = None
        self.data = None
        self.row_node_nums = {}
        self.row_nodes = {}  # 0:[0, 1, 2]
        self.max_col_count = 0

        self.file_path = "tree1.json"
        file = open(self.file_path, "r", encoding='UTF-8')
        strs = file.read()
        self.data = eval(strs)
        file.close()
        self.refresh_all()
        
        # 父子节点间画线
        def paintEvent(widget, row_nodes,event):
            painter = QPainter(widget)
            pen = QPen(Qt.white, 4, Qt.SolidLine)
            painter.setPen(pen)
            for nodes in row_nodes.values():
                for node in nodes:
                    x1 = node.x() + node.get_width() / 2
                    y1 = node.y() + 12 # + node.get_height() / 2
                    if node.parent_node:
                        x2 = node.parent_node.x() + node.parent_node.get_width() / 2
                        y2 = node.parent_node.y() + node.parent_node.get_height() / 2
                        painter.drawLine(x1, y1, x2, y2)
            painter.end()
        from functools import partial
        self.context.paintEvent = partial(paintEvent, self.context, self.row_nodes)
    
    def refresh_all(self):
        self.row_node_nums.clear()
        for nodes in self.row_nodes.values():
            for node in nodes:
                node.hide()
                node = None
        self.row_nodes.clear()
        self.max_col_count = 0
        self.create_nodes(None, self.data, 0)
        self.set_nodes_position()
        
    def set_nodes_position(self):
        all_width = (self.max_col_count + 1) * (BaseNode.get_static_width())
        offset_x = - BaseNode.get_static_width()
        for row, nodes in self.row_nodes.items():
            piece_width = all_width / (len(nodes) + 1)
            for col, node in enumerate(nodes):
                node.move((col + 1) * piece_width + offset_x, row * (node.get_height() + 10))
    
    def create_nodes(self, parent_node, data, cur_row):
        if cur_row not in self.row_node_nums:
            self.row_node_nums[cur_row] = 0
        if cur_row not in self.row_nodes:
            self.row_nodes[cur_row] = []
        
        # 创建node
        node = BaseNode(self.context)
        node.clicked.connect(self.property_win.receive_click_node)
        node.move(self.row_node_nums[cur_row] * node.get_width(), cur_row * node.get_height())
        node.set_data(data, parent_node)
        node.after_operationed.connect(self.refresh_all)
        self.row_nodes[cur_row].append(node)
        self.row_node_nums[cur_row] += 1
        self.max_col_count = self.max_col_count if self.max_col_count > self.row_node_nums[cur_row] else self.row_node_nums[cur_row]
        #children
        if "Children" not in data:
            data["Children"] = []
        children_data = data["Children"]
        for child_data in children_data:
            if child_data:
                self.create_nodes(node, child_data, cur_row + 1)

    def on_open_file(self):
        self.file_path = QFileDialog.getOpenFileName(self, "Open File","./", "Json files(*.json)")[0]
        if self.file_path:
            file = open(self.file_path, "r", encoding='UTF-8')
            strs = file.read()
            self.data = eval(strs)
            file.close()
            self.refresh_all()
            self.statusbar.showMessage("已加载：" + self.file_path)

    def on_save_file(self):
        if self.file_path:
            file2 = open(self.file_path, "w", encoding='UTF-8')
            dict_str = str(self.data)
            file2.write(dict_str.replace("\'","\""))
            file2.close()
            self.statusbar.showMessage("已保存：" + self.file_path)
        else:
            self.statusbar.showMessage("请先创建或打开一个文件")

    def on_create_file(self):
        self.file_path = "default.json"
        self.data = {
            "Type": "RootNode",
            "Name": "开始",
        }
        self.refresh_all()

    def paintEvent(self, event):
        painter = QPainter(self.context)
        pen = QPen()
        pen.setColor(QColor(0xFFFFFF))
        pen.setStyle(Qt.SolidLine)
        pen.setWidth(3)
        pen.setBrush(Qt.white)
        painter.drawLine(-100, -100, 50, 50)
        painter.end()

if __name__ == '__main__': 
    app = QApplication(sys.argv) 
    ui = MainForm() 
    ui.show()
sys.exit(app.exec_())

