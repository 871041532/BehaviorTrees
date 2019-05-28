# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'C:\Users\zhoukaibing\Desktop\demo.ui'
#
# Created by: PyQt5 UI code generator 5.11.3
#
# WARNING! All changes made in this file will be lost!

import sys 
from PyQt5.QtWidgets import QPushButton, QApplication, QMainWindow, QFileDialog, QToolTip, QDialog
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(705, 596)
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
    """docstring for MainForm"""
    def __init__(self):
        super(MainForm, self).__init__()
        self.setupUi(self)
        self.actionOpen.triggered.connect(self.on_open_file)
        self.actionNew.triggered.connect(self.on_create_file)
        self.actionSave.triggered.connect(self.on_save_file)

        self.context = QWidget()
        self.context.setMinimumSize(1000, 1000)

        self.scroll_area = QScrollArea()
        self.scroll_area.setWidget(self.context)
        self.gridLayout_3.addWidget(self.scroll_area)
    
    def on_open_file(self):
        print ("on_open_file")
    
    def on_save_file(self):
        print ("on_save_file")
    
    def on_create_file(self):
        print ("on_create_file")
        
    def paintEvent(self, event):
        painter = QPainter(self)
        color = QColor(0xDDDDDF)
        painter.fillRect(0, 0, self.width(), self.height(), color)
        pen = QPen()
        pen.setStyle(Qt.SolidLine)
        pen.setWidth(3)
        pen.setBrush(Qt.white)
        painter.setPen(pen)
        painter.drawLine(10, 50, 310, 350)
        painter.end()

if __name__ == '__main__': 
    app = QApplication(sys.argv) 
    ui = MainForm() 
    ui.show()
sys.exit(app.exec_())

