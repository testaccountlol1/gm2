#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <optional>
#include <sw/redis++?redis++.h>
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
    sw::redis::Redis redis("tcp://127.0.0.1:6379");
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
    if (redis.exists("player:hp") && redis.exists("player:lv") && redis.exists("player:xp")) {
        plr->hp = std::stoi(redis.get("player:hp").value());
        plr->lv = std::stoi(redis.get("player:lv").value());
        plr->xp = std::stoi(redis.get("player:xp").value());
    }
    auto enm = std::make_unique<Player>();
    while (window.isOpen()) {
        player.setScale({baseScale, baseScale});
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                redis.set("player:hp", std::to_string(plr->hp));
                redis.set("player:lv", std::to_string(plr->lv));
                redis.set("player:xp", std::to_string(plr->xp));
                window.close();
            }
        }
        // TODO: Make Shit idk?
    }
    return 0;
}