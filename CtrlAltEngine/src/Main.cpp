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

#include "Engine/Engine.h"

int main() {
    Engine::Engine engine;
    engine.Initialize();
    engine.Run();
    engine.Destroy();
    return 0;
}
