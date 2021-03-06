#ifndef SCHEDULE_COORDINATOR_HPP
#define SCHEDULE_COORDINATOR_HPP

#include "base_coordinator.hpp"

#include <QList>

class ScheduleCoordinator : public BaseCoordinator {
  Q_OBJECT;

public slots:
  //! \brief Needed to be instantiated
  void update(void);
  void play(void);
  void pause(void);
  void capSpeed();

public:
  //!\brief Constructor
  ScheduleCoordinator(void);
  
  //!\brief Destructor
  ~ScheduleCoordinator(void);
  
  //! \brief Add a new coordinator
  void addCoordinator(BaseCoordinator*);

private:
  QList<BaseCoordinator*> _coords;
  bool _running;
  int _step;
};

#endif//SCHEDULE_COORDINATOR_HPP
