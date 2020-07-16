#include <cmath>

#include "RidgeGeneration.h"

const std::vector<std::vector<glm::vec2>> RidgeGeneration::generate_ridges(int num_ridges, double seed, int point_resolution, std::vector<glm::vec2> random_roots)
{
	srand(seed);

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

	//for (int i = 0; i < num_ridges; i++)
	//{
	//	std::vector<glm::vec2> current_ridge;

	//	glm::vec2 p0 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));
	//	glm::vec2 p1 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));
	//	glm::vec2 p2 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));
	//	glm::vec2 p3 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));

	//	float t0 = 0;
	//	float t1 = pow(distance(p0, p1), alpha) + t0;
	//	float t2 = pow(distance(p1, p2), alpha) + t1;
	//	float t3 = pow(distance(p2, p3), alpha) + t2;

	//	for (float j = t1; j < t2; j += ((t2 - t1) / point_resolution))
	//	{
	//		glm::vec2 a1 = ((t1 - j) / (t1 - t0) * p0) + ((j - t0) / (t1 - t0) * p1);
	//		glm::vec2 a2 = ((t2 - j) / (t2 - t1) * p1) + ((j - t1) / (t2 - t1) * p2);
	//		glm::vec2 a3 = ((t3 - j) / (t3 - t2) * p2) + ((j - t2) / (t3 - t2) * p3);

	//		glm::vec2 b1 = ((t2 - j) / (t2 - t0) * a1) + ((j - t0) / (t2 - t0) * a2);
	//		glm::vec2 b2 = ((t3 - j) / (t3 - t1) * a2) + ((j - t1) / (t3 - t1) * a3);

	//		glm::vec2 c1 = ((t2 - j) / (t2 - t1) * b1) + ((j - t1) / (t2 - t1) * b2);

	//		current_ridge.push_back(c1);
	//	}
	//	random_ridges.push_back(current_ridge);
	//}

	for (int i = 0; i < num_ridges; i++)
	{
		std::vector<glm::vec2> current_ridge;

		glm::vec2 p0 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));
		glm::vec2 p1 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));
		glm::vec2 p2 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));
		glm::vec2 p3 = glm::vec2((min_x + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_x - min_x)))), (min_y + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max_y - min_y)))));

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
			//std::cout << glm::to_string(final_point) << std::endl;
			current_ridge.push_back(final_point);
		}
		random_ridges.push_back(current_ridge);
	}

	return random_ridges;
}

//double RidgeGeneration::distance(glm::vec2 point1, glm::vec2 point2)
//{
//	float under_sqrt = pow(point2[0] - point1[0], 2) + pow(point2[1] - point1[1], 2);
//	float dist = pow(under_sqrt, 0.5);
//
//	return dist;
//}

double RidgeGeneration::distance(glm::vec2 point1, glm::vec2 point2)
{
	float under_sqrt = pow(point2[0] - point1[0], 2) + pow(point2[1] - point1[1], 2);

	return under_sqrt;
}