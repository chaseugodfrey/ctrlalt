#include "Scene/Scene.h"

int main() {
    Scene::Scene game;
    game.Initialize();
    game.Run();
    game.Destroy();
    return 0;
}
