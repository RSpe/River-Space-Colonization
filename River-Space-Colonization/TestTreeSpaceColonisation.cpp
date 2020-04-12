#include "TestTreeSpaceColonisation.h"

namespace test
{
	/* Building tree trunk */
	TestTreeSpaceColonisation::TestTreeSpaceColonisation()
	{
		Build();
	}

	void TestTreeSpaceColonisation::Build()
	{
		std::cout << "--------------Build-------------" << std::endl;

		int leaves_to_generate = 100;

		random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, 1); // Generate random 2D points as leaves used for unique branch building.

		std::shared_ptr<Branch> root(new Branch(glm::vec2(NULL, NULL), glm::vec2(300.0f, 0.0f), glm::vec2(0.0f, 1.0f))); // Create root branch, NULL parents, position starting at (0.0f, 0.5), direction of (0.0f, -1.0f) which is pointing upwards.

		branches.push_back(root); // Add root as the first branch object.

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		for (int i = 0; i < leaves_to_generate; i++)
		{
			leaves.push_back(Leaf(random_leaves[i])); // Add a leaf object to the leaves vector for all randomly generate leaf points.
		}

		bool found = false;
		std::shared_ptr<Branch> current = root;

		while (!found)
		{
			/* Checking if the root is close enough to any leaves so it can begin growing towards them. */
			for (int j = 0; j < leaves_to_generate; j++)
			{
				float distance = glm::distance(current->get_position(), leaves[j].get_position());
				if (distance < max_distance) // Found branch to moved toward, end while loop.
				{
					found = true;
				}
			}
			/* Create a branch off the root branch that starts at the end of the root branch and extends the same distance upwards. This step we are growing the tree in hope we find a leaf close enough to move towards. */
			if (!found && !branches.empty())
			{
				glm::vec2 parent_direction = current->get_direction();
				glm::vec2 parent_position = glm::vec2(branches.back()->get_position());
				glm::vec2 new_direction = parent_direction;
				glm::vec2 new_position = parent_position + (new_direction * branch_length);
				std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, new_direction));
				int parent_index = branches.size() - 1;
				next_branch->set_parent_index(parent_index);
				branches.push_back(next_branch);
				current = branches.back();
			}
		}
	}

	void TestTreeSpaceColonisation::Grow()
	{
		std::cout << "--------------Grow--------------" << std::endl;
		float record = -1;

		for (int i = 0; i < leaves.size(); i++)
		{
			int closest_branch = -1;
			for (int j = 0; j < branches.size(); j++)
			{
				glm::vec2 current_branch_position = branches[j]->get_position();
				float distance = glm::distance(leaves[i].get_position(), current_branch_position);
				if (distance < min_distance) // Once branch reaches leaf, mark for deletion.
				{
					leaves[i].set_reached();
					closest_branch = -1;
					break;
				}
				else if (distance > max_distance)
				{
					// continue; Check if this is needed...
				}
				else if ((closest_branch < 0) || distance < record) // If there is no set closest branch and its within distance then it will be set as the closest branch.
				{
					closest_branch = j;
					record = distance;
				}
			}

			/* Find vector from base of branch to closest leaf, normalise, add it to the end of the branch in the same direction. */
			if (closest_branch >= 0 && !leaves[i].get_reached())
			{
				glm::vec2 new_direction = leaves[i].get_position() - (glm::vec2(branches[closest_branch]->get_position()));
				glm::vec2 normalised = glm::normalize(new_direction);
				glm::vec2 change_direction = new_direction + normalised; // Direction of current leaned towards leaf
				branches[closest_branch]->set_direction(change_direction);
				branches[closest_branch]->increment_count(1);
			}

			if (leaves[i].get_reached())
			{
				leaves.erase(leaves.begin() + i);
			}
		}

		std::vector<std::shared_ptr<Branch>> new_branches;
		for (int k = 0; k < branches.size(); k++)
		{
			if (branches[k] != nullptr)
			{
				if (branches[k]->get_count() > 0)
				{
					glm::vec2 parent_direction = branches[k]->get_direction();
					glm::vec2 parent_position = glm::vec2(branches[k]->get_position());
					glm::vec2 next_direction = branches[k]->get_direction();
					glm::vec2 new_direction = glm::normalize(next_direction / (float(branches[k]->get_count() + 1)));
					glm::vec2 new_position = parent_position + (new_direction * branch_length);
					std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, parent_direction));
					next_branch->set_parent_index(k);
					new_branches.push_back(next_branch);
				}
				branches[k]->reset();
			}
		}
		branches.insert(branches.end(), new_branches.begin(), new_branches.end());
	}

	void TestTreeSpaceColonisation::Draw() 
	{
		m_VAO = std::make_unique<VertexArray>();
		
		m_VertexBuffer = std::make_unique<VertexBuffer>(&(leaves[0].get_position()), leaves.size() * sizeof(glm::vec2));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer, layout);

		m_Shader = std::make_unique<Shader>("River.shader");
		m_Shader->Bind();
		/* Have to call uniforms after a shader is bound */
		m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		m_Shader->Bind();
		m_VAO->Bind();

		GLCall(glPointSize(3));
		GLCall(glDrawArrays(GL_POINTS, 0, 100));
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
		Grow();
		Draw();
	}

	void TestTreeSpaceColonisation::OnImGuiRender()
	{

	}

}