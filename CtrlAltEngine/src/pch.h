#pragma once

//Windows Header Files
#ifdef _WIN32
//exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

//C++ Standard Library
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <set>
#include <list>
#include <queue>
#include <deque>
#include <algorithm>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>
#include <cassert>
#include <ctime>
#include <typeindex>

//OpenGL
#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

//RapidJSON
#include "../libs/rapidjson/document.h"
#include "../libs/rapidjson/writer.h"
#include "../libs/rapidjson/stringbuffer.h"
#include "../libs/rapidjson/filereadstream.h"
#include "../libs/rapidjson/filewritestream.h"

// ImGui Headers
#include <imgui/include/imgui.h>
#include <imgui/include/imgui_impl_glfw.h>
#include <imgui/include/imgui_impl_opengl3.h>
#include <imgui/include/imgui_stdlib.h>

// Project Headers
#include "Logger/Logger.h"
#include "Math/MathLib.h"
#include "ECS/Types.h"