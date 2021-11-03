#include <stdio.h>

#include "car.h"


void Car::Innit(int doors, float gas){
  doors_ = doors;
  gas_ = gas;
  open_ = true;
}

void Car::Innit(float gas){
  doors_ = 3;
  gas_ = gas;
  open_ = true;
}

void Car::Innit(){
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
  gas_ = c.gas_;
  doors_ = c.doors_;
  open_ = c.open_;
}
Car::~Car(){
  printf("Deleting Car-------\n");
}
