/******************************************************************************/
/*!
\group  	CtrlAlt
\file		Render.h
\author 	Elton Leosantosa
\par    	leosantosa.e@digipen.edu
\date   	Sep 13, 2024
\brief		Render System Declarations and API


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

	//Component that deals with rendering something to the screen
	class CRenderable {
	public:
		//Quick render layer for now for deciding rendering order
		enum RenderLayer{
			R_BACKGROUND = 0,
			R_WORLD,
			R_UI,
			R_TOTAL
		};
	private:
		/*
		* Handle to actual underlying asset
		*/
		std::unordered_map<std::string, GLuint>::iterator textureHandle;
		std::unordered_map<std::string, GLModel>::iterator modelHandle;
		std::unordered_map<std::string, GLSLShader>::iterator shader_handle;
		/*
		* Handle to temporary asset for loading in by internal asset manager
		*/
		std::string textureName{ "default" };
		std::string meshName{ "default" };
		std::string shaderName{ "default" };
		//Flag for when temporary asset has been changed and need to be re-loaded in by asset manager
		bool compiled = false;

		//Color variable for use to modulate texture/image
		glm::vec4 color{1.f,1.f,1.f,1.f};

		//U start, U end, V start, V end
		glm::vec4 UV{ 0.f,1.f,0.f,1.f };

		//Render order
		RenderLayer render_layer{ R_WORLD };
	public:
		/*
		* Setter functions which wrap setting of temporary name as well as flagging for reload with asset manager
		*/
		void SetTexture(std::string, bool force = false);
		void SetMesh(std::string const&);
		void SetShader(std::string const&);
		void SetColor(glm::vec4 const&);
		void SetRenderLayer(RenderLayer);

		void SetTex_U(glm::vec2 const&);
		void SetTex_V(glm::vec2 const&);
		void SetTex_UV(glm::vec4 const&);
		void SetTex_UV(glm::vec4&&);


		RenderLayer GetRenderLayer() const;

		friend System::SRender;
		friend RenderPipeline;
	};

	/*
	* Function object to sort render layer
	*/
	struct {
		bool operator()(ECS::Entity const& lhs, ECS::Entity const& rhs) {
			return lhs.GetComponent<CRenderable>().GetRenderLayer() < rhs.GetComponent<CRenderable>().GetRenderLayer();
		}
	} RenderSort;

	/*
	* Current Implementation of a Sprite Animation Asset
	* Still unsure whether this should be a seperate form of text file or some form of data structure
	* potentially serialized into a json, need to think more about this
	*/
	class SpriteAnimationAsset {
	private:
		//Array of UVs for each sprite frame
		std::vector<glm::vec4> sprite_UVs{};
		GLfloat time_per_frame{ 1.f };
		//Current time of frame
		GLfloat currentTime{};
		//Index of current frame
		std::size_t currentUV{};

		bool loop{ true };
	public:
		//Name of texture it is referring to, this structure will need to be re considered for mapping of sprite animation data and target texture
		std::string textureName{};
		//Reset animation
		void Reset();
		//Update animation timer
		void Update(GLfloat);
		glm::vec4 GetCurrentUV() const;

		//Factory
		static SpriteAnimationAsset CreateSpriteAsset(std::vector<glm::vec4> const&, GLfloat, std::string);
		static SpriteAnimationAsset CreateSpriteAsset(std::vector<glm::vec4> &&, GLfloat, std::string);
	};		
	
	//State Machine for animator
	struct SpriteStateMachine {
		//vector of state transitions
		//start state, condition, end state
		std::vector<std::tuple<std::string, bool(*)(ECS::Entity const&), std::string>> state_transitions;
	};

	//Component that deals with sprite animation, will need to invert logic into system and not here
	//Currently feels like its dealing with both sprite animation and transition, need to think more about structure of this
	class CSpriteAnimator {
	private:
		//Underlying transition state machine
		SpriteStateMachine state_machine;
		//Access to each sprite animation asset
		std::unordered_map<std::string, SpriteAnimationAsset> animation_map;
		//Handles to current and starting animation
		std::string currentAnimation{};
		std::string startAnimation{};
	public:
		void AddAnimation(std::string, SpriteAnimationAsset const&);
		void AddAnimation(std::string, SpriteAnimationAsset&&);
		void AddTransition(std::string, bool(*)(ECS::Entity const&), std::string);
		void Update(GLfloat, ECS::Entity const&);
		void SetStartAnimation(std::string const&);

		std::string GetCurrentTexture() const;
		glm::vec4 GetUV() const;
	};

	//Forward
	class Camera2d;

	/*
	* Class that contains the pipeline to draw something to the window
	* Wrapper for the draw pipeline
	* Currently extremely basic, takes in 1 draw command, and draws to screen
	* Keeps track of camera, which should be split into its own component and system
	* Ownership of control of viewport is unsure right now as well
	* 
	* Uses assets from cpu memory, loads into gpu store, returns handle - eventually restructure to asset manager
	* GLFWwindow management for seperate window rendering
	*/
	class RenderPipeline {
		//Current window to draw on
		GLFWwindow* target_window{};
		//Temporary location to place camera
		Camera2d* camera{};
		//Viewport
		GLint view_width{}, view_height{};
		//std::multiset<CRenderable> objects;
		void FB_callback(GLFWwindow* window, int width, int height);
		//Converts a UV to a matrix to implement mapping- probably should not be here
		glm::mat3 GetMtx_UV(glm::vec4 const& UV) const;

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
	};

	//For now just assume only 1 camera and its not a component
	class Camera2d {
		//Up and down vectors
		glm::vec2 right{}, up{};
		//world to view xform
		glm::mat3 view_xform{};

		//------------TEMPORARY!!!!!!!
		glm::vec2 position{};

		//height of cam
		GLint height{ 1000 };
		//zoom limits
		GLint min_height{};
		GLint max_height{};
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

	//System that tells entities with animator component to update and check its state
	//Will need to invert logic so that it is here in the system and not with the component
	class SAnimator : public ECS::System 
	{
	public:
		SAnimator();
		void Update(GLfloat);
	};
}

#endif