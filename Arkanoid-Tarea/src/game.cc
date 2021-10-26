#include "..\include\game.h"

Game::Game() {
  lives = 3;
  score = 0;
  ReadConfig();
}

int Clamp(int value, int min, int max){
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}

void Game::ReadConfig(){
  
  std::fstream config_file;
  config_file.open("../data/config.txt", std::ios::in);

  if(config_file.is_open()){
    std::string line;
    int i = 0;
    while(std::getline(config_file, line)){ 
      int start = line.find("=",0) + 1;
      // volcado de todas las lineas en line
      std::string value(line.substr(start));
      value[value.find(";")] = '\0';

      // printf("%s | %s",line.c_str(), value.c_str());
      int value_int = atoi(value.c_str());

      switch (i) {
        case 0:
          config.brick_rows = Clamp(value_int,3,20);
          // printf(" : %d\n", config.brick_rows);
          break;
        case 1:
          config.brick_cols = Clamp(value_int,2,15);
          // printf(" : %d\n", config.brick_rows);
          break;
        case 2:
          config.brick_offset = Clamp(value_int,0,10);
          // printf(" : %d\n", config.brick_offset);
          break;
        case 3:
          config.brick_spawn_start = Clamp(value_int,0,100);
          // printf(" : %d\n", config.brick_spawn_start);
          break;
        case 4:
          config.brick_spawn_end = Clamp(value_int, config.brick_spawn_start, 500);
          // printf(" : %d\n", config.brick_spawn_end);
          break;
        case 5:
          config.ball_width = Clamp(value_int,5,20);
          // printf(" : %f\n", config.ball_width);
          break;
        case 6:
          config.ball_height = Clamp(value_int,5,20);
          // printf(" : %f\n", config.ball_height);
          break;
        case 7:
          config.ball_speed = Clamp(value_int,1,20);
          // printf(" : %f\n", config.ball_speed);
          break;
        case 8:
          config.platform_width = Clamp(value_int,5,20);
          // printf(" : %f\n", config.platform_width);
          break;
        case 9:
          config.platform_height = Clamp(value_int,5,20);
          // printf(" : %f\n", config.platform_height);
          break;
        case 10:
          config.platform_speed = Clamp(value_int,1,20);
          // printf(" : %f\n", config.platform_speed);
          break;
        case 11:
          config.platform_r = Clamp(value_int,0,255);
          // printf(" : %d\n", config.platform_r);
          break;
        case 12:
          config.platform_g = Clamp(value_int,0,255);
          // printf(" : %d\n", config.platform_g);
          break;
        case 13:
          config.platform_b = Clamp(value_int,0,255);
          // printf(" : %d\n", config.platform_b);
          break;
        case 14:
          config.ball_r = Clamp(value_int,0,255);
          // printf(" : %d\n", config.ball_r);
          break;
        case 15:
          config.ball_g = Clamp(value_int,0,255);
          // printf(" : %d\n", config.ball_g);
          break;
        case 16:
          config.ball_b = Clamp(value_int,0,255);
          // printf(" : %d\n", config.ball_b);
          break;
        case 17:
          config.brick_r = Clamp(value_int,0,255);
          // printf(" : %d\n", config.brick_r);
          break;
        case 18:
          config.brick_g = Clamp(value_int,0,255);
          // printf(" : %d\n", config.brick_g);
          break;
        case 19:
          config.brick_b = Clamp(value_int,0,255);
          // printf(" : %d\n", config.brick_b);
          break;
        default:
          break;
      }
      ++i;
    }

  }
  config_file.close();
  
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
  return IsInsideHitbox(first_item,second_item.x1,second_item.y1) || 
  IsInsideHitbox(first_item,second_item.x2,second_item.y1) ||
  IsInsideHitbox(first_item,second_item.x1,second_item.y2) || 
  IsInsideHitbox(first_item,second_item.x2,second_item.y2);
}

void Game::BuildBricks(sf::Vector2u window_size){

  sf::Vector2f position = sf::Vector2f(config.brick_offset,config.brick_spawn_start);
  
  float size_y = (config.brick_spawn_end - config.brick_spawn_start) / config.brick_rows;
  float size_x = (window_size.x - (config.brick_offset * config.brick_cols)) / config.brick_cols;
  sf::Vector2f size = sf::Vector2f(size_x,size_y);
  
  sf::RectangleShape shape(size);
  shape.setFillColor(sf::Color(config.brick_r, config.brick_g, config.brick_b));
  
  for (int i = 0; i < config.brick_rows; i++) {
    for (int f = 0; f < config.brick_cols; f++) {
      if (f != 0) {
        position.x += size.x + config.brick_offset;
      }
      
      shape.setPosition(position);
      Brick building_brick(shape);

      brick_list.addBrick(building_brick);
      
    }
    position.x = config.brick_offset;
    position.y += size.y + config.brick_offset;
  }
  
}

void Game::InitPLatform(sf::Vector2u window_size){
  sf::RectangleShape player_shape(sf::Vector2f(80,20));
  player_shape.setPosition(window_size.x/2,window_size.y - config.platform_height);
  
  player_shape.setFillColor(sf::Color(config.platform_r, config.platform_g, config.platform_b));

  player = PlatformClass(player_shape,config.platform_speed);
}

void Game::InitBall(){
  sf::RectangleShape shape(sf::Vector2f(config.ball_width,config.ball_height));
  
  shape.setPosition(sf::Vector2f(player.getShape().getPosition().x + player.getShape().getSize().x/2 - shape.getSize().x/2,player.getShape().getPosition().y - player.getShape().getSize().y - 5));

  shape.setFillColor(sf::Color(config.ball_r, config.ball_g, config.ball_b));
  
  ball = BallClass(shape,sf::Vector2i(1,-1),config.ball_speed);

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
 