#ifndef __BALISE_H__
#define __BALISE_H__

#include "robot.hpp"
#include "physical_calculator.hpp"
#include "position_data_bullet.hpp"
#include "world.hpp"
#include "mesh.hpp"

#include <QObject>
#include <QString>
#include <QList>
#include <QStandardItem>
#include <btBulletDynamicsCommon.h>


class Balise {
public:
  Balise(World world, Robot* chassis);
  PositionData getPosition();
  static QList<Balise*> listBalise();

private:
  Robot* _chassis;
	Mesh* _sensor_box;
  static QList<Balise*> _list;
};


#endif
