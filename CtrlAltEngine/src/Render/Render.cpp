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
#include "../Components/CTransform.h"
#include <glm/gtc/type_ptr.hpp>
//namespace 




namespace Render {

	/************************************/
	//Renderable
	/************************************/
	void CRenderable::SetTexture(std::string name) {
		textureName = name;
		compiled = false;
	}
	void CRenderable::SetMesh(std::string name) {
		meshName = name;
		compiled = false;
	}
	void CRenderable::SetShader(std::string name) {
		shaderName = name;
		compiled = false;
	}
	void CRenderable::SetColor(glm::vec4 col) {
		color = col;
	}

	void CRenderable::SetRenderLayer(RenderLayer layer) {
		render_layer = layer;
	}

	CRenderable::RenderLayer CRenderable::GetRenderLayer() const {
		return render_layer;
	}
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
	}

	GLFWwindow* RenderPipeline::CreateTargetWindow(GLint width, GLint height) {
		view_width = width;
		view_height = height;

		//Create window hints
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		glfwWindowHint(GLFW_RED_BITS, 8); glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8); glfwWindowHint(GLFW_ALPHA_BITS, 8);

		//CheckGLError();

		target_window = glfwCreateWindow(width, height, "Render", NULL, NULL);
		if (!target_window) {
			std::cerr << "GLFW unable to create OpenGL context - abort program\n";
			glfwTerminate();
			return nullptr;
		}
		glfwMakeContextCurrent(target_window);
		glViewport(0, 0, width, height);

		//Workaround no static function
		glfwSetWindowUserPointer(target_window, this);
		glfwSetFramebufferSizeCallback(target_window, [](GLFWwindow* window, int width, int height) {
			static_cast<RenderPipeline*>(glfwGetWindowUserPointer(window))->FB_callback(window, width, height);
			});
		//glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND); 
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glewInit();
		glClearColor(1.f, 0.f, 1.f, 1.f);

		CheckGLError();
		return target_window;
	}


	void RenderPipeline::SetCamera(Camera2d* cam) {
		camera = cam;
	}

	void RenderPipeline::FB_callback(GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		view_width = width;
		view_height = height;
		camera->UpdateViewtoNDC(width, height);
	}

	void RenderPipeline::SetTargetWindow(GLFWwindow* window) {
		CheckGLError();
		if (window) {
			target_window = window;
		}
		CheckGLError();
	}
	void RenderPipeline::SetTargetAsCurrent() {
		CheckGLError();
		if (target_window) {
			glfwMakeContextCurrent(target_window);
		}
		CheckGLError();
	}
	void RenderPipeline::DeleteCurrentWindow() {
		if (target_window) {
			glfwDestroyWindow(target_window);
		}
		target_window = nullptr;
	}
	GLFWwindow const* RenderPipeline::GetCurrentWindow() {
		return target_window;
	}

	void RenderPipeline::StartDraw() {
		CheckGLError();
		SetTargetAsCurrent();
		CheckGLError();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		CheckGLError();
	}
	void RenderPipeline::FinishDraw() {
		CheckGLError();
		glfwSwapBuffers(target_window);
		CheckGLError();
	}

	void RenderPipeline::Draw(CRenderable const& renderable, glm::mat3 const& tform) {
		CheckGLError();
		GLSLShader& shdr_pgm = (*renderable.shader_handle).second;
		GLModel& model = (*renderable.modelHandle).second;
		GLuint tex = (*renderable.textureHandle).second;

		shdr_pgm.Use();
		CheckGLError();
		glBindVertexArray(model.vao_ID);
		CheckGLError();

		//Use texture unit 0
		glBindTextureUnit(6, tex);
		CheckGLError();

		//Get Uniform1i to pass texture unit to shader
		GLuint uniform_var_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uTex2d");
		CheckGLError();
		if (uniform_var_loc >= 0) {
			glUniform1i(uniform_var_loc, 6);
		}
		else {
			std::cout << "Uniform Variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}
		CheckGLError();

		//Add modulate color, for now 1, 1
		uniform_var_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uColor");
		CheckGLError();
		if (uniform_var_loc >= 0) {
			glUniform4f(uniform_var_loc, renderable.color[0], renderable.color[1], renderable.color[2], renderable.color[3]);
			CheckGLError();
		}
		else {
			std::cout << "Uniform Variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}
		CheckGLError();

		//Upload xform mtx
		uniform_var_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uModel_to_NDC");
		if (uniform_var_loc >= 0) {
			//put value of matrix in it
			glUniformMatrix3fv(uniform_var_loc, 1, GL_FALSE, glm::value_ptr(tform));
		}
		else {
			std::cout << "Uniform Variable doesn't exist!!!\n";
			std::exit(EXIT_FAILURE);
		}
		CheckGLError();

		glDrawElements(model.primitive_type, model.draw_cnt, GL_UNSIGNED_SHORT, NULL);

		glBindVertexArray(0);
		CheckGLError();

		shdr_pgm.UnUse();
		CheckGLError();
	}

	//Cleanup any resources allocated
	void RenderPipeline::Cleanup() {
	}


	GLuint RenderPipeline::LoadTexture(Engine::ImageAsset const& texture) {
		CheckGLError();
		GLuint textureID{};

		//Create handle to texture loaded into gpu memory
		glCreateTextures(GL_TEXTURE_2D, 1, &textureID);
		CheckGLError();
		//Allocate space, similar to namedstorage
		glTextureStorage2D(textureID, 1, GL_RGBA8, texture.width, texture.height);
		CheckGLError();
		//Put texture data into space, similar to substorage
		glTextureSubImage2D(textureID, 0, 0, 0, texture.width, texture.height, GL_RGBA, GL_UNSIGNED_BYTE, (void*)texture.image_data);
		CheckGLError();

		return textureID;
	}

	//Release texture from gpu store, can be an array or just individual
	void RenderPipeline::ReleaseTexture(GLuint texture_array) {
		CheckGLError();
		glDeleteTextures(1, &texture_array);
		CheckGLError();
	}

	GLModel RenderPipeline::LoadModel_Triangles(std::vector<GLVertStruct> const& vtx_data, std::vector<GLushort> const& idx_data) {
		CheckGLError();
		GLModel mdl;

		//Create VBO - storage of data
		GLuint vbo_hdl;
		glCreateBuffers(1, &vbo_hdl);
		mdl.vbo_ID = vbo_hdl;
		//not nullptr cuz ur directly transfering the data into buffer, if nullptr need to use glNamedBufferSubData
		glNamedBufferStorage(vbo_hdl, sizeof(GLVertStruct) * vtx_data.size(), vtx_data.data(), GL_DYNAMIC_STORAGE_BIT);
		CheckGLError();

		//Setup vao - object that inteprets data
		//GLuint vaoObjects[1]; //<this could probably work
		glCreateVertexArrays(1, &mdl.vao_ID);
		CheckGLError();

		//Pos and UV Attributes
		glEnableVertexArrayAttrib(mdl.vao_ID, 0);	//Enable slot 0
		glEnableVertexArrayAttrib(mdl.vao_ID, 1);	//Enable slot 1


		//Setup VAO attributes
		glVertexArrayVertexBuffer(mdl.vao_ID, 0, vbo_hdl, 0, sizeof(GLVertStruct));
		glVertexArrayVertexBuffer(mdl.vao_ID, 1, vbo_hdl, sizeof(glm::vec2), sizeof(GLVertStruct));

		glVertexArrayAttribFormat(mdl.vao_ID, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribFormat(mdl.vao_ID, 1, 2, GL_FLOAT, GL_FALSE, 0);

		glVertexArrayAttribBinding(mdl.vao_ID, 0, 0);
		glVertexArrayAttribBinding(mdl.vao_ID, 1, 1);
		CheckGLError();

		//Topology
		GLuint ebo_hdl;
		glCreateBuffers(1, &ebo_hdl);
		CheckGLError();
		glNamedBufferStorage(ebo_hdl, sizeof(GLushort) * idx_data.size(),
			idx_data.data(), GL_DYNAMIC_STORAGE_BIT);
		CheckGLError();

		glVertexArrayElementBuffer(mdl.vao_ID, ebo_hdl);
		CheckGLError();

		//unbind
		glBindVertexArray(0);
		CheckGLError();
		mdl.primitive_type = GL_TRIANGLES;
		mdl.draw_cnt = static_cast<GLuint>(idx_data.size());
		mdl.primitive_cnt = static_cast<GLuint>(idx_data.size() / 3);

		return mdl;
		CheckGLError();
	}

	//Everything here should be data driven for camera default values - todo next
	void Camera2d::Init(GLint vp_width, GLint vp_height) {
		//For now just set normal orientation
		right = { 1.f,0.f };
		up = { 0.f,1.f };

		//an object of scale 1, 1 will take up 1/10 of the height screen
		height = 10;
		/*min_height = 500;
		max_height = 2000;

		height_chng_speed = 100;*/
		
		UpdateViewtoNDC(vp_width, vp_height);
		SetPosition(0.f, 0.f);
	}

	//Updates view to ndc mtx
	void Camera2d::UpdateViewtoNDC(GLint view_width, GLint view_height) {
		ar = static_cast<GLfloat>(view_width) / static_cast<GLfloat>(view_height);
		GLint width = (GLint)(ar * height);
		camwin_to_ndc_xform = glm::mat3{
			glm::vec3(2.f / width, 0, 0),
			glm::vec3(0, 2.f / height, 0),
			glm::vec3(0.f, 0.f, 1.f)
		};
		camwin_to_ndc_xform = glm::transpose(camwin_to_ndc_xform);
		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}

	void Camera2d::SetPosition(GLfloat x, GLfloat y) {
		position = { x, y };

		//Update world to view mtx
		GLfloat transX = glm::dot(right, position);
		GLfloat transY = glm::dot(up, position);
		glm::mat3 first_person_view{
			glm::vec3(right.x, right.y, -transX),
			glm::vec3(up.x, up.y, -transY),
			glm::vec3(0.f, 0.f, 1.f)
		};
		view_xform = glm::transpose(first_person_view);

		world_to_ndc_xform = camwin_to_ndc_xform * view_xform;
	}

	glm::mat3 Camera2d::GetWorldtoNDC() {
		return world_to_ndc_xform;
	}
}

namespace System {
	SRender::SRender()
	{
		RequireComponent<Render::CRenderable>();

		//Setup Render pipeline
		render_pipeline.CreateTargetWindow(900, 480);
		camera.Init(900, 480);

		//render_pipeline.SetT(render_pipeline.CreateNewWindow());
		CheckGLError();
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
		shader_map.insert({ "default", std::move(shader_pgm) });

		LoadDefaults();
		CheckGLError();
	}

	void SRender::Destroy() {
		render_pipeline.SetTargetAsCurrent();
		//Release Textures
		Logger::LogInfo("Release Image from GPU...");
		CheckGLError();
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
		CheckGLError();

		Logger::LogInfo("Releasing Shaders..");
		for (auto it = shader_map.begin(); it != shader_map.end(); ++it) {
			it->second.DeleteShaderProgram();
		}
		Logger::LogInfo("Shaders Released..");
		CheckGLError();

		render_pipeline.DeleteCurrentWindow();
	}

	void SRender::LoadDefaults() {
		CheckGLError();
		Logger::LogInfo("Setting up defaults");
		unsigned char default_color[] = {255,255,255,255};
		Engine::ImageAsset default_image{default_color, 1, 1, "default"};

		GLuint texture_handle = render_pipeline.LoadTexture(default_image);
		texture_map.insert({ default_image.name, texture_handle });
		Logger::LogInfo("Default Image");

		Logger::LogInfo("Default Quad");
		std::vector<Render::GLVertStruct> pos_vtx{
			{ glm::vec2(-.5f, -.5f),  glm::vec2(0.f, 0.f)},
			{ glm::vec2(.5f, -.5f),	glm::vec2(1.f, 0.f)},
			{ glm::vec2(.5f, .5f),	glm::vec2(1.f,1.f)},
			{ glm::vec2(-.5f, .5f),	glm::vec2(0.f,1.f)}
		};

		std::vector<GLushort> idx_vtx{
			0,1,3,
			1,2,3
		};
		Render::GLModel mdl = render_pipeline.LoadModel_Triangles(pos_vtx, idx_vtx);
		model_map.insert({ "default", mdl });
		Logger::LogInfo("Finished defaults");

		CheckGLError();
	}

	//Only Render Function, basically goto all the draw calls
	void SRender::Render()
	{
		CheckGLError();
		render_pipeline.StartDraw();
		//Create a copy of the array because entity vector is used for ecs indexing
		std::vector<ECS::Entity> entity_copy = GetEntities();
		std::sort(entity_copy.begin(), entity_copy.end(), Render::RenderSort);
		for (ECS::Entity const& entity : entity_copy)
		{
			Render::CRenderable& renderable = entity.GetComponent<Render::CRenderable>();

			glm::mat3 tform_mtx = glm::identity<glm::mat3>();

			//Scale, Rotate, Translate
			glm::mat3 scale = glm::identity<glm::mat3>();
			glm::mat3 rotate = glm::identity<glm::mat3>();
			glm::mat3 translate = glm::identity<glm::mat3>();

			//Check if have transform comp
			if (entity.HasComponent<Component::CTransform>()) {
				Component::CTransform& transform = entity.GetComponent<Component::CTransform>();

				//Scale, Rotate, Translate
				scale = {
					glm::vec3(transform.scale.X(), 0 ,0),
					glm::vec3(0, transform.scale.Y(), 0),
					glm::vec3(0, 0, 1.f)
				};

				GLfloat orientation_Rad = glm::radians(transform.rotation);
				rotate = {
					glm::vec3(cosf(orientation_Rad), -sinf(orientation_Rad), 0.f),
					glm::vec3(sinf(orientation_Rad), cosf(orientation_Rad), 0.f),
					glm::vec3(0.f, 0.f, 1.f)
				};
				rotate = glm::transpose(rotate);

				translate = {
					glm::vec3(1.f, 0.f, transform.position.X()),
					glm::vec3(0.f, 1.f, transform.position.Y()),
					glm::vec3(0.f, 0.f, 1.f)
				};
				translate = glm::transpose(translate);

				
			}

			tform_mtx = camera.GetWorldtoNDC() * translate * rotate * scale * tform_mtx;
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
			render_pipeline.Draw(renderable, tform_mtx);
			//render_pipeline.Draw(renderable);
			//Logger::LogInfo("ENTITY: " + std::to_string(entity.GetID()) + " POS: (" + std::to_string((int)transform.position.x) + ", " + std::to_string((int)transform.position.y) + ')');
		}


		render_pipeline.FinishDraw();

		CheckGLError();
	}
}

//namespace 


	void _CheckGLError(const char* file, int line)
	{
#ifndef DEBUG
		return;
#endif // only do this on debug

		GLenum err(glGetError());

		while (err != GL_NO_ERROR)
		{
			std::string error;
			switch (err)
			{
			case GL_INVALID_OPERATION:  error = "INVALID_OPERATION";      break;
			case GL_INVALID_ENUM:       error = "INVALID_ENUM";           break;
			case GL_INVALID_VALUE:      error = "INVALID_VALUE";          break;
			case GL_OUT_OF_MEMORY:      error = "OUT_OF_MEMORY";          break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:  error = "INVALID_FRAMEBUFFER_OPERATION";  break;
			}
			std::cout << "GL_" << error.c_str() << " - " << file << ":" << line << std::endl;
			err = glGetError();
		}

		return;
	}
