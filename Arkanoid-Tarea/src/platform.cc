#include "..\include\platform.h"

PlatformClass::PlatformClass(sf::RectangleShape shape, int id, float speed, sf::Vector2i direction, bool alive){
  this->shape = shape;
  this->alive = alive;
  this->speed = speed;
  this->direction = direction;
  this->id = id;
  
};
PlatformClass::PlatformClass(){};
#pragma region s-getter

float PlatformClass::getSpeed() {
  return this->speed;
}

void PlatformClass::setSpeed(float speed) {
  this->speed = speed;
}

sf::Vector2i PlatformClass::getDirection() {
  return this->direction;
}

void PlatformClass::setDirection(sf::Vector2i direction) {
  this->direction = direction;
}
#pragma endregion


void PlatformClass::MovePlatform(){
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && this->getShape().getPosition().x > 0) {

    this->direction = sf::Vector2i(-1, 0);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && this->getShape().getPosition().x < kScreenWidth - this->getShape().getSize().x) {

    this->direction = sf::Vector2i(1, 0);
  } else {

    this->direction = sf::Vector2i(0, 0);
  }

  sf::Vector2f offset = sf::Vector2f(this->direction.x * this->speed, 0.0f);
  // printf("\n%f", offset.x);
  this->shape.move(offset);
}

void PlatformClass::DrawPlatform(sf::RenderWindow *window){
  window->draw(this->shape);
}