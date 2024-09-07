#include "Game/Game.h"

int main() {
    GameClass::Game game;
    game.Initialize();
    game.Run();
    game.Destroy();
    return 0;
}
