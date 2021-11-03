#include <stdio.h>
#include "vehiclebase.h"

void VehicleBase::refuelGas ( int g ) {
  gas_ = gas_ + g;
}

void VehicleBase::consumeGas ( int g ) {
  gas_ = gas_ - g;
}

VehicleBase::VehicleBase() {
  gas_ = 0;
}

VehicleBase::VehicleBase(const VehicleBase& vb) {
  gas_ = vb.gas_;
}

VehicleBase::~VehicleBase() {
  printf("Deleting VehicleBase-------\n");
}