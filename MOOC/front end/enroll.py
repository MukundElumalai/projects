# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'enroll.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene

class Ui_Dialog_enroll(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
    
    def enroll_course(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        a=self.lineEdit.text()
        cur.execute("select check_course(%s,%s);",(a,self.user))
        x=cur.fetchall()
        conn.close()
        if(x[0][0]==1):
            self.lineEdit.clear()
            print("Enter correct course id")
        else:
            print("course found")
            conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
            cur=conn.cursor()
            a=self.lineEdit.text()
            cur.execute("select count(*)+1 from enrolled_course;")
            x=cur.fetchall()
            cnt=int(x[0][0])
            cur.execute("insert into enrolled_course(id,student_id,course_id,status) values(%s,%s,%s,%s);",(cnt,self.user,a,"studying"))
            conn.commit()
            conn.close()
            self.lineEdit.clear()
        
    def check(self):
        if(len(self.lineEdit.text())!=0):
            import psycopg2
            conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
            cur=conn.cursor()
            a=self.lineEdit.text()
            cur.execute("select check_course1(%s);",[a])
            x=cur.fetchall()
            conn.close()
            if(x[0][0]==0):
                self.lineEdit.clear()
                print("Enter correct course id")
            else:
                self.enroll_course()
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
        self.lineEdit.setGeometry(QtCore.QRect(50, 110, 361, 31))
        self.lineEdit.setObjectName("lineEdit")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(50, 70, 111, 31))
        self.label.setObjectName("label")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(290, 180, 121, 41))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.check)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name+"-ENROLL"))
        self.label.setText(_translate("Dialog", "CourseID"))
        self.pushButton.setText(_translate("Dialog", "Enter"))

