#pragma once

#include "Include.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Renderer.h"
#include "VertexBufferLayout.h"

class ImageDraw
{
public:

	void setup(int win_w, int win_h, int max_x, int min_x, int max_y, int min_y);
	void render_leaves(std::vector<glm::vec2> leaf_pos, bool leaf_convert, int leaf_storage_length);
	void render_ridges(std::vector<std::vector<glm::vec2>> random_ridges);
	void render_branches(std::vector<glm::vec4> branch_combined);

	std::vector<float> leaf_colour = { 1.0f, 0.2f, 0.3f, 1.0f };
	std::vector<float> ridge_colour = { 0.5f, 1.0f, 0.0f, 1.0f };

private:

	VertexBufferLayout layout1;
	VertexBufferLayout layout2;

	std::unique_ptr<VertexArray> m_VAO_image;

	std::unique_ptr<VertexBuffer> m_VertexBuffer1;
	std::unique_ptr<VertexBuffer> m_VertexBuffer2;
	std::unique_ptr<VertexBuffer> m_VertexBuffer3;

	std::unique_ptr<Shader> m_Shader;
	std::vector<glm::vec2> branch_combined;

	glm::mat4 projection;

	int window_width;
	int window_height;
	int max_x_point;
	int min_x_point;
	int max_y_point;
	int min_y_point;


	float clip_space_min_x;
	float clip_space_max_x;
	float clip_space_min_y;
	float clip_space_max_y;

};

