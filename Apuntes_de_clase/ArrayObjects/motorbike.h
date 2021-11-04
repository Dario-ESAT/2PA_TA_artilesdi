#ifndef __MOTORBIKE_H__
#define __MOTORBIKE_H__ 1

#include "vehiclebase.h"
class MotorBike : public VehicleBase {
public:
  MotorBike();
  MotorBike(const MotorBike& mb);
  ~MotorBike();
  
  void init(float gas);
  void init();
  
  void plantFoot(bool f);

  bool planted_;
};

#endif