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

#include "../Input/Input.h"
#include "../Components/CCollider.h"

//Temp measure to get access to engine's global input
extern Input::Input_Container global_input;
//namespace 

namespace Render {

	/************************************/
	//Renderable
	/************************************/
	void CRenderable::SetTexture(std::string name, bool force) {
		if (textureName == name && !force) {
			return;
		}
		textureName = name;
		compiled = false;
	}
	void CRenderable::SetMesh(std::string const& name) {
		meshName = name;
		compiled = false;
	}
	void CRenderable::SetShader(std::string const& name) {
		shaderName = name;
		compiled = false;
	}
	void CRenderable::SetColor(glm::vec4 const& col) {
		color = col;
	}

	void CRenderable::SetRenderLayer(RenderLayer layer) {
		render_layer = layer;
	}

	//UV Setting
	void CRenderable::SetTex_U(glm::vec2 const& u) {
		UV[0] = u[0];
		UV[1] = u[1];
	}
	void CRenderable::SetTex_V(glm::vec2 const& v) {
		UV[2] = v[0];
		UV[3] = v[1];
	}
	void CRenderable::SetTex_UV(glm::vec4 const& uv) {
		UV = uv;
	}
	void CRenderable::SetTex_UV(glm::vec4&& uv) {
		UV = std::move(uv);
	}
	CRenderable::RenderLayer CRenderable::GetRenderLayer() const {
		return render_layer;
	}


	/************************************/
	//SpriteAnimation
	/************************************/
	SpriteAnimationAsset SpriteAnimationAsset::CreateSpriteAsset(std::vector<glm::vec4> const& uv, GLfloat time, std::string tex) {
		SpriteAnimationAsset asset;
		asset.sprite_UVs = uv;
		asset.time_per_frame = time;
		asset.currentTime = time;
		asset.textureName = tex;
		return asset;
	}
	SpriteAnimationAsset SpriteAnimationAsset::CreateSpriteAsset(std::vector<glm::vec4>&& uv, GLfloat time, std::string tex) {
		SpriteAnimationAsset asset;
		asset.sprite_UVs = std::move(uv);
		asset.time_per_frame = time;
		asset.currentTime = time;
		asset.textureName = tex;
		return asset;
	}
	void SpriteAnimationAsset::Reset() {
		currentTime = time_per_frame;
		currentUV = 0;
	}
	void SpriteAnimationAsset::Update(GLfloat dt) {
		currentTime -= dt;
		//Wrap and move current frame
		if (currentTime <= 0.f) {
			currentTime = time_per_frame + currentTime;
			currentUV = (currentUV + 1) % sprite_UVs.size();
		}
	}

	glm::vec4 SpriteAnimationAsset::GetCurrentUV() const {
		return sprite_UVs[currentUV];
	}

	/************************************/
	//SpriteAnimator
	/************************************/

	void CSpriteAnimator::AddAnimation(std::string name, SpriteAnimationAsset const& asset) {
		animation_map.insert({ name, asset });
	}
	void CSpriteAnimator::AddAnimation(std::string name, SpriteAnimationAsset&& asset) {
		animation_map.insert({ name, std::move(asset) });
	}

	void CSpriteAnimator::AddTransition(std::string start, bool(*condition)(ECS::Entity const&), std::string target) {
		state_machine.state_transitions.push_back({ start, condition, target });
	}
	void CSpriteAnimator::SetStartAnimation(std::string const& anim) {
		currentAnimation = anim;
		startAnimation = anim;
	}


	void CSpriteAnimator::Update(GLfloat dt, ECS::Entity const& entity) {
		//Check state machine
		for (auto& state : state_machine.state_transitions) {
			if (std::get<0>(state) == currentAnimation && std::get<1>(state)(entity)) {
				currentAnimation = std::get<2>(state);
				animation_map.at(currentAnimation).Reset();
				break;
			}
		}
		//Update sprite frames
		animation_map.at(currentAnimation).Update(dt);
	}

	glm::vec4 CSpriteAnimator::GetUV() const {
		return animation_map.at(currentAnimation).GetCurrentUV();
	}

