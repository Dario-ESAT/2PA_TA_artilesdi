#ifndef __CAR_H__
#define __CAR_H__ 1

#include "vehiclebase.h"

class Car : public VehicleBase{
public:
  int doors_;
  bool open_;
  Car();
  Car(const Car& c);
  ~Car();

  void Innit(int doors, float gas);
  void Innit(float gas);
  void Innit();
  
  
  void virtual openDoors();
  void closeDoors();
};

#endif