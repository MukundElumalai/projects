# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'stud_main.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene
from course_details import Ui_Dialog_course_disp
from lecturer_details_stud import Ui_Dialog_lecturer_disp_stud
from enrolled_course_details import Ui_Dialog_enrolled_course_disp
from enroll import Ui_Dialog_enroll

class Ui_Dialog_student_main(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
        
    def courses(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_course_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def enrolled_course(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_enrolled_course_disp(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def lecturers(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_lecturer_disp_stud(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
        
    def enroll_course(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_enroll(self.user,self.name)
        self.ui.setupUi(self.window)
        self.window.show()
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('4.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(70, 110, 151, 51))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.courses)
        
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(70, 200, 151, 51))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.enrolled_course)
        
        self.pushButton_3 = QtWidgets.QPushButton(Dialog)
        self.pushButton_3.setGeometry(QtCore.QRect(360, 200, 151, 51))
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_3.clicked.connect(self.enroll_course)
        
        self.pushButton_4 = QtWidgets.QPushButton(Dialog)
        self.pushButton_4.setGeometry(QtCore.QRect(70, 290, 151, 51))
        self.pushButton_4.setObjectName("pushButton_4")
        self.pushButton_4.clicked.connect(self.lecturers)
        
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(40, 70, 181, 31))
        self.label.setObjectName("label")
        
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(330, 160, 111, 31))
        self.label_2.setObjectName("label_2")

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name))
        self.pushButton.setText(_translate("Dialog", "All Courses"))
        self.pushButton_2.setText(_translate("Dialog", "Enrolled Courses"))
        self.pushButton_3.setText(_translate("Dialog", "New Enroll"))
        self.pushButton_4.setText(_translate("Dialog", "Lecturers"))
        self.label.setText(_translate("Dialog", "Views:"))
        self.label_2.setText(_translate("Dialog", "Functions:"))

