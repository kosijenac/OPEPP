#include "Menu.h"
#include <SFML/Graphics.hpp>

std::vector<sf::FloatRect> draw_menu(sf::RenderWindow& w, std::string msg, sf::RectangleShape btn1, sf::RectangleShape btn2)
{
    sf::Font concrete;
    if (!concrete.loadFromFile("cmunobi.ttf"))
        return {};
    sf::Text m(msg, concrete);
    m.setFillColor(sf::Color::Blue);
    m.setCharacterSize(w.getSize().y / 15);
    sf::FloatRect mRect = m.getLocalBounds();
    m.setOrigin(mRect.left + mRect.width / 2.0f, mRect.top + mRect.height / 2.0f);
    m.setPosition(sf::Vector2f(w.getSize().x / 2.0f, 0.3f * w.getSize().y));
    w.draw(m);

    sf::FloatRect btnRect = btn1.getLocalBounds();
    btn1.setOrigin(btnRect.left + btnRect.width / 2.0f, btnRect.top + btnRect.height / 2.0f);
    btn2.setOrigin(btn1.getOrigin());
    btn1.setPosition(sf::Vector2f(w.getSize().x / 2.0f, 0.45f * w.getSize().y));
    btn2.setPosition(sf::Vector2f(w.getSize().x / 2.0f, 0.6f * w.getSize().y));
    btn1.setFillColor(sf::Color::Cyan);
    btn2.setFillColor(sf::Color::Cyan);

    w.draw(btn1);
    w.draw(btn2);

    sf::Text t1("Player vs. CPU", concrete);
    t1.setFillColor(sf::Color::Blue);
    t1.setCharacterSize(w.getSize().y / 20);
    sf::FloatRect tRect = t1.getLocalBounds();
    t1.setOrigin(tRect.left + tRect.width / 2.0f, tRect.top + tRect.height / 2.0f);
    t1.setPosition(sf::Vector2f(w.getSize().x / 2.0f, 0.45f * w.getSize().y));

    sf::Text t2("Player vs. Player", concrete);
    t2.setFillColor(sf::Color::Blue);
    t2.setCharacterSize(w.getSize().y / 20);
    tRect = t2.getLocalBounds();
    t2.setOrigin(tRect.left + tRect.width / 2.0f, tRect.top + tRect.height / 2.0f);
    t2.setPosition(sf::Vector2f(w.getSize().x / 2.0f, 0.6f * w.getSize().y));

    w.draw(t1);
    w.draw(t2);
    return { btn1.getGlobalBounds(), btn2.getGlobalBounds() };
}