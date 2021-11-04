#include <stdio.h>
#include "plane.h"

void Plane::init(int doors, float gas){
  Car::init(doors,gas);
  gear_ = false;
}

void Plane::init(float gas){
  Car::init(gas);
  gear_ = false;
}

void Plane::init(){
  Car::init();
  gear_ = false;
}

void Plane::pullGear() {
  gear_ = false;
}
void Plane::lowerGear () {
  gear_ = true;
}
void Plane::openDoors () {
  if (gear_) {
    open_ = true; 
  }
}

Plane::Plane() {
  gear_ = 0;
  gas_ = 0;
  doors_ = 0;
  open_ = false;
}

Plane::Plane(const Plane& p) {
  gear_ = p.gear_;
}

Plane::~Plane() {
  printf("Deleting Plane-------\n");
}