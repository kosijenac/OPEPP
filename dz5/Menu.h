#ifndef __MENU_H
#define __MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

std::vector<sf::FloatRect> draw_menu(sf::RenderWindow&, std::string, sf::RectangleShape, sf::RectangleShape);

#endif