#include "TerrainRender.h"

std::vector<glm::vec3> TerrainRender::generate_vertices(std::vector<std::vector<float>> feature_map, int max_x_point, int max_y_point)
{

	for (int i = 0; i < feature_map.size(); ++i)
	{
		int x_pos = i % (max_x_point - 1);
		int z_pos = i / (max_x_point - 1);

		vertices.push_back(glm::vec3(x_pos, feature_map[i][1], z_pos));
	}

	return vertices;
}

std::vector<std::vector<glm::vec2>> TerrainRender::generate_tex_coords(std::vector<std::vector<float>> feature_map, int max_x_point, int max_y_point)
{
	tex_coords = std::vector<std::vector<glm::vec2>>(max_x_point, std::vector<glm::vec2>(max_y_point));

	float tex_u = float(max_y_point) * 0.1f;
	float tex_v = float(max_x_point) * 0.1f;

	for (int y = 0; y < max_y_point; ++y)
	{
		for (int x = 0; x < max_x_point; ++x)
		{
			int index = (y * max_x_point) + x;

			float row = x / float(max_x_point - 1);
			float column = y / float(max_y_point - 1);

			tex_coords[y][x] = glm::vec2(tex_u * row, tex_v * column);
		}
	}

	return tex_coords;
}

//std::vector<glm::vec3> TerrainRender::generate_normals(int max_x_point, int max_y_point)
//{
//	normals = std::vector<std::vector<glm::vec3>>(max_y_point, std::vector<glm::vec3>(max_x_point));
//	temp_normals = std::vector<std::vector<std::vector<glm::vec3>>>(2, std::vector<std::vector<glm::vec3>>(max_y_point, std::vector<glm::vec3>(max_x_point)));
//
//	for (int y = 0; y < max_y_point - 1; ++y)
//	{
//		for (int x = 0; x < max_x_point - 1; ++x)
//		{
//			glm::vec3 vertex_a = vertices[y][x];
//			glm::vec3 vertex_b = vertices[y][x + 1];
//			glm::vec3 vertex_c = vertices[y + 1][x + 1];
//			glm::vec3 vertex_d = vertices[y + 1][x];
//
//			glm::vec3 triange_a_normal = glm::cross(vertex_a - vertex_d, vertex_d - vertex_c);
//			glm::vec3 triange_b_normal = glm::cross(vertex_c - vertex_b, vertex_b - vertex_a);
//
//			temp_normals[0][y][x] = glm::normalize(triange_a_normal);
//			temp_normals[1][y][x] = glm::normalize(triange_b_normal);
//		}
//	}
//
//	for (int i = 0; i < max_y_point; ++i)
//	{
//		for (int j = 0; j < max_x_point; ++j)
//		{
//			int first_row = i == 0;
//			int first_column = j == 0;
//			int last_row = i == max_y_point - 1;
//			int last_column = j == max_x_point - 1;
//
//			auto final_normal = glm::vec3(0.0f, 0.0f, 0.0f);
//
//			// Look for triangle to the upper-left
//			if (!first_row && !first_column) {
//				final_normal += temp_normals[0][i - 1][j - 1];
//			}
//
//			// Look for triangles to the upper-right
//			if (!first_row && !last_column) {
//				for (int k = 0; k < 2; k++) {
//					final_normal += temp_normals[k][i - 1][j];
//				}
//			}
//
//			// Look for triangle to the bottom-right
//			if (!last_row && !last_column) {
//				final_normal += temp_normals[0][i][j];
//			}
//
//			// Look for triangles to the bottom-right
//			if (!last_row && !first_column) {
//				for (int k = 0; k < 2; k++) {
//					final_normal += temp_normals[k][i][j - 1];
//				}
//			}
//
//			normals[i][j] = glm::normalize(final_normal);
//		}
//	}
//
//	return normals;
//}

std::vector<unsigned int> TerrainRender::generate_index_buffer(int max_x_point, int max_y_point)
{
	//int index = 0;
	//for (int i = 0; i < vertices.size(); ++i)
	//{
	//	if (index == 0)
	//	{
	//		indices.push_back(i);
	//		indices.push_back(i + max_x_point);
	//		indices.push_back(i + 1);
	//		indices.push_back(i + 1);
	//		indices.push_back(i + max_x_point);
	//		indices.push_back(i + 1 + max_x_point);
	//		index += 1;
	//	}

	//	else if ((i % max_x_point) != 0)
	//	{
	//		indices.push_back(i);
	//		indices.push_back(i + max_x_point);
	//		indices.push_back(i + 1);
	//		indices.push_back(i + 1);
	//		indices.push_back(i + max_x_point);
	//		indices.push_back(i + 1 + max_x_point);
	//	}
	//}
	for (int y = 0; y < max_y_point; ++y)
	{
		for (int x = 0; x < max_x_point; ++x)
		{
			int index = (y * max_x_point) + x;
			indices.push_back(index);
			indices.push_back(index + 1);
			indices.push_back(index + max_x_point);

			indices.push_back(index + 1);
			indices.push_back(index + max_x_point + 1);
			indices.push_back(index + max_x_point);
		}
	}
	
	//for (int i = 0; i < indices.size(); ++i)
	//{
	//	std::cout << indices[i] << std::endl;
	//}
	return indices;
}