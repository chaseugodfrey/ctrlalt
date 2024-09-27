#include "Render.h"

#include <array>
#include <iostream>
#include <cassert>

//ONLY INCLUDE STB_IMAGE HERE
#define STB_IMAGE_IMPLEMENTATION
//#define STBI_MALLOC
//#define STBI_REALLOC
//#define STBI_FREE
#include "STB_Image/stb_image.h"

////Search Asset directory for asset files
#include <filesystem>
#include <iostream>
#include "../Logger/Logger.h"

//Some commnets
//New branch maybe
namespace Render {
	GLFWwindow* render_window = nullptr;

	/************************************/
	//Renderable
	/************************************/
	
	//Sorting operation for priority queue
	//bool operator < (CRenderable const& lhs, CRenderable const& rhs) {
	//	if (lhs.textureHandle < rhs.textureHandle) {
	//		return true;
	//	}
	//	else if (lhs.shaderHandle < rhs.shaderHandle) {
	//		return true;
	//	}
	//	else if (lhs.meshHandle < rhs.meshHandle) {
	//		return true;
	//	}
	//	return false;
	//}

	/************************************/
	//Render Pipeline
	/************************************/

	//Once Renderpipeline is created, glew should be init
	RenderPipeline::RenderPipeline() {
		glewInit();

		glClearColor(1.f, 0.f, 1.f, 1.f);
	}

	GLFWwindow* RenderPipeline::CreateNewWindow(GLint width, GLint height) {
		//Create window hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);


		GLFWwindow* new_window = glfwCreateWindow(width, height, "Render", NULL, NULL);
		if (!new_window) {
			std::cerr << "GLFW unable to create OpenGL context - abort program\n";
			glfwTerminate();
			return nullptr;
		}
		return new_window;
	}
	void RenderPipeline::SetCurrentWindow(GLFWwindow* window) {
		target_window = window;
	}

