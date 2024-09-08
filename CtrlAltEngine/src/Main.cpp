#include "Scene/Scene.h"

int main() {
    SceneClass::Scene game;
    game.Initialize();
    game.Run();
    game.Destroy();
    return 0;
}
