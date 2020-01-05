# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'course_details.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtGui import QPixmap
from PyQt5.QtWidgets import QGraphicsScene

class Ui_Dialog_lecturer_disp(object):
    def __init__(self, user, name):
        self.user=user
        self.name=name
    
    def load_data(self):
        import psycopg2
        conn = psycopg2.connect(database = "postgres", user = "postgres", password = "mukund", host = "127.0.0.1", port = "5432")
        cur=conn.cursor()
        cur.execute("select disp_lecturers();")
        c = conn.cursor('cursor1')
        x=c.fetchall()
        self.tableWidget.setRowCount(0)
        self.tableWidget.insertRow(0)
        header=['USER_NAME','FIRST_NAME','LAST_NAME','ADMIN_ID','COURSE_ID','COURSE_NAME']
        for col_num in range(6):
            self.tableWidget.setItem(0,col_num,QtWidgets.QTableWidgetItem(str(header[col_num])))
        for row_num,row_data in enumerate(x):
            self.tableWidget.insertRow(row_num+1)
            for col_num,data in enumerate(row_data):
                self.tableWidget.setItem(row_num+1,col_num,QtWidgets.QTableWidgetItem(str(data)))
        conn.close()
    
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(640, 480)
        
        self.tableWidget = QtWidgets.QTableWidget(Dialog)
        self.tableWidget.horizontalHeader().setVisible(False)
        self.tableWidget.verticalHeader().setVisible(False)
        self.tableWidget.setGeometry(QtCore.QRect(20, 40, 601, 311))
        self.tableWidget.setRowCount(5)
        self.tableWidget.setColumnCount(6)
        self.tableWidget.setObjectName("tableWidget")
        #header=QtCore.QStringList()
        #header.append()
        #self.tableWidget.setHorizontalHeaderLabels(('Name','description','commitment','course_price','min_grade','lecturer'))﻿
        
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(261, 373, 121, 51))
        self.pushButton.setObjectName("pushButton")
        self.pushButton.clicked.connect(self.load_data)

        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", self.name+"-LECTURERS"))
        self.pushButton.setText(_translate("Dialog", "Load"))

