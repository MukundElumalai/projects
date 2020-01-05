# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'p1diag.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene
from admin_login import Ui_Dialog_admin
from stud_login import Ui_Dialog_student
from lec_login import Ui_Dialog_lecturer

class Ui_Dialog(object):
    def move_to_admin(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_admin()
        self.ui.setupUi(self.window)
        self.window.show()
    
    def move_to_stud(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_student()
        self.ui.setupUi(self.window)
        self.window.show()
    
    def move_to_lec(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_lecturer()
        self.ui.setupUi(self.window)
        self.window.show()
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('2.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(250, 110, 112, 34))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.move_to_admin)
        
        
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(250, 210, 112, 34))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.move_to_stud)
        
        
        self.pushButton_3 = QtWidgets.QPushButton(Dialog)
        self.pushButton_3.setGeometry(QtCore.QRect(250, 310, 112, 34))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_3.clicked.connect(self.move_to_lec)
        
        
        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "MOOC"))
        self.pushButton.setText(_translate("Dialog", "Admin"))
        self.pushButton_2.setText(_translate("Dialog", "Student"))
        self.pushButton_3.setText(_translate("Dialog", "Lecturer"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())

