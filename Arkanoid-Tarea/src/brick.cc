#include "..\include\brick.h"

Brick::Brick(sf::RectangleShape shape, bool alive) {
  
  this->alive = alive;
  this->shape = shape;
}

Brick::Brick(){}


BrickNode::BrickNode(Brick data){
  this->data = data;
  this->next = nullptr;
}

BrickNode::~BrickNode(){
  if (next != nullptr) {
    delete next;
  }
}

BrickList::BrickList() {
  head = nullptr;
}

BrickList::~BrickList() {
  delete head;
};

BrickNode* BrickList::getHead() {
  return this->head;
}
void BrickList::setHead(BrickNode* head) {
  this->head = head;
}

void BrickList::addBrick(Brick data) {
  BrickNode* newnode = new BrickNode(data);
  
  newnode->next = head;
  head = newnode;

};

void BrickList::printBricks(sf::RenderWindow *window){
  for (BrickNode* current = head; current != nullptr; current = current->next) {
    window->draw(current->data.getShape());
  }
}

void BrickList::printBricksAlive(sf::RenderWindow *window){
  for (BrickNode* current = head; current != nullptr; current = current->next) {
    if (current->data.getAlive()){
      window->draw(current->data.getShape());

    }
  }
}
/* 
void BrickList::deleteBricks(){

  BrickNode *current;
  while(current != nullptr){
    BrickNode* current = head;
    if(current->next != nullptr){
      head = current->next;
      current->~BrickNode();
    } else {
      head->~BrickNode();
    }
  }
} */