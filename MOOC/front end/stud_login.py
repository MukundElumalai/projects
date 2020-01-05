# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'admin_login.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene
from stud_main import Ui_Dialog_student_main
from register import Ui_Dialog_student_register

class Ui_Dialog_student(object):
    def move_to_stud(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        a=self.lineEdit.text()
        b=self.lineEdit_2.text()
        cur.execute("select student_login(%s,%s);",(a,b))
        c = conn.cursor('cursor1')
        x=c.fetchall()
        conn.close()
        if(len(x)==0):
            self.lineEdit.clear()
            self.lineEdit_2.clear()
        else:
            self.window=QtWidgets.QMainWindow()
            self.ui=Ui_Dialog_student_main(a,x[0][0]+' '+x[0][1])
            self.ui.setupUi(self.window)
            self.window.show()
        
    def check(self):
        if(len(self.lineEdit.text())!=0 and len(self.lineEdit_2.text())!=0):
            self.move_to_stud()
            self.lineEdit.clear()
            self.lineEdit_2.clear()
        else:
            self.lineEdit.clear()
            self.lineEdit_2.clear()
    
    def register(self):
        self.window=QtWidgets.QMainWindow()
        self.ui=Ui_Dialog_student_register()
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
        self.lineEdit = QtWidgets.QLineEdit(Dialog)
        self.lineEdit.setGeometry(QtCore.QRect(150, 110, 311, 31))
        self.lineEdit.setInputMask("")
        self.lineEdit.setText("")
        self.lineEdit.setObjectName("lineEdit")
        self.lineEdit_2 = QtWidgets.QLineEdit(Dialog)
        self.lineEdit_2.setGeometry(QtCore.QRect(150, 230, 311, 31))
        self.lineEdit_2.setObjectName("lineEdit_2")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(150, 78, 151, 21))
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(150, 190, 121, 31))
        self.label_2.setObjectName("label_2")
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(350, 300, 112, 34))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.check)
        
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(350, 370, 112, 34))
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_2.clicked.connect(self.register)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "STUDENT"))
        self.label.setText(_translate("Dialog", "User Name"))
        self.label_2.setText(_translate("Dialog", "Password"))
        self.pushButton.setText(_translate("Dialog", "Enter"))
        self.pushButton_2.setText(_translate("Dialog", "Register"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dialog = QtWidgets.QDialog()
    ui = Ui_Dialog_student()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())