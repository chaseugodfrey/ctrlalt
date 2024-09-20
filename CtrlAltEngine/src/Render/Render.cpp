#include "Render.h"

#include "glhelper.h"
#include <array>

//Some commnets
//New branch maybe
namespace Render {
	/************************************/
	//Renderable
	/************************************/
	
	//Sorting operation for priority queue
	bool operator < (Renderable const& lhs, Renderable const& rhs) {
		if (lhs.textureHandle < rhs.textureHandle) {
			return true;
		}
		else if (lhs.shaderHandle < rhs.shaderHandle) {
			return true;
		}
		else if (lhs.meshHandle < rhs.meshHandle) {
			return true;
		}
		return false;
	}

	/************************************/
	//Render Pipeline
	/************************************/

	//Inits glfw window - not sure if it should be here
	void RenderPipeline::Init(GLint width, GLint height, std::string const& window_title) {
		//Setting up window and input callbacks
		GLHelper::init(width, height, window_title, ptr_window);
		glEnable(GL_DEPTH_TEST);	//depth is written in fragment shader

		GLHelper::print_specs();

		//Init the actual graphics stuff here
	}
	void RenderPipeline::Draw() {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	/************************************/
	//AssetManager
	/************************************/
	void AssetManager::Init() {
		//Init all textures here
		
		//Init all meshes here, would read from file and stuff,
		
		GLModel mdl = LoadQuad();
		meshes.insert({ "quad", mdl });
	}

	void AssetManager::Cleanup() {
		for (std::pair<std::string, GLuint> const& pair : textures) {
			glDeleteTextures(1, &pair.second);
		}
		for (std::pair<std::string, GLModel> const& pair : meshes) {
			glDeleteBuffers(1, &pair.second.vbo_ID);
			glDeleteVertexArrays(1, &pair.second.vao_ID);
		}
	}

	AssetManager::GLModel AssetManager::LoadQuad() {
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