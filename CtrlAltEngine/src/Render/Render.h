/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Render.h
\author 	Elton Leosantosa
\par    	leosantosa.e@digipen.edu
\date   	Sep 13, 2024
\brief		Render System Definitions and API


Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

/// PREPROCESSOR DIRECTIVES
///=========================================================================================================
#ifndef RENDER_H
#define RENDER_H

#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <vector>
#include <set>
#include <glm/glm.hpp>
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"
#include "glslshader.h"


void _CheckGLError(const char* file, int line);

#define CheckGLError() _CheckGLError(__FILE__, __LINE__)

//Forward Declaration
namespace System {
	class SRender;
}

namespace Render {
	//Forward Declaration
	class RenderPipeline;

	//encapsulates state needed to represent a geometric model
	struct GLModel {
		GLenum		primitive_type{};	//which openGL primitive to be rendered
		GLuint		primitive_cnt{};	//how many primitives in 1 model
		GLuint		vao_ID{};			//Handle to Vertex Array Object
		GLuint		draw_cnt{};		//idx_elem_cnt replacement, now represents for both non-indexed and indexed draw methods
		GLuint		vbo_ID{};
	};
	//Structure that represents data in 1 vertex
	struct GLVertStruct {
		glm::vec2 pos;
		glm::vec2 texCoord;
	};

	//Class that represents something that can be drawn
	class CRenderable {
		std::unordered_map<std::string, GLuint>::iterator textureHandle;
		std::unordered_map<std::string, GLModel>::iterator modelHandle;
		std::unordered_map<std::string, GLSLShader>::iterator shader_handle;
		/*
		Render Variables
		*/
		std::string textureName;
		std::string meshName;
		std::string shaderName;
		bool compiled = false;
	public:
		/*
		* Ctor of CRenderable, Params are texture name, mesh name, shader name
		*/
		CRenderable(std::string texture = "default", std::string mesh = "default", std::string shader = "default")
			:textureName(texture), meshName(mesh), shaderName(shader), compiled(false)
		{}
		//Sorting operation for priority queue
		//friend bool operator < (CRenderable const&, CRenderable const&);

		friend System::SRender;
		friend RenderPipeline;
	};

	//Class that contains the pipeline to draw something to the window
	class RenderPipeline {
		GLFWwindow* target_window{};

		//std::multiset<CRenderable> objects;
	public:
		RenderPipeline();

		//Loads Model, and returns a GLModel that draws using triangles
		GLModel LoadModel_Triangles(std::vector<GLVertStruct> const&, std::vector<GLushort> const&);
		//Loads image, and returns a texture handle
		GLuint LoadTexture(Engine::ImageAsset const& texture);
		//Release texture from gpu store, can be an array or just individual
		void ReleaseTexture(GLuint texture_array);

		GLFWwindow* CreateTargetWindow(GLint width = 900, GLint height = 480);
		void SetTargetWindow(GLFWwindow* window);
		void SetTargetAsCurrent();
		GLFWwindow const* GetCurrentWindow();
		void DeleteCurrentWindow();

		//void Init(GLint width = 900, GLint height = 480, std::string const& window_title = "Hello world");
		//Draws a single renderable
		void StartDraw();
		void Draw(CRenderable const&, glm::mat3 const&);
		void FinishDraw();
		void Cleanup();
	};
}

namespace System {
	//This is basically my adapter between the rendering system itself, and the ecs system
	class SRender : public ECS::System
	{
		//Mapping string name to texture handle
		std::unordered_map<std::string, GLuint> texture_map;

		//Mapping string name to Model
		std::unordered_map<std::string, Render::GLModel> model_map;

		//Mapping string name to GLSLShader
		std::unordered_map<std::string, GLSLShader> shader_map;

		Render::RenderPipeline render_pipeline;
		//Generate the default quad and default image
		void LoadDefaults();
	public:
		SRender();

		void Render();
		void Destroy();
	};
}

#endif