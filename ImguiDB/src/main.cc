#include <SFML/Graphics.hpp>

#include "../include/structs_enums.h"
#include "../include/database.h"
#include "../include/table.h"
#include "../include/imgui_window.h"


int main() {
  // sf::RenderWindow window(sf::VideoMode(1200, 900), "DB con Imgui");
  // ImGui::SFML::Init(window);

  Database *database = new Database("../data/jardineria.db");
  printf("%d",database->number_of_tables_);

  // while (window.isOpen()) {
  // sf::Event event;
  // while (window.pollEvent(event)) {

  //   if (event.type == sf::Event::Closed)
  //   window.close();
  // }
  // printf("%d\n", window.getSize().x);
  // window.clear();
  
  // window.display();
  // }

return 0;
}

