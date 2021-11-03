#ifndef __MOTORBIKE_H__
#define __MOTORBIKE_H__ 1

#include "vehiclebase.h"
class MotorBike : public VehicleBase {
public:
  MotorBike();
  MotorBike(const MotorBike& mb);
  ~MotorBike();
  
  void Innit(float gas);
  void Innit();
  
  void plantFoot(bool f);

  bool planted_;
};

#endif