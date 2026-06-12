#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
enum class GameState
{
    Playing,
    GameOver
};
enum class Move
{
    Slash,
    Stab,
    Block,
    Knife,
    KillerCombo
};
struct mov {
    Move move;
    unsigned short dmg;
};
class Player {
public:
    short hp;
    unsigned short lv;
    unsigned int xp;
    std::vector<mov> movs;
    Player() {
        hp = 100;
        lv = 1;
        xp = 0;
        movs.push_back({ Move::Slash, 10 });
        movs.push_back({ Move::Stab, 15 });
        movs.push_back({ Move::Block, 0 });
    }
    void lrnMov(Move move, unsigned short dmg) {
        movs.push_back({ move, dmg });
    }
    bool lvu() {
        if (xp >= lv * 10) {
            xp -= lv * 10;
            lv++;
            return true;
        }
        return false;
    }
    void frgMov(Move move) {
        for (auto it = movs.begin(); it != movs.end(); ++it) {
            if (it->move == move) {
                movs.erase(it);
                break;
            }
        }
    }
    bool isa() {
        return hp > 0;
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode({1920u, 1080u}), "SFML Rogue-like Dungeon Crawler");
    window.setFramerateLimit(60);
    sf::Texture texPlr;
    if (!texPlr.loadFromFile("../../pngs/plr.png")) {
        std::cerr << "Error: Could not find image file(s)!" << std::endl;
        return -1;
    }
    texPlr.setSmooth(false);
    sf::Sprite player(texPlr);
    player.setOrigin(player.getLocalBounds().getCenter());
    player.setPosition({400.f, 400.f});
    const float baseScale = 3.f;
    auto gameState = GameState::Playing;
    auto plr = std::make_unique<Player>();
    auto enm = std::make_unique<Player>();
    while (window.isOpen()) {
        player.setScale({baseScale, baseScale});
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
        // TODO: Make Shit idk?
    }
    return 0;
}