	void RenderPipeline::SetupDraw() {
		glfwMakeContextCurrent(target_window);
		glClearColor(1.f,0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void RenderPipeline::Draw(CRenderable const& renderable) {
		GLSLShader& shdr_pgm = (*renderable.shader_handle).second;
		GLModel& model = (*renderable.modelHandle).second;
		GLuint tex = (*renderable.textureHandle).second;

		shdr_pgm.Use();

		glBindVertexArray(model.vao_ID);

		//Use texture unit 0
		glBindTextureUnit(0, tex);

		//Get Uniform1i to pass texture unit to shader
		GLuint uniform_var_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uTex2d");
		if (uniform_var_loc >= 0) {
			glUniform1i(uniform_var_loc, 0);
		}
		else {
			std::cout << "Uniform Variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}

		glDrawElements(model.primitive_type, model.draw_cnt, GL_UNSIGNED_SHORT, NULL);

		glBindVertexArray(0);

		shdr_pgm.UnUse();
	}
	////Inits glfw window - not sure if it should be here
	//void RenderPipeline::Init(GLint width, GLint height, std::string const& window_title) {
	//	//If no window, create a window - temporary since supposed to just draw to an fbo
	//	if (ptr_window == nullptr) {
	//		//Create window hints
	//		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	//		glfwWindowHint(GLFW_DEPTH_BITS, 24);
	//		glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
	//		glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);


	//		glClearColor(1.f, 1.f, 1.f, 1.f);

	//		render_window = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
	//		if (!render_window) {
	//			std::cerr << "GLFW unable to create OpenGL context - abort program\n";
	//			glfwTerminate();
	//			return;
	//			//return false;
	//		}
	//		glfwMakeContextCurrent(render_window);
	//		glEnable(GL_DEPTH_TEST);	//depth is written in fragment shader
	//	}

	//	//GLHelper::init(width, height, window_title, ptr_window);

	//	//GLHelper::print_specs();

	//	//Init the actual graphics stuff here
	//	//My assetloader is jsut a bunch of functions for now ig
	//	AssetLoader loader;
	//	loader.LoadGraphics(*this);
	//}

	//Draw all objects
	//void RenderPipeline::Draw() {
	//	glfwMakeContextCurrent(render_window);
	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//}

	//Cleanup any resources allocated
	void RenderPipeline::Cleanup() {
		glfwTerminate();
	}


	GLuint RenderPipeline::LoadTexture(Engine::ImageAsset const& texture) {
		GLuint textureID{};

		//Create handle to texture loaded into gpu memory
		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		//Allocate space, similar to namedstorage
		glTextureStorage2D(textureID, 1, GL_RGBA8, texture.width, texture.height);
		//Put texture data into space, similar to substorage
		glTextureSubImage2D(textureID, 0, 0, 0, texture.width, texture.height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)texture.image_data);

		return textureID;
	}

	//Release texture from gpu store, can be an array or just individual
	void RenderPipeline::ReleaseTexture(GLuint texture_array) {
		glDeleteTextures(1, &texture_array);
	}

	GLModel RenderPipeline::LoadModel_Triangles(std::vector<glm::vec2> const& vtx_data, std::vector<GLushort> const& idx_data) {
		GLModel mdl;

		//Create VBO - storage of data
		GLuint vbo_hdl;
		glCreateBuffers(1, &vbo_hdl);
		mdl.vbo_ID = vbo_hdl;
		//not nullptr cuz ur directly transfering the data into buffer, if nullptr need to use glNamedBufferSubData
		glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * vtx_data.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo_hdl, 0,
			sizeof(glm::vec2) * vtx_data.size(), vtx_data.data());

		//Setup vao - object that inteprets data
		GLuint vaoObjects[1]; //<this could probably work
		glCreateVertexArrays(1, vaoObjects);
		mdl.vao_ID = vaoObjects[0];

		//Pos Attributes
		glEnableVertexArrayAttrib(mdl.vao_ID, 0);	//Enable slot 0
		//use binding index 0, vbo, start from 0 bytes from memory, each ele sizeof vec2
		glVertexArrayVertexBuffer(mdl.vao_ID, 0, vbo_hdl, 0, sizeof(glm::vec2));
		glVertexArrayAttribFormat(mdl.vao_ID, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(mdl.vao_ID, 0, 0);

		//Topology
		GLuint ebo_hdl;
		glCreateBuffers(1, &ebo_hdl);
		glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_data.size(),
			idx_data.data(), GL_DYNAMIC_STORAGE_BIT);

		glVertexArrayElementBuffer(mdl.vao_ID, ebo_hdl);

		//unbind
		glBindVertexArray(0);

		mdl.primitive_type = GL_TRIANGLES;
		mdl.draw_cnt = static_cast<GLuint>(idx_data.size());
		mdl.primitive_cnt = static_cast<GLuint>(idx_data.size() / 3);

		return mdl;
	}


	/************************************/
	//AssetManager
	/************************************/
	void AssetLoader::LoadGraphics(RenderPipeline& render) {
		//Init all textures here
		
		//Init all meshes here, would read from file and stuff,
		//GLModel mdl = LoadQuad();
		//render.AddMesh("quad", std::move(mdl));
	}

	GLModel AssetLoader::LoadQuad() {
		//Init basic quad
		std::vector<glm::vec2> pos_vtx{
		glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, -0.5f),
		glm::vec2(0.5f, 0.5f),	 glm::vec2(-0.5f, 0.5f)
		};

		std::array<GLushort, 6> idx_vtx{
			0,1,3,
			1,2,3
		};

		GLModel mdl;

		//Create VBO - storage of data
		GLuint vbo_hdl;
		glCreateBuffers(1, &vbo_hdl);
		mdl.vbo_ID = vbo_hdl;
		//not nullptr cuz ur directly transfering the data into buffer, if nullptr need to use glNamedBufferSubData
		glNamedBufferStorage(vbo_hdl, sizeof(glm::vec2) * pos_vtx.size(), nullptr, GL_DYNAMIC_STORAGE_BIT);
		glNamedBufferSubData(vbo_hdl, 0,
			sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data());

		//Setup vao - object that inteprets data
		GLuint vaoObjects[1]; //<this could probably work
		glCreateVertexArrays(1, vaoObjects);
		mdl.vao_ID = vaoObjects[0];

		//Pos Attributes
		glEnableVertexArrayAttrib(mdl.vao_ID, 0);	//Enable slot 0
		//use binding index 0, vbo, start from 0 bytes from memory, each ele sizeof vec2
		glVertexArrayVertexBuffer(mdl.vao_ID, 0, vbo_hdl, 0, sizeof(glm::vec2));
		glVertexArrayAttribFormat(mdl.vao_ID, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(mdl.vao_ID, 0, 0);

		//Topology
		GLuint ebo_hdl;
		glCreateBuffers(1, &ebo_hdl);
		glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_vtx.size(),
			reinterpret_cast<GLvoid*>(idx_vtx.data()), GL_DYNAMIC_STORAGE_BIT);

		glVertexArrayElementBuffer(mdl.vao_ID, ebo_hdl);

		//unbind
		glBindVertexArray(0);

		mdl.primitive_type = GL_TRIANGLES;
		mdl.draw_cnt = static_cast<GLuint>(idx_vtx.size());
		mdl.primitive_cnt = 2;
		return mdl;
	}
}

