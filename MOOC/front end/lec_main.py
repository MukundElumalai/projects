# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'lec_main.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene
from course_details import Ui_Dialog_course_disp
from my_course_details import Ui_Dialog_my_course_disp
from my_student_details import Ui_Dialog_my_student_disp
from setmark import Ui_Dialog_setmark

class Ui_Dialog_lecturer_main(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
    
    def courses(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_course_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()

    def my_courses(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_my_course_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def my_students(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_my_student_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def set_mark(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_setmark(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('5.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(80, 110, 161, 51))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.courses)
        
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(80, 210, 161, 51))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.my_students)
        
        self.pushButton_3 = QtWidgets.QPushButton(Dialog)
        self.pushButton_3.setGeometry(QtCore.QRect(80, 310, 161, 51))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_3.clicked.connect(self.my_courses)
        
        self.pushButton_4 = QtWidgets.QPushButton(Dialog)
        self.pushButton_4.setGeometry(QtCore.QRect(390, 210, 151, 51))
        self.pushButton_4.setObjectName("pushButton_4")
        self.pushButton_4.clicked.connect(self.set_mark)
        
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(50, 70, 101, 31))
        self.label.setObjectName("label")
        
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(360, 160, 101, 31))
        self.label_2.setObjectName("label_2")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name))
        self.pushButton.setText(_translate("Dialog", "Courses"))
        self.pushButton_2.setText(_translate("Dialog", "My_Students"))
        self.pushButton_3.setText(_translate("Dialog", "My_Courses"))
        self.pushButton_4.setText(_translate("Dialog", "Set Mark"))
        self.label.setText(_translate("Dialog", "View:"))
        self.label_2.setText(_translate("Dialog", "Functions:"))

