#include "..\include\brick.h"

Brick::Brick(sf::RectangleShape shape, int id, bool alive) {
  
  this->id = id;
  this->alive = alive;
  this->shape = shape;
}

Brick::Brick(){}


BrickNode::BrickNode(Brick data){
  this->data = data;
  this->next = nullptr;
}

BrickList::BrickList() {
  head = NULL;
}
BrickList::~BrickList() {};

BrickNode* BrickList::getHead() {
  return this->head;
}
void BrickList::setHead(BrickNode* head) {
  this->head = head;
}

void BrickList::addBrick(Brick data) {
  BrickNode* newnode = new BrickNode(data);
  
  // printf("\n%d-> x: %2f",data.getId(), data.getShape().getPosition().x);
  newnode->next = head;
  head = newnode;

};

void BrickList::printBricks(sf::RenderWindow *window){
  static bool x = true;
  for (BrickNode* current = head; current != nullptr; current = current->next) {
    if (x) {
      // printf("\n%d-> x: %2f y: %2f",current->data.getId(), current->data.getShape().getPosition().x, current->data.getShape().getPosition().y);
    }
    
    window->draw(current->data.getShape());
  }
  x = false;
}

void BrickList::printBricksAlive(sf::RenderWindow *window){
  for (BrickNode* current = head; current != nullptr; current = current->next) {
    if (current->data.getAlive()){
      window->draw(current->data.getShape());

    }
  }
}