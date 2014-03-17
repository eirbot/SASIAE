/*
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QtWidgets/QApplication>
*/
#include <iostream>
#include <QDebug>

#include "../coordinator/coordinator.hpp"


int main(int argc, char* argv[])
{
    std::cout << "Creation de l'application..." << std::endl;
    Coordinator * cdn=& Coordinator::getInstance(argc, argv);
/*
  std::cout << "Creation de l'application..." << std::endl;
  QApplication app(argc, argv);
*/

  std::cout << "Chargement des robots et de la table..." << std::endl;
  //cdn->openTable("coucou");
  cdn->openRobot("",Coordinator::MAIN_ROBOT1);

  QTimer *timerUpdate = new QTimer(cdn);

  qDebug() << "connect and start timer";
  cdn->startUpdateTimer(timerUpdate);

  std::cout << "Boucle principale..." << std::endl;
  cdn->exec();


  /*
  std::cout << "Creation de la fenetre principale..." << std::endl;
  MainWindow mainwindow;
  //mainwindow.animate();
  mainwindow.show();
  mainwindow.getTimer()->start();

  std::cout << "Boucle principale..." << std::endl;
  app.exec();
  std::cout << "Fin de l'application..." << std::endl;
*/
  return 0;

}


