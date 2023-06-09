#include "Connect4.h"
#include "Menu.h"
#include "PlayerMinMax.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    sf::RenderWindow win(sf::VideoMode(800, 600), "Connect 4");
    int h = (argc == 3 ? atoi(argv[1]) : 6), w = (argc == 3 ? atoi(argv[2]) : 7);
    bool menu = true, singlePlayer = false;
    string message("Select game mode");
    while (win.isOpen()) {
        sf::Event d;
        if (menu) {
            while (win.waitEvent(d) && menu) {
                win.clear(sf::Color::Yellow);
                sf::RectangleShape btn1(sf::Vector2f(0.4f * win.getSize().x, 0.1f * win.getSize().y));
                sf::RectangleShape btn2(sf::Vector2f(0.4f * win.getSize().x, 0.1f * win.getSize().y));
                vector<sf::FloatRect> bounds = draw_menu(win, message, btn1, btn2);
                if (d.type == sf::Event::Closed)
                    win.close();
                if (d.type == sf::Event::Resized)
                    win.setView(sf::View(sf::FloatRect(0, 0, d.size.width, d.size.height)));
                if (d.type == sf::Event::MouseButtonPressed && d.mouseButton.button == sf::Mouse::Left) {
                    if (bounds[0].contains(d.mouseButton.x, d.mouseButton.y)) {
                        menu = false;
                        singlePlayer = true;
                    }
                    if (bounds[1].contains(d.mouseButton.x, d.mouseButton.y)) {
                        menu = false;
                        singlePlayer = false;
                    }
                }
                win.display();
            }
        } else {
            Connect4 env(h, w);
            // Podesiti CPUonTurn na true i PLAYER2 u PLAYER1 ako zelimo da CPU igra prvi
            bool CPUonTurn = false;
            PlayerMinMax bot(PLAYER2, w * 1024);
            while (win.waitEvent(d) && !env.get_status()) {
                env.draw_board(win);
                if (CPUonTurn) {
                    env.step(win, bot.get_action(env.get_board(), env.get_status()));
                    env.draw_board(win);
                    CPUonTurn = false;
                }
                if (d.type == sf::Event::Closed)
                    win.close();
                if (d.type == sf::Event::Resized)
                    win.setView(sf::View(sf::FloatRect(0, 0, d.size.width, d.size.height)));
                if (d.type == sf::Event::MouseButtonPressed && d.mouseButton.button == sf::Mouse::Left) {
                    env.step(win, (int)((float)w * d.mouseButton.x / win.getSize().x) + 1);
                    env.draw_board(win);
                    if (singlePlayer)
                        CPUonTurn = true;
                }
                win.display();
            }
            message = env.get_status_desc();
            env.draw_board(win);
            win.display();
            sf::sleep(sf::milliseconds(250));
            menu = true;
        }
    }
    return 0;
}