#include "TestTreeSpaceColonisation.h"

// TODO: Add root generation class

	/* Building tree trunk */
TestTreeSpaceColonisation::TestTreeSpaceColonisation()
{
	image.setup(window_width, window_height, max_x_point, min_x_point, max_y_point, min_y_point);
	terrain.setup();

	Build();
}

void TestTreeSpaceColonisation::Build()
{
	random_leaves = LeafGeneration::generate_leaves(leaves_to_generate, set_seed, tree_number, max_x_point, min_x_point, max_y_point, min_y_point); // Generate random 2D points as leaves used for unique branch building.
	random_roots = std::vector<glm::vec2>(random_leaves.begin() + leaves_to_generate, random_leaves.end());
	random_leaves.erase(random_leaves.begin() + leaves_to_generate, random_leaves.end());
	//random_ridges = RidgeGeneration::generate_ridges(ridge_number, set_seed, ridge_definition, random_roots); // Ridge number, seed, number of points in ridge (higher  = smoother, greater resolution)

	for (int n = 0; n < ridge_number; ++n)
	{
		for (int m = 0; m < ridge_definition; ++m)
		{
			random_ridges_1d.push_back(random_ridges[n][m]);
		}
	}

	//for (int z = 0; z < random_roots.size(); ++z)
	//{
	//	std::cout << glm::to_string(random_roots[z]) << std::endl;
	//}

	//for (int z = 0; z < random_ridges_1d.size(); ++z)
	//{
	//	std::cout << glm::to_string(random_ridges_1d[z]) << std::endl;
	//}

	for (int i = 0; i < tree_number; i++)
	{
		//std::cout << "--------------Build-------------" << std::endl;
		int root_position = i * 2;

		finish = false;

		//std::cout << glm::to_string(random_roots[i]) << std::endl;

		std::shared_ptr<Branch> root(new Branch(random_roots[i], random_roots[i], glm::vec2(0.0f, 1.0f), 0, 0)); // Create root branch using direction of (0.0f, 1.0f) which is pointing upwards.
		//std::shared_ptr<Branch> root(new Branch(glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, -1.0f), glm::vec2(0.0f, 1.0f)));

		branches.push_back(root); // Add root as the first branch object.

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
				float parent_height = current->get_height();
				float new_height = parent_height + (sqrt(pow((new_position[0] - parent_position[0]), 2) + pow((new_position[1] - parent_position[1]), 2)));
				if (new_height > max_height)
				{
					max_height = new_height;
				}
				std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, parent_direction, new_height, parent_height));
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
					//branches[closest_branch]->set_height(1);
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
					float parent_height = branches[k]->get_height();
					float new_height = parent_height + (sqrt(pow((new_position[0] - parent_position[0]), 2) + pow((new_position[1] - parent_position[1]), 2)));
					//std::cout << parent_height << " " << new_height << std::endl;
					if (new_height > max_height)
					{
						max_height = new_height;
					}

					std::shared_ptr<Branch> next_branch(new Branch(parent_position, new_position, new_direction, new_height, parent_height));

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

