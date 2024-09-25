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

namespace Render {
	//encapsulates state needed to represent a geometric model
	struct GLModel {
		GLenum		primitive_type{};	//which openGL primitive to be rendered
		GLuint		primitive_cnt{};	//how many primitives in 1 model
		GLuint		vao_ID{};			//Handle to Vertex Array Object
		GLuint		draw_cnt{};		//idx_elem_cnt replacement, now represents for both non-indexed and indexed draw methods
		GLuint		vbo_ID{};
	};

	//Class that represents something that can be drawn
	class Renderable {
		/*
		Render Variables
		*/
		GLuint textureHandle;
		GLuint shaderHandle;
		GLuint meshHandle;
	public:
		//Sorting operation for priority queue
		friend bool operator < (Renderable const&, Renderable const&);
	};

	//Class that contains the pipeline to draw something to the window
	class RenderPipeline {
		std::map<std::string, GLuint> textures;
		std::map<std::string, GLModel> meshes;	//For now just init quad

		GLFWwindow* ptr_window{};

		std::multiset<Renderable> objects;
	public:
		RenderPipeline(GLFWwindow* window = nullptr) : ptr_window(window) {}

		void Init(GLint width = 900, GLint height = 480, std::string const& window_title = "Hello world");
		void Draw();
		void Cleanup();

		//API to add assets
		void AddMesh(std::string name, GLModel&&);
		void AddTexture(std::string name, GLuint);	//temporary func
	};

	//Class that serves as an assetmanager for now
	class AssetLoader {

		
		GLModel LoadQuad();	//Example of loading in something, reference for nxt time
	public:
		void LoadGraphics(RenderPipeline& render);
	};
}

#endif