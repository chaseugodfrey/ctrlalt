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

#include "Application/Application.h"

int main() {
    Application::App app{};
    app.Init();
    app.Run();
    app.Shutdown();
    return 0;
}
