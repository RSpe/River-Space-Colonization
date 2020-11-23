#pragma once

#include "Include.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

class TerrainDraw
{
public:

	void setup();

	void render_leaves(std::vector<glm::vec2> leaf_pos, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	void render_ridges(std::vector<std::vector<glm::vec2>> random_ridges, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	void render_branches(std::vector<glm::vec4> branch_combined, glm::mat4 projection, glm::mat4 view, glm::mat4 model);
	void render_terrain(std::vector<glm::vec3> height_combined, std::vector<unsigned int> index_buffer, glm::mat4 projection, glm::mat4 view, glm::mat4 model, int max_x_point, int max_y_point);
	
	std::vector<float> leaf_colour = { 1.0f, 0.2f, 0.3f, 1.0f };
	std::vector<float> ridge_colour = { 0.5f, 1.0f, 0.0f, 1.0f };

private:

	VertexBufferLayout layout1;
	VertexBufferLayout layout2;
	VertexBufferLayout layout3;

	std::unique_ptr<VertexArray> m_VAO_terrain;

	std::unique_ptr<VertexBuffer> m_VertexBuffer1;
	std::unique_ptr<VertexBuffer> m_VertexBuffer2;
	std::unique_ptr<VertexBuffer> m_VertexBuffer3;
	std::unique_ptr<VertexBuffer> m_VertexBuffer4;

	std::unique_ptr<Shader> m_Shader;
};

