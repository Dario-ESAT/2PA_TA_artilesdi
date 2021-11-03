#ifndef __PLANE_H__
#define __PLANE_H__ 1
#include "car.h"

class Plane : public Car{
public:
  Plane();
  Plane(const Plane& p);
  ~Plane();
  
  void Innit(int doors, float gas);
  void Innit(float gas);
  void Innit();

  void openDoors();
  void pullGear();
  void lowerGear();

  bool gear_;
};

#endif