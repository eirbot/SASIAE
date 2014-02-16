#include "coordinator.hpp"
#include "mainwindow.h"
#include "../modules/servo.hpp"


Coordinator* Coordinator::_instance=NULL;


Coordinator& Coordinator::getInstance() {
  if(Coordinator::_instance)
    return *Coordinator::_instance;
  else
    return *(Coordinator::_instance = new Coordinator()); 
}

Coordinator::Coordinator() : _physic(this), _gui(this){
  _running = false;
  _codeFactor = 1;
  _sync = 1;
  _codeFactor = 1;
  _timeStep = 1./120.;
  _maxSubStep = 20;
  connect(this, SIGNAL(GUISend(QString)), ,)
  connect(this, SIGNAL(calcNextStep(double,int)), &_physic, SLOT(nextStep(double,int)));
}

Coordinator::~Coordinator(){
  QHash<QString, QProcess*>::iterator j;
  _codeInfo.squeeze();
  for (j = _codeInfo.begin(); j != _codeInfo.end(); ++j){
    closeRobot(j.value());
    j.value()=NULL;
  }
}


void Coordinator::play() {
  _running = true;
  if(_sync > _codeInfo.size())
    gotoNextStep();
}

void Coordinator::pause() {
  _running = false;
}

void Coordinator::stepDone() {
  if(++_sync > _codeInfo.size()) // all codeInfo.are sync, calculator was the last one
    {
      gotoNextStep();
    }
}

void Coordinator::openTable(const QString& XMLPath) {
  //TODO really read the file
  (void) XMLPath;
}
void Coordinator::openRobot(const QString& XMLPath, Coordinator::Slot slot) {

  (void) slot;
  /* For the tests*/
 
  Modules *mod =new Servo(0);
  QString code=XMLPath;
  QString name("TESTER");

  //TODO really read the file  
  //Don't forget to join robotCodeName and moduleName for addModule.

  qDebug() << "code +name"<< code + name << '\n' ;

  if(!addModule(code+name,mod)){
    qDebug() << "error addToRobotModule" << '\n' ;
    return;
  }

  QProcess* proc=new QProcess(this);
  
  if(!addToRobotCode(code,proc)){
    qDebug() << "error addToRobotCode" << '\n' ;
    return;
  }

  if(!addModuleAndCodeName(mod, code, name )){
    qDebug() << "error addModuleAndCodeName" << '\n' ;
    return;
  }

  /*The coordinator launches the processus robot which launches the ClientThread.*/
  proc->start("./client",QStringList());

  if(!proc->waitForStarted()) {
    qDebug() << "error starting client process" << '\n' ;
    return ;
  }
   
  qDebug() << "connecting signal..." << '\n' ;
  QObject::connect(proc,SIGNAL(readyRead()),this,SLOT(CTReceived()));
  qDebug() << "signal connected" << '\n' ;
}


void Coordinator::CTReceived() {
  /* A terme le nom du code robot qui envoie le message
     est récupéré */

  
  /**/
  if(NULL==sender()) {
    qDebug() << "sender null in CTReceived";
    return ;
  } 
  QProcess * client=sender();//=_codeInfo.value(code);
  QString code=_codeInfo.key(client);
  
  QString message=readMessage(client);
  QStringList args=message.split(" ");
  QString name;
  name=args[1];

  switch((args[0].toStdString())[0]){
  case('D'):
    Modules * mod;
    name =code+name;
    qDebug() << "name : " << name ;

    if(_moduleFromName.contains(name)){
      mod=_moduleFromName.value(name);
      args.removeFirst(); // remove destination
      args.removeFirst(); // remove name
      qDebug()<< "Message (" << args.join(" ") << ")send to module "<< mod << " named " <<  _moduleFromName.key(mod) << '\n';
    }
    else{
      mod=NULL;
      qDebug()<<"This device's name does not correspond to a module."  << '\n';
    }
    break;
  case('T'):
    if(++_sync>_codeInfo.size()) // all modules are synchronised
      gotoNextStep();

    break;
  case('M'):
    args.removeFirst();
    qDebug() << "message to GUI : " << args.join(" ") << '\n';
    emit(GUISend(args.join(" ")));
    break;
    // verif du bon etat du message ?
  default:
    ;
  }
}


void Coordinator::MReceived(QString message) {
  if(sender() != 0) 
    {
      //find which modules send the message
      if(_moduleInfo.contains(sender()))
  	{
  	  QString code = _moduleInfo.value(sender()).first;
  	  QString module = _moduleInfo.value(sender()).second;
  	  sendDeviceMessage(module, message, code); 
	  
	}
      else 
	qDebug() << "module does not exist";
    }
}

void Coordinator::gotoNextStep() {
  if(_running) 
    {
      _sync = 0;
      sendSyncMessages(); 
    }
}

void Coordinator::sendDeviceMessage(QString name, QString msg, QString code) {
  if(_codeInfo.contains(code))
    sendDeviceMessage(name, msg, _codeInfo.value(code));
  else 
    qDebug() << "error sendDeviceMessage : robot code name unknown";
}

void Coordinator::sendDeviceMessage(QString name, QString msg, QProcess* p) {
  sendMessages(QString("D ") + name + " " + msg + "\n", p);
}

void Coordinator::sendMessages(QString msg, QProcess* p) {
  p->write(msg.toUtf8());
}

 
void Coordinator::closeRobot(Slot robot){
  QString robotName=_robotInfo.value(robot);
  QProcess * robotProcess=_codeInfo.value(robotName);
  closeRobot(robotProcess);
}

void Coordinator::closeRobot(QProcess *robot){
  robot->closeWriteChannel();
  if(!robot->waitForFinished()) {
    qDebug() << "error waitForFinished closeRobot" << '\n';
    return ;
  }
  delete robot;  
}


QString Coordinator::readMessage(QProcess * proc)const{
  char c;

  //TODO utiliser QBuffer au lieu de QString !
  QString buffer(COORD_BUFFER_SIZE);
  /*
    Attention source de bug : 
    Si le message ne contient pas de saut de ligne 
    le message n'est pas transmis et le processus est tué.
    Cela peut arriver si un message est lu avant d'être 
    entièrement écrit.
  */
  
  if(!proc->getChar(&c)) {
    proc->waitForReadyRead();
  }
  else {
    qDebug() << c << "char before reading \n";
    buffer = c;
  }
  while(proc->getChar(&c) && c != '\n') {
    buffer += c;
  }
  if(c == '\n') {
    qDebug() << buffer << "message before sending\n";
    return buffer;
  }
  else {
    proc->kill();
    proc->waitForFinished();
    return "Process killed";
  }
}

bool Coordinator::addToRobotCode(QString name, QProcess * proc){
  _codeInfo.insert(name,proc);
  return (_codeInfo.value(name)==proc);
}

bool Coordinator::addModuleAndCodeName(Modules * key, QString code, QString module ){
  QPair<QString,QString> p(code,module);
  _moduleInfo.insert(key,p);
  
  return (_moduleInfo.contains(key));
}


bool Coordinator::addModule(QString name, Modules * mod){
  _moduleFromName.insert(name,mod);
  
  return (_moduleFromName.contains(name));
}

void Coordinator::sendSyncMessages() {
  //sync UI time
  emit(timer(_physic.getTime()));
  foreach(QProcess* code, _codeInfo) {
    sendMessages(QString("T ") + _physic.getTime() + " " + _codeFactor, code);
  }
  emit(calcNextStep(_timeStep,_maxSubStep));
  
}
