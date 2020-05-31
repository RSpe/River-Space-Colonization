#include "TestTreeSpaceColonisation.h"

// TODO: Add root generation class

namespace test
{
	/* Building tree trunk */
	TestTreeSpaceColonisation::TestTreeSpaceColonisation()
	{
		Build();
	}

	void TestTreeSpaceColonisation::Build()
	{
		int leaves_to_generate = 100;

		random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, 1); // Generate random 2D points as leaves used for unique branch building. **

		random_ridges = RidgeGeneration::generate_ridges(1, 1);

		for (int i = 0; i < tree_number; i++)
		{
			//std::cout << "--------------Build-------------" << std::endl;
			int root_position = i * 2;

			finish = false;

			std::shared_ptr<Branch> root(new Branch(glm::vec2(root_array[root_position], root_array[root_position + 1]), glm::vec2(root_array[root_position], root_array[root_position + 1]), glm::vec2(0.0f, 1.0f))); // Create root branch, itself as its parent, position starting at (0.0f, -600.0f), direction of (0.0f, 1.0f) which is pointing upwards. **

			branches.push_back(root); // Add root as the first branch object.`

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
					glm::vec2 parent_position = branches.back()->get_position();
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
	}

	void TestTreeSpaceColonisation::Grow()
	{
		//std::cout << "--------------Grow--------------" << std::endl;
		float record = -1;

		if (finish == false)
		{
			if (leaves.size() == 0)
			{
				finish = true;
				return;
			}

			std::cout << "check" << std::endl;

			for (int i = 0; i < leaves.size(); i++)
			{
				int closest_branch = -1;
				for (int j = 0; j < branches.size(); j++)
				{
					bool skip = false; // Skips leaf node if the path to it from some branch intersects with a ridge line.
					glm::vec2 current_branch_position = branches[j]->get_position();
					glm::vec2 current_leaf_pos = leaves[i].get_position();

					
					for (double k = 0; k < random_ridges.size(); k += 2)
					{
						float check_intersect_t = ((current_branch_position[0] - random_ridges[k][0]) * (random_ridges[k][1] - random_ridges[k + 1][1]) - (current_branch_position[1] - random_ridges[k][1]) * (random_ridges[k][0] - random_ridges[k + 1][0])) / ((current_branch_position[0] - current_leaf_pos[0]) * (random_ridges[k][1] - random_ridges[k + 1][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (random_ridges[k][0] - random_ridges[k + 1][0]));
						float check_intersect_u = (((current_branch_position[0] - current_leaf_pos[0]) * (current_branch_position[1] - random_ridges[k][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (current_branch_position[0] - random_ridges[k][0])) / ((current_branch_position[0] - current_leaf_pos[0]) * (random_ridges[k][1] - random_ridges[k + 1][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (random_ridges[k][0] - random_ridges[k + 1][0]))) * -1;
						if (check_intersect_t >= 0 && check_intersect_t <= 1 && check_intersect_u >= 0 && check_intersect_u <= 1)
						{
							skip = true;
						}
					}
					
					if (skip == true)
					{
						continue;
					}

					float distance = glm::distance(leaves[i].get_position(), current_branch_position);
					if (distance < min_distance) // Once branch reaches leaf, mark for deletion.
					{ 
						//std::cout << distance << std::endl;
						leaves[i].set_reached();
						closest_branch = -1;
						break;
					}
					else if (distance > max_distance)
					{
						continue;
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
					{
						glm::vec2 new_direction = leaves[i].get_position() - (glm::vec2(branches[closest_branch]->get_position()));
						glm::vec2 normalised = glm::normalize(new_direction);
						branches[closest_branch]->set_direction(normalised);
						branches[closest_branch]->increment_count(1);
					}
				}

				if (leaves[i].get_reached())
				{
					leaves.erase(leaves.begin() + i);
				}
			}

			/* Find new branches */
			std::vector<std::shared_ptr<Branch>> new_branches;
			for (int k = 0; k < branches.size(); k++)
			{
				if (branches[k] != nullptr)
				{
					if (branches[k]->get_count() > 0)
					{
						glm::vec2 parent_direction = branches[k]->get_direction();
						glm::vec2 parent_position = branches[k]->get_position();
						glm::vec2 new_direction = glm::normalize(parent_direction / (float(branches[k]->get_count() + 1)));
						glm::vec2 new_position = parent_position + (new_direction * branch_length);
						std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, new_direction));


						next_branch->set_parent_index(k);
						new_branches.push_back(next_branch);
					}
					branches[k]->reset();
				}
			}
			branches.insert(branches.end(), new_branches.begin(), new_branches.end());
		}
	}

	void TestTreeSpaceColonisation::Draw() 
	{
		std::vector<glm::vec2> leaf_pos;
		std::vector<glm::vec2> ridge_pos;
		std::vector<glm::vec2> branch_pos;

		for (int i = 0; i < leaves.size(); i++)
		{
			glm::vec2 pixel_pos_leaf = (leaves[i].get_position());
			glm::vec2 norm_leaf = glm::vec2(pixel_pos_leaf[0] / window_width, pixel_pos_leaf[1] / window_height);
			leaf_pos.push_back(norm_leaf);
		}

		for (int i = 0; i < random_ridges.size(); i++)
		{
			glm::vec2 norm_ridge = glm::vec2(random_ridges[i][0] / window_width, random_ridges[i][1] / window_height);
			ridge_pos.push_back(norm_ridge);
		}

		for (int j = 0; j < branches.size(); j++)
		{
			glm::vec2 pixel_pos_branch = (branches[j]->get_position());
			glm::vec2 pixel_pos_parent = (branches[j]->get_parent());
			glm::vec2 norm_branch = glm::vec2(pixel_pos_branch[0] / window_width, pixel_pos_branch[1] / window_height);
			glm::vec2 norm_parent = glm::vec2(pixel_pos_parent[0] / window_width, pixel_pos_parent[1] / window_height);
			branch_pos.push_back(norm_parent);
			branch_pos.push_back(norm_branch);
		}

		m_VAO = std::make_unique<VertexArray>();
		
		m_VertexBuffer1 = std::make_unique<VertexBuffer>(leaf_pos.data(), leaf_pos.size() * sizeof(glm::vec2));
		m_VertexBuffer2 = std::make_unique<VertexBuffer>(branch_pos.data(), branch_pos.size() * sizeof(glm::vec2));
		m_VertexBuffer3 = std::make_unique<VertexBuffer>(ridge_pos.data(), ridge_pos.size() * sizeof(glm::vec2));

		VertexBufferLayout layout1;

		layout1.Push<float>(2);

		m_VAO->AddBuffer(*m_VertexBuffer1, layout1);

		m_Shader = std::make_unique<Shader>("River.shader");
		m_Shader->Bind();
		/* Have to call uniforms after a shader is bound */
		m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLCall(glPointSize(3));
		GLCall(glDrawArrays(GL_POINTS, 0, leaf_pos.size()));

		m_VAO->AddBuffer(*m_VertexBuffer3, layout1);
		m_Shader->SetUniform4f("u_Color", 0.039f, 0.439f, 0.0f, 1.0f);

		GLCall(glDrawArrays(GL_LINES, 0, ridge_pos.size()));

		m_VAO->AddBuffer(*m_VertexBuffer2, layout1);
		m_Shader->SetUniform4f("u_Color", 0.0f, 0.003f, 0.439f, 1.0f);

		//std::cout << branch_pos.size() << std::endl;
		GLCall(glDrawArrays(GL_LINES, 0, branch_pos.size()));

	}

	//void TestTreeSpaceColonisation::SetSeed(int seed)
	//{
	//	given_seed = seed;
	//}

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