#include "TerrainDraw.h"

void TerrainDraw::setup()
{
	m_VAO_terrain = std::make_unique<VertexArray>();

	layout1.Push<float>(2);

	layout2.Push<float>(4);
	layout2.Push<float>(4);

	layout3.Push<float>(3);
	//layout3.Push<float>(4);
	//layout3.Push<float>(4);
}

void TerrainDraw::render_leaves(std::vector<glm::vec2> leaf_pos, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("GeneralTerrain.shader");
	m_Shader->Bind();
	/* Have to call uniforms after a shader is bound */
	m_Shader->SetUniform4f("u_Color", leaf_colour[0], leaf_colour[1], leaf_colour[2], leaf_colour[3]);
	m_Shader->SetUniformMat4f("u_Proj", projection);
	m_Shader->SetUniformMat4f("u_View", view);
	m_Shader->SetUniformMat4f("u_Model", model);

	m_VertexBuffer1 = std::make_unique<VertexBuffer>(leaf_pos.data(), leaf_pos.size() * sizeof(glm::vec2));

	m_VAO_terrain->AddBuffer(*m_VertexBuffer1, layout1);

	GLCall(glPointSize(3));
	GLCall(glDrawArrays(GL_POINTS, 0, leaf_pos.size()));
}

void TerrainDraw::render_ridges(std::vector<std::vector<glm::vec2>> random_ridges, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("GeneralTerrain.shader");
	m_Shader->Bind();

	for (int i = 0; i < random_ridges.size(); i++)
	{
		m_Shader->SetUniformMat4f("u_Proj", projection);
		m_Shader->SetUniformMat4f("u_View", view);
		m_Shader->SetUniformMat4f("u_Model", model);
		m_Shader->SetUniform4f("u_Color", ridge_colour[0], ridge_colour[1], ridge_colour[2], ridge_colour[3]);

		m_VertexBuffer2 = std::make_unique<VertexBuffer>(random_ridges[i].data(), random_ridges[i].size() * sizeof(glm::vec2));
		m_VAO_terrain->AddBuffer(*m_VertexBuffer2, layout1);

		GLCall(glDrawArrays(GL_POINTS, 0, random_ridges[i].size()));
	}
}

void TerrainDraw::render_branches(std::vector<glm::vec4> branch_combined, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("RiverTerrain.shader");
	m_Shader->Bind();

	m_Shader->SetUniformMat4f("u_Proj", projection);
	m_Shader->SetUniformMat4f("u_View", view);
	m_Shader->SetUniformMat4f("u_Model", model);

	m_VertexBuffer3 = std::make_unique<VertexBuffer>(branch_combined.data(), branch_combined.size() * sizeof(glm::vec4));
	m_VAO_terrain->AddBuffer(*m_VertexBuffer3, layout2);

	glDrawArrays(GL_POINTS, 0, branch_combined.size());
}

void TerrainDraw::render_terrain(std::vector<glm::vec3> height_combined, std::vector<unsigned int> index_buffer, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	m_Shader->Unbind();
	m_Shader = std::make_unique<Shader>("SudoCompleteTerrain.shader");
	m_Shader->Bind();

	m_Shader->SetUniformMat4f("u_Proj", projection);
	m_Shader->SetUniformMat4f("u_View", view);
	m_Shader->SetUniformMat4f("u_Model", model);

	m_VertexBuffer4 = std::make_unique<VertexBuffer>(height_combined.data(), height_combined.size() * sizeof(glm::vec3));
	m_VAO_terrain->AddBuffer(*m_VertexBuffer4, layout3);

	unsigned int IBO;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer.size() * sizeof(unsigned int), index_buffer.data(), GL_STATIC_DRAW);

	GLCall(glDrawElements(GL_TRIANGLE_STRIP, index_buffer.size(), GL_UNSIGNED_INT, 0));
}