void TestTreeSpaceColonisation::Draw(glm::mat4 perspective_proj, glm::mat4 view, glm::mat4 model)
{
	if (image_draw == true)
	{
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		std::vector<glm::vec2> leaf_pos;

		int leaf_storage_length = leaves.size(); // Used to check if there is no more leaves to show.

		int branch_storage_length = branches.size();
		int branch_position_length = branch_combined.size() / 4; // There is double the amount of branch positions stored as we need to store the parent and current point so a line can be drawn between the two.

		//std::cout << check_leaf_change << " " << leaf_storage_length << std::endl;
		if (check_leaf_change != leaf_storage_length)
		{
			check_leaf_change = leaf_storage_length;
			check_branch_change = branch_storage_length;
			no_change_count = 0;
		}

		else if (check_leaf_change == leaf_storage_length)
		{
			if (no_change_count == 5)
			{
				//leaf_pos = {};
				image_draw = false;
				image_write = true;
				leaf_convert = false;
			}
			else
			{
				no_change_count += 1;
			}
		}

		for (int i = 0; i < leaf_storage_length; ++i)
		{
			glm::vec2 pixel_pos_leaf = (leaves[i].get_position());
			//std::cout << pixel_pos_leaf[0] << " " << pixel_pos_leaf[1] << std::endl;
			leaf_pos.push_back(glm::vec2(pixel_pos_leaf[0], pixel_pos_leaf[1]));
		}

		if (image_draw == false)
		{
			for (int j = branch_position_length; j < branch_storage_length; ++j)
			{
				// Used to limit river height so terrain generation size stays within 0 -> 1
				float new_current_height = 0.8 * (branches[j]->get_height() - 0) / (max_height - 0);
				float new_parent_height = 0.8 * (branches[j]->get_parent_height() - 0) / (max_height - 0);
				//float new_current_height = 0.9 * (branches[j]->get_height());
				//float new_parent_height = 0.9 * (branches[j]->get_parent_height());

				// Set position
				glm::vec2 pixel_pos_branch = (branches[j]->get_position());
				glm::vec2 pixel_pos_parent = (branches[j]->get_parent());
				glm::vec4 current_rgb_height = glm::vec4(tree_colour[0], tree_colour[1], tree_colour[2], new_current_height);
				glm::vec4 parent_rgb_height = glm::vec4(tree_colour[0], tree_colour[1], tree_colour[2], new_parent_height);
				branch_combined.push_back(glm::vec4(pixel_pos_branch[0], pixel_pos_branch[1], 0.0f, 1.0f));
				branch_combined.push_back(current_rgb_height);
				branch_combined.push_back(glm::vec4(pixel_pos_parent[0], pixel_pos_parent[1], 0.0f, 1.0f));
				branch_combined.push_back(parent_rgb_height);
			}
		}

		image.render_leaves(leaf_pos, leaf_convert, leaf_storage_length);
		//image_draw.render_ridges(random_ridges, orthographic_proj);
		//image.render_leaves(leaf_pos, orthographic_proj);
		image.render_branches(branch_combined);
	}

	else if (image_write == true)
	{
		height_generation.generate_heights(window_width, window_height, max_x_point, max_y_point, tree_colour, ridge_colour, tree_number);
		height_generation.write_pgm_height_map(max_x_point, max_y_point);
		
		feature_map = height_generation.get_feature_map();
		//height_generation.show_feature_map(feature_map, max_x_point);
		
		image_write = false;
		//terrain_render = true;
	}

	else if (terrain_render == true)
	{
		vertices = terrain_build.generate_vertices(feature_map, max_x_point, max_y_point);

		//terrain_build.generate_tex_coords(feature_map, max_x_point, max_y_point);
		//normals = terrain_build.generate_normals(max_x_point, max_y_point);
		index_buffer = terrain_build.generate_index_buffer(max_x_point, max_y_point);
		//std::cout << index_buffer.size() << std::endl;
		//for (int i = 0; i < index_buffer.size(); ++i)
		//{
		//	std::cout << index_buffer[i] << std::endl;
		//}

		for (int i = 0; i < vertices.size(); ++i)
		{
			height_combined.push_back(vertices[i]);
			//height_combined.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			//height_combined.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		}

		terrain_render = false;
		terrain_draw = true;
	}

	else if (terrain_draw == true)
	{
		GLCall(glClearColor(1.0f, 1.0f, 1.0f, 1.0f));
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//terrain.render_leaves(leaf_pos, perspective_proj, view, model);
		//terrain.render_ridges(random_ridges, perspective_proj, view, model);
		//terrain.render_branches(branch_combined, perspective_proj, view, model);
		terrain.render_terrain(height_combined, index_buffer, perspective_proj, view, model);
	}
}

void TestTreeSpaceColonisation::OnUpdate(float deltaTime)
{
		
}

void TestTreeSpaceColonisation::OnRender(glm::mat4 perspective_proj, glm::mat4 view, glm::mat4 model)
{
	Grow();
	Draw(perspective_proj, view, model);
}

void TestTreeSpaceColonisation::OnImGuiRender()
{

}