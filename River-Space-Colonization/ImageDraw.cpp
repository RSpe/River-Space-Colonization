#include "ImageDraw.h"

void ImageDraw::setup(int win_w, int win_h, int max_x, int min_x, int max_y, int min_y)
{
	m_VAO_image = std::make_unique<VertexArray>();

	layout1.Push<float>(2);

	layout2.Push<float>(4);
	layout2.Push<float>(4);

	window_width = win_w;
	window_height = win_h;
	max_x_point = max_x;
	min_x_point = min_x;
	max_y_point = max_y;
	min_y_point = min_y;
}

void ImageDraw::render_leaves(std::vector<glm::vec2> leaf_pos, bool leaf_convert, int leaf_storage_length)
{
	std::vector<glm::vec2> convert_leaf_pos;

	for (int i = 0; i < leaf_pos.size(); ++i)
	{
		float x_pos = (2.0f * (leaf_pos[i][0] - min_x_point) / (float)(max_x_point - min_x_point) - 1.0f) * (max_x_point / (float)window_width);
		float y_pos = (2.0f * (leaf_pos[i][1] - min_y_point) / (float)(max_y_point - min_y_point) - 1.0f) * (max_y_point / (float)window_height);

		convert_leaf_pos.push_back(glm::vec2(x_pos, y_pos));
	}

	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("GeneralImage.shader");
	m_Shader->Bind();
	/* Have to call uniforms after a shader is bound */
	m_Shader->SetUniform4f("u_Color", leaf_colour[0], leaf_colour[1], leaf_colour[2], leaf_colour[3]);

	m_VertexBuffer1 = std::make_unique<VertexBuffer>(convert_leaf_pos.data(), convert_leaf_pos.size() * sizeof(glm::vec2));

	m_VAO_image->AddBuffer(*m_VertexBuffer1, layout1);

	GLCall(glPointSize(3));
	GLCall(glDrawArrays(GL_POINTS, 0, convert_leaf_pos.size()));
}

void ImageDraw::render_ridges(std::vector<std::vector<glm::vec2>> random_ridges)
{
	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("GeneralTerrain.shader");
	m_Shader->Bind();

	for (int i = 0; i < random_ridges.size(); i++)
	{
		m_VertexBuffer2 = std::make_unique<VertexBuffer>(random_ridges[i].data(), random_ridges[i].size() * sizeof(glm::vec2));
		m_VAO_image->AddBuffer(*m_VertexBuffer2, layout1);
		m_Shader->SetUniform4f("u_Color", ridge_colour[0], ridge_colour[1], ridge_colour[2], ridge_colour[3]);

		GLCall(glDrawArrays(GL_POINTS, 0, random_ridges[i].size()));
	}
}

void ImageDraw::render_branches(std::vector<glm::vec4> branch_combined)
{
	std::vector<glm::vec4> convert_branch_pos;

	for (int i = 0; i < branch_combined.size(); i += 2)
	{
		float x_pos = (2.0f * (branch_combined[i][0] - min_x_point) / (float)(max_x_point - min_x_point) - 1.0f) * (max_x_point / (float)window_width);
		float y_pos = (2.0f * (branch_combined[i][1] - min_y_point) / (float)(max_y_point - min_y_point) - 1.0f) * (max_y_point / (float)window_height);

		//std::cout << x_pos << " " << y_pos << std::endl;

		convert_branch_pos.push_back(glm::vec4(x_pos, y_pos, 0.0f, 1.0f));
		convert_branch_pos.push_back(branch_combined[i + 1]);
	}

	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("RiverImage.shader");
	m_Shader->Bind();

	m_VertexBuffer3 = std::make_unique<VertexBuffer>(convert_branch_pos.data(), convert_branch_pos.size() * sizeof(glm::vec4));

	m_VAO_image->AddBuffer(*m_VertexBuffer3, layout2);

	glDrawArrays(GL_LINES, 0, convert_branch_pos.size());
}