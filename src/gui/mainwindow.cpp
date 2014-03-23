#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget* parent):
  QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow constructor";
    _model = new QStandardItemModel(0,2,this);
    ui->setupUi(this);
    ui->treeView->setModel(_model);
    connect(ui->actionChoisir,SIGNAL(triggered()),this,SLOT(openDirForTable()));
    connect(ui->actionRobot_new_1,SIGNAL(triggered()),this,SLOT(openDirForRobot()));
    connect(ui->button_play,SIGNAL(clicked()),this,SLOT(slotPlay()));
    connect(ui->button_pause,SIGNAL(clicked()),this,SLOT(slotPause()));
  //Ui_MainWindow::setupUi(this);
//        QObject::connect(button_robot1, SIGNAL(clicked()), qApp, SLOT(quit()));
  
  //QObject::connect(button_robot1, SIGNAL(clicked()), this, SLOT(do_sth()));
}

MainWindow::~MainWindow()
{
    emit uiPause();
    delete ui;
}
void MainWindow::addRobot(QStandardItem* item) {
  _model->appendRow(item);
}
/*
 * Ancient version
void MainWindow::animateRobot(qreal x,qreal y){
    qDebug() << "MainWindow::animateRobot";
    ui->graphicsView->moveRobot(x,y);
    ui->graphicsView->moveRobot();
}
*/

QTimeLine *MainWindow::getTimer()const{
 return   ui->graphicsView->timer;
}

void MainWindow::do_sth()
{
    std::cout<<"signal envoyé"<< std::endl;

    /*plainTextEdit->setPlainText(QApplication::translate("MainWindow", "lol", 0, QApplication::UnicodeUTF8)); */
}

void MainWindow::slotPlay() {
    emit uiPlay();
}
void MainWindow::slotPause() {
    emit uiPause();
}

void MainWindow::wantClose() {
    emit uiPause();
    emit close();
}
/* 
   Function for integration's tests
 */
void MainWindow::CReceived(QString message){
  qDebug() << "Message received from Coordinator to GUI : " << message ;
}

  void MainWindow::openDirForTable(){
      const QString fileName = QFileDialog::getOpenFileName(this,
          "Open Xml file", "./", "Config Files (*.xml)");
      qDebug() << "MainWindow emit tableFileStl(" <<fileName << ") to ";
      emit tableFileXml(fileName);
     }


  void MainWindow::openDirForRobot(){
      QString fileName = QFileDialog::getOpenFileName(this,
          "Open Xml file", "./", "Config Files (*.xml)");

      QString name=("Robotname"); // todo : ask user
      emit robotFileXml(name,fileName);
     }

  const QGraphicsScene* MainWindow::getScene(void)const{
    return ui->graphicsView->scene();
  }
  QGraphicsScene* MainWindow::getScene(void)
  {
    return ui->graphicsView->scene();
  }
