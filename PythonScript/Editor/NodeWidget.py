
import sys
from PyQt5.QtWidgets import QPushButton, QApplication, QMainWindow, QFileDialog, QToolTip, QDialog
from PyQt5.QtGui import QIcon, QFont
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5 import QtGui
from PyQt5.QtCore import Qt
from PyQt5 import QtCore, QtGui, QtWidgets

class BaseNode(QtWidgets.QWidget):
    def __init__(self, parent):
        super(BaseNode, self).__init__(parent)
        self.setMinimumSize(self.get_width(), self.get_height())
        self.setGeometry(0, 0, self.get_width(), self.get_height())
        self.layout = QHBoxLayout()
        self.setLayout(self.layout)

        font = QFont("微软雅黑", 10)  # , QFont.Bold
        self.name_label = QLabel(self)
        self.name_label.setText("default")
        self.name_label.setFont(font)
        self.name_label.setWordWrap(True)
        self.layout.addWidget(self.name_label)

        color = "background-color:#a3a380"
        self.setStyleSheet(color)

        self.data = None

    def set_data(self, data):
        self.data = data
        name = self.data["Name"]
        self.name_label.setText(name)




    def get_width(self):
        return 100

    def get_height(self):
        return 100

    def paintEvent(self, event):
        painter = QPainter(self)
        color = QColor(0xa3a380)
        painter.fillRect(0, 0, self.width(), self.height(), color)
        # pen = QPen()
        # pen.setStyle(Qt.SolidLine)
        # pen.setWidth(3)
        # pen.setBrush(Qt.white)
        # painter.setPen(pen)
        # painter.drawLine(10, 50, 310, 350)
        painter.end()