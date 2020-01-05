# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'setmark.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene

class Ui_Dialog_setmark(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
        
    def set_mark(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        a=self.lineEdit.text()
        cur.execute("select check_setmark(%s);",[a])
        x=cur.fetchall()
        conn.close()
        if(x[0][0]==0):
            self.lineEdit.clear()
            print("Enter correct student username")
        else:
            print("student username correct")
            conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
            cur=conn.cursor()
            a=self.lineEdit.text()
            b=self.lineEdit_2.text()
            cur.execute("update enrolled_course set status=%s,final_grade=%s where enrolled_course.id=%s;",("completed",b,a))
            conn.commit()
            conn.close()
            self.lineEdit.clear()
            self.lineEdit_2.clear()
    
    def check(self):
        if(len(self.lineEdit.text())!=0 and len(self.lineEdit_2.text())!=0):
            self.set_mark()
        else:
            print("enter all values")
        
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.graphicsView = QtWidgets.QGraphicsView(Dialog)
        self.graphicsView.setGeometry(QtCore.QRect(0, 0, 640, 480))
        self.scene=QGraphicsScene()
        self.scene.addPixmap(QPixmap('5.jpeg'))
        self.graphicsView.setScene(self.scene)
        self.graphicsView.setObjectName("graphicsView")
        
        self.lineEdit = QtWidgets.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(70, 90, 331, 31))
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_2.setGeometry(QtCore.QRect(70, 210, 331, 31))
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(70, 50, 161, 31))
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(70, 180, 131, 21))
        self.label_2.setObjectName("label_2")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(330, 290, 131, 61))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.check)


        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name+"-SET MARK"))
        self.label.setText(_translate("Dialog", "enrolled_course_id"))
        self.label_2.setText(_translate("Dialog", "Mark"))
        self.pushButton.setText(_translate("Dialog", "Enter"))