namespace System {
	SRender::SRender()
	{
		RequireComponent<Render::CRenderable>();

		//Setup Render pipeline
		render_pipeline.SetCurrentWindow(render_pipeline.CreateNewWindow());

		//Load Assets
		static const char* asset_directory = "../Assets/";
		static const char* png_extention = ".png";
		static const char* vtx_extention = ".vert";
		static const char* frg_extention = ".frag";
		Logger::LogInfo("Loading Assets..");
		std::vector<Engine::ImageAsset> image_data;
		std::vector<std::filesystem::path> vtx_shaders;
		std::vector<std::filesystem::path> frg_shaders;
		//Loop get all of png extension in asset directory
		for (std::filesystem::directory_entry const& dir : 
			std::filesystem::recursive_directory_iterator(asset_directory)) {
			//Prints path of asset, filename of asset without ext, ext of asset
			std::cout << "Path: " << dir.path() << " Asset: " << dir.path().stem() << " Extention: " << dir.path().extension() << std::endl;
			//.png
			if (dir.path().extension() == png_extention) {
				int x{}, y{}, n{};
				unsigned char* data = stbi_load(static_cast<const char*>(dir.path().string().c_str()), &x, &y, &n, STBI_rgb_alpha);
				if (data == NULL) {
					Logger::LogInfo(std::string("ERROR: Unable to load: ") + dir.path().filename().string().c_str());	//shouldnt reach here
					continue;
				}
				image_data.push_back({ data, x, y, dir.path().stem().string() });
			}
			//.vert
			else if (dir.path().extension() == vtx_extention) {
				vtx_shaders.push_back(dir.path());
			}
			//.frag
			else if (dir.path().extension() == frg_extention) {
				frg_shaders.push_back(dir.path());
			}
		}
		Logger::LogInfo("Assets loaded..");

		//Setting up texture handles
		Logger::LogInfo("Loading Image to GPU..");
		for (Engine::ImageAsset const& image : image_data) {
			GLuint texture_handle = render_pipeline.LoadTexture(image);
			texture_map.insert({ image.name, texture_handle });
		}
		Logger::LogInfo("Image in GPU done..");

		//Release Assets
		Logger::LogInfo("Releasing Image Data");
		for (Engine::ImageAsset const& image : image_data) {
			stbi_image_free(image.image_data);
		}
		Logger::LogInfo(std::string("Released Image Data"));

		//Constructing shader programs
		//For now assume that there is only 1 vtx and frg shader
		assert((vtx_shaders.size() != 1 || frg_shaders.size() != 1) || "There should only be one set of shaders!");

		GLSLShader shader_pgm;
		std::vector<std::pair<GLenum, std::string>> shdr_files{
			std::make_pair(GL_VERTEX_SHADER, vtx_shaders[0].string()),
			std::make_pair(GL_FRAGMENT_SHADER, frg_shaders[0].string()) };
		shader_pgm.CompileLinkValidate(shdr_files);
		shader_map.insert({ "default", shader_pgm });

		LoadDefaults();
	}

	SRender::~SRender() {
		//Release Textures
		Logger::LogInfo("Release Image from GPU...");
		for (std::pair<std::string, GLuint> const& kvp : texture_map) {
			render_pipeline.ReleaseTexture(kvp.second);
		}
		Logger::LogInfo("Image Release done..");

		Logger::LogInfo("Release GPU Buffers...");
		//Release vaos
		for (std::pair<std::string, Render::GLModel> const& kvp : model_map) {
			glDeleteBuffers(1, &kvp.second.vbo_ID);
			glDeleteVertexArrays(1, &kvp.second.vao_ID);
		}
		Logger::LogInfo("GPU Buffer done..");


		//Release Shaders done via destructor
	}

	void SRender::LoadDefaults() {
		Logger::LogInfo("Setting up defaults");
		unsigned char default_color[] = {255,255,255,255};
		Engine::ImageAsset default_image{default_color, 1, 1, "default"};

		GLuint texture_handle = render_pipeline.LoadTexture(default_image);
		texture_map.insert({ default_image.name, texture_handle });
		Logger::LogInfo("Default Image");

		Logger::LogInfo("Default Quad");
		std::vector<glm::vec2> pos_vtx{
		glm::vec2(-0.5f, -0.5f), glm::vec2(0.5f, -0.5f),
		glm::vec2(0.5f, 0.5f),	 glm::vec2(-0.5f, 0.5f)
		};

		std::vector<GLushort> idx_vtx{
			0,1,3,
			1,2,3
		};
		Render::GLModel mdl = render_pipeline.LoadModel_Triangles(pos_vtx, idx_vtx);
		model_map.insert({ "default", mdl });
		Logger::LogInfo("Finished defaults");
	}

	//Only Render Function, basically goto all the draw calls
	void SRender::Render()
	{
		render_pipeline.SetupDraw();
		for (ECS::Entity const& entity : GetEntities())
		{
			Render::CRenderable& renderable = entity.GetComponent<Render::CRenderable>();
			//Setup component if not setup yet
			if (!renderable.compiled) {
				renderable.textureHandle = texture_map.find(renderable.textureName) != texture_map.end() 
					? texture_map.find(renderable.textureName) : texture_map.find("default");

				renderable.shader_handle = shader_map.find(renderable.shaderName) != shader_map.end()
					? shader_map.find(renderable.shaderName) : shader_map.find("default");

				renderable.modelHandle = model_map.find(renderable.meshName) != model_map.end() 
					? model_map.find(renderable.meshName) : model_map.find("default");

				renderable.compiled = true;
			}
			render_pipeline.Draw(renderable);
			//render_pipeline.Draw(renderable);
			//Logger::LogInfo("ENTITY: " + std::to_string(entity.GetID()) + " POS: (" + std::to_string((int)transform.position.x) + ", " + std::to_string((int)transform.position.y) + ')');
		}
	}
}