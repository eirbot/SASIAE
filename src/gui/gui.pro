######################################################################
# Automatically generated by qmake (3.0) dim. f�vr. 16 11:48:39 2014
######################################################################

TEMPLATE = app
TARGET = gui
DESTDIR = ../../build/
INCLUDEPATH += . \
/usr/local/include/bullet \
/usr/include/bullet \
/usr/include/bullet/Glut/GL \
../../../aversive--/include/sasiae \
../ \


QMAKE_CFLAGS = -Wno-unused-parameter
QMAKE_CFLAGS = -Wno-ignored-qualifiers
QMAKE_CFLAGS = -Wno-unused-variable

QT += widgets
QT += xml
QT += xmlpatterns

QMAKE_CXXFLAGS = -std=c++11
LIBS += -L/usr/local/include/bullet/HACD -lHACD -L/usr/local/lib -lBulletDynamics -L/usr/local/lib -lBulletCollision
LIBS += -L/usr/local/lib -lLinearMath -lglut -lGLU -lQt5XmlPatterns

#LIBPATH += ../../../bullet-2.81-rev2613/Extras/HACD/
LIBPATH += ../HACD/

# Input
HEADERS += mainwindow.h \
#    item_robot.h \ 
    ../common/object_config.hpp \
    ../common/position_data.hpp \
    posdialog.h

HEADERS += ../coordinator/coordinator.hpp \
    ../coordinator/physical_coordinator.hpp \
    ../coordinator/robot_coordinator.hpp \
    ../coordinator/module_coordinator.hpp \
    ../coordinator/schedule_coordinator.hpp \
    ../coordinator/base_coordinator.hpp \
    ../coordinator/gui_coordinator.hpp \
    ../coordinator/config_robot_coordinator.hpp \

HEADERS +=   ../xml_parser/xml_parser.hpp

HEADERS += ../physical_calculator/physical_calculator.hpp \
    ../physical_calculator/robot.hpp \
    ../physical_calculator/wheel.hpp \
    ../physical_calculator/printable_mobile_object.hpp \
    ../physical_calculator/position_data_bullet.hpp \
    ../physical_calculator/stlmesh.hpp \
    ../physical_calculator/mesh.hpp \
    ../physical_calculator/dist_sensor.hpp \
    ../physical_calculator/balise.hpp \
    ../physical_calculator/world.hpp

HEADERS += ../modules/module.hpp \
#    ../modules/servo.hpp \
#    ../modules/encoder.hpp \
#    ../modules/motor_wheel.hpp

HEADERS += ../stl/STLReader.hpp


FORMS += mainwindow.ui \
    posdialog.ui

SOURCES += main.cpp mainwindow.cpp \
#    item_robot.cpp \
    ../common/object_config.cpp \
    ../common/position_data.cpp \
    posdialog.cpp

SOURCES += ../coordinator/coordinator.cpp \
    ../coordinator/physical_coordinator.cpp \
    ../coordinator/robot_coordinator.cpp \
    ../coordinator/module_coordinator.cpp \
    ../coordinator/schedule_coordinator.cpp \
    ../coordinator/config_robot_coordinator.cpp \
    ../coordinator/gui_coordinator.cpp

SOURCES +=   ../xml_parser/xml_parser.cpp

SOURCES += ../physical_calculator/physical_calculator.cpp \
    ../physical_calculator/robot.cpp \
    ../physical_calculator/wheel.cpp \
    ../physical_calculator/printable_mobile_object.cpp \
    ../physical_calculator/stlmesh.cpp \
    ../physical_calculator/mesh.cpp \
    ../physical_calculator/world.cpp \
    ../physical_calculator/dist_sensor.cpp \
    ../physical_calculator/balise.cpp \
    ../physical_calculator/position_data_bullet.cpp

#SOURCES += ../modules/motor_wheel.cpp \
#    ../modules/servo.cpp \
#    ../modules/encoder.cpp

SOURCES +=   ../stl/STLReader.cpp

#OTHER_FILES += \
#    ../coordinator/xml_parser/Makefile

RESOURCES += ../../ressources/xsd.qrc

# The following keeps the generated files at least somewhat separate 
# from the source files.
UI_DIR = uics
MOC_DIR = mocs
OBJECTS_DIR = objs
