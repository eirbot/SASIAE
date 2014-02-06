#include "coordinator.hpp"


Coordinator* Coordinator::_instance=NULL;


Coordinator& Coordinator::getInstance() {
  if(Coordinator::_instance)
    return *Coordinator::_instance;
  else
    return *(Coordinator::_instance = new Coordinator()); 
}

Coordinator::Coordinator() : _physic(this){
  _running = false;
  _codeFactor = 1;
  _sync = 1;
  _codeFactor = 1;
  _timeStep = 1./120.;
  _maxSubStep = 20;
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
  //TODO really read the file
 (void) slot;
  /* For the tests*/
 
  Modules *mod =new Servo(0);
  QString name(XMLPath);
    if(!addToRobotModule("TESTER",mod)){
    qDebug() << "error addToRobotModule" << '\n' ;
    return;
  }

  QProcess* proc=new QProcess(this);
  
  if(!addToRobotCode(name,proc)){
    qDebug() << "error addToRobotCode" << '\n' ;
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
  QProcess * client=_codeInfo.value("client");
  QString message=readMessage(client);
  if(client !=NULL) qDebug() << "message Client : " << message << '\n' ;
  QStringList args=message.split(" ");
  QString name;
  name=args[1];
  int i;
  for(i=0;i<args.length();i++){
    qDebug() << "args["<<i<<"] : "<< args[i] << '\n' ;
  }
  Modules * mod;
  qDebug() << "name : " << name ;
  if(_moduleInfo.contains(name)){
    mod=_moduleInfo.value(name);
    qDebug()<< "module name : " << mod << '\n';
    // the message is set to the corresponding module
    //std::cout << args[2] <<" envoyé au module " << name << std::endl;
    // Trouver un moyen de concaténer la chaine du message join ?
    //emit mod::sendMessage(args[2].join(" "));
    // savoir qui a emit le signal QObject
    // verif du bon etat du message ?
  }
  else{
    mod=NULL;
    qDebug()<<"This device's name does not correspond to a module."  << '\n';
  }
}
void Coordinator::MReceived(QString message) {
  (void) message;
  // if(sender() != 0) // shouldn't be directly called
  //   {
  //     //find which modules send the message
  //     if(_moduleInfo.contains(sender()))
  // 	{
  // 	  QString code = _codeInfo.value(sender()).first;
  // 	  QString module = _moduleInfo.value(sender()).second;
  // 	  sendDeviceMessage(module, message, code); 
  // 	}
  //   }
}


void Coordinator::gotoNextStep() {
  if(_running) 
  {
    _sync = 0;
    sendSyncMessages(); //a decommenter une fois la fonction debuguée ELLE A JAMAIS ETE BUGGE CONTRAIREMNT A DES OBGJET DANS DES COMMITS !
  }
}

void Coordinator::sendDeviceMessage(QString name, QString msg, QString code) {
  if(_codeInfo.contains(code))
    sendDeviceMessage(name, msg, _codeInfo.value(code));
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
  unsigned int i = 0;
  char c;

  //TODO utiliser QBuffer au lieu de QString !
  QString buffer(COORD_BUFFER_SIZE);

  
  if(!proc->getChar(&c)) {
    proc->waitForReadyRead();
  }
  else {
    buffer = c;
  }
  while(proc->getChar(&c) && c != '\n') {
    buffer += c;
  }
  if(c == '\n') {
    qDebug() << buffer << "just before sending\n";
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

bool Coordinator::addToRobotModule(QString name, Modules * mod){
  _moduleInfo.insert(name,mod);
  
  return (_moduleInfo.contains(name));
}

void Coordinator::sendSyncMessages() {
  /*  //sync UI time
  emit(timer(_physic.getTime()));
  foreach(QProcess* code, _codeInfo) {
    sendMessages(QString("T ") + _physic.getTime() + " " + _codeFactor, code);
  }
  emit(calcNextStep(_timeStep,_maxSubStep));
  */
}