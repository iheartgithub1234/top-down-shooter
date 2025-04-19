#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

std::vector<std::vector<sf::Vector2f>> bullets = {};
sf::Vector2f player = {450, 450};
float speed = 5;

bool isMouseHeld = false;
sf::Vector2i mousePosition;
int num = 1;

sf::Color rgb() {
    float hue = num % 360;
    float c = 255;
    float x = (1 - std::abs(fmod(hue / 60.0, 2) - 1)) * c;
    float m = 0;

    float r, g, b;
    if (hue < 60)      { r = c; g = x; b = 0; }
    else if (hue < 120) { r = x; g = c; b = 0; }
    else if (hue < 180) { r = 0; g = c; b = x; }
    else if (hue < 240) { r = 0; g = x; b = c; }
    else if (hue < 300) { r = x; g = 0; b = c; }
    else                { r = c; g = 0; b = x; }

    return sf::Color(r + m, g + m, b + m, 20);
}

int main() {
     sf::RenderWindow window(sf::VideoMode(1000, 1000), "Shooter");
     window.setFramerateLimit(200);

     while (window.isOpen()) {
          sf::Event event;

          while (window.pollEvent(event)) {
               if (event.type == sf::Event::Closed) {
                    window.close();
               }

               if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    isMouseHeld = true;
               }

               if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                    isMouseHeld = false;
               }

               if (event.type == sf::Event::MouseMoved) {
                    mousePosition = sf::Mouse::getPosition(window);
               }
          }

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player.y > 0) {
               player.y -= speed;
          }

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && player.y < window.getSize().y - 100) {
               player.y += speed;
          }

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.x > 0) {
               player.x -= speed;
          }

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.x < window.getSize().x - 100) {
               player.x += speed;
          }

          if (isMouseHeld) {
               float xDist = player.x + 50 - mousePosition.x;
               float yDist = player.y + 50 - mousePosition.y;

               float distance = std::sqrt(xDist * xDist + yDist * yDist);
               float dx = xDist / distance;
               float dy = yDist / distance;

               sf::Vector2f newVelocity = {-dx * 5, -dy * 5};
               bullets.push_back({{player.x + 40, player.y + 40}, newVelocity});
          }

          window.clear(sf::Color(30, 30, 30));

          sf::CircleShape circle(50);
          circle.setPosition(player);
          circle.setFillColor(sf::Color(200, 200, 200));
          window.draw(circle);

          for (int i = 0; i < bullets.size(); i++) {
               for(int j = 1; j <= 5; j++) {
                    sf::CircleShape bullet(j * 3);
                    bullet.setPosition({bullets[i][0].x - j*3 + 10, bullets[i][0].y - j*3 + 10});
                    bullet.setFillColor(rgb());
                    window.draw(bullet);
               }

               bullets[i][0].x += bullets[i][1].x;
               bullets[i][0].y += bullets[i][1].y;

               if (bullets[i][0].y < 0 || bullets[i][0].y > window.getSize().y - 20 || bullets[i][0].x < 0 || bullets[i][0].x > window.getSize().x - 20) {
                    bullets.erase(bullets.begin() + i);
                    i--;
               }
          }

          num += 2;

          window.display();
     }

     return 0;
}
