#include "..\include\ball.h"
#include "..\include\definitions.h"

  BallClass::BallClass(int id, sf::RectangleShape shape, sf::Vector2i direction, float speed, bool alive){
    this->shape = shape;
    this->alive = alive;
    this->speed = speed;
    this->direction = direction;
  }
  BallClass::BallClass(){};

  void BallClass::setDirection(sf::Vector2i direction) {
    this->direction = direction;
  }

  sf::Vector2i BallClass::getDirection() {
    return this->direction;
  }

  void BallClass::setSpeed(float speed) {
  	this->speed = speed;
  }

  float BallClass::getSpeed() {
  	return this->speed;
  }

  void BallClass::CheckBoundaries(){
    if(this->shape.getPosition().x <= 0 || this->shape.getPosition().x >= kScreenWidth - this->shape.getSize().x){
      Bounce('S');
    }

    if(this->shape.getPosition().y <= 0){
      Bounce('T');
    }
    
  }
  void BallClass::Bounce(char direction){

    /*
    T = Top/Bottom
    S = Sides
    */

    switch (direction) {
    case 'T':
      this->direction.x =  this->direction.x * -1;
      this->direction.y = this->direction.y * -1;
    case 'S':
      this->direction.x =  this->direction.x * -1;
      break;
    default:
      break;
    }

  }

  void BallClass::MoveBall(){
    
    sf::Vector2f offset = sf::Vector2f(this->direction.x * this->speed, this->direction.y * this->speed);
    this->shape.move(offset);
    
  }

  void BallClass::DrawBall(sf::RenderWindow *window){
    window->draw(this->shape);
  }