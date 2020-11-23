#include "TerrainRender.h"

std::vector<glm::vec3> TerrainRender::generate_vertices(std::vector<std::vector<float>> feature_map, int max_x_point, int max_y_point)
{

	for (int i = 0; i < max_y_point; ++i)
	{
		for (int j = 0; j < max_x_point; ++j)
		{
			int index = (i * max_x_point) + j;

			float s = (j / (float)(max_x_point - 1));
			float t = (i / (float)(max_y_point - 1));

			float x_pos = (s * max_x_point) - (max_x_point * 0.5f);
			float y_pos = feature_map[index][1] * 100.0f;
			float z_pos = (t * max_y_point) - (max_y_point * 0.5f);

			vertices.push_back(glm::vec3(x_pos, y_pos, z_pos));
		}
	}

	return vertices;
}

std::vector<glm::vec2> TerrainRender::generate_tex_coords(std::vector<std::vector<float>> feature_map, int max_x_point, int max_y_point)
{
	float tex_u = float(max_y_point) * 0.1f;
	float tex_v = float(max_x_point) * 0.1f;

	for (int i = 0; i < feature_map.size(); ++i)
	{
		int x_pos = i % (max_x_point - 1);
		int z_pos = i / (max_x_point - 1);

		tex_coords.push_back(glm::vec2(tex_u * x_pos, tex_v * z_pos));
	}

	return tex_coords;
}

std::vector<unsigned int> TerrainRender::generate_index_buffer(int max_x_point, int max_y_point)
{
	int primitive_restart = max_x_point * max_y_point;
	for (int y = 0; y < max_y_point; ++y)
	{
		for (int x = 0; x < max_x_point; ++x)
		{
			for (int n = 0; n < 2; ++n)
			{
				int row = y + n;
				int index = row * max_x_point + x;
				indices.push_back(index);
			}
		}
		indices.push_back(primitive_restart);
	}
	
	return indices;
}