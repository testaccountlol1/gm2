#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
enum class GameState
{
    Menu,
    Playing,
    Paused,
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
    int hp;
    unsigned short lv;
    unsigned short xp;
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
    void isa() {
        return hp > 0;
    }
};
int main() {
    //add code here
    return 0;
}