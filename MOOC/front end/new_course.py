# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'course_enter.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene

class Ui_Dialog_add_course(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
        
    def insert_course(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        a=self.lineEdit_6.text()
        cur.execute("select check_lecturer(%s);",[a])
        x=cur.fetchall()
        conn.close()
        if(x[0][0]==0):
            self.lineEdit_6.clear()
            print("Enter correct lecturer username")
        else:
            print("lecturer found")
            conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
            cur=conn.cursor()
            a=self.lineEdit.text()
            b=self.lineEdit_2.text()
            c=self.lineEdit_3.text()
            d=self.lineEdit_4.text()
            e=self.lineEdit_5.text()
            f=self.lineEdit_6.text()
            cur.execute("select count(*)+1 from course;")
            x=cur.fetchall()
            cnt=int(x[0][0])
            cur.execute("insert into course values(%s,%s,%s,%s,%s,%s);",(cnt,a,c,b,e,d))
            conn.commit()
            cur.execute("insert into course_created_by values(%s,%s);",(self.user,cnt))
            conn.commit()
            cur.execute("insert into on_course values(%s,%s);",(f,cnt))
            conn.commit();
            conn.close()
            self.lineEdit.clear()
            self.lineEdit_2.clear()
            self.lineEdit_3.clear()
            self.lineEdit_4.clear()
            self.lineEdit_5.clear()
            self.lineEdit_6.clear()
            
        
    def check(self):
        if(len(self.lineEdit.text())!=0 and len(self.lineEdit_2.text())!=0 and len(self.lineEdit_3.text())!=0 and len(self.lineEdit_4.text())!=0 and len(self.lineEdit_5.text())!=0 and len(self.lineEdit_6.text())!=0):
            self.insert_course()
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
        self.lineEdit.setGeometry(QtCore.QRect(30, 40, 400, 31))
        self.lineEdit.setObjectName("lineEdit")
        
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(30, 10, 111, 21))
        self.label.setObjectName("label")
        
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(30, 80, 331, 21))
        self.label_2.setObjectName("label_2")
        
        self.lineEdit_2 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_2.setGeometry(QtCore.QRect(30, 110, 400, 31))
        self.lineEdit_2.setObjectName("lineEdit_2")
        
        self.label_3 = QtWidgets.QLabel(Dialog)
        self.label_3.setGeometry(QtCore.QRect(30, 150, 361, 21))
        self.label_3.setObjectName("label_3")
        
        self.lineEdit_3 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_3.setGeometry(QtCore.QRect(30, 180, 400, 31))
        self.lineEdit_3.setObjectName("lineEdit_3")
        
        self.label_4 = QtWidgets.QLabel(Dialog)
        self.label_4.setGeometry(QtCore.QRect(30, 220, 121, 21))
        self.label_4.setObjectName("label_4")
        
        self.lineEdit_4 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_4.setGeometry(QtCore.QRect(30, 250, 400, 31))
        self.lineEdit_4.setObjectName("lineEdit_4")
        
        self.label_5 = QtWidgets.QLabel(Dialog)
        self.label_5.setGeometry(QtCore.QRect(30, 290, 361, 21))
        self.label_5.setObjectName("label_5")
        
        self.lineEdit_5 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_5.setGeometry(QtCore.QRect(30, 320, 400, 31))
        self.lineEdit_5.setObjectName("lineEdit_5")
        
        self.label_6 = QtWidgets.QLabel(Dialog)
        self.label_6.setGeometry(QtCore.QRect(30, 360, 361, 21))
        self.label_6.setObjectName("label_6")
        
        self.lineEdit_6 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_6.setGeometry(QtCore.QRect(30, 390, 400, 31))
        self.lineEdit_6.setObjectName("lineEdit_6")
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(450, 400, 141, 51))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.check)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name+"-ADD COURSE"))
        self.label.setText(_translate("Dialog", "Course Name"))
        self.label_2.setText(_translate("Dialog", "Description"))
        self.label_3.setText(_translate("Dialog", "Commitment"))
        self.label_4.setText(_translate("Dialog", "Minimum Grade"))
        self.label_5.setText(_translate("Dialog", "Course Price"))
        self.label_6.setText(_translate("Dialog", "Lecturer username"))
        self.pushButton.setText(_translate("Dialog", "Enter"))

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog_add_course("mukund_nf","Mukund Elumalai")
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())

