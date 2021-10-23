#include "..\include\game.h"

Game::Game() {
  lives = 3;
  score = 0;
}

bool Game::IsInsideHitbox(hitbox item, float x, float y){
  return x>item.x1 && x<item.x2 && y>item.y1 && y<item.y2;
}

char Game::GetWhereIs(hitbox item, hitbox second_item){
  if (item.y1 >= second_item.y2 || item.y2 <= second_item.y1) {
    return 'T';
  } else if(item.x1 >= second_item.x2 || item.x2 <= second_item.x1){
    return 'S';
  }
  
  return 'N';
}

bool Game::Collision(hitbox first_item, hitbox second_item){
  return IsInsideHitbox(first_item,second_item.x1,second_item.y1)||IsInsideHitbox(first_item,second_item.x2,second_item.y1)||
      IsInsideHitbox(first_item,second_item.x1,second_item.y2)||IsInsideHitbox(first_item,second_item.x2,second_item.y2);
}

void Game::buildBricks(){

  sf::Vector2f position = sf::Vector2f(5,50);
  sf::Vector2f size = sf::Vector2f(61,30);
  sf::RectangleShape shape(size);
  int id = 0;
  for (int i = 0; i < rows; i++) {
    for (int f = 0; f < cols; f++) {
      if (f != 0) {
        position.x += size.x + 5;
      }
      
      shape.setPosition(position);
      Brick building_brick(shape,id);

      brick_list.addBrick(building_brick);
      
      id++;
    }
    position.x = 5;
    position.y += size.y + 5;
  }
  
}

void Game::initPLatform(){
  sf::RectangleShape player_shape(sf::Vector2f(80,20));
  player_shape.setPosition(360,860);
  player_shape.setFillColor(sf::Color::Green);
  player = PlatformClass(player_shape,1,5);
  printf("platform-> %f\n",player.getShape().getPosition().y);
}

void Game::initBall(){
  sf::RectangleShape shape(sf::Vector2f(10,10));
  shape.setPosition(sf::Vector2f(player.getShape().getPosition().x + player.getShape().getSize().x/2 - shape.getSize().x/2,player.getShape().getPosition().y - player.getShape().getSize().y - 5));
  ball = BallClass(1,shape,sf::Vector2i(1,-1),7);
  printf("ball-> %f\n",ball.getShape().getPosition().y);
}

void Game::BallBricksCollision(){
  sf::Vector2f raycast = sf::Vector2f(ball.getShape().getPosition().x + ball.getDirection().x * ball.getSpeed(), ball.getShape().getPosition().y + ball.getDirection().y * ball.getSpeed());
  
  hitbox h_ball_raycast = {raycast.x,raycast.y,
    raycast.x + ball.getShape().getSize().x,raycast.y + ball.getShape().getSize().y};
  
  hitbox h_ball = {ball.getShape().getPosition().x,ball.getShape().getPosition().y,
    ball.getShape().getPosition().x + ball.getShape().getSize().x,ball.getShape().getPosition().y + ball.getShape().getSize().y};
  
  for (BrickNode* current = brick_list.getHead(); current != nullptr; current = current->next) {
    if (current->data.getAlive()) {
      hitbox h_brick = {current->data.getShape().getPosition().x,current->data.getShape().getPosition().y,
        current->data.getShape().getPosition().x + current->data.getShape().getSize().x,current->data.getShape().getPosition().y + current->data.getShape().getSize().y};

      if (Collision(h_brick,h_ball_raycast)) {
        current->data.setAlive(false);
        ball.Bounce(GetWhereIs(h_brick,h_ball));
        break;
      }
    }
  }
}

void Game::PlatformBallCollision(){
  sf::Vector2f raycast = sf::Vector2f(ball.getShape().getPosition().x + ball.getDirection().x * ball.getSpeed(), ball.getShape().getPosition().y + ball.getDirection().y * ball.getSpeed());

  hitbox h_ball_raycast = {raycast.x,raycast.y,
    raycast.x + ball.getShape().getSize().x,raycast.y + ball.getShape().getSize().y};
  
  hitbox h_ball = {ball.getShape().getPosition().x,ball.getShape().getPosition().y,
    ball.getShape().getPosition().x + ball.getShape().getSize().x,ball.getShape().getPosition().y + ball.getShape().getSize().y};
  hitbox h_platform = {player.getShape().getPosition().x,player.getShape().getPosition().y,
        player.getShape().getPosition().x + player.getShape().getSize().x,player.getShape().getPosition().y + player.getShape().getSize().y};
    
  if (Collision(h_platform,h_ball_raycast)) {
    if (player.getDirection().x != 0) {
      ball.setDirection(sf::Vector2i(player.getDirection().x, -1));
    } else {
      ball.setDirection(sf::Vector2i(ball.getDirection().x, -1));
    }
  }
}

void Game::RestartPLayer() {
  sf::RectangleShape shape = player.getShape(); 
  shape.setPosition(360,860);
  player.setShape(shape);
  
  shape = ball.getShape();
  shape.setPosition(sf::Vector2f(player.getShape().getPosition().x + player.getShape().getSize().x/2 - shape.getSize().x/2,player.getShape().getPosition().y - player.getShape().getSize().y - 5));
  ball.setShape(shape);
}

void Game::RestartLvL(){
  RestartPLayer();
  lives = 3;
  for (BrickNode* current = brick_list.getHead(); current != nullptr; current = current->next) {
    current->data.setAlive();
  }
}

void Game::CheckLoss(){
    if(ball.getShape().getPosition().y >= kScreenHeight - ball.getShape().getSize().y){
      lives--;
      if (lives < 0){
        RestartLvL();
      } else {
        RestartPLayer();
      }
    }
  }
 