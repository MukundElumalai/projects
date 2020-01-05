# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'admin_main.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene
from new_course import Ui_Dialog_add_course
from add_lec import Ui_Dialog_add_lec
from course_details import Ui_Dialog_course_disp
from lecturer_details import Ui_Dialog_lecturer_disp
from student_details_admin import Ui_Dialog_student_disp

class Ui_Dialog_ad_main(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
        
    def courses(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_course_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def add_course(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_add_course(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def add_lecturer(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_add_lec(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def students(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_student_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def lecturers(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_lecturer_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('3.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(80, 100, 151, 61))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.courses)
        
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(80, 320, 151, 61))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.students)
        
        self.pushButton_3 = QtWidgets.QPushButton(Dialog)
        self.pushButton_3.setGeometry(QtCore.QRect(380, 150, 161, 61))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_3.clicked.connect(self.add_lecturer)
        
        self.pushButton_4 = QtWidgets.QPushButton(Dialog)
        self.pushButton_4.setGeometry(QtCore.QRect(80, 210, 151, 61))
        self.pushButton_4.setObjectName("pushButton_4")
        self.pushButton_4.clicked.connect(self.lecturers)
        
        self.pushButton_6 = QtWidgets.QPushButton(Dialog)
        self.pushButton_6.setGeometry(QtCore.QRect(380, 250, 161, 61))
        self.pushButton_6.setObjectName("pushButton_6")
        self.pushButton_6.clicked.connect(self.add_course)
        
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(40, 40, 231, 51))
        self.label.setObjectName("label")
        
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(350, 80, 181, 31))
        self.label_2.setObjectName("label_2")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name))
        self.pushButton.setText(_translate("Dialog", "Courses"))
        self.pushButton_2.setText(_translate("Dialog", "Students"))
        self.pushButton_3.setText(_translate("Dialog", "Add Lecturer"))
        self.pushButton_4.setText(_translate("Dialog", "Lecturers"))
        self.pushButton_6.setText(_translate("Dialog", "Add Course"))
        self.label.setText(_translate("Dialog", "View:"))
        self.label_2.setText(_translate("Dialog", "Functions:"))

