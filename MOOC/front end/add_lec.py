# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'add_lec.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene

class Ui_Dialog_add_lec(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
        
    def insert_lec(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        a=self.lineEdit.text()
        cur.execute("select check_lecturer_username(%s);",[a])
        x=cur.fetchall()
        conn.close()
        if(x[0][0]==1):
            self.lineEdit.clear()
            print("Enter different lecturer username")
        else:
            print("lecturer username available")
            conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
            cur=conn.cursor()
            a=self.lineEdit.text()
            b=self.lineEdit_2.text()
            c=self.lineEdit_3.text()
            d=self.lineEdit_4.text()
            cur.execute("insert into lecturer values(%s,%s,%s,%s,%s);",(c,d,a,b,self.user))
            conn.commit()
            conn.close()
            self.lineEdit.clear()
            self.lineEdit_2.clear()
            self.lineEdit_3.clear()
            self.lineEdit_4.clear()
    
    def check(self):
        if(len(self.lineEdit.text())!=0 and len(self.lineEdit_2.text())!=0 and len(self.lineEdit_3.text())!=0 and len(self.lineEdit_4.text())!=0):
            self.insert_lec()
        else:
            print("enter all values")
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('3.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.lineEdit = QtWidgets.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(30, 60, 381, 31))
        self.lineEdit.setObjectName("lineEdit")
        
        self.lineEdit_2 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_2.setGeometry(QtCore.QRect(30, 140, 381, 31))
        self.lineEdit_2.setObjectName("lineEdit_2")
        
        self.lineEdit_3 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_3.setGeometry(QtCore.QRect(30, 220, 381, 31))
        self.lineEdit_3.setObjectName("lineEdit_3")
        
        self.lineEdit_4 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_4.setGeometry(QtCore.QRect(30, 300, 381, 31))
        self.lineEdit_4.setObjectName("lineEdit_4")
        
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(30, 30, 141, 31))
        self.label.setObjectName("label")
        
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(30, 110, 121, 31))
        self.label_2.setObjectName("label_2")
        
        self.label_3 = QtWidgets.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(30, 190, 91, 31))
        self.label_3.setObjectName("label_3")
        
        self.label_4 = QtWidgets.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(30, 270, 101, 31))
        self.label_4.setObjectName("label_4")
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(430, 380, 141, 51))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.check)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name+"-ADD LECTURER"))
        self.label.setText(_translate("Dialog", "User Name"))
        self.label_2.setText(_translate("Dialog", "Password"))
        self.label_3.setText(_translate("Dialog", "First Name"))
        self.label_4.setText(_translate("Dialog", "Last Name"))
        self.pushButton.setText(_translate("Dialog", "Enter"))

