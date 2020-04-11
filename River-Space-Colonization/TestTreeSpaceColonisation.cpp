#include "TestTreeSpaceColonisation.h"

namespace test
{

	TestTreeSpaceColonisation::TestTreeSpaceColonisation()
	{
		int leaves_to_generate = 100;

		random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, 1);

		std::shared_ptr<Branch> root(new Branch(NULL, glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, -1.0f)));

		this->branches.push_back(root);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		for (int i = 0; i < leaves_to_generate; i++)
		{
			leaves.push_back(Leaf(this->random_leaves[i]));
		}

		bool found = false;
		std::shared_ptr<Branch> current = root;

		while (!found)
		{
			for (int j = 0; j < leaves_to_generate; j++)
			{
				float dist = glm::distance(current->get_position(), leaves[j].get_position());
				if (dist < max_dist) {
					found = true;
				}
			}

			if (!found)
			{
				glm::vec2 new_position = (current->get_position()) + (current->get_direction());
				glm::vec2 new_direction = current->get_direction();
				std::shared_ptr<Branch> next_branch(new Branch(current, new_position, new_direction));
				current = next_branch;
				this->branches.push_back(current);
			}
		}
		//m_VAO = std::make_unique<VertexArray>();

		//m_VertexBuffer = std::make_unique<VertexBuffer>(leaf, 100 * 2 * sizeof(float));

		//VertexBufferLayout layout;
		//layout.Push<float>(2);
		//m_VAO->AddBuffer(*m_VertexBuffer, layout);

		//m_Shader = std::make_unique<Shader>("River.shader");
		//m_Shader->Bind();
		///* Have to call uniforms after a shader is bound */
		//m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

	}

	TestTreeSpaceColonisation::~TestTreeSpaceColonisation()
	{

	}

	void TestTreeSpaceColonisation::SetSeed(int seed)
	{
		//given_seed = seed;
	}

	void TestTreeSpaceColonisation::OnUpdate(float deltaTime)
	{
		
	}

	void TestTreeSpaceColonisation::OnRender()
	{
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Shader->Bind();
		m_VAO->Bind();

		GLCall(glPointSize(3));
		GLCall(glDrawArrays(GL_POINTS, 0, 100));

	}

	void TestTreeSpaceColonisation::OnImGuiRender()
	{

	}

}