	std::string CSpriteAnimator::GetCurrentTexture() const {
		return animation_map.at(currentAnimation).textureName;
	}

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
		if (window) {};
		glViewport(0, 0, width, height);
		view_width = width;
		view_height = height;
		camera->UpdateViewtoNDC(width, height);
	}

	glm::mat3 RenderPipeline::GetMtx_UV(glm::vec4 const& uv) const{
		GLfloat uLength = uv[1] - uv[0];
		GLfloat vLength = uv[3] - uv[2];
		glm::mat3 uvMtx{
			glm::vec3{uLength, 0.f, uv[0]},
			glm::vec3{0.f, vLength, uv[2]},
			glm::vec3{0.f,0.f,1.f}
		};

		return glm::transpose(uvMtx);
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

	//Setups for render pipeline if required
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

	//Draw an individual render component
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

		uniform_var_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uUV_tform");
		CheckGLError();
		if (uniform_var_loc >= 0) {
			//Convert uv vec to mtx
			glm::mat3 uvTform = GetMtx_UV(renderable.UV);
			glUniformMatrix3fv(uniform_var_loc, 1, GL_FALSE, glm::value_ptr(uvTform));
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

	//Draw a single line
	void RenderPipeline::DrawLine(glm::mat3 const& tform, glm::vec4 color, GLModel const& mdl, GLSLShader& shdr_pgm) {
		//say which shdr to use now
		shdr_pgm.Use();
		//say which vao to use for pipeline
		glBindVertexArray(mdl.vao_ID);

		//Add modulate color, for now 1, 1
		GLuint uniform_var_loc = glGetUniformLocation(shdr_pgm.GetHandle(), "uColor");
		CheckGLError();
		if (uniform_var_loc >= 0) {
			glUniform4f(uniform_var_loc, color[0], color[1], color[2], color[3]);
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

		glDrawArrays(mdl.primitive_type, 0, mdl.draw_cnt);

		glBindVertexArray(0);
		shdr_pgm.UnUse();
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
	}

	GLModel RenderPipeline::LoadModel_Line() {
		std::vector<glm::vec2> pos_vtx{
			glm::vec2{0.f,0.f}, glm::vec2{1.f,0.f}
		};
		//Create model
		GLModel mdl;

		//Create vbo here
		glCreateBuffers(1, &mdl.vbo_ID);
		//not nullptr cuz ur directly transfering the data into buffer, if nullptr need to use glNamedBufferSubData
		glNamedBufferStorage(mdl.vbo_ID, sizeof(glm::vec2) * pos_vtx.size(), pos_vtx.data(), GL_DYNAMIC_STORAGE_BIT);

		//Setup vao
		glCreateVertexArrays(1, &mdl.vao_ID);
		glEnableVertexArrayAttrib(mdl.vao_ID, 0);	//use slot 0
		glVertexArrayVertexBuffer(mdl.vao_ID, 0, mdl.vbo_ID, 0, sizeof(glm::vec2));	//use binding index 0, vbo, start from 0 bytes from memory, each ele sizeof vec2
		glVertexArrayAttribFormat(mdl.vao_ID, 0, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(mdl.vao_ID, 0, 0);

		//unbind
		glBindVertexArray(0);

		mdl.primitive_type = GL_LINES;
		//i guess it cant implictly type cast in static func? weird error not too sure
		mdl.draw_cnt = 2;
		mdl.primitive_cnt = 1;
		return mdl;
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
	/************************************/
	//SRender
	/************************************/
	SRender::SRender()
	{
		RequireComponent<Render::CRenderable>();

		//Setup some keybind stuff, temp
		global_input.Init_Add_Keybind("debug toggle", GLFW_KEY_G, Input::Input_Container::TRIGGER);

		//Setup Render pipeline
		render_pipeline.CreateTargetWindow(900, 480);
		camera.Init(900, 480);
		render_pipeline.SetCamera(&camera);

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
		shader_map.insert({ "default", shader_pgm });

		GLSLShader shader_pgm2;
		std::vector<std::pair<GLenum, std::string>> shdr_files2{
			std::make_pair(GL_VERTEX_SHADER, vtx_shaders[1].string()),
			std::make_pair(GL_FRAGMENT_SHADER, frg_shaders[1].string()) };
		shader_pgm2.CompileLinkValidate(shdr_files2);
		shader_map.insert({ "PlainColor", shader_pgm2 });

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
			{ glm::vec2(-.5f, -.5f),  glm::vec2(0.f, 1.f)},
			{ glm::vec2(.5f, -.5f),	glm::vec2(1.f, 1.f)},
			{ glm::vec2(.5f, .5f),	glm::vec2(1.f,0.f)},
			{ glm::vec2(-.5f, .5f),	glm::vec2(0.f,0.f)}
		};

		std::vector<GLushort> idx_vtx{
			0,1,3,
			1,2,3
		};
		Render::GLModel mdl = render_pipeline.LoadModel_Triangles(pos_vtx, idx_vtx);
		model_map.insert({ "default", mdl });

		Render::GLModel line = render_pipeline.LoadModel_Line();
		model_map.insert({ "line", line });

		Logger::LogInfo("Finished defaults");
		CheckGLError();
	}

	void SRender::UpdateFlags() {
		if (global_input.Action("debug toggle")) {
			Logger::LogInfo("debug toggle");
			draw_debug = !draw_debug;
		}
	}

	//Only Render Function, basically goto all the draw calls
	void SRender::Render()
	{
		CheckGLError();
		render_pipeline.StartDraw();
		//Create a copy of the array because entity vector is used for ecs indexing
		std::vector<ECS::Entity> entity_copy = GetEntities();
		//sorting every frame kinda L
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
					glm::vec3(transform.scale.x, 0 ,0),
					glm::vec3(0, transform.scale.y, 0),
					glm::vec3(0, 0, 1.f)
				};

				GLfloat orientation_Rad = (GLfloat)(glm::radians(transform.rotation));
				rotate = {
					glm::vec3(cosf(orientation_Rad), -sinf(orientation_Rad), 0.f),
					glm::vec3(sinf(orientation_Rad), cosf(orientation_Rad), 0.f),
					glm::vec3(0.f, 0.f, 1.f)
				};
				rotate = glm::transpose(rotate);

				translate = {
					glm::vec3(1.f, 0.f, transform.position.x),
					glm::vec3(0.f, 1.f, transform.position.y),
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

			//Draw debug info if needed
			if (draw_debug && entity.HasComponent<Component::CTransform>() && entity.HasComponent<Component::AABB>()) {
				//render_pipeline.DrawLine(tform_mtx, { 1.f,0.f,0.f,1.f }, model_map["line"], shader_map["PlainColor"]);
				/*
				* !!!!!==============THIS IS TEMPORARY DEBUG INFO, COLLISION IS NOT DONE==================
				* !!!!!==============THIS IS NOT TESTED, IF IT DOSENT WORK COMMENT IT OUT=================
				*/
				//Get 4 corners of aabb
				Component::CTransform& transform = entity.GetComponent<Component::CTransform>();
				glm::vec2 pos = { transform.position.x, transform.position.y };
				glm::vec2 scale = { transform.scale.x, transform.scale.y };
				glm::vec2 TL{ pos.x - scale.x * 0.5f, pos.y + scale.y * 0.5f };
				glm::vec2 TR{ pos.x + scale.x * 0.5f, pos.y + scale.y * 0.5f };
				glm::vec2 BL{ pos.x - scale.x * 0.5f, pos.y - scale.y * 0.5f };
				glm::vec2 BR{ pos.x + scale.x * 0.5f, pos.y - scale.y * 0.5f };


				DrawLine(TL, TR, { 0.f,1.f,0.f,1.f });
				DrawLine(TR, BR, { 0.f,1.f,0.f,1.f });
				DrawLine(BR, BL, { 0.f,1.f,0.f,1.f });
				DrawLine(BL, TL, { 0.f,1.f,0.f,1.f });
			}
			//Draw velocity debug info
			if (draw_debug && entity.HasComponent<Component::CTransform>() && entity.HasComponent<Component::CRigidBody>()) {
				Component::CTransform& transform = entity.GetComponent<Component::CTransform>();
				Component::CRigidBody& rigidbody = entity.GetComponent<Component::CRigidBody>();
				MathLib::vec2 targetPos = transform.position + rigidbody.vel;

				glm::vec2 target = { targetPos.x, targetPos.y };
				glm::vec2 pos = { transform.position.x, transform.position.y };

				DrawLine(pos, target, {0.f,1.f,1.f,1.f});
			}
		}
		//Example of drawing of line
		if (draw_debug) {
			DrawLine({ -3.f,-1.7f }, { 1.5f, 4.9f });
		}

		render_pipeline.FinishDraw();

		CheckGLError();
	}

	//Draws a single line from start to end with color
	void SRender::DrawLine(glm::vec2 start, glm::vec2 end, glm::vec4 color) {
		//Length of line
		GLfloat length = glm::length(end - start);
		//Start position is start

		//Angle between 1,0 and end-start
		glm::vec2 line = glm::normalize(end - start);
		GLfloat dot = glm::dot(line, { 1.f,0.f });
		GLfloat angle = acosf(dot);
		//Use inward normal to determine positive or negative angle
		glm::vec2 norm{ -line.y, line.x };
		//If greater then 0, means angle is clockwise, meaning -angle
		if (glm::dot(norm, { 1.f,0.f }) > 0) {
			angle = -angle;
		}

		//Scale, Rotate, Translate
		glm::mat3 scale = {
			glm::vec3(length, 0 ,0),
			glm::vec3(0, length, 0),
			glm::vec3(0, 0, 1.f)
		};

		glm::mat3 rotate = {
			glm::vec3(cosf(angle), -sinf(angle), 0.f),
			glm::vec3(sinf(angle), cosf(angle), 0.f),
			glm::vec3(0.f, 0.f, 1.f)
		};
		rotate = glm::transpose(rotate);

		glm::mat3 translate = {
			glm::vec3(1.f, 0.f, start.x),
			glm::vec3(0.f, 1.f, start.y),
			glm::vec3(0.f, 0.f, 1.f)
		};
		
		translate = glm::transpose(translate);

		glm::mat3 tform = camera.GetWorldtoNDC() * translate * rotate * scale;

		render_pipeline.DrawLine(tform, color, model_map["line"], shader_map["PlainColor"]);
	}

	/************************************/
	//SAnimator
	/************************************/
	SAnimator::SAnimator() {
		RequireComponent<Render::CRenderable>();
		RequireComponent<Render::CSpriteAnimator>();
	}
	void SAnimator::Update(GLfloat dt) {
		for (ECS::Entity const& entity : GetEntities())
		{
			Render::CSpriteAnimator& animator = entity.GetComponent<Render::CSpriteAnimator>();
			Render::CRenderable& renderable = entity.GetComponent<Render::CRenderable>();
			animator.Update(dt, entity);
			renderable.SetTexture(animator.GetCurrentTexture());
			renderable.SetTex_UV(animator.GetUV());
		}
	}
}

//namespace 


	void _CheckGLError(const char* file, int line)
	{
#ifndef _DEBUG
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
