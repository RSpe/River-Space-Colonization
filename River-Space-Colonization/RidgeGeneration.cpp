#include <cmath>

#include "RidgeGeneration.h"

const std::vector<std::vector<glm::vec2>> RidgeGeneration::generate_ridges(int num_ridges, double seed, int point_resolution, std::vector<glm::vec2> random_roots)
{
	float alpha = 0.5;
	float tension = 0;
	
	std::vector<std::vector<glm::vec2>> random_ridges;

	std::vector<glm::vec2> set_points;

	std::vector<float> x_vector;
	std::vector<float> y_vector;

	for (int j = 0; j < random_roots.size(); ++j)
	{
		x_vector.push_back(random_roots[j][0]);
		y_vector.push_back(random_roots[j][1]);
	}

	float min_x = *min_element(x_vector.begin(), x_vector.end());
	float max_x = *max_element(x_vector.begin(), x_vector.end());
	float min_y = *min_element(y_vector.begin(), y_vector.end());
	float max_y = *max_element(y_vector.begin(), y_vector.end());

	std::mt19937::result_type set_seed = seed;
	std::mt19937 gen(set_seed);
	std::uniform_real_distribution<float> x_pos(min_x, max_x);
	std::uniform_real_distribution<float> y_pos(min_y, max_y);

	for (int i = 0; i < num_ridges; i++)
	{
		std::vector<glm::vec2> current_ridge;

		glm::vec2 p0 = glm::vec2(x_pos(gen), y_pos(gen));
		glm::vec2 p1 = glm::vec2(x_pos(gen), y_pos(gen));
		glm::vec2 p2 = glm::vec2(x_pos(gen), y_pos(gen));
		glm::vec2 p3 = glm::vec2(x_pos(gen), y_pos(gen));

		float t01 = pow(distance(p0, p1), alpha);
		float t12 = pow(distance(p1, p2), alpha);
		float t23 = pow(distance(p2, p3), alpha);

		glm::vec2 m1 = (1.0f - tension) * (p2 - p1 + t12 * ((p1 - p0) / t01 - (p2 - p0) / (t01 + t12)));
		glm::vec2 m2 = (1.0f - tension) * (p2 - p1 + t12 * ((p3 - p2) / t23 - (p3 - p1) / (t12 + t23)));

		glm::vec2 a = 2.0f * (p1 - p2) + m1 + m2;
		glm::vec2 b = -3.0f * (p1 - p2) - m1 - m1 - m2;
		glm::vec2 c = m1;
		glm::vec2 d = p1;

		for (float j = 0; j < point_resolution; ++j)
		{
			float mult = j * (1.0f / point_resolution);
			glm::vec2 final_point = (a * mult * mult * mult) + (b * mult * mult) + (c * mult) + d;
			current_ridge.push_back(final_point);
		}
		random_ridges.push_back(current_ridge);
	}

	return random_ridges;
}

double RidgeGeneration::distance(glm::vec2 point1, glm::vec2 point2)
{
	float under_sqrt = pow(point2[0] - point1[0], 2) + pow(point2[1] - point1[1], 2);

	return under_sqrt;
}