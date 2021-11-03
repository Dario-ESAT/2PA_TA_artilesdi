#include <stdio.h>
#include "plane.h"

void Plane::Innit(int doors, float gas){
  doors_ = doors;
  gas_ = gas;
  open_ = true;
}

void Plane::Innit(float gas){
  doors_ = 3;
  gas_ = gas;
  open_ = true;
}

void Plane::Innit(){
  doors_ = 3;
  gas_ = 0;
  open_ = true;
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
  gas_ = p.gas_;
  doors_ = p.doors_;
  open_ = p.open_;
}

Plane::~Plane() {
  printf("Deleting Plane-------\n");
}