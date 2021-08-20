#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 600), "name", sf::Style::Close);
  while (window.isOpen()) {
    sf::Event e;
    while (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed)
        window.close();
    }
    window.clear();
    window.display();
  }
  return 0;
}
