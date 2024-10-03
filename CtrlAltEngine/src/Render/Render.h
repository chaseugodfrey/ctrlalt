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
#include "glslshader.h"
#include <GLFW/glfw3.h>

#include <string>
#include <map>
#include <vector>
#include <set>
#include <glm/glm.hpp>
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"


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
	public:
		//Quick render layer for now
		enum RenderLayer{
			R_BACKGROUND = 0,
			R_WORLD,
			R_UI,
			R_TOTAL
		};
	private:
		std::unordered_map<std::string, GLuint>::iterator textureHandle;
		std::unordered_map<std::string, GLModel>::iterator modelHandle;
		std::unordered_map<std::string, GLSLShader>::iterator shader_handle;
		/*
		Render Variables
		*/
		std::string textureName{ "default" };
		std::string meshName{ "default" };
		std::string shaderName{ "default" };
		bool compiled = false;
		glm::vec4 color{1.f,1.f,1.f,1.f};
		RenderLayer render_layer{ R_WORLD };
	public:
		//Sorting operation for priority queue
		//friend bool operator < (CRenderable const&, CRenderable const&);
		void SetTexture(std::string);
		void SetMesh(std::string);
		void SetShader(std::string);
		void SetColor(glm::vec4);
		void SetRenderLayer(RenderLayer);
		RenderLayer GetRenderLayer() const;

		friend System::SRender;
		friend RenderPipeline;
	};
	struct {
		bool operator()(ECS::Entity const& lhs, ECS::Entity const& rhs) {
			return lhs.GetComponent<CRenderable>().GetRenderLayer() < rhs.GetComponent<CRenderable>().GetRenderLayer();
		}
	} RenderSort;

	//Forward
	class Camera2d;

	//Class that contains the pipeline to draw something to the window
	class RenderPipeline {
		GLFWwindow* target_window{};
		Camera2d* camera{};
		GLint view_width{}, view_height{};
		//std::multiset<CRenderable> objects;
		void FB_callback(GLFWwindow* window, int width, int height);
	public:
		RenderPipeline();

		//Load a line Model
		GLModel LoadModel_Line();
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

		void SetCamera(Camera2d*);

		//void Init(GLint width = 900, GLint height = 480, std::string const& window_title = "Hello world");
		//Draws a single renderable
		void StartDraw();
		void Draw(CRenderable const&, glm::mat3 const&);
		void DrawLine(glm::mat3 const&, glm::vec4 color, GLModel const&, GLSLShader&);
		void FinishDraw();
		void Cleanup();
	};

	//For now just assume only 1 camera and its not a component
	class Camera2d {
		glm::vec2 right{}, up{};
		glm::mat3 view_xform{};

		//------------TEMPORARY!!!!!!!
		glm::vec2 position;

		//height of cam
		GLint height{ 1000 };
		//zoom limits
		GLint min_height;
		GLint max_height;
		//1 if zooming in, -1 if zooming out
		GLint height_chng_dir{ 1 };

		//Zoom speed
		GLint height_chng_speed{ 100 };

		//aespect ration
		GLfloat ar{};
		glm::mat3 camwin_to_ndc_xform{};
		glm::mat3 world_to_ndc_xform{};

		//speed for the camera to move
		GLfloat linear_speed{ 2.f };

		//Could be viewport or something else, not sure yet
		//GLFWwindow const* target_window;
	public:
		void SetPosition(GLfloat, GLfloat);
		void Init(GLint view_width, GLint view_height);
		void UpdateViewtoNDC(GLint view_width, GLint view_height);
		glm::mat3 GetWorldtoNDC();
	};
}

namespace System {
	//This is basically my adapter between the rendering system itself, and the ecs system
	class SRender : public ECS::System
	{
		bool draw_debug{ false };
		//Mapping string name to texture handle
		std::unordered_map<std::string, GLuint> texture_map;

		//Mapping string name to Model
		std::unordered_map<std::string, Render::GLModel> model_map;

		//Mapping string name to GLSLShader
		std::unordered_map<std::string, GLSLShader> shader_map;

		//Render pipeline
		Render::RenderPipeline render_pipeline;

		//Assume only 1 camera for now
		Render::Camera2d camera;

		//Generate the default quad and default image
		void LoadDefaults();

		//Draw line from 2 world positions, internal function, only called in render
		void DrawLine(glm::vec2, glm::vec2, glm::vec4 color = {0.f,0.f,0.f,1.f});
	public:
		SRender();

		//Check for changes in input for now, should be changed to engine env variables
		void UpdateFlags();
		void Render();
		void Destroy();
	};
}

#endif