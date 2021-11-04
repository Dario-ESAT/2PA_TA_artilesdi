#include <stdio.h>

#include "car.h"


void Car::init(int doors, float gas){
  doors_ = doors;
  gas_ = gas;
  open_ = true;
}

void Car::init(float gas){
  doors_ = 3;
  gas_ = gas;
  open_ = true;
}

void Car::init(){
  doors_ = 3;
  gas_ = 0;
  open_ = true;
}

void Car::openDoors () {
  open_ = true;
}

void Car::closeDoors () {
  open_ = false;
}

Car::Car() {
  gas_ = 0;
  doors_ = 0;
  open_ = false;
}
Car::Car(const Car& c) {
  doors_ = c.doors_;
  open_ = c.open_;
}
Car::~Car(){
  printf("Deleting Car-------\n");
}
