#include "TestTreeSpaceColonisation.h"

namespace test
{
	/* Building tree trunk */
	TestTreeSpaceColonisation::TestTreeSpaceColonisation()
	{
		Build();
		Ridges();
		//Grow();
	}

	void TestTreeSpaceColonisation::Build()
	{
		for (int i = 0; i < tree_number; i++)
		{
			//std::cout << "--------------Build-------------" << std::endl;
			int root_position = i * 2;

			finish = false;
			int leaves_to_generate = 200;

			random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, 1); // Generate random 2D points as leaves used for unique branch building. **

			std::cout << root_array[i] << root_array[i + 1] << std::endl;
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
						//std::cout << distance << std::endl;
						//std::cout << glm::to_string(current->get_position()) << std::endl;
						//std::cout << glm::to_string(leaves[j].get_position()) << std::endl;
						found = true;
					}
				}
				/* Create a branch off the root branch that starts at the end of the root branch and extends the same distance upwards. This step we are growing the tree in hope we find a leaf close enough to move towards. */
				if (!found && !branches.empty())
				{
					//std::cout << "check" << std::endl;
					//std::cout << glm::to_string(current->get_direction()) << std::endl;
					glm::vec2 parent_direction = current->get_direction();
					glm::vec2 parent_position = branches.back()->get_position();
					//std::cout << glm::to_string(parent_position) << std::endl;
					glm::vec2 new_direction = parent_direction;
					glm::vec2 new_position = parent_position + (new_direction * branch_length);
					//std::cout << glm::to_string(new_position) << std::endl;
					std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, new_direction));
					int parent_index = branches.size() - 1;
					//std::cout << glm::to_string(next_branch->get_parent()) << std::endl;
					next_branch->set_parent_index(parent_index);
					//std::cout << glm::to_string(next_branch->get_parent()) << std::endl;
					//std::cout << glm::to_string(next_branch->get_position()) << std::endl;
					branches.push_back(next_branch);
					current = branches.back();
				}
			}
			//for (int i = 0; i < branches.size(); i++)
			//{
			//	std::cout << glm::to_string(branches[i]->get_position()) << std::endl;
			//}
		}
		
	}

	void TestTreeSpaceColonisation::Ridges()
	{

	}

	void TestTreeSpaceColonisation::Grow()
	{
		//std::cout << "--------------Grow--------------" << std::endl;
		float record = -1;

		if (finish == false)
		{
			//std::cout << leaves.size() << std::endl;
			if (leaves.size() == 0)
			{
				finish = true;
				//std::cout << "finished" << std::endl;
				return;
			}

			//std::cout << "leaves" << std::endl;
			//std::cout << leaves.size() << std::endl;
			for (int i = 0; i < leaves.size(); i++)
			{
				int closest_branch = -1;
				for (int j = 0; j < branches.size(); j++)
				{
					glm::vec2 current_branch_position = branches[j]->get_position();
					//std::cout << glm::to_string(current_branch_position) << std::endl;
					float distance = glm::distance(leaves[i].get_position(), current_branch_position);
					//std::cout << record << std::endl;
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
						//std::cout << "check" << std::endl;
						closest_branch = j;
						record = distance;
					}
				}


				/* Find vector from base of branch to closest leaf, normalise, add it to the end of the branch in the same direction. */
				if (closest_branch >= 0 && !leaves[i].get_reached())
				{
					//std::cout << "------------------------------" << std::endl;
					//std::cout << closest_branch << std::endl;
					glm::vec2 new_direction = leaves[i].get_position() - (glm::vec2(branches[closest_branch]->get_position()));
					//std::cout << glm::to_string(glm::vec2(branches[closest_branch]->get_position())) << std::endl;
					//std::cout << glm::to_string(leaves[i].get_position()) << std::endl;
					//std::cout << glm::to_string(new_direction) << std::endl;
					glm::vec2 normalised = glm::normalize(new_direction);
					//std::cout << glm::to_string(branches[closest_branch]->get_direction()) << std::endl;
					//std::cout << glm::to_string(normalised) << std::endl;
					branches[closest_branch]->set_direction(normalised);
					branches[closest_branch]->increment_count(1);
					//std::cout << branches[closest_branch]->get_count() << std::endl;
				}

				if (leaves[i].get_reached())
				{
					//std::cout << "check" << std::endl;
					//std::cout << i << std::endl;
					//std::cout << leaves.size() << std::endl;
					leaves.erase(leaves.begin() + i);
					//std::cout << leaves.size() << std::endl;
				}
			}

			/* Find new branches */
			std::vector<std::shared_ptr<Branch>> new_branches;
			for (int k = 0; k < branches.size(); k++)
			{
				//std::cout << branches.size() << std::endl;
				if (branches[k] != nullptr)
				{
					if (branches[k]->get_count() > 0)
					{
						//std::cout << k << std::endl;
						//std::cout << glm::to_string(branches[k]->get_direction()) << std::endl;
						glm::vec2 parent_direction = branches[k]->get_direction();
						glm::vec2 parent_position = branches[k]->get_position();
						//std::cout << glm::to_string(parent_position) << std::endl;
						//glm::vec2 norm_direction = glm::normalize(parent_direction / (float(branches[k]->get_count() + 1)));
						//std::cout << branches[k]->get_count() << std::endl;
						//std::cout << glm::to_string(new_direction) << std::endl;
						glm::vec2 new_direction = glm::normalize(parent_direction / (float(branches[k]->get_count() + 1)));
						glm::vec2 new_position = parent_position + (new_direction * branch_length);
						/* glm::vec2 new_direction = parent_direction; glm::vec2 new_position = parent_position + (parent_direction * branch_length) */
						std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, new_direction));
						//std::cout << glm::to_string(next_branch->get_parent()) << std::endl;
						//std::cout << glm::to_string(next_branch->get_position()) << std::endl;


						next_branch->set_parent_index(k);
						new_branches.push_back(next_branch);
					}
					branches[k]->reset();
				}
			}
			//std::cout << "--------------------" << std::endl;
			//std::cout << new_branches.size() << std::endl;
			//std::cout << "new" << std::endl;
			branches.insert(branches.end(), new_branches.begin(), new_branches.end());
			//std::cout << branches.size() << std::endl;
		}
		//for (int p = 0; p < branches.size(); p++)
		//{
		//	std::cout << glm::to_string(branches[p]->get_parent()) << std::endl;
		//	std::cout << glm::to_string(branches[p]->get_position()) << std::endl;
		//}
	}

	void TestTreeSpaceColonisation::Draw() 
	{
		std::vector<glm::vec2> leaf_pos;
		std::vector<glm::vec2> branch_pos;

		for (int i = 0; i < leaves.size(); i++)
		{
			glm::vec2 pixel_pos_leaf = (leaves[i].get_position());
			glm::vec2 con_leaf = glm::vec2(pixel_pos_leaf[0] / window_width, pixel_pos_leaf[1] / window_height);
			//std::cout << glm::to_string(con_leaf) << std::endl;
			leaf_pos.push_back(con_leaf);
		}

		//std::cout << "-------------------" << std::endl;
		for (int j = 0; j < branches.size(); j++)
		{
			//std::cout << glm::to_string(branches[i]) << std::endl;
			//std::cout << glm::to_string((branches[j]->get_position())) << std::endl;
			glm::vec2 pixel_pos_branch = (branches[j]->get_position());
			glm::vec2 pixel_pos_parent = (branches[j]->get_parent());
			//std::cout << glm::to_string(branches[j]->get_parent()) << std::endl;
			//std::cout << glm::to_string(branches[j]->get_position()) << std::endl;
			glm::vec2 norm_branch = glm::vec2(pixel_pos_branch[0] / window_width, pixel_pos_branch[1] / window_height);
			glm::vec2 norm_parent = glm::vec2(pixel_pos_parent[0] / window_width, pixel_pos_parent[1] / window_height);
			//std::cout << glm::to_string(con_branch) << std::endl; // Branches look to be set incorrectly
			branch_pos.push_back(norm_parent);
			branch_pos.push_back(norm_branch);
			//std::cout << glm::to_string(norm_branch) << std::endl;
			//std::cout << glm::to_string(norm_parent) << std::endl;
		}
		//std::cout << "-------------------" << std::endl;

		m_VAO = std::make_unique<VertexArray>();
		
		m_VertexBuffer1 = std::make_unique<VertexBuffer>(leaf_pos.data(), leaf_pos.size() * sizeof(glm::vec2));
		m_VertexBuffer2 = std::make_unique<VertexBuffer>(branch_pos.data(), branch_pos.size() * sizeof(glm::vec2));

		VertexBufferLayout layout1;
		VertexBufferLayout layout2;
		layout1.Push<float>(2);
		layout2.Push<float>(2);
		m_VAO->AddBuffer(*m_VertexBuffer1, layout1);

		m_Shader = std::make_unique<Shader>("River.shader");
		m_Shader->Bind();
		/* Have to call uniforms after a shader is bound */
		m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLCall(glPointSize(3));
		GLCall(glDrawArrays(GL_POINTS, 0, leaf_pos.size()));

		m_VAO->AddBuffer(*m_VertexBuffer2, layout2);

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