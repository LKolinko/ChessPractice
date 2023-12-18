#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
std::vector<std::vector<int>> b;
int k = 0, n = 0;
bool good(int i, int n, int stolb, std::vector<int>& a) {
 for (int j = 0; j < stolb; j++) if (a[j] == i) return false;
 for (int j = 0; j < stolb; j++) if (abs(j - stolb) == abs(i - a[j])) return false;
 return true;
}
void bt(int i, int n, std::vector<int>& a) {
 if (i == n) {
  k++;
  b.push_back(a);
  return;
 }
 for (int j = 0; j < n; j++) {
  a[i] = j;
  if (good(j, n, i, a)) bt(i + 1, n, a);
 }
}
int main() {
 sf::RenderWindow w(sf::VideoMode(700, 50), "Enter n: ");
 sf::Font font;
 font.loadFromFile("arialmt.ttf");
 sf::Text txt;
 std::string str = "enter the size of the table: ";
 txt.setFont(font);
 txt.setString(str);
 txt.setCharacterSize(40);
 while (w.isOpen()) {
  sf::Event e;
  while (w.pollEvent(e)) {
   if (e.type == sf::Event::TextEntered) {
    if (e.key.code > 47 && e.key.code < 58) {
     char text[] = { e.key.code };
     n *= 10;
     n += atoi(text);
     str.push_back(text[0]);
     txt.setString(str);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) {
     n /= 10;
     if (size(str) > 29) {
      str.pop_back();
      txt.setString(str);
     }
    }
   }
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
    if (n == 2 || n == 3 || n == 0 || n > 13) {
     std::string str2 = "error";
     txt.setString(str2);
     if (size(str) > 29) str.pop_back();
     if (n > 11) {
      std::string str2 = "error";
      txt.setString(str2);
      if (size(str) > 29) str = "enter the size of the table: ", n = 0;
     }
     n /= 10;
    }
    else w.close();
   }
  }
  w.clear();
  w.draw(txt);
  w.display();
 }
 sf::RectangleShape rect[2555];
 sf::RenderWindow window(sf::VideoMode(53 * n, 53 * n), "the queen");
 window.display();
 std::vector<int> a(n);
 bt(0, n, a);
 int string = 0;
 sf::Image heroimage;
 heroimage.loadFromFile("queen.png");
 sf::Texture herotexture;
 herotexture.loadFromImage(heroimage);
 sf::Sprite herosprite;
 herosprite.setTexture(herotexture); 
 while (window.isOpen()) {
  int l = 0;
  sf::Event event;
  while (window.pollEvent(event)) {
   if (event.type == sf::Event::Closed) window.close();
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && string > 0) string--;
   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && string < k - 1) string++;
  }
  for (int i = 0, ind = 0; i < n * 53; i += 53, ind++) {
   for (int j = 0, j1 = 0; j < n * 53; j += 53, j1++, l++) {
    if ((i & 1 && j + 1 & 1) || (i + 1 & 1 && j & 1)) rect[l].setFillColor(sf::Color(160, 82, 45));
    rect[l].setSize(sf::Vector2f(48, 48));
    rect[l].setPosition(i, j);
    window.draw(rect[l]);
    if (j1 == b[string][ind]) {
     herosprite.setPosition(i, j);
     window.draw(herosprite);
    }
   }
  }
  window.display();
 }
}
