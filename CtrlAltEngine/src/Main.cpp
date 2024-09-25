#include "Engine/Engine.h"

int main() {
    Engine::Engine engine;
    engine.Initialize();
    engine.Run();
    engine.Destroy();
    return 0;
}
