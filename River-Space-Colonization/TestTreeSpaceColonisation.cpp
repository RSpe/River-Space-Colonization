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
		float clip_space_width_boundary = window_width / window_width;
		float clip_space_height_boundary = window_height / window_height;

		float clip_space_min_x = min_x_point / window_width;
		float clip_space_max_x = max_x_point / window_width;
		float clip_space_min_y = min_y_point / window_height;
		float clip_space_max_y = max_y_point / window_height;

		random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, set_seed, tree_number, clip_space_min_x, clip_space_max_x, clip_space_min_y, clip_space_max_y); // Generate random 2D points as leaves used for unique branch building.
		random_roots = std::vector<glm::vec2>(random_leaves.begin() + leaves_to_generate, random_leaves.end());
		random_ridges = RidgeGeneration::generate_ridges(ridge_number, set_seed, ridge_definition, random_roots); // Ridge number, seed, number of points in ridge (higher  = smoother, greater resolution)

		for (int n = 0; n < ridge_number; ++n)
		{
			for (int m = 0; m < ridge_definition; ++m)
			{
				random_ridges_1d.push_back(random_ridges[n][m]);
			}
		}

		for (int z = 0; z < random_ridges_1d.size(); ++z)
		{
			std::cout << glm::to_string(random_ridges_1d[z]) << std::endl;
		}

		for (int i = 0; i < tree_number; i++)
		{
			//std::cout << "--------------Build-------------" << std::endl;
			int root_position = i * 2;

			finish = false;

			//std::cout << glm::to_string(random_roots[i]) << std::endl;

			std::shared_ptr<Branch> root(new Branch(random_roots[i], random_roots[i], glm::vec2(0.0f, 1.0f))); // Create root branch using direction of (0.0f, 1.0f) which is pointing upwards.
			//std::shared_ptr<Branch> root(new Branch(glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, 1.0f)));

			branches.push_back(root); // Add root as the first branch object.`

			GLCall(glEnable(GL_BLEND));
			GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

			for (int i = 0; i < leaves_to_generate; ++i)
			{
				leaves.push_back(Leaf(random_leaves[i])); // Add a leaf object to the leaves vector for all randomly generate leaf points.
			}

			bool found = false;
			std::shared_ptr<Branch> current = root;

			while (!found)
			{
				/* Checking if the root is close enough to any leaves so it can begin growing towards them. */
				for (int j = 0; j < leaves_to_generate; ++j)
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
					glm::vec2 new_position = parent_position + (parent_direction * branch_length);
					std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, parent_direction));
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
			bool skip = false;
			if (leaves.size() == 0)
			{
				finish = true;
				height_enable_count += 1;
				return;
			}

			for (int i = 0; i < leaves.size(); ++i)
			{
				int closest_branch = -1;
				for (int j = 0; j < branches.size(); ++j)
				{
					bool skip = false;
					glm::vec2 current_branch_position = branches[j]->get_position();
					glm::vec2 current_leaf_pos = leaves[i].get_position();

					for (double j = 0; j < random_ridges_1d.size(); ++j)
					{
						if (j == 0)
						{
							float check_intersect_t = ((current_branch_position[0] - random_ridges_1d[j][0]) * (random_ridges_1d[j][1] - random_ridges_1d[j + 1][1]) - (current_branch_position[1] - random_ridges_1d[j][1]) * (random_ridges_1d[j][0] - random_ridges_1d[j + 1][0])) /
								((current_branch_position[0] - current_leaf_pos[0]) * (random_ridges_1d[j][1] - random_ridges_1d[j + 1][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (random_ridges_1d[j][0] - random_ridges_1d[j + 1][0]));
							float check_intersect_u = (((current_branch_position[0] - current_leaf_pos[0]) * (current_branch_position[1] - random_ridges_1d[j][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (current_branch_position[0] - random_ridges_1d[j][0])) /
								((current_branch_position[0] - current_leaf_pos[0]) * (random_ridges_1d[j][1] - random_ridges_1d[j + 1][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (random_ridges_1d[j][0] - random_ridges_1d[j + 1][0])) * -1);
							if (check_intersect_t >= 0 && check_intersect_t <= 1 && check_intersect_u >= 0 && check_intersect_u <= 1)
							{
								skip = true;
							}
						}
						else
						{
							float check_intersect_t = ((current_branch_position[0] - random_ridges_1d[j][0]) * (random_ridges_1d[j][1] - random_ridges_1d[j - 1][1]) - (current_branch_position[1] - random_ridges_1d[j][1]) * (random_ridges_1d[j][0] - random_ridges_1d[j - 1][0])) /
								((current_branch_position[0] - current_leaf_pos[0]) * (random_ridges_1d[j][1] - random_ridges_1d[j - 1][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (random_ridges_1d[j][0] - random_ridges_1d[j - 1][0]));
							float check_intersect_u = (((current_branch_position[0] - current_leaf_pos[0]) * (current_branch_position[1] - random_ridges_1d[j][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (current_branch_position[0] - random_ridges_1d[j][0])) /
								((current_branch_position[0] - current_leaf_pos[0]) * (random_ridges_1d[j][1] - random_ridges_1d[j - 1][1]) - (current_branch_position[1] - current_leaf_pos[1]) * (random_ridges_1d[j][0] - random_ridges_1d[j - 1][0])) * -1);
							if (check_intersect_t >= 0 && check_intersect_t <= 1 && check_intersect_u >= 0 && check_intersect_u <= 1)
							{
								skip = true;
							}
						}
					}

					if (skip == true)
					{
						continue;
					}

					float distance = glm::distance(leaves[i].get_position(), current_branch_position);

					if (distance < min_distance) // Once branch reaches leaf, mark for deletion.
					{
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
			for (int k = 0; k < branches.size(); ++k)
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
			//std::cout << count << std::endl;
		}
	}

	void TestTreeSpaceColonisation::Draw()
	{
		VertexBufferLayout layout1;

		layout1.Push<float>(2);
		if (height_enable_count == 0)
		{
			int leaf_storage_length = leaves.size(); // Used to check if there is no more leaves to show.
			std::vector<glm::vec2> leaf_pos;

			int branch_storage_length = branches.size();
			int branch_position_length = branch_pos.size() / 2; // There is double the amount of branch positions stored as we need to store the parent and current point so a line can be drawn between the two.

			if (check_leaf_change != leaf_storage_length || check_branch_change != branch_storage_length)
			{
				check_leaf_change = leaf_storage_length;
				check_branch_change = branch_storage_length;
				no_change_count = 0;
			}

			else if (check_leaf_change == leaf_storage_length || check_branch_change == branch_storage_length)
			{
				if (no_change_count == 5)
				{
					finish = true;
					height_enable_count += 1;
				}
				else
				{
					no_change_count += 1;
				}
			}

			if (leaf_storage_length != 0)
			{
				for (int i = 0; i < leaf_storage_length; ++i)
				{
					//std::cout << leaves.size() << std::endl;
					glm::vec2 pixel_pos_leaf = (leaves[i].get_position());
					leaf_pos.push_back(pixel_pos_leaf);
				}
			}
			else
			{
				leaf_pos = {};
			}

			if (branch_position_length != branch_storage_length)
			{
				for (int j = branch_position_length; j < branch_storage_length; ++j)
				{
					glm::vec2 pixel_pos_branch = (branches[j]->get_position());
					glm::vec2 pixel_pos_parent = (branches[j]->get_parent());
					branch_pos.push_back(pixel_pos_branch);
					branch_pos.push_back(pixel_pos_parent);
				}
			}

			m_VAO = std::make_unique<VertexArray>();

			m_VertexBuffer1 = std::make_unique<VertexBuffer>(leaf_pos.data(), leaf_pos.size() * sizeof(glm::vec2));
			m_VertexBuffer2 = std::make_unique<VertexBuffer>(branch_pos.data(), branch_pos.size() * sizeof(glm::vec2));

			//VertexBufferLayout layout1;

			//layout1.Push<float>(2);

			m_VAO->AddBuffer(*m_VertexBuffer1, layout1);

			m_Shader = std::make_unique<Shader>("River.shader");
			m_Shader->Bind();
			/* Have to call uniforms after a shader is bound */
			m_Shader->SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);

			GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			GLCall(glPointSize(3));
			GLCall(glDrawArrays(GL_POINTS, 0, leaf_pos.size()));

			for (int m = 0; m < random_ridges.size(); m++)
			{
				m_VertexBuffer3 = std::make_unique<VertexBuffer>(random_ridges[m].data(), random_ridges[m].size() * sizeof(glm::vec2));
				m_VAO->AddBuffer(*m_VertexBuffer3, layout1);
				m_Shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

				GLCall(glDrawArrays(GL_LINE_STRIP, 0, random_ridges[m].size()));
			}

			m_VAO->AddBuffer(*m_VertexBuffer2, layout1);
			m_Shader->SetUniform4f("u_Color", 0.0f, 1.0f, 0.5f, 1.0f);

			GLCall(glDrawArrays(GL_LINES, 0, branch_pos.size()));
		}
		else if (finish == true && height_enable_count == 1)
		{
			HeightGeneration height_generation;
			//glGenFramebuffers(1, frame_buffer);
			//glBindFramebuffer(GL_PIXEL_PACK_BUFFER, *frame_buffer);
			height_map = height_generation.create_base_heights(window_width, window_height);
			//m_VertexBuffer4 = std::make_unique<VertexBuffer>(height_map.data(), height_map.size() * sizeof(float));
			//m_VAO->AddBuffer(*m_VertexBuffer4, layout1);
			//m_Shader->SetUniform4f("u_Color", 1.0f, 0.0f, 0.0f, 1.0f);

			//for (int n = 1; n < window_height - 50; ++n)
			//{
			//	for (int m = 1; m < window_width - 50; ++m)
			//	{
			//		if (m != window_width - 50)
			//		{
			//			std::cout << height_map[n * m] << " ";
			//		}
			//		else
			//		{
			//			std::cout << height_map[n * m] << std::endl;
			//		}
			//	}
			//}

			//GLCall(glPointSize(1));
			//glDrawArrays(GL_POINTS, 0, height_map.size());

			height_enable_count += 1;

			//std::cout << height_map.size() << std::endl;
		}
		else
		{
			glDrawArrays(GL_POINTS, 0, height_map.size());
		}
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