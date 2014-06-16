#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <btBulletDynamicsCommon.h>
#include "printable_mobile_object.hpp"
#include "world.hpp"
#include "mesh.hpp"

class Robot :  public PrintableMobileObject, public btRaycastVehicle {
private:
  btRaycastVehicle::btVehicleTuning _tuning;
  static Robot* _r;
  //rajouter la balise
public:

  Robot(World& world, const ObjectConfig::meshConfig& cfg, float mass, PositionData start_pos);
  static Robot* getRobot();
  ~Robot();

  /* This function is called in Wheel::init().
   * In order to put a wheel on a robot, you must 
   * call Wheel::init() or call 
   * Wheel::Wheel(Robot*, btVector3, btVector3, btScalar, bool);
   */
  btWheelInfo& addWheel (const btVector3 &connectionPointCS0,
			 const btVector3 &wheelDirectionCS0,
			 const btVector3 &wheelAxleCS,
			 btScalar wheelRadius,
			 bool isFrontWheel);
};
#endif //ROBOT_HPP
