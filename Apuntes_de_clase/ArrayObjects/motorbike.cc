#include <stdio.h>
#include "motorbike.h"

void MotorBike::init(float gas){
  gas_ = gas;
  planted_ = true;
}

void MotorBike::init(){
  gas_ = 0;
  planted_ = true;
}

void MotorBike::plantFoot(bool f) {
  planted_ = f;
}

MotorBike::MotorBike() {
  planted_ = false;
  gas_ = 0;
}

MotorBike::MotorBike(const MotorBike& mb) {
  planted_ = mb.planted_;
}

MotorBike::~MotorBike() {
  printf("Deleting MotorBike-------\n");
}