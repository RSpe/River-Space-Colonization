#pragma once

#include "Include.h"

class TerrainRender
{
public:

	std::vector<glm::vec3> generate_vertices(std::vector<std::vector<float>> feature_map, int max_x_point, int max_y_point);
	std::vector<glm::vec2> generate_tex_coords(std::vector<std::vector<float>> feature_map, int max_x_point, int max_y_point);
	std::vector<glm::vec3> generate_normals(std::vector<std::vector<glm::vec3>> vertices, int max_x_point, int max_y_point);
	std::vector<unsigned int> generate_index_buffer(int max_x_point, int max_y_point);

private:

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> tex_coords;
	std::vector<glm::vec3> normals;
	std::vector<std::vector<std::vector<glm::vec3>>> temp_normals;
	std::vector<unsigned int> indices;
};