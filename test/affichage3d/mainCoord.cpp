/*
Bullet Continuous Collision Detection and Physics Library
Copyright (c) 2003-2007 Erwin Coumans  http://continuousphysics.com/Bullet/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/


#include "test3dCoordinator.hpp"
//#include "test3d.hpp"
#include "bullets3D/GlutStuff.h"
#include <btBulletDynamicsCommon.h>
#include <LinearMath/btHashMap.h>
#include<cstdio>

//! \warning you have to defines theses vars else where...
extern int myargc;
extern char** myargv;

int main(int argc,char** argv)
{
  myargc = argc;
  myargv = argv;

  BasicDemo ccdDemo;
  fprintf(stderr,"after declaration");
  ccdDemo.myinit();
  ccdDemo.initPhysics();


  return glutmain(argc, argv,1024,600,"Bullet Physics Demo. http://bulletphysics.org",&ccdDemo);
	
  //default glut doesn't return from mainloop
  return 0;
}

