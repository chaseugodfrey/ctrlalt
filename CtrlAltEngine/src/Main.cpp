/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Main.cpp
\author 	Michael Lazaroo
\par    	m.lazaroo@digipen.edu
\date   	Sep 08, 2024
\brief
*/
/******************************************************************************/
#include "../src/pch.h"
#include "Engine/Engine.h"

int main() {
    Engine::Engine engine;
    engine.Setup();
    engine.Initialize();
    engine.Run();
    engine.Destroy();
    return 0;
}
