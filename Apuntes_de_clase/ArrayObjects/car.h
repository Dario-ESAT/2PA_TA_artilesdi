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

  void init(int doors, float gas);
  void init(float gas);
  void init();
  
  
  void virtual openDoors();
  void closeDoors();
};

#endif