# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'register.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene


class Ui_Dialog_student_register(object):
    def insert_stud(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        a=self.lineEdit.text()
        cur.execute("select check_student_username(%s);",[a])
        x=cur.fetchall()
        conn.close()
        if(x[0][0]==1):
            self.lineEdit.clear()
            print("Enter different student username")
        else:
            print("student username available")
            conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
            cur=conn.cursor()
            a=self.lineEdit.text()
            b=self.lineEdit_2.text()
            c=self.lineEdit_3.text()
            d=self.lineEdit_4.text()
            e=self.lineEdit_5.text()
            cur.execute("insert into student values(%s,%s,%s,%s,%s);",(c,d,a,b,e))
            conn.commit()
            conn.close()
            self.lineEdit.clear()
            self.lineEdit_2.clear()
            self.lineEdit_3.clear()
            self.lineEdit_4.clear()
            self.lineEdit_5.clear()
    
    def check(self):
        if(len(self.lineEdit.text())!=0 and len(self.lineEdit_2.text())!=0 and len(self.lineEdit_3.text())!=0 and len(self.lineEdit_4.text())!=0 and len(self.lineEdit_5.text())!=0):
            self.insert_stud()
        else:
            print("enter all values")
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('4.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.lineEdit = QtWidgets.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(50, 60, 321, 31))
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_2.setGeometry(QtCore.QRect(50, 130, 321, 31))
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.lineEdit_3 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_3.setGeometry(QtCore.QRect(50, 210, 321, 31))
        self.lineEdit_3.setObjectName("lineEdit_3")
        self.lineEdit_4 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_4.setGeometry(QtCore.QRect(50, 280, 321, 31))
        self.lineEdit_4.setObjectName("lineEdit_4")
        self.lineEdit_5 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_5.setGeometry(QtCore.QRect(50, 350, 321, 31))
        self.lineEdit_5.setObjectName("lineEdit_5")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(50, 30, 101, 31))
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(50, 100, 121, 31))
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(50, 178, 171, 31))
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(50, 250, 131, 31))
        self.label_4.setObjectName("label_4")
        self.label_5 = QtWidgets.QLabel(Dialog)
        self.label_5.setGeometry(QtCore.QRect(50, 320, 81, 31))
        self.label_5.setObjectName("label_5")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(400, 400, 131, 51))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.check)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "REGISTER"))
        self.label.setText(_translate("Dialog", "username"))
        self.label_2.setText(_translate("Dialog", "password"))
        self.label_3.setText(_translate("Dialog", "First Name"))
        self.label_4.setText(_translate("Dialog", "Last Name"))
        self.label_5.setText(_translate("Dialog", "Location"))
        self.pushButton.setText(_translate("Dialog", "Enter"))

