#include "..\include\definitions.h"

void EntityClass::setAlive(bool alive){
  this->alive = alive;
}

bool EntityClass::getAlive() {
  return this->alive;
}

sf::RectangleShape EntityClass::getShape(){
  return this->shape;
}

void EntityClass::setShape(sf::RectangleShape shape) {
  this->shape = shape;
}