#ifndef __VEHICLEBASE_H__
#define __VEHICLEBASE_H__ 1

class VehicleBase {

public:
  VehicleBase();
  VehicleBase(const VehicleBase& vb);
  ~VehicleBase();

  void refuelGas(int g);
  void consumeGas(int g);

  float gas_;
};


#endif