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
#ifndef ECS_H
#define ECS_H

#include <GLEW/GL/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <vector>
#include <glm/glm.hpp>

namespace Render {

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
		GLFWwindow* ptr_window{};
		std::vector<Renderable> objects;
	public:
		RenderPipeline(GLFWwindow* window) : ptr_window(window) {}
		void Init(GLint width, GLint height, std::string const& window_title);

		void Draw();
	};


	//Class that serves as an assetmanager for now
	class AssetManager {
		//encapsulates state needed to represent a geometric model
		struct GLModel {
			GLenum		primitive_type{};	//which openGL primitive to be rendered
			GLuint		primitive_cnt{};	//how many primitives in 1 model
			GLuint		vao_ID{};			//Handle to Vertex Array Object
			GLuint		draw_cnt{};		//idx_elem_cnt replacement, now represents for both non-indexed and indexed draw methods
			GLuint		vbo_ID{};
		};
		
		std::map<std::string, GLuint> textures;
		std::map<std::string, GLModel> meshes;	//For now just init quad

		GLModel LoadQuad();	//Example of loading in something, reference for nxt time
	public:
		void Init();
		void Cleanup();
	};
}

#endif