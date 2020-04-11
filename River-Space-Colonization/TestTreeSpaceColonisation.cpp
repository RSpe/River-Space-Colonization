#include "TestTreeSpaceColonisation.h"

namespace test
{

	TestTreeSpaceColonisation::TestTreeSpaceColonisation()
	{
		//std::cout << "Start!" << std::endl;

		int leaves_to_generate = 100;

		random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, 1);
		glm::vec2(0.0f, 0.5f);

		std::shared_ptr<Branch> root(new Branch(NULL, glm::vec2(0.0f, 0.5f), glm::vec2(0.0f, -1.0f)));

		branches.push_back(root);

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		for (int i = 0; i < leaves_to_generate; i++)
		{
			//std::cout << i << std::endl;
			leaves.push_back(Leaf(this->random_leaves[i]));
		}

		bool found = false;
		std::shared_ptr<Branch> current(root);

		while (!found)
		{
			for (int j = 0; j < leaves_to_generate; j++)
			{
				std::cout << j << std::endl;
				float distance = glm::distance(current->get_position(), leaves[j].get_position());
				if (distance < max_distance) {
					found = true;
				}
			}

			if (!found)
			{
				glm::vec2 new_position = (current->get_position()) + (current->get_direction());
				glm::vec2 new_direction = current->get_direction();
				std::shared_ptr<Branch> next_branch(new Branch(current, new_position, new_direction));
				current = next_branch;
				branches.push_back(current);
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

	void TestTreeSpaceColonisation::Grow()
	{
		int num_leaves = leaves.size();
		int num_branches = branches.size();

		for (int i = 0; i < num_leaves; i++)
		{
			std::cout << "growing" << std::endl;
			Leaf leaf = leaves[i];
			std::shared_ptr<Branch> closest_branch(NULL);
			int record = 100000;
			for (int j = 0; j < num_branches; j++)
			{
				glm::vec2 current_branch_position = branches[j]->get_position();
				float distance = glm::distance(leaf.get_position(), current_branch_position);
				if (distance < min_distance)
				{
					leaf.set_reached();
					closest_branch = NULL;
					break; 
				}
				else if (distance > max_distance)
				{
					continue;
				}
				else if (closest_branch == NULL || distance < record)
				{
					closest_branch = branches[j];
					record = distance;
				}
			}

			if (closest_branch != NULL)
			{
				glm::vec2 new_direction = leaf.get_position() - closest_branch->get_position();
				glm::vec2 normalised = glm::normalize(new_direction);
				glm::vec2 change_direction = closest_branch->get_direction() + normalised; // Direction of current leaned towards leaf
				closest_branch->set_direction(change_direction);
				closest_branch->increment_count(1);
			}

			if (leaf.get_reached())
			{
				leaves.erase(leaves.begin() + i);
			}
		}

		for (int k = num_branches - 1; k >= 0; k--)
		{
			std::shared_ptr<Branch> current_branch(branches[k]);
			if (current_branch->get_count() > 0)
			{
				glm::vec2 old_position = current_branch->get_position();
				glm::vec2 old_direction = current_branch->get_direction();
				current_branch->set_direction(old_direction / current_branch->get_count());
				glm::vec2 new_position = old_position + old_direction;
				std::shared_ptr<Branch> new_branch(new Branch(current_branch, new_position, old_direction));
				branches.push_back(new_branch);
			}
			current_branch->reset();
		}
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
		//GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//m_Shader->Bind();
		//m_VAO->Bind();

		//GLCall(glPointSize(3));
		//GLCall(glDrawArrays(GL_POINTS, 0, 100));

	}

	void TestTreeSpaceColonisation::OnImGuiRender()
	{

	}

}