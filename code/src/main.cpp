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
std::vector<std::string> playerMoves;
unsigned int mp = 0;
int main() {
    //add code here
    return 0;
}